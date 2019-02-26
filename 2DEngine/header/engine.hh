#ifndef __ENGINE_HH__
#define __ENGINE_HH__

#include<thread>
#include<string>
#include<exception>
#include<dlfcn.h>

#include"physics.hh"
#include"graphics.hh"
#include"image.hh"
#include"entity.hh"
#include"bufferedIO.hh"
#include"shared_types.hh"
#include"resourcemanager.hh"

class unrecognizedKeywordException : public std::out_of_range{
private:
  std::string mMesg;

public:
  unrecognizedKeywordException( const std::string& word, const std::string& file ):
    mMesg( "Unrecognized keyword " + word + " in file " + file + "." ){
  }

  virtual const char* what() const noexcept{
    return mMesg.c_str();
  }
};

class badLibFuncReferenceException : public std::exception{
private:
  std::string mMesg;

public:
  badLibFuncReferenceException( const std::string& symName ):
    mMesg( "Symbol not found: \t" + symName + "." ){
  }

  virtual const char* what() const noexcept{
    return mMesg.c_str();
  }
};

class libraryNotFoundException : public std::exception{
private:
  std::string mMesg;

public:
  libraryNotFoundException( const std::string& name ):
    mMesg( "Library not found " + name + "." ){
  }

  virtual const char* what() const noexcept{
    return mMesg.c_str();
  }
};

class engine{
public:
  typedef void* handle_type;
  typedef entity<image> ent_type;
  typedef std::function<void( std::string, std::string,
                              resourcemanager<image>&,
                              std::map<std::string, renderable>& )>
                              configCallback;

private:
  std::map<std::string, configCallback> mConfigCallbacks;
  std::map<std::string, renderable> mRenderables;
  std::vector<handle_type> mHandles;
  resourcemanager<image> mImages;

  physics mPsx;
  graphics mGfx;
  IO mio;

public:
  engine() = default;
  engine( const std::string& configName ){
    loadConfig( configName );
  }
  virtual ~engine(){
    for( auto lib : mHandles ){
      dlclose( lib );
    }
  }

  void registerConfigCallback( const std::string& name, configCallback ccb ){
    mConfigCallbacks[name] = ccb;
  }

  void loadConfig( const std::string& configName ){
    handle_type hndl;
    std::fstream config( configName );
    std::string line;

    while( std::getline( config, line ) ){
      if( line[0] == '#' || line.size() == 0 ){
        continue;
      }
      std::stringstream ss( line );
      std::string word;
      std::string name;

      ss >> word;
      ss >> name;

      if( word == "img" ){
        std::string file;

        ss >> file;
        mImages.acquire( file, name );
      } else if( word == "tri" ){
        std::array<coord, 3> arr;

        for( auto cor : arr ){
          int x;
          int y;

          ss >> x;
          ss >> y;

          cor.first = x;
          cor.second = y;
        }

        tri tr( coord( arr[0].first, arr[0].second ), coord( arr[0].first, arr[0].second ), coord( arr[0].first, arr[0].second ) );
        mRenderables[name] = tr;
      } else if( word == "ent" ){
        std::string img;
        ent_type ent;

        ss >> img;
        ent.addElement( mImages[img] );
        mEntities[name] = ent;
      } else if( word == "stbb" ){
        std::array<coord, 2> arr;

        for( auto cor : arr ){
          int x;
          int y;

          ss >> x;
          ss >> y;

          cor.first = x;
          cor.second = y;
        }
        mEntities[name].getHitBox() = std::pair<coord, coord>( arr[0], arr[1] );
      } else if( word == "stp" ){
        double x;
        double y;

        ss >> x;
        ss >> y;
        mEntities[name].getPosition() = vec2( x, y );
      } else if( word == "stv" ){
        double x;
        double y;

        ss >> x;
        ss >> y;
        mEntities[name].getVelocity() = vec2( x, y );
      } else if( word == "sta" ){
        double x;
        double y;

        ss >> x;
        ss >> y;
        mEntities[name].getAcceleration() = vec2( x, y );
      } else if( word == "stm" ){
        double val;

        ss >> val;
        mEntities[name].getMass() = val;
      } else if( word == "phys" ){
        std::stringstream ss( line );
        std::string alias;

        ss >> alias;
        ss >> alias;
        ss >> alias;

        mPsx.addEntity( alias, mEntities[name] );
      } else if( word == "lib" ){
        hndl = dlopen( name.data(), RTLD_LAZY );

        if( !hndl ){
          throw libraryNotFoundException( name );
        }
        mHandles.push_back( hndl );
      } else if( word == "cbk" ){
        std::string fn;
        char key;
        char* error;

        ss >> key;
        ss >> fn;
        auto tmp = ( void( * )( ent_type& ) )dlsym( hndl, fn.data() );
        if( ( error = dlerror() ) != 0 ){
          throw badLibFuncReferenceException( fn );
        }
        auto callback = std::bind( tmp, std::ref( mEntities[name] ) );
        mio.registerCallback( key, callback );
      } else {
        try{
          mConfigCallbacks.at( word )( name, line, mImages, mRenderables );
        } catch( std::out_of_range& e ){
          throw unrecognizedKeywordException( word, configName );
        }
      }
    }
  }

  template<typename OSTREAM>
  void tick( std::clock_t diff, OSTREAM& os ){
    mPsx.handleCollisions();
    mPsx.tick( diff );
    mGfx.tick( os );
  }

  template<typename OSTREAM>
  void run( OSTREAM& os){
    std::thread thd( &IO::killThread, &mio );
    std::clock_t last = clock();

    while( !mio.shouldQuit() ){
      std::clock_t now = clock();
      std::clock_t diff = now - last;
      last = now;
      tick( diff, os );
    }
  }
};

#endif


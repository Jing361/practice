#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include<map>
#include<string>
#include<memory>

#include<screen.hh>
#include<shared_types.hh>

class graphics;

class renderable{
private:
  class interface{
  public:
    virtual
    void
    draw( graphics& ) const = 0;
  };

  template<typename T>
  class wrapper : public interface{
  private:
    T mUnder;

  public:
    wrapper( T t )
      : mUnder( t ){
    }

    void
    draw( graphics& gfx ) const{
      mUnder.draw( gfx );
    }
  };

  std::shared_ptr<interface> mIface;

public:
  renderable() = default;

  renderable( const renderable& ) = default;

  renderable( renderable&& ) = default;

  template<typename T>
  renderable( T t )
    : mIface( std::make_shared<wrapper<T> >( t ) ){
  }

  ~renderable() = default;

  renderable&
  operator=( const renderable& ) = default;

  renderable&
  operator=( renderable&& ) = default;

  template<typename T>
  renderable&
  operator=( T t ){
    mIface = std::make_shared<wrapper<T> >( t );

    return *this;
  }

  void
  draw( graphics& gfx ) const;
};

/*!
 * @todo
 * The rendenring space should be allowed to be larger than the screen space.
 * So the rendering space needs some way to be translated to screen space.
 */
class graphics{
private:
  screen mScreen;
  std::map<std::string, renderable> mParts;

  void
  drawFlatTopTri( coord v1, coord v2, coord v3, char c );

  void
  drawFlatBotTri( coord v1, coord v2, coord v3, char c );

  void
  drawTri( coord v1, coord v2, coord v3, coord loc, char c );

  void
  drawFlatLine( int y, int x1, int x2, char c );

  void
  drawLine( coord v1, coord v2, char c );

public:
  graphics( unsigned int X, unsigned int Y );

  ~graphics() = default;

  void
  clearBuffer();

  template<typename OSTREAM>
  OSTREAM&
  show( OSTREAM& os ){
    for( auto pr : mParts ){
      pr.second.draw( *this );
    }

    mScreen.display( os );

    return os;
  }

  void
  add( const std::string& name, const renderable& rndrbl );

  void
  draw( simple_tri t, coord cor, char c );

  void
  draw( simple_line l, char c );

  void
  draw( const renderable& rndrbl );

  void
  draw( coord cr, char c );
};

class tri{
private:
  simple_tri mCoords;
  char mVal;

public:
  tri( simple_tri stri, char c = '+' );

  tri( coord c1, coord c2, coord c3, char c = '+' );

  void draw( graphics& gfx ) const;
};

class line{
private:
  simple_line mLine;
  char mVal;

public:
  line( simple_line sl, char c = '+' );

  line( coord c1, coord c2, char c = '+' );

  void
  draw( graphics& gfx ) const;
};

#endif


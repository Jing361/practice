#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include<map>
#include<string>
#include<memory>

#include<screen.hh>
#include<shared_types.hh>

class graphics;

class gEntity{
private:
  class interface{
  public:
    virtual
    void
    draw( graphics&, const vec2_position& ) const = 0;
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
    draw( graphics& gfx, const vec2_position& pos ) const{
      mUnder.draw( gfx, pos );
    }
  };

  std::shared_ptr<interface> mIface;

public:
  gEntity() = default;

  gEntity( const gEntity& ) = default;

  gEntity( gEntity&& ) = default;

  template<typename T>
  gEntity( T t )
    : mIface( std::make_shared<wrapper<T> >( t ) ){
  }

  ~gEntity() = default;

  gEntity&
  operator=( const gEntity& ) = default;

  gEntity&
  operator=( gEntity&& ) = default;

  template<typename T>
  gEntity&
  operator=( T t ){
    mIface = std::make_shared<wrapper<T> >( t );

    return *this;
  }

  void
  draw( graphics& gfx, const vec2_position& pos ) const;
};

/*!
 * @todo
 * The rendenring space should be allowed to be larger than the screen space.
 * So the rendering space needs some way to be translated to screen space.
 */
class graphics{
private:
  screen mScreen;
  std::map<std::string, gEntity> mParts;

  void
  drawFlatTopTri( coord v1, coord v2, coord v3, char c );

  void
  drawFlatBotTri( coord v1, coord v2, coord v3, char c );

  void
  drawTri( coord v1, coord v2, coord v3, char c );

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
      pr.second.draw( *this, {0, 0} );
    }

    mScreen.display( os );

    return os;
  }

  void
  addEntity( const std::string& name, const gEntity& ent );

  void
  draw( simple_tri t, char c, const vec2_position& loc = {0, 0} );

  void
  draw( simple_line l, char c, const vec2_position& loc = {0, 0} );

  void
  draw( const gEntity& ent, const vec2_position& loc = {0, 0} );

  void
  draw( coord cr, char c, const vec2_position& loc = {0, 0} );
};

class tri{
private:
  simple_tri mCoords;
  char mVal;

public:
  tri( simple_tri stri, char c = '+' );

  tri( coord c1, coord c2, coord c3, char c = '+' );

  void draw( graphics&, const vec2_position& ) const;
};

class line{
private:
  simple_line mLine;
  char mVal;

public:
  line( simple_line sl, char c = '+' );

  line( coord c1, coord c2, char c = '+' );

  void
  draw( graphics&, const vec2_position& ) const;
};

class polygon{
private:
  std::vector<coord> mPoints;
  char mVal;

public:
  template<typename inputIter>
  polygon( inputIter first, inputIter last, char c )
    : mPoints( first, last )
    , mVal( c ){
  }

  polygon( const std::vector<coord>& vec, char c );

  void
  draw( graphics& gfx, const vec2_position& pos ) const;
};

#endif


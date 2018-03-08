#include<algorithm>

#include<graphics.hh>

using namespace std;

void
gEntity::draw( graphics& gfx ) const{
  mIface->draw( gfx );
}

void
graphics::drawFlatTopTri( coord v1, coord v2, coord v3, char c ){
  vector<coord> vec{v1, v2, v3};

  auto lowIt = min_element( vec.begin(), vec.end(),
    []( coord a, coord b )->bool{
      return a[1] < b[1];
    }
  );

  coord low = *lowIt;
  vec.erase( lowIt );

  double slope0 = ( double )( vec[0][0] - low[0] )
                / ( double )( vec[0][1] - low[1] );
  double slope1 = ( double )( vec[1][0] - low[0] )
                / ( double )( vec[1][1] - low[1] );
  double x0 = low[0];
  double x1 = low[0];

  for( int i = low[1]; i <= vec[0][1]; ++i ){
    drawFlatLine( i, x0, x1, c );
    x0 += slope0;
    x1 += slope1;
  }
}

void
graphics::drawFlatBotTri( coord v1, coord v2, coord v3, char c ){
  vector<coord> vec{v1, v2, v3};

  auto hiIt = max_element( vec.begin(), vec.end(),
    []( coord a, coord b )->bool{
      return a[1] < b[1];
    }
  );

  coord hi = *hiIt;
  vec.erase( hiIt );

  double slope0 = ( double )( vec[0][0] - hi[0] )
                / ( double )( vec[0][1] - hi[1] );
  double slope1 = ( double )( vec[1][0] - hi[0] )
                / ( double )( vec[1][1] - hi[1] );
  double x0 = hi[0];
  double x1 = hi[0];

  for( int i = hi[1]; i >= vec[0][1]; --i ){
    drawFlatLine( i, x0, x1, c );
    x0 -= slope0;
    x1 -= slope1;
  }
}

void
graphics::drawTri( coord v1, coord v2, coord v3, coord loc, char c ){
  vector<coord> vec{ v1, v2, v3 };
  for( coord& it : vec ){
    it[0] += loc[0];
    it[1] += loc[1];
  }
  sort( vec.begin(), vec.end(), [](coord a, coord b ){
    return a[1] < b[1];
  });

  if( vec[0][1] == vec[1][1] ){
    drawFlatBotTri( v1, v2, v3, c );
  } else if( vec[1][1] == vec[2][1] ){
    drawFlatTopTri( v1, v2, v3, c );
  } else {
    coord v4 = coord( {( ( vec[1][1] - vec[0][1] )
                     / ( ( vec[0][1] - vec[2][1] )
                       / ( vec[0][0] - vec[2][0] ) ) )
                         + vec[0][0], vec[1][1]} );

    drawFlatTopTri( vec[0], vec[1], v4, c );
    drawFlatBotTri( vec[1], v4, vec[2], c );
  }
}

void
graphics::drawFlatLine( int y, int x1, int x2, char c ){
  int start = min( x1, x2 );
  int end = max( x1, x2 );

  for( ; start <= end; ++start ){
    mScreen.draw( start, y, c );
  }
}

void
graphics::drawLine( coord v1, coord v2, char c ){
  int start = min( v1[0], v2[0] );
  int end = max( v1[0], v2[0] );
  double slope = double( v1[1] - v2[1] )
               / double( v1[0] - v2[0] );
  int offset = v1[1] - ( slope * v1[0] );

  for( ; start <= end; ++start ){
    mScreen.draw( start, ( slope * start ) + offset, c );
  }
}

graphics::graphics( unsigned int X, unsigned int Y )
  : mScreen( X, Y ){
}

void
graphics::clearBuffer(){
  mScreen.clear();
}

void
graphics::addEntity( const string& name, const gEntity& rndrbl ){
  mParts.emplace( name, rndrbl );
}

void
graphics::draw( simple_tri t, coord cor, char c ){
  drawTri( get<0>( t ), get<1>( t ), get<2>( t ), cor, c );
}

void
graphics::draw( simple_line l, char c ){
  drawLine( get<0>( l ), get<1>( l ), c );
}

void
graphics::draw( const gEntity& rndrbl ){
  rndrbl.draw( *this );
}

void
graphics::draw( coord cr, char c ){
  mScreen.draw( get<0>( cr ), get<1>( cr ), c );
}

/*******
 * tri *
 *******/

tri::tri( simple_tri stri, char c )
  : mCoords( stri )
  , mVal( c ){
}

tri::tri( coord c1, coord c2, coord c3, char c )
  : tri( {c1, c2, c3}, c ){
}

void
tri::draw( graphics& gfx ) const{
  gfx.draw( mCoords, {0, 0}, mVal );
}

/********
 * line *
 ********/

line::line( simple_line sl, char c )
  : mLine( sl )
  , mVal( c ){
}

line::line( coord c1, coord c2, char c )
  : line( {c1, c2}, c ){
}

void
line::draw( graphics& gfx ) const{
  gfx.draw( mLine, mVal );
}

/***********
 * polygon *
 ***********/

polygon::polygon( const std::vector<coord>& vec, char c )
  : mPoints( vec )
  , mVal( c ){
}

/*! @todo make poly's fillable */
void
polygon::draw( graphics& gfx ) const{
  vector<coord> corners( mPoints );
  corners.push_back( mPoints[0] );

  auto one = corners.begin();
  for( auto two = one + 1; two != corners.end(); ++one, ++two ){
    gfx.draw( {*one, *two}, mVal );
  }
}


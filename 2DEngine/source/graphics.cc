#include<graphics.hh>

void
graphics::drawFlatTopTri( coord v1, coord v2, coord v3, char c ){
  std::vector<coord> vec{v1, v2, v3};

  auto lowIt = std::min_element( vec.begin(), vec.end(),
    []( coord a, coord b )->bool{
      return a.second < b.second;
    }
  );

  coord low = *lowIt;
  vec.erase( lowIt );

  double liSlope = ( double )( vec[0].first  - low.first )
                 / ( double )( vec[0].second - low.second );
  double riSlope = ( double )( vec[1].first  - low.first )
                 / ( double )( vec[1].second - low.second );
  double xr = low.first;
  double xl = low.first;

  for( unsigned int i = low.second; i < vec[0].second; ++i ){
    drawFlatLine( i, xl, xr, c );
    xl += liSlope;
    xr += riSlope;
  }
}

void
graphics::drawFlatBotTri( coord v1, coord v2, coord v3, char c ){
  std::vector<coord> vec{v1, v2, v3};

  auto hiIt = std::max_element( vec.begin(), vec.end(),
    []( coord a, coord b )->bool{
      return a.second < b.second;
    }
  );

  coord hi = *hiIt;
  vec.erase( hiIt );

  double liSlope = ( double )( vec[0].first  - hi.first )
                 / ( double )( vec[0].second - hi.second );
  double riSlope = ( double )( vec[1].first  - hi.first )
                 / ( double )( vec[1].second - hi.second );
  double xr = hi.first;
  double xl = hi.first;

  for( unsigned int i = hi.second; i > vec[0].second - 1; --i ){
    drawFlatLine( i, xl, xr, c );
    xl -= liSlope;
    xr -= riSlope;
  }
}

void
graphics::drawFlatLine( int y, int x1, int x2, char c ){
  int start = std::min( x1, x2 );
  int end = std::max( x1, x2 );

  for( ; start <= end; ++start ){
    mScreen.draw( y, start, c );
  }
}

void
graphics::drawTri( coord v1, coord v2, coord v3, coord loc, char c ){
  std::vector<coord> vec{ v1, v2, v3 };
  for( coord& it:vec ){
    it.first += loc.first;
    it.second += loc.second;
  }
  std::sort( vec.begin(), vec.end(), [](coord a, coord b ){
    return a.second < b.second;
  });

  if( vec[1].second == vec[2].second ){
    drawFlatBotTri( v1, v2, v3, c );
  } else if( vec[0].second == vec[1].second ){
    drawFlatTopTri( v1, v2, v3, c );
  } else {
    coord v4 = coord( ( ( vec[1].second - vec[0].second ) / 
                      ( ( vec[0].second - vec[2].second ) / 
                        ( vec[0].first  - vec[2].first ) ) ) + 
                          vec[0].first, vec[1].second );

    drawFlatTopTri( vec[0], vec[1], v4, c );
    drawFlatBotTri( vec[1], v4, vec[2], c );
  }
}

void
graphics::drawLine( coord v1, coord v2, char c ){
  int start = std::min( v1.first, v2.first );
  int end = std::max( v1.first, v2.first );
  double slope = ( v2.second - v1.second ) / ( v2.first - v1.first );
  int offset = v1.second - ( slope * v1.first );

  for( ; start <= end; ++start ){
    mScreen.draw( slope * start + offset, start, c );
  }
}

graphics::graphics( unsigned int X, unsigned int Y )
  : mScreen( X, Y ){
}

void
graphics::add( const std::string& name, const renderable& rndrbl ){
  mParts.emplace( name, rndrbl );
}

void
graphics::draw( tri t, coord cor, char c ){
  drawTri( std::get<0>( t ), std::get<1>( t ), std::get<2>( t ), cor, c );
}

void
graphics::draw( line l, char c ){
  drawLine( std::get<0>( l ), std::get<1>( l ), c );
}


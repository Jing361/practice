#include<iostream>
#include<vector>
#include<array>
#include<random>
#include<cmath>
#include<utility>

using namespace std;

enum RESOURCE{
  RESOURCE_MIN = 0,
  RESOURCE_NONE = 0,
  RESOURCE_MAX,
};

enum TERRAIN{
  TERRAIN_MIN = 0,
  TERRAIN_FLAT= 0,
  TERRAIN_HILLY,
  TERRAIN_MAX,
};

enum WILDLIFE{
  WILDLIFE_MIN = 0,
  WILDLIFE_NONE = 0,
  WILDLIFE_SQUIRRELS,
  WILDLIFE_DEER,
  WILDLIFE_MAX,
};

class gridSquare{
public:
  pair<double, double> mGradient;
  TERRAIN mTerrain;
  vector<RESOURCE> mResources;
  vector<WILDLIFE> mWildlife;
};

#define MAP_SIZE 30
#define MAX_RESOURCE_COUNT 3
#define MAX_WILDLIFE_COUNT 3

int main( int argc, char** argv ){
  array<array<gridSquare, MAP_SIZE>, MAP_SIZE> map;
  vector<pair<int, int> > townLocations; 

  random_device rd;
  mt19937 rate( rd() );
  normal_distribution<> gradientGene( 0, 4 );
  uniform_int_distribution<> resourceGene( RESOURCE_MIN, RESOURCE_MAX - 1 );
  uniform_int_distribution<> terrainGene( TERRAIN_MIN, TERRAIN_MAX - 1 );
  uniform_int_distribution<> wildlifeGene( WILDLIFE_MIN, WILDLIFE_MAX - 1 );
  uniform_int_distribution<> maxResourceGene( 0, MAX_RESOURCE_COUNT );
  uniform_int_distribution<> maxWildlifeGene( 0, MAX_WILDLIFE_COUNT );

  unsigned int x = 0;
  unsigned int y = 0;
  for( auto& it : map ){
    for( auto& sq : it ){
      unsigned int maxResources = maxResourceGene( rate );
      unsigned int maxWildlife = maxWildlifeGene( rate );

      sq.mGradient.first = gradientGene( rate );
      sq.mGradient.second = gradientGene( rate );

      sq.mTerrain = ( TERRAIN )terrainGene( rate );
      for( unsigned int i = 0; i < maxResources; ++i ){
        sq.mResources.push_back( ( RESOURCE )terrainGene( rate ) );
      }
      for( unsigned int i = 0; i < maxWildlife; ++i ){
        sq.mWildlife.push_back( ( WILDLIFE )wildlifeGene( rate ) );
      }

      if( round( sq.mGradient.first ) == 0 && round( sq.mGradient.second ) == 0 ){
        townLocations.emplace_back( x, y );
      }
      ++y;
    }

    ++x;
    y = 0;
  }

  cout << "valid town locations" << '\n';
  for( auto it : townLocations ){
    cout << it.first << ',' << it.second << '\n';
  }
  cout << flush;

  return 0;
}


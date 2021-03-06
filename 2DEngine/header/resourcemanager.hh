#ifndef __RESOURCE_MANAGER_HH__
#define __RESOURCE_MANAGER_HH__

#include<string>
#include<map>
#include<fstream>
#include<functional>
#include<utility>

template<typename RESOURCE, typename REFERENCE = std::string>
class resourcemanager{
public:
  using res_type = RESOURCE;
  using ref_type = REFERENCE;
  using processCallback = std::function<res_type( std::fstream&& )>;

private:
  std::map<ref_type, res_type> mResources;
  processCallback resourceCallback;

public:
  resourcemanager( processCallback callback =
    []( std::fstream&& file )->res_type{
      return res_type( std::move( file ) );
    } ):
    resourceCallback( callback ){
  }

  void acquire( const std::string& fileName, const ref_type& resourceName ){
    mResources[resourceName] = resourceCallback( std::fstream( fileName ) );
  }

  res_type& retrieve( const ref_type& resourceName ){
    return mResources.at( resourceName );
  }

  res_type& operator[]( const ref_type& resourceName ){
    return mResources.at( resourceName );
  }

  const res_type& retrieve( const ref_type& resourceName ) const{
    return mResources.at( resourceName );
  }

  const res_type& operator[]( const ref_type& resourceName ) const{
    return mResources.at( resourceName );
  }
};

#endif


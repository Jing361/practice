#ifndef __RESOURCE_MANAGER_HH__
#define __RESOURCE_MANAGER_HH__

#include<string>
#include<map>
#include<fstream>
#include<functional>

template<typename RESOURCE, typename REFERENCE = std::string>
class resourcemanager{
public:
  typedef RESOURCE res_type;
  typedef REFERENCE ref_type;
  typedef std::function<res_type( std::fstream )> processCallback;

private:
  std::map<ref_type, res_type> mResources;
  processCallback resourceCallback;

public:
  resourcemanager( processCallback callback = []->res_type( std::fstream file ){ return res_type( file ); } ):
    resourceCallback( callback ){
  }

  void acquire( const std::string& fileName, const ref_type& resourceName ){
    mResources[resourceName] = resourceCallback( std::fstream( fileName ) );
  }
  res_type& retrieve( const ref_type& resourceName ){
    return mResources.at( resourceName );
  }
};

#endif


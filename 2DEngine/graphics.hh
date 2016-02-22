#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include<string>
#include<map>
#include<vector>
#include<functional>
#include"image.hh"
#include"entity.hh"
#include"engine.hh"
#include"buffer.hh"

template<unsigned int X, unsigned int Y>
class graphics{
private:
  buffer<X, Y> m_frame;
  engine m_eng;

public:
  typedef void (*configCallbackPtr) (std::string, std::string, 
                                     std::map<std::string, image>, 
                                     std::map<std::string, entity<image>>, 
                                     std::map<std::string, tri>
                                    );
  typedef std::function<void(std::string, std::string, 
                             std::map<std::string, image>, 
                             std::map<std::string, entity<image>>, 
                             std::map<std::string, tri>
                            )> configCallback;
  std::function<void(double)> m_tickCallback;
  std::map<std::string, image> m_images;
  std::map<std::string, entity<image>> m_entities;
  std::map<std::string, tri> m_triangles;
  std::vector<void*> m_libs;
  std::map<std::string, configCallback> m_configCallbacks;

  virtual ~graphics();

  void loadConfig(std::string configFile);
  void tick(double diff);
  void run();
};

#include"graphics.cc"

#endif


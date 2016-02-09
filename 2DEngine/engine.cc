#include"engine.hh"
#include<iostream>

engine::engine(char kill):
  m_wait(&engine::killThread, this),
  m_killChar(kill){
}

engine::~engine(){
  m_wait.join();
}

void engine::killThread(){
  bufferedIO b;
  b.turnOff();
  char c;
  while(c != m_killChar && !m_end){
    c = getchar();
    try{
      auto cb = m_callbacks.at(c);
      cb();
    } catch(std::out_of_range& e){
      //nothing to be done
    }
  }
  m_end = true;
  b.turnOn();
}

bool& engine::shouldQuit(){
  return m_end;
}

void engine::registerCallback(char c, callback cb){
  m_callbacks[c] = cb;
}


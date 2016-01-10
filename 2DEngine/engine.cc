#include"engine.hh"

engine::engine():
  m_wait(&engine::killThread, this){
}

engine::~engine(){
  m_wait.join();
}

void engine::killThread(){
  bufferedIO b;
  b.turnOff();
  char c = ' ';
  while(c != 'q'){
    c = getchar();
  }
  m_end = true;
  b.turnOn();
}

bool engine::shouldQuit(){
  return m_end;
}


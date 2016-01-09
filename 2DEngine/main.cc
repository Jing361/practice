#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<termios.h>
#include<unistd.h>
#include"image.hh"
#include"buffer.hh"

class bufferedIO{
private:
  bool m_isBuffer = true;

public:
  void turnOn(){
    struct termios t;
    //get the current terminal I/O structure
    tcgetattr(0, &t);
    //Manipulate the flag bits to do what you want it to do
    t.c_lflag |= ICANON;
    //Apply the new settings
    tcsetattr(0, TCSANOW, &t);
    m_isBuffer = true;
  }

  void turnOff(){
    struct termios t;
    //get the current terminal I/O structure
    tcgetattr(0, &t);
    //Manipulate the flag bits to do what you want it to do
    t.c_lflag &= ~ICANON;
    //Apply the new settings
    tcsetattr(0, TCSANOW, &t);
    m_isBuffer = false;
  }

  void toggleBuffering(){
    if(m_isBuffer){
      turnOff();
    } else {
      turnOn();
    }
  }

};

class engine{
private:
  bool m_end = false;
  std::thread wait;

public:
  engine():
    wait(&engine::killThread, this){
  }

  virtual ~engine(){
    wait.join();
  }

  void killThread(){
    bufferedIO b;
    b.turnOff();
    char c = ' ';
    while(c != 'q'){
      c = getchar();
    }
    m_end = true;
    b.turnOn();
  }

  bool shouldQuit(){
    return m_end;
  }
};

int main(){
  buffer<20, 20> frame;
  std::string str("A\n"
                  "BB\n"
                  "CCC\n");
  image img(str);
  engine eng;
  coord v1(1, 5);
  coord v2(8, 8);
  coord v3(3, 1);

  while(!eng.shouldQuit()){
    frame.clear();
    frame.draw(img, coord(10, 10));
    frame.drawTri(v1, v2, v3);
    frame.display();
  }
  return 0;
}


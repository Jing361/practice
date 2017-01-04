#include"WatorGame.hh"
#include<memory>
//Use things like drawable or renderable virtual base classes for fish and shark?

using namespace std;

int main(int argc, char** argv){
  shared_ptr<Game> pGame( new WatorGame );
  pGame->run();
  return 0;
}


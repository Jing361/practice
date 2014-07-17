#include"WatorGame.hh"
//Use things like drawable or renderable virtual base classes for fish and shark?

int main(int argc, char** argv){
  Game& game = *new WatorGame;
  game.run();
  return 0;
}


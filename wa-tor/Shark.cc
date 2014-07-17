#include"Shark.hh"

Shark::Shark():Shark(0, 0, 0){  }

Shark::Shark(int x, int y, int z):Entity(x, y, z){  }

Shark::Shark(const vec& pos):Shark(pos.x, pos.y, pos.z){  }


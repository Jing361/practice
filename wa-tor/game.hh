
class Game{
protected:
  bool running;
public:
  Game();
  ~Game();
  void run();
  void initialize();
  void cleanup();
  void loop();
  void tick();
};


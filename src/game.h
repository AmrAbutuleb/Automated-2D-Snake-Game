#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "Autoplayer.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int mode);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  bool PowerSpeedCell(int x, int y);
  bool PowerSlowCell(int x, int y);
  bool FoodCell(int x, int y);
  bool ExtraLifeCell(int x, int y);
  

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point powerspeed;
  SDL_Point powerslow;
  SDL_Point extralife;
  std::unique_ptr<AutoPlayer> CPU;  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  void PlaceExtraLife();
  void PlacePowerSpeed();
  void PlacePowerSlow();
  void PlaceFood();
  void Update();
  void SetPlayer();
};

#endif
#ifndef AUTOPLAYER_H
#define AUTOPLAYER_h

#include "snake.h"
#include "SDL.h"

class AutoPlayer {
 public:
  //Rule of Five
  AutoPlayer(const Snake* snake, const SDL_Point* food, const SDL_Point* powerslow, const SDL_Point* extralife);
  ~AutoPlayer();
  AutoPlayer(const AutoPlayer &source);
  AutoPlayer &operator=(const AutoPlayer &source);
  AutoPlayer(AutoPlayer &&source);
  void play();    
 
 private:
  const Snake* snake;
  const SDL_Point* food;
  const SDL_Point* powerslow;
  const SDL_Point* extralife;
};

#endif
#include "game.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

int Globe::lives{0};

Game::Game(std::size_t grid_width, std::size_t grid_height, int mode)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)-1),
      random_h(0, static_cast<int>(grid_height)-1) {
  if (mode == 2) SetPlayer();
  PlaceFood();
  PlacePowerSpeed();
  PlacePowerSlow();
  PlaceExtraLife();
}

bool Game::FoodCell(int x, int y) {
  if (x == food.x && y == food.y) {
    return true;
  }
  return false;
}

bool Game::PowerSpeedCell(int x, int y) {
  if (x == powerspeed.x && y == powerspeed.y) {
    return true;
  }
 return false;
}

bool Game::PowerSlowCell(int x, int y) {
  if (x == powerslow.x && y == powerslow.y) {
    return true;
  }
 return false;
}

bool Game::ExtraLifeCell(int x, int y) {
  if (x == extralife.x && y == extralife.y) {
    return true;
  }
 return false;
}

void Game::SetPlayer() {
  CPU.reset(new AutoPlayer(&snake, &food, &powerslow, &extralife));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if (CPU) CPU->play();
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, powerspeed, powerslow, extralife);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, snake.speed, Globe::lives);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by any other item
    if (!snake.SnakeCell(x, y) && !Game::PowerSpeedCell(x, y) && !Game::PowerSlowCell(x, y) && !Game::ExtraLifeCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlacePowerSpeed() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by any other item
    if (!snake.SnakeCell(x, y) && !Game::FoodCell(x, y) && !Game::PowerSlowCell(x, y) && !Game::ExtraLifeCell(x,y)) {
      powerspeed.x = x;
      powerspeed.y = y;
      return;
    }
  }
}

void Game::PlacePowerSlow() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by any item
    if (!snake.SnakeCell(x, y) && !Game::FoodCell(x, y) && !Game::PowerSpeedCell(x, y) && !Game::ExtraLifeCell(x,y)) {
      powerslow.x = x;
      powerslow.y = y;
      return;
    }
  }
}

void Game::PlaceExtraLife() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by any item
    if (!snake.SnakeCell(x, y) && !Game::FoodCell(x, y) && !Game::PowerSpeedCell(x, y) && !Game::PowerSlowCell(x, y)) {
      extralife.x = x;
      extralife.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    
  }
  // Check if there's a powerspeed over here
  if (powerspeed.x == new_x && powerspeed.y == new_y) {
    //increases speed
    snake.speed += 0.06;
    PlacePowerSpeed();
  }

  if (powerslow.x == new_x && powerslow.y == new_y) {
    //decreases speed
    snake.speed -= 0.06;
    PlacePowerSlow();
  }
  
  if (extralife.x == new_x && extralife.y == new_y) {
    //adds a life
    Globe::lives++;
    PlaceExtraLife();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
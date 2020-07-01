#include <iostream>
#include "Autoplayer.h"
#include "snake.h"

AutoPlayer::AutoPlayer(const Snake* snake, const SDL_Point* food, const SDL_Point* powerslow, const SDL_Point* extralife) : snake(snake), food(food), powerslow(powerslow), extralife(extralife){
    std::cout << "AutoPlayer's Constructor called.\n";
};

AutoPlayer::~AutoPlayer() {
    std::cout << "AutoPlayer's Destructor called.\n";
}

AutoPlayer::AutoPlayer(const AutoPlayer &source){
    snake = source.snake;
    food = source.food;
    powerslow = source.powerslow;
    extralife = source.extralife;
    std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
}

AutoPlayer& AutoPlayer::operator=(const AutoPlayer &source){
    std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    snake = source.snake;
    food = source.food;
    powerslow = source.powerslow;
    extralife = source.extralife;
    return *this;
}
    
AutoPlayer::AutoPlayer(AutoPlayer &&source){
    std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
    snake = source.snake;
    food = source.food;
    powerslow = source.powerslow;
    extralife = source.extralife;
    source.snake = nullptr;
    source.food = nullptr;
    powerslow = nullptr;
    extralife = nullptr;
}

void AutoPlayer::play()
{
    int xCo = static_cast<int>(snake->head_x);
    int yCo = static_cast<int>(snake->head_y);
    // Preparing an event
    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;

    if (xCo == food->x && snake->speed < 0.41 ) 
    {
        if (yCo > food->y) sdlevent.key.keysym.sym = SDLK_UP;
        else sdlevent.key.keysym.sym = SDLK_DOWN;
    }
    else if(yCo == food->y && snake->speed < 0.41)
    {
        if (yCo > food->x) sdlevent.key.keysym.sym = SDLK_LEFT;
        else sdlevent.key.keysym.sym = SDLK_RIGHT;
    }
    
    if(snake->speed > 0.41 && xCo == powerslow->x)
    {
        if (yCo > powerslow->y) sdlevent.key.keysym.sym = SDLK_UP;
        else sdlevent.key.keysym.sym = SDLK_DOWN;
    }
    else if(snake->speed > 0.41 && yCo == powerslow->y)
    {
        if (xCo > powerslow->x) sdlevent.key.keysym.sym = SDLK_LEFT;
        else sdlevent.key.keysym.sym = SDLK_RIGHT;
    }

    if(xCo == extralife->x && Globe::lives < 20 && snake->speed < 0.41)
    {
        if (yCo > extralife->y) sdlevent.key.keysym.sym = SDLK_UP;
        else sdlevent.key.keysym.sym = SDLK_DOWN;
    }
    else if(yCo == extralife->y && Globe::lives < 20 && snake->speed < 0.41)
    {
        if (xCo > extralife->x) sdlevent.key.keysym.sym = SDLK_LEFT;
        else sdlevent.key.keysym.sym = SDLK_RIGHT;
    }

    SDL_PushEvent(&sdlevent);
}
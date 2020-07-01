#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <bits/stdc++.h>
#include "playerhistory.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  std::string current_player_name;
  std::map<std::string, int> current_player_map;

  int kMode;
  std::cout << "Welcome to one of the most awesome Snake Games out there!\n";
  std::cout << "Press 1 if you want to Play.\n";
  std::cout << "Press 2 if you want the CPU to Play.\n";
  std::cout << "Press 3 if you would like to see game history.\n";
  std::cin >> kMode;
  if(kMode == 1){
    std::cout << "Please enter your name\n";
    std::cin >> current_player_name;
  }

  while (kMode != 1 && kMode != 2 && kMode != 3) 
  {
    std::cout << "Invalid choice.\n";
    std::cout << "Press 1 if you want to Play.\n";
    std::cout << "Press 2 if you want the CPU to Play.\n";
    std::cout << "Press 3 if you would like to see game history.\n";
    
    std::cin >> kMode;
  }
  if (kMode == 3){
    PlayerHistory dm;
        std::map<std::string, int> recorded_players;
        recorded_players = dm.ReadGameHistory();
        if (recorded_players.size() > 0)
        {
            dm.DisplayPlayers(recorded_players);
        }
        else
        {
            std::cout << "The history for this game does not exist ...!" << std::endl;
        }
        return 0;
  }
  if (kMode == 2){
    current_player_name = "CPU";
  }
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, kMode); 
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  PlayerHistory *newph = new PlayerHistory();
  std::cout << current_player_name;
  int player_score = game.GetScore();
  current_player_map.insert(std::make_pair(current_player_name, player_score));
  newph->WriteThisGame(current_player_map);
  std::cout << " has Scored a total of : " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
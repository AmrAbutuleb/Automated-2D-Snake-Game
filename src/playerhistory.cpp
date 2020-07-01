#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include "playerhistory.h"


using std::string;
using std::vector;
using std::string;
using std::vector;

std::map<string, int> PlayerHistory::ReadGameHistory()
{

  string line;
  string player_name;
  int player_score;
  std::map<string, int> players_map;
  std::map<string, int>::iterator itr;

  std::ifstream filestream("Game_History.txt");

  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {

      std::istringstream linestream(line);
      if(linestream >> player_name >> player_score)
      {
        players_map.insert(std::make_pair(player_name, player_score));
        itr = players_map.find(player_name);

        if (itr != players_map.end()){
            itr->second = player_score ;
         }
      }
    }
    filestream.close();
    std::cout << "File Read Successfully" << std::endl;
    return players_map;
  }
  else
  {
    std::ofstream outfile("Game_History.txt");
    std::cout << "Game_History file does not exist. and a new one has been created" << std::endl;
  }
  return players_map;
};

void PlayerHistory::DisplayPlayers(std::map<string, int> aux_map)
{
  int i = 1;
  for(auto it = aux_map.begin(); it !=aux_map.end(); ++it)
  {
    std::cout << i << ". player : " << it->first << ", score : " << it->second << std::endl;
    i++;
    if (i > 10)
      break;
  }
};

void PlayerHistory::WriteThisGame(std::map<string, int> players_map)
{
  std::map<string, int>::iterator it;
  std::ofstream dataFile;

  dataFile.open("Game_History.txt", std::ios::binary | std::ios::out | std::ios::app);
  if (!dataFile.is_open())
  {
    std::cout << " not possible to open file" << std::endl;
  }
  else
  {
    for (it = players_map.begin(); it != players_map.end(); it++)
    {
      dataFile << (*it).first << " " << (*it).second << "\n";
    }

    dataFile.close();
  }
}

#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using std::map;
using std::string;

class PlayerHistory
{

public:
    PlayerHistory(){};
    PlayerHistory(string a, int b) : player_name(a), player_score(b){};

    string GetPlayerName(){return player_name;};
    map<string, int> ReadGameHistory();
    void DisplayPlayers(std::map<string, int> aux_map);
    void WriteThisGame(std::map<string, int> players_map);

    void SetPlayerName();
    void SetPlayerScore();
    void SetPlayerGameTime();

private:
    string player_name;
    int player_score;
};
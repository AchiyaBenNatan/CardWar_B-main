#ifndef GAME_H
#define GAME_H
#include "player.hpp"
using namespace std;
#include <vector>
namespace ariel{
    class Game
    {
    private:
        Player &pl1;
        Player &pl2;
        string log;
        string lastTurn;
    public:
        Game();
        Game(Player &pl1, Player &pl2);
        int playTurn();
        void printLastTurn();
        int playAll();
        void printWiner();
        void printLog();
        void printStats();
        Player getFirstPlayer();
        Player getSecondPlayer();
    };
}
#endif
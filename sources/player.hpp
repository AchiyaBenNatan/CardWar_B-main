#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "card.hpp"
using namespace ariel;
namespace ariel{
    class Player
    {
    private: 
    std::string name;
    std::vector<ariel::Card> deck;
    int stackS = 0;
    int cardsTaken = 0;
    public: 
        Player();
        Player(std::string name);
        Player(const Player &player);
        Player& operator=(const Player& other);
        Player(Player&& other) noexcept;
        Player& operator=(Player&& other) noexcept;
        int stacksize();
        int cardesTaken();
        void setCards(std::vector<ariel::Card> *deck);
        std::vector<ariel::Card> &getCards();
        std::string getname();
        void setStackSize(int stackSize);
        void setCardsTaken(int cardsTaken);
        ~Player();
    };
}
#endif
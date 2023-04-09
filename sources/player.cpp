#include "player.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace ariel;
namespace ariel{
Player::Player()
    {
        this->name = "Achiya";
    }
    Player::Player(std::string name):name(name)
    {
        this->name = name;
    }
    Player::Player(const Player &other)
    {
        this->name = other.name;
    }
    Player::Player(Player&& other) noexcept {}
    Player& Player::operator=(const Player& other){
    if (this != &other) {
        this->name = other.name;
        this->deck = other.deck;
        this->stackS = other.stackS;
        this->cardsTaken = other.cardsTaken;
    }
    return *this;
}

Player& Player::operator=(Player&& other)noexcept{
    if (this != &other) {
        this->name = std::move(other.name);
        this->deck = std::move(other.deck);
        this->stackS = other.stackS;
        this->cardsTaken = other.cardsTaken;
    }
    return *this;
}
    void Player::setCards(std::vector<ariel::Card> *newdeck)
    {
        this->deck = *newdeck;
    }
    std::vector<ariel::Card> &Player::getCards()
    {
        return deck;
    }
    Player::~Player()
    {
    }
    int Player::stacksize()
    {
        return this->stackS;
    }
    int Player::cardesTaken()
    {
        return this->cardsTaken;
    }
    void Player::setCardsTaken(int cards)
    {
        this->cardsTaken = cards;
    }
    void Player::setStackSize(int stack)
    {
        this->stackS = stack;
    }
    std::string Player::getname()
    {
        return this->name;
    }
}
#include "card.hpp"
#include <iostream>
using namespace ariel;
namespace ariel
{
    Card::Card()
    {
        this->num = 1;
        this->suit = 'h';
    }
    Card::Card(int num, char suit)
    {
        this->num = num;
        this->suit = suit;
    }
    int Card::getNum()
    {
        return this->num;
    }
    char Card::getSuit()
    {
        return this->suit;
    }
    std::string Card::toString()
    {
        return "Number: "+ std::to_string(this->num)+ " Suit: "+this->suit+". ";
    }
}
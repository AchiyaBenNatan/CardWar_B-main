#ifndef CARD_H
#define CARD_H
#include <stdio.h>
#include <iostream>
using namespace std;
namespace ariel{
    class Card
    {
    private:
        int num;
        char suit;
    public:
        Card();
        Card(int num , char shape);
        int getNum();
        char getSuit();
        std::string toString();
    };
}
#endif
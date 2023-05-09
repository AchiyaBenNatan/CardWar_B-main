#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace ariel;
#include "doctest.h"
#include <string.h>
using namespace doctest;

TEST_CASE("players name")
{
    Player p1("player one");
    Player p2("player two");
    CHECK(p1.getname()=="player one");
    CHECK(p2.getname()=="player two");
}
TEST_CASE("game turn test")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    CHECK(p1.stacksize()==26);
    CHECK(p2.stacksize()==26);
    game.playTurn();
    CHECK(p1.stacksize()<26);
    CHECK(p2.stacksize()<26);
}
TEST_CASE("game played")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    game.playAll();
    CHECK(p1.stacksize()==0);
    CHECK(p2.stacksize()==0);
    CHECK(p1.cardesTaken()+p2.cardesTaken() == 52);
}
TEST_CASE("card check")
{
    Card c1(3,'h'), c2(5 ,'c');
    CHECK(c1.getNum()==3);
    CHECK(c2.getNum()==5);
    CHECK(c1.getSuit()=='h');
    CHECK(c2.getSuit()=='c');
}
TEST_CASE("check after game over throw.")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    game.playAll();
    CHECK_THROWS(game.playTurn());
}
TEST_CASE("null")
{
    CHECK_THROWS(Player(NULL));
    CHECK_THROWS(Game());
}
TEST_CASE("game players test")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    CHECK(game.getFirstPlayer().getname() == p1.getname());
    CHECK(game.getSecondPlayer().getname() == p2.getname());
}
TEST_CASE("game players test")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    Card c1 = p1.getCards().back();
    Card c2 = p2.getCards().back();
    game.playTurn();
    if (c1.getNum()>c2.getNum()&&c1.getNum()!=1&&c2.getNum()!=1
        ||(c1.getNum()==1&&c2.getNum()!=2)||(c1.getNum()==2&&c2.getNum()==1))
    {
        CHECK(p1.cardesTaken()==2);
        CHECK(p2.cardesTaken()==0);
    }
    else if(c2.getNum()>c1.getNum()&&c2.getNum()!=1&&c1.getNum()!=1
        ||(c2.getNum()==1&&c1.getNum()!=2)||(c2.getNum()==2&&c1.getNum()==1))
    {
        CHECK(p2.cardesTaken()==2);
        CHECK(p1.cardesTaken()==0);
    }
    else{
        CHECK(c1.getNum()==c2.getNum());
    }
}

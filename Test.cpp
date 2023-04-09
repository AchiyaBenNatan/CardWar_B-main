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
TEST_CASE("tie or not tie")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    CHECK(p1.stacksize()==26);
    CHECK(p2.stacksize()==26);
    int p1CardsTaken = 0, p2CardsTaken = 0;
    while (game.printLastTurn() == "Tie"||p1.stacksize()!=0)
    {
        p1CardsTaken = p1.cardesTaken();
        p2CardsTaken = p2.cardesTaken();
        game.playTurn();
    }
    if(game.printLastTurn() == "Tie"){
    p1CardsTaken -= p1.cardesTaken();
    p2CardsTaken -= p2.cardesTaken(); 
    bool cardstakenTie = (p1CardsTaken>2||p2CardsTaken>2);
    CHECK(cardstakenTie == true);
    }
    else{
        CHECK(p1.stacksize()==0);
        CHECK(p2.stacksize()==0);
    }
}
TEST_CASE("check winner")
{
    Player p1("player one");
    Player p2("player two");
    Game game(p1,p2);
    game.playAll();
    if (p1.cardesTaken()>p2.cardesTaken())
    {
        CHECK(game.printWiner() == p1.getname());
    }
    if (p1.cardesTaken()<p2.cardesTaken())
    {
        CHECK(game.printWiner() == p2.getname());
    }
    else{
        CHECK(p1.stacksize()==26);
        CHECK(p2.stacksize()==26);
    }
}
TEST_CASE("check")
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

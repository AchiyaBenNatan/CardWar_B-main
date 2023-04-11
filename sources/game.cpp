#include "game.hpp"
#include "player.hpp"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std; 
using namespace ariel;
namespace ariel{
    static bool tie = false;
    int numOfTie = 0;
    double draws = 0;
    double turns = 0;
    Player p1 = Player();
    string lastTurn = "";
    string log = "";
    Game::Game():pl1(p1), pl2(p1)
    {
        throw std::invalid_argument("cant build a game without players.");
    }
    void printVector(std::vector<Card> &deck)
    {
        for (size_t i = 0; i < deck.size(); i++)
        {
            cout<<deck[i].toString()<<endl;
        }
    }
    Game::Game(Player &p1, Player &p2):pl1(p1), pl2(p2)
    {
        draws = 0;
        turns = 0;
        int index = 0;
        std::vector<Card> deck;
        for (char suit : {'H', 'D', 'C', 'S'}) { 
        for (int num = 1; num <= 13; num++) 
            deck.push_back(Card(num, suit)); 
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 theSeed(seed);
        std::shuffle(deck.begin(), deck.end(), theSeed);
        std::vector <Card> p1Vector(deck.begin(),deck.begin()+26);
        pl1.setCards(&p1Vector);
        std::vector <Card> p2Vector(deck.begin()+26,deck.end());
        pl2.setCards(&p2Vector);
        pl1.setStackSize(26);
        pl2.setStackSize(26);
    }
    int Game::playTurn()
    {
        if (!tie)
        {
            lastTurn = "";
        }
        if(&pl1 == &pl2){
            throw std::invalid_argument("choose 2 players not 1.\n");
            return 1;
        }
        if (pl1.stacksize() == 0)
        {
            throw std::invalid_argument("Game is over.\n");
            return 1;
        }
        if (tie&&pl1.stacksize()>1)
        {
            pl1.getCards().pop_back();
            pl2.getCards().pop_back();
            pl1.setStackSize(pl1.stacksize() - 1);
            pl2.setStackSize(pl2.stacksize() - 1);
            draws++;
        }
        else if (tie&&pl1.stacksize()==1)
        {
            pl1.setStackSize(pl1.stacksize() - 1);
            pl2.setStackSize(pl2.stacksize() - 1);
            pl1.setCardsTaken(pl1.cardesTaken()+2*numOfTie);
            pl2.setCardsTaken(pl2.cardesTaken()+2*numOfTie);
            draws++;

            return 0;
        }
        Card c1 = pl1.getCards().back();
        Card c2 = pl2.getCards().back();
        pl1.getCards().pop_back();
        pl2.getCards().pop_back();
        pl1.setStackSize(pl1.stacksize() - 1);
        pl2.setStackSize(pl2.stacksize() - 1);

        if (c1.getNum()>c2.getNum())
        {
            pl1.setCardsTaken(pl1.cardesTaken()+2+4*numOfTie);
            lastTurn += pl1.getname()+" " + c1.toString() + ", "+pl2.getname()+" " + c2.toString()+", "+ pl1.getname() + " wins!\n";
            log += lastTurn;
            tie = false;
            numOfTie = 0;
            turns++;
            pl1.setStackSize(pl1.getCards().size());
            pl2.setStackSize(pl2.getCards().size());
        }
        else if (c1.getNum()<c2.getNum())
        {
            pl2.setCardsTaken(pl2.cardesTaken()+2+4*numOfTie);
            lastTurn += pl1.getname()+" " + c1.toString() + ", "+pl2.getname()+" " + c2.toString()+", "+ pl2.getname() + " wins!\n";
            log += lastTurn;
            tie = false;
            numOfTie = 0;
            turns++;
            pl1.setStackSize(pl1.getCards().size());
            pl2.setStackSize(pl2.getCards().size());
        }
        else 
        {
            
            tie = true;
            numOfTie++;
            draws++;
            lastTurn += pl1.getname()+" " + c1.toString() + ", "+pl2.getname()+" " + c2.toString()+", tie. \n";
            if(pl1.stacksize()>0)
            {
                playTurn();
            }
            else 
            {
                numOfTie--;
                pl1.setCardsTaken(pl1.cardesTaken()+1+2*numOfTie);
                pl2.setCardsTaken(pl2.cardesTaken()+1+2*numOfTie);
                pl1.setStackSize(0);
                pl2.setStackSize(0);
            }   
        }
        return 0;
    }
    void Game::printLastTurn()
    {
            cout << lastTurn << endl;
    }
    int Game::playAll()
    {
        //printVector(pl1.getCards());
        while (pl1.stacksize()!=0)
        {
            
            playTurn();
            //printLastTurn();
        }
        //cout << "Game is over.\n";
        return 0;
    }
    void Game::printWiner()
    {
        cout << pl1.cardesTaken() << " " << pl2.cardesTaken() << "\n";
        if (pl1.cardesTaken()>pl2.cardesTaken())
        {
            cout << pl1.getname() << " wins!\n";
        }
        else if (pl1.cardesTaken()<pl2.cardesTaken())
        {
            cout << pl2.getname() << " wins!\n";
        }
        else
        {
            cout<<"Its a tie. No winner!\n"<<endl;
        }
    }
    void Game::printLog()
    {
        cout << log << endl;
    }
    void Game::printStats()
    {
        cout<<pl1.getname()<<" won " <<pl1.cardesTaken()<< " cards."<< pl2.getname()<<" won " <<pl2.cardesTaken()<< " cards."<<endl
        <<draws<<" draws have happend. Draw rate is: "<<draws/turns<<endl;
    }
    Player Game::getFirstPlayer()
    {
        return this->pl1;
    }
    Player Game::getSecondPlayer()
    {
        return this->pl2;
    }
}
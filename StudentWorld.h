#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
using namespace std;

class Actor;
class Player_Avatar;
class BadGuy;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    Board* getBoard() {return bd;}
    Player_Avatar* getPlayer1() {return m_Player1;}
    Player_Avatar* getPlayer2() {return m_Player2;}
    void changeBankMoney(int num) {cBank += num;}
    int getBankMoney() {return cBank;}
    void resetBank() {cBank = 0;}
    void replaceSquare(int x, int y);
    bool isASquare(Board::GridEntry g);
    bool VortexConnection(int x, int y);
    void addVortex(int x, int y, int Dir);
    
private:
    Player_Avatar* m_Player1;
    Player_Avatar* m_Player2;
    vector<Actor*> actors;
    Board* bd;
    int cBank;
    int n_actors = 0;
};

#endif // STUDENTWORLD_H_

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"


class Actor : public GraphObject
{
  public:
    Actor(StudentWorld* sw, int ID, int startX, int startY, int startD, int depth, double size);
    virtual void doSomething() = 0;
    bool isAlive();
    void setDead();
    StudentWorld* getWrld(){return m_world;}
    bool canMoveForward(int direction);
    bool CheckLoc(Player_Avatar* player);
    void addTick(Player_Avatar* player);
    void resetTick(Player_Avatar* player);
    int returnTick(Player_Avatar* player);
    bool newPlyr(Player_Avatar* player);
    int checkFork(int Dir, int x, int y);
    void setValidDirection(Actor* player);
    int getBdir(){return Bdir;}
    void setBdir(int x){Bdir = x;}
    virtual bool isImpactable(){return false;}
    virtual bool isSquare(){return true;}
    void teleport();
  private:
    StudentWorld* m_world;
    bool m_alive;
    int countTick1;
    int countTick2;
    int Bdir;
};



class Player_Avatar : public Actor
{
public:
    Player_Avatar(StudentWorld* sw, int ID, int startX, int startY, int startD);
    void changeCoins(int numCoins);
    int getCoins() {return m_coins;}
    int getTicksToMove() {return ticks_to_move;}
    int getStars() {return m_stars;}
    void SwapPosition();
    bool getVortex() {return vortex;}
    void giveVortex() {vortex = true;}
    void takeVortex() {vortex = false;}
    void changeStars(int numStar);
    void doSomething();
    virtual int getPnum() = 0;
    bool getWaitingToMove() {return Waiting_to_move;}
    bool getTeleported(){return teleported;}
    void setTeleported(bool x){teleported = x;}
    void setCoin(int x){m_coins = x;}
    void setStar(int x){m_stars = x;}
private:
    int m_coins;
    int m_stars;
    bool vortex;
    int ticks_to_move;
    bool Waiting_to_move;
    int die_roll = 0;
    int moveCount = 0;
    bool teleported = false;

};

class Peach : public Player_Avatar
{
public:
    Peach(StudentWorld* sw, int startX, int startY);
    virtual bool isSquare(){return false;}
    int getPnum(){return pnum;}
private:
    int pnum = 1;
};

class Yoshi : public Player_Avatar
{
public:
    Yoshi(StudentWorld* sw, int startX, int startY);
    virtual bool isSquare(){return false;}
    int getPnum(){return pnum;}
private:
    int pnum = 2;
};


class BadGuy : public Actor
{
public:
    BadGuy(StudentWorld* sw, int ID, int startX, int startY, int startD);
    virtual void doSomething() = 0;
    int getPcounter(){return pause_counter;}
    void setPcounter(int x){pause_counter += x;}
    void resetPcount(){pause_counter = 180;}
    bool getPaused(){return paused;}
    void setPaused(bool x){paused = x;}
    void decrementTicks(){ticks_to_move--;}
    void setTicks(int x){ticks_to_move = x;}
    int getTicks(){return ticks_to_move;}
    virtual bool isImpactable(){return true;}
    virtual bool isSquare(){return false;}
    

private:
    bool paused;
    int pause_counter;
    int ticks_to_move;
};

class Bowser : public BadGuy
{
public:
    Bowser(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};

class Boo : public BadGuy
{
public:
    Boo(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};


class Square : public Actor
{
public:
    Square(StudentWorld* sw, int ID, int startX, int startY, int spritedir, int depth);
    virtual void doSomething() = 0;
};


class Coin_Square : public Square
{
public:
    Coin_Square(StudentWorld* sw, int ID, int startX, int startY, int amount);
    void doSomething();
    int getAmount(){return m_amount;}
private:
    int m_amount;
};


class Red_Square : public Coin_Square
{
public:
    Red_Square(StudentWorld* sw, int startX, int startY);
};

class Blue_Square : public Coin_Square
{
public:
    Blue_Square(StudentWorld* sw, int startX, int startY);
};

class Star_Square : public Square
{
public:
    Star_Square(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};



class Directional_Square : public Square
{
public:
    Directional_Square(StudentWorld* sw, int startX, int startY, int direction);
    virtual void doSomething();
    int getSpriteDir() {return spriteDir;}
private:
    int spriteDir;
};


class Bank_Square : public Square
{
public:
    Bank_Square(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};

class Event_Square : public Square
{
public:
    Event_Square(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};

class Dropping_Square : public Square
{
public:
    Dropping_Square(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
};

class Vortex : public Square
{
public:
    Vortex(StudentWorld*sw, int startX, int startY, int startD);
    void doSomething();
    
};
#endif // ACTOR_H_


#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void StudentWorld::replaceSquare(int x, int y){
    
    for(int z = 0; z < actors.size(); z++){
        if(actors[z]->getX()/16 == x && actors[z]->getY()/16 == y && actors[z]->isSquare()){
            Actor* t = actors[z];
            delete t;
            playSound(SOUND_DROPPING_SQUARE_CREATED);
            actors[z] = new Dropping_Square(this,SPRITE_WIDTH * x,SPRITE_HEIGHT * y);
        }
    }
}

bool StudentWorld::VortexConnection(int x, int y){
    for(auto L = actors.begin(); L != actors.end(); L++){
        if((*L)->isImpactable()){
            if((abs(x - (*L)->getX()) < 16 && y == (*L)->getY()) || (abs(y - (*L)->getY()) < 16 && x == (*L)->getX())){
                (*L)->teleport();
                return true;
            }
        }
    }
    return false;
}




bool StudentWorld::isASquare(Board::GridEntry g) {
    switch(g) {
        case Board::blue_coin_square:
        case Board::red_coin_square:
        case Board::event_square:
        case Board::up_dir_square:
        case Board::down_dir_square:
        case Board::right_dir_square:
        case Board::left_dir_square:
        case Board::bank_square:
        case Board::star_square:
            return true;
            break;
        case Board::boo:
        case Board::bowser:
        case Board::player:
            return false;
            break;
        default:
            return false;
            break;
    }
}


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}


void StudentWorld::addVortex(int x, int y, int Dir){
    actors.push_back(new Vortex(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, Dir));
}

int StudentWorld::init()
{
    
    bd = new Board;
    ostringstream oss;
    oss << "board0" << getBoardNumber() << ".txt";
    string L = oss.str();
    string board_file = assetPath() + L;
    Board::LoadResult result = bd->loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        for(int x = 0; x < 16; x++){
            for(int y = 0; y < 16; y++){
                Board::GridEntry ge = bd->getContentsOf(x, y);
                switch (ge) {
                    case Board::empty:
                        break;
                    case Board::boo:{
                        actors.push_back(new Blue_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        actors.push_back(new Boo(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::bowser:{
                        actors.push_back(new Blue_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        actors.push_back(new Bowser(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::player:{
                        actors.push_back(new Blue_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        m_Player1 = new Peach(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y);
                        m_Player2 = new Yoshi(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y);
                        break;
                    }
                    case Board::red_coin_square:{
                        actors.push_back(new Red_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::blue_coin_square:{
                        actors.push_back(new Blue_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::star_square:{
                        actors.push_back(new Star_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::down_dir_square:{
                        actors.push_back(new Directional_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 270));
                        break;
                    }
                    case Board::left_dir_square:{
                        actors.push_back(new Directional_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 180));
                        break;
                    }
                    case Board::right_dir_square:{
                        actors.push_back(new Directional_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 0));
                        break;
                    }
                    case Board::up_dir_square:{
                        actors.push_back(new Directional_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y, 90));
                        break;
                    }
                    case Board::bank_square:{
                        actors.push_back(new Bank_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
                    case Board::event_square:{
                        actors.push_back(new Event_Square(this, SPRITE_WIDTH * x, SPRITE_HEIGHT * y));
                        break;
                    }
            }
        }

     }
     }
    startCountdownTimer(99);
    
    
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::move()
{
    if(timeRemaining() <= 0){
        playSound(SOUND_GAME_FINISHED);
        if(getPlayer1()->getCoins() > getPlayer2()->getCoins() && getPlayer1()->getStars() > getPlayer2()->getStars()){
            setFinalScore(getPlayer1()->getStars(), getPlayer1()->getCoins());
            return GWSTATUS_PEACH_WON;
        } else if(getPlayer2()->getCoins() > getPlayer1()->getCoins() && getPlayer2()->getStars() > getPlayer1()->getStars()){
            setFinalScore(getPlayer2()->getStars(), getPlayer2()->getCoins());
            return GWSTATUS_YOSHI_WON;
        } else if(getPlayer1()->getStars() == getPlayer2()->getStars() && getPlayer1()->getCoins() > getPlayer2()->getCoins()){
            setFinalScore(getPlayer1()->getStars(), getPlayer1()->getCoins());
            return GWSTATUS_PEACH_WON;
        } else if(getPlayer1()->getStars() == getPlayer2()->getStars() && getPlayer2()->getCoins() > getPlayer1()->getCoins()){
            setFinalScore(getPlayer2()->getStars(), getPlayer2()->getCoins());
            return GWSTATUS_YOSHI_WON;
        } else if(getPlayer1()->getStars() > getPlayer2()->getStars() && getPlayer1()->getCoins() <= getPlayer2()->getCoins()){
            setFinalScore(getPlayer1()->getStars(), getPlayer1()->getCoins());
            return GWSTATUS_PEACH_WON;
        } else if(getPlayer2()->getStars() > getPlayer1()->getStars() && getPlayer2()->getCoins() <= getPlayer1()->getCoins()){
            setFinalScore(getPlayer2()->getStars(), getPlayer2()->getCoins());
            return GWSTATUS_YOSHI_WON;
        } else{
            int x = randInt(1, 2);
            if(x == 1){
                setFinalScore(getPlayer1()->getStars(), getPlayer1()->getCoins());
                return GWSTATUS_PEACH_WON;
            } else{
                setFinalScore(getPlayer2()->getStars(), getPlayer2()->getCoins());
                return GWSTATUS_YOSHI_WON;
            }
        }
    }
    
    m_Player1->doSomething();
    m_Player2->doSomething();
    

    
    for(int j = 0; j < actors.size(); j++){
        if(actors[j]->isAlive() == true){
            actors[j]->doSomething();
        }
    }
    
    for(int p = 0; p < actors.size(); p++){
        if(actors[p]->isAlive() == false){
            delete actors[p];
        }
    }


    
    ostringstream oss;
    int x = getPlayer1()->getStars();
    oss << "P1 Roll: " << getPlayer1()->getTicksToMove() / 8;
    oss << " Stars: " << x;
    oss << " $$: " << getPlayer1()->getCoins();
    if(getPlayer1()->getVortex()){
        oss << " VOR";
    }

    oss << " | Time: " << timeRemaining();
    oss << " | Bank: " << cBank;
    oss << " | P2 Roll: " << getPlayer2()->getTicksToMove() / 8;
    oss << " Stars: " << getPlayer2()->getStars();
    oss << " $$: " << getPlayer2()->getCoins();
    if(getPlayer2()->getVortex()){
        oss << " VOR";
    }
    
    setGameStatText(oss.str());
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    
    for(int k = 0; k < actors.size(); k++){
        delete actors[k];
    }
    delete m_Player1;
    m_Player1 = nullptr;
    delete m_Player2;
    m_Player2 = nullptr;

}

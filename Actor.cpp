#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

Actor::Actor(StudentWorld* sw, int ID, int startX, int startY, int startD, int depth, double size)
: GraphObject(ID, startX, startY, startD, depth, size), m_world(sw), m_alive(true),countTick1(0), countTick2(0){}


bool Actor::isAlive(){return m_alive;}
void Actor::setDead(){m_alive = false;}


bool Actor::canMoveForward(int direction){
    switch(direction) {
        case right: {
            if(getWrld()->getBoard()->getContentsOf( getX()/16 + 1, getY()/16) != Board::empty){
                return true;
                break;
            }
               return false;
               break;
        }
        case left : {
                if(getWrld()->getBoard()->getContentsOf( getX()/16 - 1, getY()/16) != Board::empty){
                    return true;
                    break;
                }
                   return false;
                   break;
        }
        case up : {
            if(getWrld()->getBoard()->getContentsOf( getX()/16, getY()/16 + 1) != Board::empty){
                return true;
                break;
            }
               return false;
               break;
        }
        case down : {
            if(getWrld()->getBoard()->getContentsOf( getX()/16, getY()/16 - 1) != Board::empty){
                return true;
                break;
            }
               return false;
               break;
        }
    }
            
            return false;
}

int Actor::checkFork(int Dir, int x, int y){
    int count = 0;
    switch (Dir) {
        case 0:
            if(getWrld()->getBoard()->getContentsOf(x / 16 + 1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16, y / 16 + 1) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x / 16, y / 16 - 1) != Board::empty){
                count++;
            }
            break;
        case 180:
            if(getWrld()->getBoard()->getContentsOf(x/16-1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16, y/16 + 1) != Board::empty){
               count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16, y/16 - 1) != Board::empty){
                count++;
            }
            break;
        case 90:
            if(getWrld()->getBoard()->getContentsOf(x/16+1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16-1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16, y/16 + 1) != Board::empty){
                count++;
            }
            break;
        case 270:
            if(getWrld()->getBoard()->getContentsOf(x/16+1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16-1, y/16) != Board::empty){
                count++;
            }
            if(getWrld()->getBoard()->getContentsOf(x/16, y/16 - 1) != Board::empty){
               count++;
            }
            break;
    }
    return count;
}



///
///
///
/// PLAYER_AVATAR IMPLEMENTATIONS
///
///
///
///
///

Player_Avatar::Player_Avatar(StudentWorld* sw, int ID, int startX, int startY, int startD)
: Actor(sw, ID, startX, startY, startD, 0, 1.0), vortex(false), m_coins(0), m_stars(0), ticks_to_move(0), Waiting_to_move(true) {setBdir(startD);}

void Actor::teleport(){
        while(true){
            int x = randInt(0, 15);
            int y = randInt(0, 15);
            if(getWrld()->getBoard()->getContentsOf(x, y) != Board::empty){
                this->moveTo(x * 16, y * 16);
                return;
            }
        }
}

void Player_Avatar::SwapPosition(){
    if(getPnum() == 1){
        
        // change x, y
        int tempx = getWrld()->getPlayer2()->getX();
        int tempy = getWrld()->getPlayer2()->getY();
        getWrld()->getPlayer2()->moveTo(getWrld()->getPlayer1()->getX(), getWrld()->getPlayer1()->getY());
        getWrld()->getPlayer1()->moveTo(tempx, tempy);
        
        // change ticks
        int tempticks = getWrld()->getPlayer2()->ticks_to_move;
        getWrld()->getPlayer2()->ticks_to_move = getWrld()->getPlayer1()->ticks_to_move;
        getWrld()->getPlayer1()->ticks_to_move = tempticks;
        
        // change walk and sprite dir
        int tempDir = getWrld()->getPlayer2()->getBdir();
        int tempDirection = getWrld()->getPlayer2()->getDirection();
        getWrld()->getPlayer2()->setBdir(getWrld()->getPlayer1()->getBdir());
        getWrld()->getPlayer2()->setDirection(getWrld()->getPlayer1()->getDirection());
        getWrld()->getPlayer1()->setBdir(tempDir);
        getWrld()->getPlayer1()->setDirection(tempDirection);
        
        // change roll/walk state;
        bool state = getWrld()->getPlayer2()->getWaitingToMove();
        getWrld()->getPlayer2()->Waiting_to_move = getWrld()->getPlayer1()->getWaitingToMove();
        getWrld()->getPlayer1()->Waiting_to_move = state;
        
    } else{
        
        // change x, y
        int tempx = getWrld()->getPlayer1()->getX();
        int tempy = getWrld()->getPlayer1()->getY();
        getWrld()->getPlayer1()->moveTo(getWrld()->getPlayer2()->getX(), getWrld()->getPlayer2()->getY());
        getWrld()->getPlayer2()->moveTo(tempx, tempy);
        
        // change ticks
        int tempticks = getWrld()->getPlayer1()->ticks_to_move;
        getWrld()->getPlayer1()->ticks_to_move = getWrld()->getPlayer2()->ticks_to_move;
        getWrld()->getPlayer2()->ticks_to_move = tempticks;
        
        // change walk and sprite dir
        int tempDir = getWrld()->getPlayer1()->getBdir();
        int tempDirection = getWrld()->getPlayer1()->getDirection();
        getWrld()->getPlayer1()->setBdir(getWrld()->getPlayer2()->getBdir());
        getWrld()->getPlayer1()->setDirection(getWrld()->getPlayer2()->getDirection());
        getWrld()->getPlayer2()->setBdir(tempDir);
        getWrld()->getPlayer2()->setDirection(tempDirection);
        
        // change roll/walk state;
        bool state = getWrld()->getPlayer1()->getWaitingToMove();
        getWrld()->getPlayer1()->Waiting_to_move = getWrld()->getPlayer2()->getWaitingToMove();
        getWrld()->getPlayer2()->Waiting_to_move = state;
       
    }
}

void Player_Avatar::changeCoins(int numCoins){
    int x = m_coins + numCoins;
    if(x < 0){
        m_coins = 0;
    } else {
        m_coins += numCoins;
    }
}
void Player_Avatar::changeStars(int numStar){
    int x = m_stars + numStar;
    if(x < 0){
        m_stars = 0;
    } else {
        m_stars += numStar;
    }
}

void Player_Avatar::doSomething()
{
    if(Waiting_to_move){
        if(getTeleported()){
            if(!canMoveForward(getBdir())){
                int z = randInt(1, 4);
                if(z == 1 && canMoveForward(right)){
                        setDirection(0);
                        setBdir(right);
                } else if(z == 2 && canMoveForward(left)){
                        setDirection(180);
                        setBdir(left);
                } else if(z == 3 && canMoveForward(up)){
                        setDirection(0);
                        setBdir(up);
                } else {
                        setDirection(0);
                        setBdir(down);
                }
            }
            setTeleported(false);
        }
        
        switch (getWrld()->getAction(getPnum())) {
            case ACTION_ROLL: {
                int die_roll = randInt(1, 10);
                ticks_to_move = die_roll * 8;
                Waiting_to_move = false;
                break;
            }
            case ACTION_FIRE: {
                if(!vortex){
                    return;
                } else{
                    getWrld()->addVortex(getX()/16, getY()/16, getBdir());
                    getWrld()->playSound(SOUND_PLAYER_FIRE);
                    vortex = false;
                }
            }
            case ACTION_NONE:
                break;
        }
    }

    if(!Waiting_to_move){
        moveCount++;
        int x = getX();
        int y = getY();
        int count = checkFork(getBdir(), getX(), getY());
        
        bool sq;

        if(getWrld()->getBoard()->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::up_dir_square || getWrld()->getBoard()->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::down_dir_square || getWrld()->getBoard()->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::right_dir_square || getWrld()->getBoard()->getContentsOf(x/SPRITE_WIDTH, y/SPRITE_HEIGHT) == Board::left_dir_square){
            sq = false;
        } else{
            sq = true;
        }
        if(count > 1 && x % 16 == 0 && y % 16 == 0 && sq && moveCount > 1){
            int input = getWrld()->getAction(getPnum());
            switch (input) {
                case ACTION_UP:
                    if((!canMoveForward(up)) || getBdir() == 270){
                        return;
                    }
                    setDirection(0);
                    setBdir(90);
                    break;
                case ACTION_DOWN:
                    if((!canMoveForward(down)) || getBdir() == 90){
                        return;
                    }
                    setDirection(0);
                    setBdir(270);
                    break;
                case ACTION_LEFT:
                    if((!canMoveForward(left)) || getBdir() == 0){
                        return;
                    }
                    setDirection(180);
                    setBdir(180);
                    break;
                case ACTION_RIGHT:
                    if((!canMoveForward(right)) || getBdir() == 180){
                        return;
                    }
                    setDirection(0);
                    setBdir(0);
                    break;
                case ACTION_NONE:
                    return;
                default:
                    return;
            }
        }
        if(!canMoveForward(getBdir())){
            int x = getX();
            int y = getY();
            if(x % 16 == 0 && y % 16 == 0){
                x/=16;
                y/=16;
                if(getBdir() == 90 || getBdir() == 270){
                    if(getWrld()->getBoard()->getContentsOf(x+1, y) != Board::empty){
                        setDirection(0);
                        setBdir(0);
                    } else if(getWrld()->getBoard()->getContentsOf(x-1, y) != Board::empty){
                        setDirection(180);
                        setBdir(180);
                    }
                } else {
                    if(getWrld()->getBoard()->getContentsOf(x, y + 1) != Board::empty){
                        setDirection(0);
                        setBdir(90);
                    } else if(getWrld()->getBoard()->getContentsOf(x, y - 1) != Board::empty){
                        setDirection(0);
                        setBdir(270);
                    }
                }
            }
        }
        moveAtAngle(getBdir(), 2);
        ticks_to_move--;
        if(ticks_to_move == 0){
            Waiting_to_move = true;
        }
        return;
    }
}
    


///
/// PEACH IMPLEMENTATIONS
///

Peach::Peach(StudentWorld* sw, int startX, int startY)
: Player_Avatar(sw, IID_PEACH, startX, startY, 0){}

///
/// YOSHI IMPLEMENTATIONS
///

Yoshi::Yoshi(StudentWorld* sw, int startX, int startY)
: Player_Avatar(sw, IID_YOSHI, startX, startY, 0){}

///
/// BAD_GUY IMPLEMENTATIONS
///

BadGuy::BadGuy(StudentWorld* sw, int ID, int startX, int startY, int startD)
: Actor(sw, ID, startX, startY, startD, 1, 1.0), paused(true), pause_counter(180)
{setBdir(startD);}


///
/// BOWSER IMPLEMENTATIONS
///

Bowser::Bowser(StudentWorld* sw, int startX, int startY)
: BadGuy(sw, IID_BOWSER, startX, startY, 0){}

void Bowser::doSomething(){
    if(getPaused()){
        if(CheckLoc(getWrld()->getPlayer1()) && (getWrld()->getPlayer1()->getWaitingToMove())){
            if(newPlyr(getWrld()->getPlayer1())){
                int x = randInt(1, 2);
                if(x == 1){
                    getWrld()->getPlayer1()->setCoin(0);
                    getWrld()->getPlayer1()->setStar(0);
                    getWrld()->playSound(SOUND_BOWSER_ACTIVATE);
                }
                addTick(getWrld()->getPlayer1());
            }
        } else if(CheckLoc(getWrld()->getPlayer2()) && (getWrld()->getPlayer2()->getWaitingToMove())){
            if(newPlyr(getWrld()->getPlayer2())){
                int x = randInt(1, 2);
                if(x == 1){
                    getWrld()->getPlayer2()->setCoin(0);
                    getWrld()->getPlayer2()->setStar(0);
                    getWrld()->playSound(SOUND_BOWSER_ACTIVATE);
                }
                addTick(getWrld()->getPlayer2());
            }
        }
        setPcounter(-1);
        if(getPcounter() == 0){
            int squares_to_move = randInt(1, 10);
            setTicks(squares_to_move * 8);
            while(true){
                int z = randInt(1, 4);
                if(z == 1 && canMoveForward(right)){
                    setDirection(0);
                    setBdir(right);
                    break;
                } else if(z == 2 && canMoveForward(left)){
                    setDirection(180);
                    setBdir(left);
                    break;
                } else if(z == 3 && canMoveForward(up)){
                    setDirection(0);
                    setBdir(up);
                    break;
                } else {
                    setDirection(0);
                    setBdir(down);
                    break;
                }
            }
            if(!CheckLoc(getWrld()->getPlayer1())){
                resetTick(getWrld()->getPlayer1());
            }
            if(!CheckLoc(getWrld()->getPlayer2())){
                resetTick(getWrld()->getPlayer2());
            }
            setPaused(false);
        }
    }
    
    if(!getPaused()){
        int count = checkFork(getBdir(), getX(), getY());
        if(count > 1 && getX() % 16 == 0 && getY() % 16 == 0){
            while(true){
                int z = randInt(1, 4);
                if(z == 1 && canMoveForward(right)){
                    setDirection(0);
                    setBdir(right);
                    break;
                } else if(z == 2 && canMoveForward(left)){
                    setDirection(180);
                    setBdir(left);
                    break;
                } else if(z == 3 && canMoveForward(up)){
                    setDirection(0);
                    setBdir(up);
                    break;
                } else {
                    setDirection(0);
                    setBdir(down);
                    break;
                }
            }
        }
        if(!canMoveForward(getBdir()) && getX() % 16 == 0 && getY() % 16 == 0){
            if(getBdir() == 0 || getBdir() == 180){
                if(canMoveForward(up)){
                    setDirection(0);
                    setBdir(90);
                } else if(canMoveForward(down)){
                    setDirection(0);
                    setBdir(270);
                }
            } else if(getBdir() == 90 || getBdir() == 270){
                if(canMoveForward(right)){
                    setDirection(0);
                    setBdir(0);
                } else if(canMoveForward(left)){
                    setDirection(180);
                    setBdir(180);
                }
            }
        }
        moveAtAngle(getBdir(), 2);
        decrementTicks();
        if(getTicks() == 0){
            setPaused(true);
            resetPcount();
            int x = randInt(1, 4);
            if(x == 1){
                getWrld()->replaceSquare(getX()/16, getY()/16);
            }
        }
    }
}

///
/// BOO IMPLEMENTATIONS
///

Boo::Boo(StudentWorld* sw, int startX, int startY)
: BadGuy(sw, IID_BOO, startX, startY, 0){}

void Boo::doSomething(){
    if(getPaused()){
        if(CheckLoc(getWrld()->getPlayer1()) && (getWrld()->getPlayer1()->getWaitingToMove())){
            if(newPlyr(getWrld()->getPlayer1())){
                int x = randInt(1, 2);
                if(x == 1){
                    int t_coins = getWrld()->getPlayer1()->getCoins();
                    getWrld()->getPlayer1()->setCoin(getWrld()->getPlayer2()->getCoins());
                    getWrld()->getPlayer2()->setCoin(t_coins);
                } else if(x == 2){
                    int t_stars = getWrld()->getPlayer1()->getStars();
                    getWrld()->getPlayer1()->setStar(getWrld()->getPlayer2()->getStars());
                    getWrld()->getPlayer2()->setStar(t_stars);
                }
                getWrld()->playSound(SOUND_BOO_ACTIVATE);
                addTick(getWrld()->getPlayer1());
            }
        }
        else if(CheckLoc(getWrld()->getPlayer2()) && (getWrld()->getPlayer2()->getWaitingToMove())){
            if(newPlyr(getWrld()->getPlayer2())){
                int x = randInt(1, 2);
                if(x == 1){
                    int t_coins = getWrld()->getPlayer2()->getCoins();
                    getWrld()->getPlayer2()->setCoin(getWrld()->getPlayer1()->getCoins());
                    getWrld()->getPlayer1()->setCoin(t_coins);
                } else if(x == 2){
                    int t_stars = getWrld()->getPlayer2()->getStars();
                    getWrld()->getPlayer2()->setStar(getWrld()->getPlayer1()->getStars());
                    getWrld()->getPlayer1()->setStar(t_stars);
                }
                getWrld()->playSound(SOUND_BOO_ACTIVATE);
                addTick(getWrld()->getPlayer2());
            }
        }
        setPcounter(-1);
        if(getPcounter() == 0){
            int squares_to_move = randInt(1, 3);
            setTicks(squares_to_move * 8);
            while(true){
                int z = randInt(1, 4);
                if(z == 1 && canMoveForward(right)){
                    setDirection(0);
                    setBdir(right);
                    break;
                } else if(z == 2 && canMoveForward(left)){
                    setDirection(180);
                    setBdir(left);
                    break;
                } else if(z == 3 && canMoveForward(up)){
                    setDirection(0);
                    setBdir(up);
                    break;
                } else {
                    setDirection(0);
                    setBdir(down);
                    break;
                }
            }
            if(!CheckLoc(getWrld()->getPlayer1())){
                resetTick(getWrld()->getPlayer1());
            }
            if(!CheckLoc(getWrld()->getPlayer2())){
                resetTick(getWrld()->getPlayer2());
            }
            
            setPaused(false);
        }
    }
    if(!getPaused()){
        int count = checkFork(getBdir(), getX(), getY());
        if(count > 1 && getX() % 16 == 0 && getY() % 16 == 0){
            while(true){
                int z = randInt(1, 4);
                if(z == 1 && canMoveForward(right)){
                    setDirection(0);
                    setBdir(right);
                    break;
                } else if(z == 2 && canMoveForward(left)){
                    setDirection(180);
                    setBdir(left);
                    break;
                } else if(z == 3 && canMoveForward(up)){
                    setDirection(0);
                    setBdir(up);
                    break;
                } else {
                    setDirection(0);
                    setBdir(down);
                    break;
                }
            }
        }
        if(!canMoveForward(getBdir()) && getX() % 16 == 0 && getY() % 16 == 0){
            if(getBdir() == 0 || getBdir() == 180){
                if(canMoveForward(up)){
                    setDirection(0);
                    setBdir(90);
                } else if(canMoveForward(down)){
                    setDirection(0);
                    setBdir(270);
                }
            } else if(getBdir() == 90 || getBdir() == 270){
                if(canMoveForward(right)){
                    setDirection(0);
                    setBdir(0);
                } else if(canMoveForward(left)){
                    setDirection(180);
                    setBdir(180);
                }
            }
        }
        moveAtAngle(getBdir(), 2);
        decrementTicks();
        if(getTicks() == 0){
            setPaused(true);
            resetPcount();
        }
    }
    return;
}

///
///
///
/// SQUARE IMPLEMENTATIONS
///
///
///
///

Square::Square(StudentWorld* sw, int ID, int startX, int startY, int spritedir, int depth)
: Actor(sw, ID, startX, startY, spritedir, depth, 1.0){}

bool Actor::CheckLoc(Player_Avatar* player){
    if(getX() == player->getX() && getY() == player->getY()){
        return true;
    } else {
        return false;
    }
}

int Actor::returnTick(Player_Avatar *player){
    if(player == getWrld()->getPlayer1()){
        return countTick1;
    } else{
        return countTick2;
    }
}

void Actor::addTick(Player_Avatar *player){
    if(player == getWrld()->getPlayer1()){
        countTick1++;
    } else{
        countTick2++;
    }
}

void Actor::resetTick(Player_Avatar *player){
    if(player == getWrld()->getPlayer1()){
        countTick1 = 0;
    } else{
        countTick2 = 0;
    }
}

bool Actor::newPlyr(Player_Avatar* player){
    if(player == getWrld()->getPlayer1()){
        return countTick1 == 0;
    } else{
        return countTick2 == 0;
    }
}


///
/// COIN_SQUARE IMPLEMENTATIONS
///

Coin_Square::Coin_Square(StudentWorld* sw, int ID, int startX, int startY, int amount)
: Square(sw, ID, startX, startY, 0, 1), m_amount(amount){}

void Coin_Square::doSomething(){
    if(!isAlive()){
        return;
    }
    
    if(CheckLoc(getWrld()->getPlayer1()) && getWrld()->getPlayer1()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer1())){
            if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::blue_coin_square || getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::bowser || getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::boo || getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::player){
                getWrld()->getPlayer1()->changeCoins(getAmount());
                getWrld()->playSound(SOUND_GIVE_COIN);
            } else if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::red_coin_square){
                getWrld()->getPlayer1()->changeCoins(getAmount());
                getWrld()->playSound(SOUND_TAKE_COIN)   ;
            }
            addTick(getWrld()->getPlayer1());
        }
    }
    
    if(!CheckLoc(getWrld()->getPlayer1())){
        resetTick(getWrld()->getPlayer1());
    }


    if(CheckLoc(getWrld()->getPlayer2()) && getWrld()->getPlayer2()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer2())){
            if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::blue_coin_square){
                getWrld()->getPlayer2()->changeCoins(getAmount());
                getWrld()->playSound(SOUND_GIVE_COIN);
            } else if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::red_coin_square){
                getWrld()->getPlayer2()->changeCoins(getAmount());
                getWrld()->playSound(SOUND_TAKE_COIN);
            }
            addTick(getWrld()->getPlayer2());
        }
    }

    if(!CheckLoc(getWrld()->getPlayer2())){
        resetTick(getWrld()->getPlayer2());
    }
    
    return;
}

Red_Square::Red_Square(StudentWorld* sw, int startX, int startY)
: Coin_Square(sw, IID_RED_COIN_SQUARE, startX, startY, -3){}


Blue_Square::Blue_Square(StudentWorld* sw, int startX, int startY)
: Coin_Square(sw, IID_BLUE_COIN_SQUARE, startX, startY, 3){}

///
/// STAR_SQUARE IMPLEMENTATIONS
///

Star_Square::Star_Square(StudentWorld* sw, int startX, int startY)
: Square(sw, IID_STAR_SQUARE, startX, startY, 0, 1) {}


void Star_Square::doSomething()
{
    if(CheckLoc(getWrld()->getPlayer1())){
        if(newPlyr(getWrld()->getPlayer1())){
            if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::star_square){
                if(getWrld()->getPlayer1()->getCoins() < 20){
                    return;
                } else{
                    getWrld()->getPlayer1()->changeCoins(-20);
                    getWrld()->getPlayer1()->changeStars(1);
                    getWrld()->playSound(SOUND_GIVE_STAR);
                }
            }
            addTick(getWrld()->getPlayer1());
        }
    }
    
    if(!CheckLoc(getWrld()->getPlayer1())){
        resetTick(getWrld()->getPlayer1());
    }
    
    if(CheckLoc(getWrld()->getPlayer2())){
        if(newPlyr(getWrld()->getPlayer2())){
            if(getWrld()->getBoard()->getContentsOf(getX() / 16, getY() / 16) == Board::star_square){
                if(getWrld()->getPlayer2()->getCoins() < 20){
                    return;
                } else{
                    getWrld()->getPlayer2()->changeCoins(-20);
                    getWrld()->getPlayer2()->changeStars(1);
                    getWrld()->playSound(SOUND_GIVE_STAR);
                }
            }
            addTick(getWrld()->getPlayer2());
        }
    }
    
    if(!CheckLoc(getWrld()->getPlayer2())){
        resetTick(getWrld()->getPlayer2());
    }
    
}
///
/// DIRECTIONAL_SQUARE IMPLEMENTATIONS
///

Directional_Square::Directional_Square(StudentWorld* sw, int startX, int startY, int direction)
: Square(sw, IID_DIR_SQUARE, startX, startY, direction, 1), spriteDir(direction){}

void Directional_Square::doSomething()
{
    if(CheckLoc(getWrld()->getPlayer1())){
        if(getSpriteDir() == 0){
            getWrld()->getPlayer1()->setDirection(0);
            getWrld()->getPlayer1()->setBdir(0);
        } else if(getSpriteDir() == 180){
            getWrld()->getPlayer1()->setDirection(180);
            getWrld()->getPlayer1()->setBdir(180);
        } else if(getSpriteDir() == 90){
            getWrld()->getPlayer1()->setDirection(0);
            getWrld()->getPlayer1()->setBdir(90);
        } else if(getSpriteDir() == 270){
            getWrld()->getPlayer1()->setDirection(0);
            getWrld()->getPlayer1()->setBdir(270);
        }
    }
    
    if(CheckLoc(getWrld()->getPlayer2())){
        if(getSpriteDir() == 0){
            getWrld()->getPlayer2()->setDirection(0);
            getWrld()->getPlayer2()->setBdir(0);
        } else if(getSpriteDir() == 180){
            getWrld()->getPlayer2()->setDirection(180);
            getWrld()->getPlayer2()->setBdir(180);
        } else if(getSpriteDir() == 90){
            getWrld()->getPlayer2()->setDirection(0);
            getWrld()->getPlayer2()->setBdir(90);
        } else if(getSpriteDir() == 270){
            getWrld()->getPlayer2()->setDirection(0);
            getWrld()->getPlayer2()->setBdir(270);
        }
    }
    
    return;
}

///
/// BANK_SQUARE IMPLEMENTATIONS
///

Bank_Square::Bank_Square(StudentWorld* sw, int startX, int startY)
: Square(sw, IID_BANK_SQUARE, startX, startY, 0, 1){}
void Bank_Square::doSomething()
{
    if(CheckLoc(getWrld()->getPlayer1()) && getWrld()->getPlayer1()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer1())){
            getWrld()->getPlayer1()->changeCoins(getWrld()->getBankMoney());
            getWrld()->resetBank();
            addTick(getWrld()->getPlayer1());
            getWrld()->playSound(SOUND_WITHDRAW_BANK);
        }
    }
    if(!CheckLoc(getWrld()->getPlayer1())){
        resetTick(getWrld()->getPlayer1());
    }
    
    if(CheckLoc(getWrld()->getPlayer1()) && (!getWrld()->getPlayer1()->getWaitingToMove())){
        if(getWrld()->getPlayer1()->getCoins() < 5){
            int x = getWrld()->getPlayer1()->getCoins();
            getWrld()->getPlayer1()->changeCoins(-x);
            getWrld()->changeBankMoney(x);
            getWrld()->playSound(SOUND_DEPOSIT_BANK);
        } else{
            getWrld()->getPlayer1()->changeCoins(-5);
            getWrld()->changeBankMoney(5);
            getWrld()->playSound(SOUND_DEPOSIT_BANK);
        }
    }
    
    
    if(CheckLoc(getWrld()->getPlayer2()) && getWrld()->getPlayer2()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer2())){
            getWrld()->getPlayer2()->changeCoins(getWrld()->getBankMoney());
            getWrld()->resetBank();
            addTick(getWrld()->getPlayer2());
            getWrld()->playSound(SOUND_WITHDRAW_BANK);
        }
    }
    if(!CheckLoc(getWrld()->getPlayer2())){
        resetTick(getWrld()->getPlayer2());
    }
    
    if(CheckLoc(getWrld()->getPlayer2()) && (!getWrld()->getPlayer2()->getWaitingToMove())){
        if(getWrld()->getPlayer2()->getCoins() < 5){
            int x = getWrld()->getPlayer2()->getCoins();
            getWrld()->getPlayer2()->changeCoins(-x);
            getWrld()->changeBankMoney(x);
            getWrld()->playSound(SOUND_DEPOSIT_BANK);
        } else{
            getWrld()->getPlayer2()->changeCoins(-5);
            getWrld()->changeBankMoney(5);
            getWrld()->playSound(SOUND_DEPOSIT_BANK);
        }
    }
    
    
}

///
/// EVENT_SQUARE IMPLEMENTATIONS
///

Event_Square::Event_Square(StudentWorld* sw, int startX, int startY)
: Square(sw, IID_EVENT_SQUARE, startX, startY, 0, 1){}
void Event_Square::doSomething()
{
    if(CheckLoc(getWrld()->getPlayer1()) && getWrld()->getPlayer1()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer1())){
            int x = randInt(1, 3);
            switch (x) {
                case 1:
                    if(newPlyr(getWrld()->getPlayer1())){
                        getWrld()->getPlayer1()->teleport();
                        getWrld()->playSound(SOUND_PLAYER_TELEPORT);
                        getWrld()->getPlayer1()->setTeleported(true);
                    }
                    break;
                case 2:
                    addTick(getWrld()->getPlayer2());
                    getWrld()->getPlayer1()->SwapPosition();
                    getWrld()->playSound(SOUND_PLAYER_TELEPORT);
                    break;
                case 3:
                    addTick(getWrld()->getPlayer1());
                    if(!getWrld()->getPlayer1()->getVortex()){
                        getWrld()->getPlayer1()->giveVortex();
                        getWrld()->playSound(SOUND_GIVE_VORTEX);
                    }
                    break;
            }
        }
    }
    else if(CheckLoc(getWrld()->getPlayer2()) && getWrld()->getPlayer2()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer2())){
            int x = randInt(1, 3);
            switch (x) {
                case 1:
                    if(newPlyr(getWrld()->getPlayer2())){
                        getWrld()->getPlayer2()->teleport();
                        getWrld()->playSound(SOUND_PLAYER_TELEPORT);
                        getWrld()->getPlayer2()->setTeleported(true);
                    }
                    break;
                case 2:
                    addTick(getWrld()->getPlayer1());
                    getWrld()->getPlayer2()->SwapPosition();
                    getWrld()->playSound(SOUND_PLAYER_TELEPORT);
                    break;
                case 3:
                    addTick(getWrld()->getPlayer2());
                    if(!getWrld()->getPlayer2()->getVortex()){
                        getWrld()->getPlayer2()->giveVortex();
                        getWrld()->playSound(SOUND_GIVE_VORTEX);
                    }
                    break;
            }
        }
    }
    
    if(!CheckLoc(getWrld()->getPlayer1())){
        resetTick(getWrld()->getPlayer1());
    }
    
    if(!CheckLoc(getWrld()->getPlayer2())){
        resetTick(getWrld()->getPlayer2());
    }
}
///
/// DROPPING_SQUARE IMPLEMENTATIONS
///

Dropping_Square::Dropping_Square(StudentWorld* sw, int startX, int startY)
: Square(sw, IID_DROPPING_SQUARE, startX, startY, 0, 1){}
void Dropping_Square::doSomething()
{
    if(CheckLoc(getWrld()->getPlayer1()) && getWrld()->getPlayer1()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer1())){
            int x = randInt(1, 2);
            switch (x) {
                case 1:
                    getWrld()->getPlayer1()->changeCoins(-10);
                    getWrld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                    break;
                case 2:
                    getWrld()->getPlayer1()->changeStars(-1);
                    getWrld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                    break;
            }
            addTick(getWrld()->getPlayer1());
        }
    }
    if(!CheckLoc(getWrld()->getPlayer1())){
        resetTick(getWrld()->getPlayer1());
    }
    
    
    if(CheckLoc(getWrld()->getPlayer2()) && getWrld()->getPlayer2()->getWaitingToMove()){
        if(newPlyr(getWrld()->getPlayer2())){
            int x = randInt(1, 2);
            switch (x) {
                case 1:
                    getWrld()->getPlayer2()->changeCoins(-10);
                    getWrld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                    break;
                case 2:
                    getWrld()->getPlayer2()->changeStars(-1);
                    getWrld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                    break;
            }
            addTick(getWrld()->getPlayer2());
        }
    }
    if(!CheckLoc(getWrld()->getPlayer2())){
        resetTick(getWrld()->getPlayer2());
    }
}

Vortex::Vortex(StudentWorld* sw, int startX, int startY, int startD)
: Square(sw, IID_VORTEX, startX, startY, 0, 0){setBdir(startD);}

void Vortex::doSomething(){
    if(!isAlive()){
        return;
    }else{
        if(getX() <= 0 || getX() >= VIEW_WIDTH || getY() <= 0 || getY() >= VIEW_HEIGHT){
            setDead();
            return;
        }
        if(getWrld()->VortexConnection(getX(), getY())){
            getWrld()->playSound(SOUND_HIT_BY_VORTEX);
            setDead();
        }
        moveAtAngle(getBdir(), 2);
    }
}

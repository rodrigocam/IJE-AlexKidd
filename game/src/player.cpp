#include "player.hpp"

Player::Player(std::string spritePath, int positionX, int positionY,
                                       int width, int height) : GameObject(spritePath,
                                                                           positionX,
                                                                           positionY,
                                                                           width, height){
    animator = new Animation(spritePath, 6, 6, 0.1);

    animator->addAction("right",1,3);
    animator->addAction("left",20,22);
    animator->addAction("up_right",5,5);
    animator->addAction("up_left",18,18);
    animator->addAction("kick_right",6,6);
    animator->addAction("kick_left",17,17);
    animator->addAction("downRight",15,16);
    animator->addAction("downLeft", 32, 33);
    animator->addAction("down_idle_right", 15,15);
    animator->addAction("down_idle_left", 33,33);
    animator->addAction("idle_right",0,0);
    animator->addAction("idle_left",23,23);

    idleAnimationNumber = 0;
    idleDownAnimationNumber = 15;
    isStanding = true;
    isJumping = false;
    isFalling = false;
    movingToRight = true;
    blockChangeDirection = false;
    movementIsBlock = false;
    isCollidingRight = false;
    isCollidingLeft = false;
}

Player::~Player(){}

void Player::update(double timeElapsed){
    double incX;
    double incY = 0.15*timeElapsed;

    if(isStanding){
        incX = 0.25*timeElapsed;
    }else{
        incX = 0.15*timeElapsed;
    }

    verifyLayDown();
    walkInY(incX, incY);
    walkInX(incX, incY);

    animator->update();
}

void Player::draw(){
    animator->draw(getPositionX(), getPositionY());
}

void Player::walkInX(double & incX, double &incY){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
        incX = incX;
        idleAnimationNumber = 0;
        movingToRight = true;
        if(isStanding){
            animator->setInterval("right");
        }else{
            animator->setInterval("downRight");
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
        incX = incX * (0-1);
        idleAnimationNumber = 15;
        movingToRight = false;
        if(isStanding){
            animator->setInterval("left");
        }else{
            animator->setInterval("downLeft");
        }
    }else {
        incX = 0;
        if(idleAnimationNumber == 0 && !isJumping){
            animator->setInterval("idle_right");
            if(!isStanding){
                animator->setInterval("down_idle_right");
            }
            movingToRight = true;
        }else if(!isJumping){
            animator->setInterval("idle_left");
            if(!isStanding){
                animator->setInterval("down_idle_left");
            }
            movingToRight = false;
        }
    }
    if(movingToRight && getPositionX() >= 350 && movementIsBlock){
        incX = 0;
    }else if(!movingToRight && getPositionX() <= 300 && movementIsBlock){
        incX = 0;
    }
    setPositionX(getPositionX()+incX);
    if(CollisionManager::instance.verifyCollisionWithGround(this)){
        //std::cout << "AQ" << std::endl;
        isFalling = false;
        setPositionX(getPositionX()+(incX*(0-1)));
    }
    if(CollisionManager::instance.verifyRightCollisionWithGround(this)){
        //std::cout << "AQ" << std::endl;
        std::cout << "LIXO1" << std::endl;
        isCollidingRight = true;
    }else{
        std::cout << "AQ1" << std::endl;
        isCollidingRight = false;
    }
    if(CollisionManager::instance.verifyLeftCollisionWithGround(this)){
        std::cout << "LIXO2" << std::endl;
        isCollidingLeft = true;
    }else{
        std::cout << "AQ2" << std::endl;
        isCollidingLeft = false;
    }
}

void Player::walkInY(double & incX, double & incY){
    setPositionY(getPositionY()+(incY*1.5));
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)){
        if(!isFalling){
            isJumping = true;
            if(idleAnimationNumber == 0){
                animator->setInterval("up_right");
            }else{
                animator->setInterval("up_left");
            }
            setPositionY(getPositionY()+incY*(0-3));
        }
    }
    if(isJumping){
        if(InputManager::instance.isKeyReleased(InputManager::KeyPress::KEY_PRESS_UP)){
            //std::cout << "AQ" << std::endl;
            isFalling = true;
            if(idleAnimationNumber == 0){
                animator->setInterval("kick_right");
            }else{
                animator->setInterval("kick_left");
            }
        }
    }
    if(CollisionManager::instance.verifyCollisionWithGround(this)){
        isFalling = false;
        isJumping = false;
        setPositionY(getPositionY()+(incY*(0-1.5)));
    }
}

void Player::verifyLayDown(){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_DOWN)){
        isStanding = false;
    }else if(InputManager::instance.isKeyReleased(InputManager::KeyPress::KEY_PRESS_DOWN)){
        isStanding = true;
    }
}

void Player::blockMovement(){
    movementIsBlock = true;
}

void Player::unblockMovement(){
    movementIsBlock = false;
}

std::string Player::getPlayerStatus(){
    if(isStanding){
        return "standing";
    }else{
        return "laydown";
    }
}

bool Player::getCollideRight(){
    return isCollidingRight;
}

bool Player::getCollideLeft(){
    return isCollidingLeft;
}

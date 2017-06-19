#include "player.hpp"

Player::Player(std::string spritePath, int positionX, int positionY,
                                       int width, int height) : GameObject(spritePath,
                                                                           positionX,
                                                                           positionY,
                                                                           width, height){
    animator = new Animation(spritePath, 6, 6, 0.1);

    animator->addAction("right",1,3);
    animator->addAction("left",20,22);
    animator->addAction("up",5,6);
    animator->addAction("downRight",15,16);
    animator->addAction("downLeft", 32, 33);
    animator->addAction("down_idle_right", 15,15);
    animator->addAction("down_idle_left", 33,33);
    animator->addAction("idle_right",0,0);
    animator->addAction("idle_left",23,23);

    idleAnimationNumber = 0;
    idleDownAnimationNumber = 15;
    isStanding = true;
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
        incX = 0.05*timeElapsed;
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
        if(idleAnimationNumber == 0){
            animator->setInterval("idle_right");
            if(!isStanding){
                animator->setInterval("down_idle_right");
            }
            movingToRight = true;
        }else{
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
        setPositionX(getPositionX()+(incX*(0-1)));
    }
    if(CollisionManager::instance.verifyRightCollisionWithGround(this)){
        std::cout << "AQ" << std::endl;
        isCollidingRight = true;
    }else{
        isCollidingRight = false;
    }
    if(CollisionManager::instance.verifyLeftCollisionWithGround(this)){
        isCollidingLeft = true;
    }else{
        isCollidingLeft = false;
    }
}

void Player::walkInY(double & incX, double & incY){
    setPositionY(getPositionY()+(incY));
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)){
        std::cout << "AQ" << std::endl;
        animator->setInterval("right");
        setPositionY(getPositionY()+incY*(0-2));
    }
    if(CollisionManager::instance.verifyCollisionWithGround(this)){
        setPositionY(getPositionY()+(incY*(0-1)));
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

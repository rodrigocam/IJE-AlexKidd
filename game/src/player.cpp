#include "player.hpp"

Player::Player(std::string spritePath, int positionX, int positionY,
                                       int width, int height) : GameObject(spritePath,
                                                                           positionX,
                                                                           positionY,
                                                                           width, height){
    animator = new Animation(spritePath, 6, 6, 0.1);

    animator->addAction("right",1,3);
    animator->addAction("left",20,22);
    animator->addAction("downRight",15,16);
    animator->addAction("downLeft", 32, 33);
    animator->addAction("down_idle_right", 15,15);
    animator->addAction("down_idle_left", 33,33);
    animator->addAction("idle_right",0,0);
    animator->addAction("idle_left",23,23);

    idleAnimationNumber = 0;
    idleDownAnimationNumber = 15;
    isStanding = true;
    blockChangeDirection = false;
}

Player::~Player(){}

void Player::update(double timeElapsed){
    double incX;

    if(isStanding){
        incX = 0.10*timeElapsed;
    }else{
        incX = 0.05*timeElapsed;
    }

    verifyLayDown();
    walkInX(incX);

    animator->update();
}

void Player::draw(){
    animator->draw(getPositionX(), getPositionY());
}

void Player::walkInX(double & incX){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
        incX = incX;
        idleAnimationNumber = 0;
        if(isStanding){
            animator->setInterval("right");
        }else{
            animator->setInterval("downRight");
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
        incX = incX * (0-1);
        idleAnimationNumber = 15;
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
        }else{
            animator->setInterval("idle_left");
            if(!isStanding){
                animator->setInterval("down_idle_left");
            }
        }
    }
    setPositionX(getPositionX()+incX);
}

void Player::verifyLayDown(){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_DOWN)){
        isStanding = false;
    }else if(InputManager::instance.isKeyReleased(InputManager::KeyPress::KEY_PRESS_DOWN)){
        isStanding = true;
    }
}

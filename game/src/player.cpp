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
}

Player::~Player(){}

void Player::update(double timeElapsed){
    auto incY = 0.15*timeElapsed;
    auto incX = 0.15*timeElapsed;

    walkInX(incX);
    layDown(incX);
    //walkInY(incY, incX);

    if(incX == 0 && incY == 0){
        if(idleAnimationNumber == 0){
          animator->setInterval("idle_right");
        }else{
          animator->setInterval("idle_left");
        }
    }
    animator->update();
}

void Player::draw(){
    animator->draw(getPositionX(), getPositionY());
}

void Player::walkInX(double & incX){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
        incX = incX;
        idleAnimationNumber = 0;
        idleDownAnimationNumber = 15;
        if(animator->getCurAction().compare("down_idle_right") == 0 ||
           animator->getCurAction().compare("downRight") == 0){
            std::cout << "LALA" << std::endl;
            animator->setInterval("downRight");
        }else{
            animator->setInterval("right");
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
        incX = incX * (0-1);
        idleAnimationNumber = 23;
        idleDownAnimationNumber = 33;
        if(animator->getCurAction().compare("down_idle_left") == 0){
            animator->setInterval("downLeft");
        }else{
            animator->setInterval("left");
        }
    }
    else {
        incX = 0;
        if(idleAnimationNumber == 0){
            animator->setInterval("idle_right");
        }else{
            animator->setInterval("idle_left");
        }
    }
    setPositionX(getPositionX()+incX);
}

void Player::walkInY(double & incY, double incX){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)){
        incY = incY * (0-1);
        idleAnimationNumber = 5;
        if(incX == 0){
            animator->setInterval("up");
        }
    }
    else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)){
        incY = incY;
        idleAnimationNumber = 0;
        if(incX == 0){
            animator->setInterval("down");
        }
    }
    else {
        incY = 0;
    }
    setPositionY(getPositionY()+incY);
}

void Player::layDown(double & incX){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_DOWN)){
        if(idleDownAnimationNumber == 15){
            animator->setInterval("down_idle_right");
        }else{
            animator->setInterval("down_idle_left");
        }
        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
            animator->setInterval("downRight");
        }else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
            animator->setInterval("downLeft");
        }
    }
}

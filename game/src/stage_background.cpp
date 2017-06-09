#include "stage_background.hpp"

StageBackground::StageBackground(std::string spritePath, int initialPosition, Player *player){
    sprite = new Sprite(spritePath);
    spritePosition = initialPosition;
    playerReference = player;
}

StageBackground::~StageBackground(){}

void StageBackground::draw(){
    sprite->draw(spritePosition, 0);
}

void StageBackground::update(double timeElapsed){
    double increment;
    if(playerReference->getPlayerStatus().compare("standing") == 0){
        increment = 0.20*timeElapsed;
    }else{
        increment = 0.10*timeElapsed;
    }
    moveBackground(increment);
    draw();
}

void StageBackground::moveBackground(double & increment){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT) &&
       playerReference->getPositionX() >= 350){
        if(getSpritePosition() > -2560 ){
            playerReference->blockMovement();
            increment = increment * (0-1);
        }else{
            playerReference->unblockMovement();
            increment = 0;
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT) &&
            playerReference->getPositionX() <= 300){
        if(getSpritePosition() < 0){
            playerReference->blockMovement();
            increment = increment;
        }else{
            playerReference->unblockMovement();
            increment = 0;
        }
    }
    else {
        increment = 0;
    }

    setSpritePosition(getSpritePosition()+increment);
}

int StageBackground::getSpritePosition(){
    return spritePosition;
}

void StageBackground::setSpritePosition(int newPosition){
    spritePosition = newPosition;
}

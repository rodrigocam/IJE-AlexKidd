#include "stage_background.hpp"

StageBackground::StageBackground(std::string spritePath, int initialPosition){
    sprite = new Sprite(spritePath);
    spritePosition = initialPosition;
}

StageBackground::~StageBackground(){}

void StageBackground::draw(){
    sprite->draw(spritePosition, 0);
}

void StageBackground::update(double timeElapsed){
    auto increment = 0.15*timeElapsed;
    moveBackground(increment);
    draw();
}

void StageBackground::moveBackground(double & increment){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)){
        if(getSpritePosition() > -2560 ){
            increment = increment * (0-1);
        }else{
            increment = 0;
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)){
        if(getSpritePosition() < 0){
            increment = increment;
        }else{
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

#include "stage_background.hpp"

StageBackground::StageBackground(std::string spritePath, int initialPosition,
                                                        Player *player){
    sprite = new Sprite(spritePath);
    spritePosition = initialPosition;
    playerReference = player;

    groundList.push_back(new Ground(0,387,1152,100));
    groundList.push_back(new Ground(1152,419,243,100));
    groundList.push_back(new Ground(1395,387,765,100));
    groundList.push_back(new Ground(2160,419,195,100));
    groundList.push_back(new Ground(2355,387,1152,100));

    // wallList.push_back(new Wall(1160,375,10,30));
    // wallList.push_back(new Wall(1440,375,1,10));

    for(auto ground: groundList){
        //std::cout << "entrou" << std::endl;
        CollisionManager::instance.addGround(ground);
    }

    // for(auto wall: wallList){
    //     std::cout << "entrou" << std::endl;
    //     CollisionManager::instance.addWall(wall);
    // }
}

StageBackground::~StageBackground(){}

void StageBackground::draw(){
    sprite->draw(spritePosition, 0);
    for(auto ground: groundList){
        //std::cout << ground->getWidth() << std::endl;
        ground->GameObject::draw(ground->getGroundPositionX(), ground->getPositionY());
    }
}

void StageBackground::update(double timeElapsed){
    double increment;
    if(playerReference->getPlayerStatus().compare("standing") == 0){
        increment = 0.20*timeElapsed;
    }else{
        increment = 0.10*timeElapsed;
    }
    moveBackground(increment);
}

void StageBackground::moveBackground(double & increment){
    if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT) &&
       playerReference->getPositionX() >= 350){
        if(getSpritePosition() > -2558 ){
            playerReference->blockMovement();
            increment = increment * (0-1);
            //std::cout << "FIRST " << increment << std::endl;
        }else{
            playerReference->unblockMovement();
            increment = 0;
        }
    }
    else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT) &&
            playerReference->getPositionX() <= 300){
        if(getSpritePosition() < -2){
            playerReference->blockMovement();
            increment = increment;
            //std::cout << "SECOND " << increment << std::endl;
        }else{
            playerReference->unblockMovement();
            increment = 0;
        }
    }
    else {
        increment = 0;
    }
    //std::cout << "INCREMENT " << increment << std::endl;
    setSpritePosition(getSpritePosition()+increment);
    groundList[0]->setGroundPositionX(groundList[0]->getGroundPositionX()+increment);
    for(unsigned int i=1; i<groundList.size(); i++){
        groundList[i]->setGroundPositionX(groundList[i-1]->getGroundPositionX()+groundList[i-1]->getWidth());
    }
    // int i = 0;
    // for(auto ground : groundList) {
    //     (*ground).setGroundPositionX((*ground).getGroundPositionX()+increment);
    //     std::cout << "POSITION " << i << " " << (*ground).getGroundPositionX() << std::endl;
    //     i++;
    // }
}

int StageBackground::getSpritePosition(){
    return spritePosition;
}

void StageBackground::setSpritePosition(int newPosition){
    spritePosition = newPosition;
}

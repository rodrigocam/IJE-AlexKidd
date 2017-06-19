#include "ground.hpp"

using namespace engine;

Ground::Ground(double positionX, double positionY,int width, int height) : GameObject(positionX,
                                                                                  positionY,
                                                                                  width,
                                                                                  height){
    groundPositionX = positionX;
}

Ground::~Ground(){}

void Ground::draw(){
    // SDL_SetRenderDrawColor(WindowManager::getGameCanvas(), 255, 0, 0, 255);
    // std::cout << (*rect).x << std::endl;
    // SDL_RenderDrawRect(WindowManager::getGameCanvas(), rect);
}

void Ground::update(double timeElapsed){

}

void Ground::moveGround(){

}

void Ground::setGroundPositionX(int newPosition){
    groundPositionX = newPosition;
    setPositionX(groundPositionX);
}

int Ground::getGroundPositionX(){
    return groundPositionX;
}

#include "wall.hpp"
#include "log.h"

Wall::Wall(double positionX, double positionY, int width, int height) : GameObject(positionX,
                                                                                   positionY,
                                                                                   width,
                                                                                   height){

}

Wall::~Wall(){}
void Wall::update(double timeElapsed){
    timeElapsed = timeElapsed;
}

void Wall::draw(){

}

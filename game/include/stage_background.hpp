#ifndef STAGE_BACKGROUND_HPP
#define STAGE_BACKGROUND_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "sprite.hpp"

#include <iostream>
#include <string>

using namespace engine;

class StageBackground{
public:
    StageBackground(std::string spritePath, int initialPosition);
    ~StageBackground();
    void update(double timeElapsed);
    void draw();
    void setSpritePosition(int newPosition);
    int getSpritePosition();

private:
    Sprite *sprite;
    int spritePosition;
    void moveBackground(double &increment);
};

#endif

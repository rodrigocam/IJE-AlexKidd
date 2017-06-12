#ifndef STAGE_BACKGROUND_HPP
#define STAGE_BACKGROUND_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "wall.hpp"

#include <iostream>
#include <string>

using namespace engine;

class StageBackground{
public:
    StageBackground(std::string spritePath, int initialPosition,
                                            Player *player);
    ~StageBackground();
    void update(double timeElapsed);
    void draw();
    void setSpritePosition(int newPosition);
    int getSpritePosition();

private:
    Sprite *sprite;
    Player *playerReference;
    std::vector<Ground*> groundList;
    std::vector<Wall*> wallList;
    int spritePosition;
    void moveBackground(double &increment);
};

#endif

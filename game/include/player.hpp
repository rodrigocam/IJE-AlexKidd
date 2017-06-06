#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "engine.hpp"
#include "game_object.hpp"
#include "animation.hpp"
#include "input_manager.hpp"

using namespace engine;

class Player: public GameObject{
public:
    Player(std::string spritePath, int positionX, int positionY, int width, int height);
    ~Player();
    void update(double timeElapsed);
    void draw();

private:
    Animation* animator;
    int idleAnimationNumber;
    int idleDownAnimationNumber;
    void walkInX(double & incX);
    void walkInY(double & incY, double incX);
    void layDown(double & incX);
};

#endif

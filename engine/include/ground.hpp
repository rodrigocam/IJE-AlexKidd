#ifndef GROUND_HPP
#define GROUND_HPP

#include "game_object.hpp"
#include <utility>

namespace engine{
    class Ground: public GameObject{
    public:
        Ground(double positionX, double positionY,int width, int height);
        ~Ground();
        void draw();
        void update(double timeElapsed);
        void moveGround();
        void setGroundPositionX(int newPosition);
        int getGroundPositionX();
    private:
        int groundPositionX;
    };
}

#endif

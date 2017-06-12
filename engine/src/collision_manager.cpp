#include "collision_manager.hpp"
#include "log.h"

using namespace engine;

CollisionManager CollisionManager::instance;

    void CollisionManager::addWall(GameObject* g){
        wallList.push_back(g);
    }

    void CollisionManager::addEnemy(GameObject* g){
        enemyList.push_back(g);
    }

    void CollisionManager::addGround(GameObject* g){
        groundList.push_back(g);
    }

    void CollisionManager::addBox(GameObject* g){
        boxList.push_back(g);
    }

    bool CollisionManager::verifyCollisionWithWalls(GameObject* g1){
        for(GameObject * wall : wallList) {
            if(verifyCollision(wall, g1)){
                return true;
            }
        }
        return false;
    }

    bool CollisionManager::verifyCollisionWithEnemies(GameObject* g1){
        for(GameObject * enemy : enemyList) {
            if(verifyCollision(enemy, g1)){
                return true;
            }
        }
        return false;
    }

    GameObject* CollisionManager::verifyCollisionWithBoxes(GameObject* g1){
        for(GameObject * box : boxList) {
            if(verifyCollision(box, g1)){
                return box;
            }
        }
        return NULL;
    }

    bool CollisionManager::verifyCollisionWithGround(GameObject* g1){
        for(GameObject * ground : groundList) {
            if(verifyCollision(ground, g1)){
                return true;
            }
        }
        return false;
    }

    bool CollisionManager::verifyLateralCollisionWithGround(GameObject* g1){
        for(GameObject * ground : groundList) {
            if(verifyLateralCollision(ground, g1)){
                return true;
            }
        }
        return false;
    }

    void CollisionManager::resetLists(){
        wallList.clear();
        enemyList.clear();
        groundList.clear();
        boxList.clear();
    }

    bool CollisionManager::verifyCollision( GameObject* g1, GameObject* g2){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA;
        int leftB, rightB, topB, bottomB;

        //Calculate the sides of rect A
        leftA = g1->getPositionX();
        rightA = leftA + g1->getWidth();
        topA = g1->getPositionY();
        bottomA = topA + g1->getHeight();

        //Calculate the sides of rect B
        leftB = g2->getPositionX();
        rightB = leftB + g2->getWidth();
        topB = g2->getPositionY();
        bottomB = topB + g2->getHeight();

        /*std::cout << "BOTTOM A " << bottomA << " TOP B " << topB << std::endl;
        std::cout << "TOP A " << topA << "BOTTOM B " << bottomB << std::endl;
        std::cout << "RIGHT A " << rightA << " left B " << leftB << std::endl;
        std::cout << "LEFT A " << leftA << "RIGHT B " << rightB << std::endl;*/

        //If any of the sides from A are outside of B
        if( bottomA <= topB ){ return false;}
        if( topA >= bottomB ){ return false;}
        if( rightA <= leftB ){ return false;}
        if( leftA >= rightB ){ return false;}
        //If none of the sides from A are outside B
        //std::cout << "COLIDIU" << std::endl;
        return true;
    }

    bool CollisionManager::verifyLateralCollision( GameObject* g1, GameObject* g2){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA;
        int leftB, rightB, topB, bottomB;

        //Calculate the sides of rect A
        leftA = g1->getPositionX();
        rightA = leftA + g1->getWidth();
        topA = g1->getPositionY();
        bottomA = topA + g1->getHeight();

        //Calculate the sides of rect B
        leftB = g2->getPositionX();
        rightB = leftB + g2->getWidth();
        topB = g2->getPositionY();
        bottomB = topB + g2->getHeight();

        // if( rightA <= leftB ){ return false;}
        // if( leftA >= rightB ){ return false;}

        //std::cout << "A " << topA << std::endl;
        //std::cout << "B " << bottomB << std::endl;
        //abs(bottomB-topA) >= 50
        if( rightA <= leftB ){ return false;}
        if( leftA >= rightB ){ return false;}

        return true;
    }

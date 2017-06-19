#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include <stdlib.h>
#include "engine.hpp"
#include "game_object.hpp"

using namespace engine;

class CollisionManager{
public:
    bool verifyCollisionWithWalls(GameObject* g);
    bool verifyCollisionWithEnemies(GameObject* g);
    bool verifyCollisionWithGround(GameObject* g);
    bool verifyRightCollisionWithGround(GameObject* g);
    bool verifyLeftCollisionWithGround(GameObject* g);
    GameObject* verifyCollisionWithBoxes(GameObject* g);
    bool verifyCollision(GameObject* g1, GameObject* g2);
    bool verifyRightCollision(GameObject* g1, GameObject* g2);
    bool verifyLeftCollision(GameObject* g1, GameObject* g2);
    void addWall(GameObject* g);
    void addEnemy(GameObject* g);
    void addGround(GameObject* g);
    void addBox(GameObject* g);
    void resetLists();
    static CollisionManager instance;
private:
    std::vector<GameObject*> wallList;
    std::vector<GameObject*> enemyList;
    std::vector<GameObject*> groundList;
    std::vector<GameObject*> boxList;
};

#endif

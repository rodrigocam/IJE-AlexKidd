#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "stage_background.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "wall.hpp"

using namespace engine;

class GameScene: public Scene{
public:
    GameScene(int id);
    ~GameScene();
    void load();
    void draw();
    void update(double timeElapsed);
    void unload();
private:
    std::vector<GameObject*> gameObjectsList;
    std::vector<StageBackground*> stageBackgroundList;
    std::vector<Ground*> groundList;
    std::vector<Wall*> wallList;
    Player* player;
    StageBackground *stageOneBackground;
};

#endif

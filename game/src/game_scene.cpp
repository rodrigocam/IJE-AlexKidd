#include "game_scene.hpp"
#include <typeinfo>

GameScene::GameScene(int id) : Scene(id){

}

GameScene::~GameScene(){}

void GameScene::draw(){
    for(auto gameObject : gameObjectsList) {
        (*gameObject).draw();
    }
}

void GameScene::update(double timeElapsed){
    for(auto gameObject : gameObjectsList) {
        (*gameObject).update(timeElapsed);
    }
    for (auto stageBackground : stageBackgroundList){
        (*stageBackground).update(timeElapsed);
    }
}

void GameScene::load(){
    stageBackgroundList.push_back(new StageBackground("assets/sprites/stage_background/complete.png", 0));

    //stageBackgroundList.push_back(new StageBackground("assets/sprites/stage_background/stage1_B.png", 640));

    //stageBackgroundList.push_back(new StageBackground("assets/sprites/stage_background/stage1_C.png", 1280));

    //stageBackgroundList.push_back(new StageBackground("assets/sprites/stage_background/stage1_D.png", 1920));

    //stageBackgroundList.push_back(new StageBackground("assets/sprites/stage_background/stage1_E.png", 2560));

}

void GameScene::unload(){

}

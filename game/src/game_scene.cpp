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
    gameObjectsList.push_back(new Player("assets/sprites/ALEX2.png", 20, 325, 20, 20));

}

void GameScene::unload(){

}

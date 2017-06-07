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
    player = new Player("assets/sprites/ALEX2.png", 20, 325, 20, 20);
    stageOneBackground = new StageBackground("assets/sprites/stage_background/complete.png", 0, player);

    gameObjectsList.push_back(player);
    stageBackgroundList.push_back(stageOneBackground);
}

void GameScene::unload(){

}

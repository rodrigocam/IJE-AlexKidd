#include "game_scene.hpp"
#include <typeinfo>

GameScene::GameScene(int id) : Scene(id){

}

GameScene::~GameScene(){}

void GameScene::draw(){
    stageOneBackground->draw();
    //player->GameObject::draw(player->getPositionX(), player->getPositionY());
    for(auto gameObject : gameObjectsList) {
        (*gameObject).draw();
    }
}

void GameScene::update(double timeElapsed){
    stageOneBackground->update(timeElapsed);
    for(auto gameObject : gameObjectsList) {
        (*gameObject).update(timeElapsed);
    }
}

void GameScene::load(){
    player = new Player("assets/sprites/ALEX2.png", 20, 320, 88, 64);

    stageOneBackground = new StageBackground("assets/sprites/stage_background/complete.png",
                                             0, player);

    gameObjectsList.push_back(player);
    stageBackgroundList.push_back(stageOneBackground);

}

void GameScene::unload(){

}

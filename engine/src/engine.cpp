#include "engine.hpp"
#include "sprite.hpp"
#include "scene_manager.hpp"
#include "input_manager.hpp"
#include "game_object.hpp"
#include "animation.hpp"
#include <vector>
#include <iostream>


namespace engine{

    const std::string GAME_NAME = "Alex Kidd";
    const std::pair <int, int> WINDOW_SIZE (640, 450);

    SceneManager* sceneManager;
    WindowManager* windowManager;
    SDLManager* sdlManager;
    double startTime;
    double stepTime;
    double timeElapsed;
    double frameTime;
    double frameRate = 60.0;
    SceneManager* getSceneManager(){
        return sceneManager;
    }
    void loadEngine(){
        sceneManager = new SceneManager();
        windowManager = new WindowManager();
        sdlManager = new SDLManager();
        startTime = SDL_GetTicks();
        stepTime = startTime;
        frameTime = 1000.0/frameRate;

        if(!sdlManager->initSDL()){
            ERROR("ERRO AO INICIAR SDL");
            exit(-1);
        }else if(!windowManager->createWindow(GAME_NAME, WINDOW_SIZE)){
            ERROR("ERRO AO CRIAR JANELA");
            exit(-1);
        }
    }

    void run(){
        bool isRunning = true;
        SDL_Event event;

        while(isRunning){
            stepTime = SDL_GetTicks();

            engine::InputManager::instance.update(event);
            SDL_RenderClear(WindowManager::getGameCanvas());

            if(engine::InputManager::instance.getQuitRequest()){
                isRunning = false;
                sdlManager->finalizeSDL();
                windowManager->destroyWindow();
                continue;
            }


            timeElapsed = SDL_GetTicks() - stepTime;
            DEBUG("TICKS:" + std::to_string(SDL_GetTicks()));
            DEBUG("frameTime:" + std::to_string(frameTime));
            DEBUG("timeElapsed: " + std::to_string(timeElapsed));
            if(frameTime > timeElapsed){
                DEBUG("SDL_DELAY: " + std::to_string(frameTime - timeElapsed));
                SDL_Delay(frameTime - timeElapsed);
                timeElapsed = SDL_GetTicks() - stepTime;
            }

            if(sceneManager->getCurrentScene() != NULL){
              sceneManager->getCurrentScene()->update(timeElapsed);
              sceneManager->getCurrentScene()->draw();
            }
            SDL_RenderPresent(WindowManager::getGameCanvas());
        }
    }
}

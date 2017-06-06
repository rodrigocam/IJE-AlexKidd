#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "sprite.hpp"
#include <unordered_map>

namespace engine{
    class Animation : public Sprite{
    public:
        Animation(std::string newDirectory, int rows, int columns, double allTime);
        ~Animation();

        void init();
        void update();
        void draw(int x, int y);
        void next();
        void shutdown();
        void setTotalTime(double newTotalTime);
        void setCurrentPositionFrame(int positionFrame);
        void setInterval(std::string action);
        void addAction(std::string name_action, int initial, int last);
        std::string getCurAction();
        std::pair<std::string, std::pair<int, int>> getInterval();

    private:
        int currentPositionFrame;
        int quantity;
        int widthFrame;
        int heightFrame;
        double totalTime;
        double startTime;
        double timeElapsed;
        double stepTime;
        std::string curAction;
        std::pair<std::string, std::pair<int, int>> interval;
        std::pair<int, int> matrix; // rows and columns
        std::unordered_map<std::string, std::pair<int,int>> list_actions;
    };
}
#endif

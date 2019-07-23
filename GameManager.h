#pragma once

#include <MinGE.h>
#include "Board.h"

class GameManager : public Script
{
    public:
        void start() override;

        virtual void registerEvent(sf::Int8 _type, vec2 _mp);
        virtual void emitEvent();

    private:
        std::vector<Player*> players;
};

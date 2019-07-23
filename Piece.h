#pragma once

#include <MinGE.h>

class Piece : public Script
{
    public:
        void update() override
        {

        }

        sf::Int8 id;
        sf::Int8 selectedBy;
};

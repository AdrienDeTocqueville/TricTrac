#pragma once

#include "Emplacements.h"
#include "Piece.h"

const int dameCount = 2;
const int diceCount = 2;
const int jetonCount = 2;

class Board: public Script
{
    public:
        void start() override;

        void moveChecker(Entity* checker, Fleche dest);

        bool addChecker(Entity* checker, Fleche fleche);
        Entity* removeChecker(Fleche fleche);

        bool addJeton(Entity* jeton, Slot slot);
        Entity* removeJeton(Slot slot);

        void rollDices();

        vec3 getFlechePosition(Fleche fleche, bool add = true);
        vec3 getSlotPosition(Slot slot);

        Piece* getPiece(sf::Int8 _id);

        std::vector<Entity*>& getFleche(Fleche fleche);

    private:
        std::vector<Entity*> board[2][12];
        Entity* slots[3][6];
};

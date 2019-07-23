#pragma once

#include <MinGE.h>
#include "Client.h"

class Player : public Script
{
    public:
        void start() override
        {
            selectedId = -1;
            selected = nullptr;

            lastUpdate.restart();
        }

        void updatePosition(vec2 _mp)
        {
            if (client && lastUpdate.getElapsedTime().asSeconds() > 1.0f)
            {
                lastUpdate.restart();
                client->emitEvent(MOUSE, id, _mp);
            }

            tr->setPosition(vec3(_mp.x, _mp.y, 6.0f));

            if (selected)
                selected->setPosition(vec3(_mp.x, _mp.y-0.3f, 5.0f));
        }

        void select(sf::Int8 _id)
        {
            Piece* piece = board->getPiece(_id);
                piece->selectedBy = id;

            selectedId = _id;
            selected = piece->find<Transform>();

            board->removeChecker(Fleche(selected->getPosition()));
        }

        void unselect()
        {
            board->addChecker(selected->getEntity(), Fleche(selected->getPosition()));

            Piece* piece = selected->find<Piece>();
                piece->selectedBy = -1;

            selectedId = -1;
            selected = nullptr;
        }

        sf::Int8 id, selectedId;
        sf::Clock lastUpdate;

        Board* board;
        Client* client;
        Transform* selected;
};

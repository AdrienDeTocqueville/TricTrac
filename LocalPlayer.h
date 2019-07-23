#pragma once

#include "Player.h"

class LocalPlayer : public Player
{
    public:
        void update() override
        {
            float hfov = 0.5f*Camera::main->getFOV();
            float ar = Camera::main->getAspectRatio();

            vec2 mp = Input::getMousePositionRelative();
            mp.x *= hfov; mp.y = mp.y * hfov/ar+0.3f;

            updatePosition(mp);

            if (Input::getMousePressed(sf::Mouse::Button::Left))
            {
                client->emitEvent(CLICK, id, mp);
                lastUpdate.restart();
            }
        }
};

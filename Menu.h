#pragma once

#include "Server.h"
#include "Client.h"

class Menu : public Script
{
    public:
        void start() override
        {
            Entity* fleche = Entity::findByTag("Fleche");
            Entity* slot = Entity::findByTag("SlotJeton");

            for (float side: {-1.0f, 1.0f})
            for (unsigned i(0) ; i < 6 ; i++)
            {
                Entity::clone( fleche, vec3(side * (0.9f + i), -3.5f, 0.0f) );
                Entity::clone( fleche, vec3(side * (0.9f + i), 3.5f, 0.0f), vec3(0, 0, PI) );
            }

            Entity::clone( slot, vec3(-5.9f, 0.0f, 0.0f) );

            for (float side: {-0.6f, 0.6f})
            for (float pos: {-5.9f, -4.4f, -2.4f, -0.7f, 0.7f, 6.1f})
                Entity::clone( slot, vec3(pos, side, 0.0f) );


            std::cout << std::endl << std::endl;
            std::cout << "Press L to play a local game" << std::endl;
            std::cout << "Press J to join a game server" << std::endl;
            std::cout << "Press H to host a game server" << std::endl;
            std::cout << std::endl << std::endl;
        }

        void update() override
        {
            if (!Input::hasFocus())
                return;

            if (Input::getMouseDown(sf::Mouse::Left))
                std::cout << 1  << "  " ;
            else
                std::cout << 0  << "  " ;


            if (Input::getMousePressed(sf::Mouse::Left))
                std::cout << "Pressed" ;

            if (Input::getMouseReleased(sf::Mouse::Left))
                std::cout << "Released" ;

                std::cout << std::endl;

//            if (Input::getKeyDown(sf::Keyboard::L) || Input::getMousePressed(sf::Mouse::Left))
//            {
//                std::cout << "Starting local game" << std::endl;
//
//                Entity::findByTag("Table")->insert<GameManager>();
//
//                getEntity()->destroy();
//                return;
//            }
//            if (Input::getKeyDown(sf::Keyboard::J) || Input::getMousePressed(sf::Mouse::Right))
//            {
//                Entity::create("Player", true, vec3(0, 0, 4.0f), vec3(0, 0, PI), vec3(0.4f))
//                    ->insert<Graphic>(new Model("Models/Hand/hand.obj"));
//
//                Entity::findByTag("Table")->insert<Client>();
//
//                getEntity()->destroy();
//                return;
//            }
//
//            else if (Input::getKeyDown(sf::Keyboard::H) || Input::getMousePressed(sf::Mouse::Middle))
//            {
////                Entity::create("Player", true);
//                Entity::create("Player", true, vec3(0, 0, 4.0f), vec3(0, 0, PI), vec3(0.4f))
//                    ->insert<Graphic>(new Model("Models/Hand/hand.obj"));
//
//                Entity::findByTag("Table")->insert<Server>();
//
//                getEntity()->destroy();
//                return;
//            }
        }

        void onDestroy() override
        {
//            Input::setCursorMode(GE_FREE_HIDDEN);
        }
};

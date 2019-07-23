#pragma once

#include <MinGE.h>
#include "RemoteClient.h"

class Server;

class RemoteClient: public Script
{
    friend class Server;

    public:
        void start() override;

        void update() override;

        void onDestroy() override;

//        void emitEvent(sf::Int8 _type, sf::Int8 _idSrc, sf::Int8 _idDest);
//        void emitEvent(sf::Int8 _type, sf::Int8 _id);
        void emitEvent(sf::Int8 _type);

        // ????????????????????????
        template <typename Arg, typename... Args>
        void emitEvent(Arg&& arg, Args&&... args)
        {
            sf::Packet event;
            event << std::forward<Arg>(arg);
            using expander = int[];
            (void)expander{(void(event << std::forward<Args>(args)),0)...}; // ???

            socket->send(event);
        }

    private:
        sf::TcpSocket* socket;
};

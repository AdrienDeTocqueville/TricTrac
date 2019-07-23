#include "RemoteClient.h"
#include "Server.h"

void RemoteClient::start()
{ }

void RemoteClient::update()
{
}

void RemoteClient::onDestroy()
{
    delete socket;
}

//void RemoteClient::emitEvent(sf::Int8 _type, sf::Int8 _idSrc, sf::Int8 _idDest)
//{
//    sf::Packet event;
//    event << _type << _idSrc << _idDest;
//
//    socket->send(event);
//}
//
//void RemoteClient::emitEvent(sf::Int8 _type, sf::Int8 _id)
//{
//    sf::Packet event;
//    event << _type << _id;
//
//    socket->send(event);
//}

void RemoteClient::emitEvent(sf::Int8 _type)
{
    sf::Packet event;
    event << _type;

    socket->send(event);
}

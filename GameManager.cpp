#include "GameManager.h"
#include "LocalPlayer.h"

void GameManager::start()
{
    insert<Board>();

    Entity::findByTag("MainCamera")->insert<LocalPlayer>(this);

    players.push_back( Entity::findByTag("MainCamera")->find<LocalPlayer>() );
}

void GameManager::registerEvent(sf::Int8 _type, vec2 _mp)
{
    if (_type == CLICK)
        emitEvent(_type, _mp);
//    {
//        float hfov = 0.5f * Camera::main->getFOV();
//        float ar = Camera::main->getAspectRatio();
//
//        vec3 origin = vec3(hfov*_mp.x, hfov*_mp.y/ar, 2.0f);
//
//        RayHit hit = PhysicEngine::get()->raycast(origin, vec3(0, 0, -1.0f));
//
//        if (hit.distance != -1.0f)
//            return hit.collider->getEntity();
//
//        return nullptr;
//    }
}

void GameManager::emitEvent()
{
}

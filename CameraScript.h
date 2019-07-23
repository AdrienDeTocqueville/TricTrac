#ifndef CAMERASCRIPT_H
#define CAMERASCRIPT_H

#include <MinGE.h>

class TPSCamera : public Script
{
    public:
        TPSCamera(Transform* _target, float _sensivity = 0.2f, float _distance = 0.01f, vec3 _offset = vec3(0.0f)):
            target(_target), angles(0.5f*PI, 0.35f*PI), clampAngleY(-0.499f*PI, 0.499f*PI),
            sensivity(_sensivity), distance(_distance), offset(_offset)
        { }

        /// Methods (public)
            void update() override
            {
                Debug::drawVector(vec3(0.0f), vec3(1, 0, 0), vec3(1, 0, 0));
                Debug::drawVector(vec3(0.0f), vec3(0, 1, 0), vec3(0, 1, 0));
                Debug::drawVector(vec3(0.0f), vec3(0, 0, 1), vec3(0, 0, 1));


                angles += radians(Input::getMouseDelta() * sensivity);
                angles.y = clamp(angles.y, clampAngleY.x, clampAngleY.y);

                distance = max(0.01f, distance - 0.2f*Input::getMouseWheelDelta());
            }

            void lateUpdate() override
            {
                if (Input::getCursorMode() != GE_CAPTURE)
                    return;

                /// FPS
//                tr->rotation = quat(vec3(0.0f, angles.y, angles.x));


                /// TPS
                tr->position = target->getToWorldSpace(offset) - quat(vec3(0.0f, angles.y, angles.x))*vec3(distance, 0.0f, 0.0f);
                tr->lookAt(target->getToWorldSpace(offset));



                tr->toMatrix();
            }

            void lookAt(vec3 _pos)
            {
                tr->lookAt(_pos);
                vec3 ea = eulerAngles(tr->rotation);

                angles.x = ea.z;
                angles.y = ea.y;
            }

    private:
        Transform* target;

        vec2 angles;
        vec2 clampAngleY;

        float sensivity;
        float distance;

        vec3 offset;
};

class FreeFlyCamera : public Script
{
    public:
        FreeFlyCamera(float _sensivity = 0.2f):
            angles(0.0f), clampAngleY(-0.499f*PI, 0.499f*PI),
            sensivity(_sensivity)
        { }

        /// Methods (public)
            void start() override
            {
                Input::getMouseDelta();
                Input::setCursorMode(GE_CAPTURE);
            }

            void update() override
            {
                Debug::drawVector(vec3(0.0f), vec3(1, 0, 0), vec3(1, 0, 0));
                Debug::drawVector(vec3(0.0f), vec3(0, 1, 0), vec3(0, 1, 0));
                Debug::drawVector(vec3(0.0f), vec3(0, 0, 1), vec3(0, 0, 1));

                angles += radians(Input::getMouseDelta() * sensivity);
                angles.y = clamp(angles.y, clampAngleY.x, clampAngleY.y);
            }

            void lateUpdate() override
            {
                if (Input::getCursorMode() != GE_CAPTURE)
                    return;

                vec3 dir = tr->getVectorToWorldSpace(vec3(1, 0, 0));
                vec3 left = tr->getVectorToWorldSpace(vec3(0, 1, 0));

                float speed = (Input::getKeyDown(sf::Keyboard::LShift)?10.0f:4.0f) * Time::deltaTime;

                if (Input::getKeyDown(sf::Keyboard::Z)) tr->position +=  dir * speed;
                if (Input::getKeyDown(sf::Keyboard::S)) tr->position -=  dir * speed;
                if (Input::getKeyDown(sf::Keyboard::Q)) tr->position += left * speed;
                if (Input::getKeyDown(sf::Keyboard::D)) tr->position -= left * speed;

                tr->position += Input::getMouseWheelDelta()*2*speed*dir;
                tr->rotation = quat(vec3(0.0f, angles.y, angles.x));

                tr->toMatrix();
            }

            void lookAt(vec3 _pos)
            {
                tr->lookAt(_pos);
                vec3 ea = eulerAngles(tr->rotation);

                angles.x = ea.z;
                angles.y = ea.y;
            }

    private:
        vec2 angles;
        vec2 clampAngleY;

        float sensivity;
};

#endif // CAMERASCRIPT_H

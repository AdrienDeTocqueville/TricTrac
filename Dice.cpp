#include "Dice.h"

int Dice::counter = 0;

void Dice::start()
{
    index = counter++;
    rb = find<RigidBody>();
}

void Dice::update()
{
    if (tr->position.z < -1.0f)
        roll(rotation, amplitude);
}

void Dice::roll(float _rotation, float _amplitude)
{
    value = -1;

    rotation = _rotation;
    amplitude = _amplitude;

    tr->setPosition(vec3(2.9f + index, -4.15f, 1.6f));
    tr->setRotation(vec3(2*rotation, rotation, 0));


    rb->setLinearVelocity(vec3(0.0f));
    rb->setAngularVelocity(vec3(0.0f));

    rb->applyForceToCOM( 10.0f*vec3(rotation, amplitude, -0.1f) );
}

int Dice::computeValue()
{
    vec3 numbers[6] =
    {
        vec3(0, 0, -1),
        vec3(0, 1, 0),
        vec3(1, 0, 0),
        vec3(-1, 0, 0),
        vec3(0, -1, 0),
        vec3(0, 0, 1),
    };

    int faceIndex = 0;

    for (int i(0) ; i < 6 ; i++)
    {
        numbers[i] = tr->getVectorToWorldSpace(numbers[i]);

        if (numbers[i].z > numbers[faceIndex].z)
            faceIndex = i;
    }

    return faceIndex+1;
}

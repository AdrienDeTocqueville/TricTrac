#pragma once

#include <MinGE.h>

enum State {Rolling, Invalid, Valid};

class Dice : public Script
{
    public:
        void start() override;
        void update() override;

        void roll(float _rotation, float _amplitude);

        int computeValue();

    private:
        RigidBody* rb = nullptr;

        int value = -1;
        float rotation, amplitude;

        int index;
        static int counter;
};

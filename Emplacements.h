#pragma once

#include <MinGE.h>

enum Team {White, Black, None};

struct Fleche
{
    Fleche(Team _team, int _num);
    Fleche(int _team, int _num);
    Fleche(vec3 p);
    Fleche();

    void clip();
    void unClip();
    bool inBounds();
    Fleche operator+(const int& i);

    Team team;
    int num;

    static Fleche talons[2];
    static Fleche repos[2];
};

struct Slot
{
    Slot(Team _team, int _num);
    Slot(vec3 p);
    Slot();

    Team team;
    int num;

    static Slot talons[3];
};

std::ostream& operator<<(std::ostream& os, const Fleche& fleche);
bool operator==(const Fleche& a, const Fleche& b);
bool operator!=(const Fleche& a, const Fleche& b);

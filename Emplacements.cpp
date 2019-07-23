#include "Emplacements.h"

/// Fleche
Fleche Fleche::talons[2] = {{Team::White, 0}, {Team::Black, 0}};
Fleche Fleche::repos[2] = {{Team::White, 11}, {Team::Black, 11}};

Fleche::Fleche(Team _team, int _num):
    team(_team), num(_num)
{}

Fleche::Fleche(int _team, int _num):
    Fleche((Team)_team, _num)
{}

Fleche::Fleche(vec3 p):
    team(p.y < 0 ? Team::White : Team::Black)
{
    if (p.x < 0)
        num = (int)(p.x + 0.9f) + 5;
    else
        num = (int)(p.x - 0.9f) + 6;
}

Fleche::Fleche():
    team(Team::None), num(-1)
{}

void Fleche::clip()
{
    if (num > 11)
    {
        team = (Team)(1-team);
        num = 23 - num;
    }
}

void Fleche::unClip()
{
    team = (Team)(1-team);
    num = 23 - num;
}

bool Fleche::inBounds()
{
    return num < 24;
}

std::ostream& operator<<(std::ostream& os, const Fleche& fleche)
{
    return os << fleche.team  << "  " << fleche.num;
}

Fleche Fleche::operator+(const int& i)
{
    return Fleche(team, num+i);
}

bool operator==(const Fleche& a, const Fleche& b)
{
    Fleche aa = a, bb = b;

    aa.clip();
    bb.clip();

    return aa.team == bb.team && aa.num == bb.num;
}

bool operator!=(const Fleche& a, const Fleche& b)
{
    Fleche aa = a, bb = b;

    aa.clip();
    bb.clip();

    return aa.team != bb.team || aa.num != bb.num;
}

/// Slot
Slot Slot::talons[3] = {{Team::White, 0}, {Team::Black, 0}, {Team::None, 0}};

Slot::Slot(Team _team, int _num):
    team(_team), num(_num)
{}

Slot::Slot(vec3 p)
{
    if (p.y < -0.5f)
        team = Team::White;

    else if (p.y > 0.5f)
        team = Team::Black;

    else
        team = Team::None;

    std::vector<float> slots = {-5.9f, -4.4f, -2.4f, -0.7f, 0.7f, 6.1f};

    for (unsigned i(0) ; i < slots.size() ; i++)
    {
        if (p.x == slots[i])
            num = i;
    }
}

Slot::Slot():
    team(Team::None), num(0)
{}

#include "Board.h"
#include "Dice.h"

void Board::start()
{
    for (int i(0); i < 3; i++)
    for (int j(0); j < 6; j++)
        slots[i][j] = nullptr;


    Entity* dames[] = { Entity::findByTag("DameBlanche"), Entity::findByTag("DameNoire") };
    Entity* jeton = Entity::findByTag("Jeton");
    Entity* dice = Entity::findByTag("Dice");

    Entity* dame;

    sf::Int8 id = 0;

    // Spawn checkers
        for (int j(0) ; j < 2 ; j++)
        for (int i(0) ; i < dameCount ; i++)
        {
            dame = Entity::clone(dames[j]);
                dame->tag = "Piece";
                dame->find<Piece>()->id = id++;
                dame->find<Piece>()->selectedBy = -1;

            addChecker( dame, Fleche::talons[j] );
        }

    // Spawn jetons and slots
        addJeton( Entity::clone(jeton), Slot::talons[Team::White] );
        addJeton( Entity::clone(jeton), Slot::talons[Team::None] );
        addJeton( Entity::clone(jeton), Slot::talons[Team::Black] );


    // Spawn dices
        Entity::clone(dice, vec3(0.25f, 0.0f, 1.05f), vec3(0.0f), vec3(2.0f));
        Entity::clone(dice, vec3(-0.25f, 0.0f, 1.05f), vec3(0.0f), vec3(2.0f));
}

void Board::moveChecker(Entity* checker, Fleche dest)
{
    vec3 cp = checker->find<Transform>()->getPosition();

    auto& f = getFleche(Fleche(cp));

    for (unsigned i(0) ; i < f.size() ; i++)
    {
        if (f[i] == checker)
        {
            f[i] = f.back();
            f.pop_back();
        }
    }

    getFleche(dest).push_back(checker);
    checker->find<Transform>()->setPosition(getFlechePosition(dest));
}

bool Board::addChecker(Entity* checker, Fleche fleche)
{
    auto& f = getFleche(fleche);

    if (f.size() && checker->tag != f.front()->tag)
        return false;

    checker->find<Transform>()->setPosition(getFlechePosition(fleche));

    f.push_back(checker);

    return true;
}

Entity* Board::removeChecker(Fleche fleche)
{
    std::vector<Entity*>& p = getFleche(fleche);

    Entity* checker = p.back();
    p.pop_back();

    return checker;
}

bool Board::addJeton(Entity* jeton, Slot slot)
{
    if (slots[slot.team][slot.num] != nullptr)
        return false;

    jeton->find<Transform>()->setPosition(getSlotPosition(slot));

    slots[slot.team][slot.num] = jeton;

    return true;
}

Entity* Board::removeJeton(Slot slot)
{
    Entity* jeton = slots[slot.team][slot.num];
    slots[slot.team][slot.num] = nullptr;

    return jeton;
}

void Board::rollDices()
{
    for (Entity* dice: Entity::findAllByTag("Dice", false))
    {
        float rotation = Random::nextFloat(-0.5f*PI, 0.5f*PI);
        float amplitude = Random::nextFloat(2.0f, 4.0f);

        dice->find<Dice>()->roll(rotation, amplitude);
    }
}

vec3 Board::getFlechePosition(Fleche fleche, bool add)
{
    int currentStack = getFleche(fleche).size() - (int)!add;

    fleche.clip();
    int index = fleche.num < 6 ? 5-fleche.num : fleche.num-6;
    int div = currentStack / 4;

    vec3 pos(0.9f + index, -4.5f + (currentStack%4), 0.11f + div*0.2f);

    if (fleche.num < 6)
        pos.x *= -1.0f;

    if (fleche.team == Team::Black)
        pos.y *= -1.0f;

    return pos;
}

vec3 Board::getSlotPosition(Slot slot)
{
    std::vector<float> slots = {-5.9f, -4.4f, -2.4f, -0.7f, 0.7f, 6.1f};

    float y = 0.0f;
    if (slot.team == Team::White)
        y = -0.6f;
    else if (slot.team == Team::Black)
        y = 0.6f;

    return vec3(slots[slot.num], y, 0.1f);
}

Piece* Board::getPiece(sf::Int8 _id)
{
    for (Entity* e: Entity::findAllByTag("Piece", false))
    {
        Piece* p = e->find<Piece>();

        if (p->id == _id)
            return p;
    }

    return nullptr;
}

std::vector<Entity*>& Board::getFleche(Fleche fleche)
{
    fleche.clip();

    return board[fleche.team][fleche.num];
}

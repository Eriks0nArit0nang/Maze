#include "EnemyWeapon.h"
#include "Character.h"

EnemyWeapon::EnemyWeapon(int xPos, int yPos, WeaponProperties weaponProperties, Character * watcher):
    Weapon(xPos, yPos, weaponProperties, watcher){}

EnemyWeapon::~EnemyWeapon(){}

void EnemyWeapon::Action( Character * character)
{
    if (character->Visit(*this))
    {
        // need to make the call for side effects
    }
}

void EnemyWeapon::Update()
{
    if (destroyThis)
    {
        delete this;
        return;
    }
    SetX(watcher->GetX());
    SetY(watcher->GetY());
}

void EnemyWeapon::Detonate()
{
    // Nothing to do
}

void EnemyWeapon::Draw(BITMAP *buffer, int midX, int midY)
{
}

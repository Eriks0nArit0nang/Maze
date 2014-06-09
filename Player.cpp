#include "Player.h"
#include "WeaponType.h"
#include "Map.h"
#include "Input.h"
#include <utility>
#include <iostream>

#include "Bomb.h"
#include "Nuke.h"
#include "AbstractGun.h"
#include "Gun.h"
#include "WideShot.h"
#include "ExplodingShot.h"
#include "Grenade.h"

const int Player::HEALTH = 1000;
const int Player::RADIUS = 5;

Player::Player(double xPos, double yPos, WeaponProperties weaponProperties[WEAPON_TYPES]):
    Character(Player::HEALTH, xPos, yPos, Player::RADIUS, _Gun, weaponProperties),money(0){}

void Player::Attack ()
{
    WeaponType option = activeWeapon;
    std::pair<int,int> input = Input::GetInstance()->GetWeapons();
    if (input.first / 1000 == 1)
        option = _Mine;
    else if (input.first / 100 == 1)
        option = _Nuke;
    else if (input.first / 10 == 1)
    {
        NextWeapon();
        option = activeWeapon;
    }
    else if (input.first / 1 == 1)
    {
        PrevWeapon();
        option = activeWeapon;
    }
    
    if (input.first != 0 || input.second != 0)
        switch (option)
        {
            case _None:
            case _Enemy:
                std::cerr << "Invalid active weapon for character\n";
                break;
            case _Gun:
                // TODO
                break;
            case _WideShot:
            case _ExplodingShot:
                std::cerr << "Specific Gun upgrades cannot be passed to Player:Attack\n";
                break;
            case _Grenade:
                weapons.push_back(new Grenade(GetX(), GetY(), GetWeaponProperties(option), input.second));
                break;
            case _Mine:
                weapons.push_back(new Bomb(GetX(), GetY(), GetWeaponProperties(option)));
                break;
            case _Nuke:
                weapons.push_back(new Nuke(GetX(), GetY(), GetWeaponProperties(option)));
                break;
            case _WallBreaker:
                break;
            default:
                std::cerr << "No mapping provided for Player::Attack for given WeaponType\n";
                break;
        }
    
}

void Player::Move ()
{
    // TODO get input into a singleton class to extract movement values
    Map *map = Map::GetInstance();
    int xChange = 0, yChange = 0;
    
    xVel += xChange;
    yVel += yChange;
    xPos += xVel;
    if (CollideWithWall('x',map->GetGrid(), map->GetGridSize()))
    {
       xPos-=xVel;
       xVel/=3.0;
    }
    yPos += yVel;
    if (CollideWithWall('y',map->GetGrid(), map->GetGridSize()))
    {
       yPos-=yVel;
       yVel/=3.0;
    }
    xVel *= .8;
    yVel *= .8;
}

void Player::AddMoney(int m)
{
    money += m;
}

int Player::GetMoney() const
{
    return money;
}

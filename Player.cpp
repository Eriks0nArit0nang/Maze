#include "Player.h"
#include "WeaponType.h"
#include "WeaponProperties.h"
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

Player::Player(double xPos, double yPos):
    Character(Player::HEALTH, xPos, yPos, Player::RADIUS, _Gun),money(0)
{
    InitializeWeaponProperties();
}

void Player::InitializeWeaponProperties()
{
    
    weaponProperties[_None] = WeaponProperties(_None, 0);
    weaponProperties[_Gun] = WeaponProperties(_Gun, -1);
    weaponProperties[_WideShot] = WeaponProperties(_WideShot, 1);
    weaponProperties[_ExplodingShot] = WeaponProperties(_ExplodingShot, 1);
    weaponProperties[_Grenade] = WeaponProperties(_Grenade, 200);
    weaponProperties[_Mine] = WeaponProperties(_Mine, 10);
    weaponProperties[_Nuke] = WeaponProperties(_Nuke, 1);
    weaponProperties[_WallBreaker] = WeaponProperties(_WallBreaker, 1);
    weaponProperties[_Enemy] = WeaponProperties(_Enemy, 0);
}

void Player::Attack ()
{
    attackDelay--;
    WeaponType option = activeWeapon;
    std::pair<int,int> input = Input::GetInstance()->GetWeapons();
    if (input.first / 1000 == 1)
        option = _Mine;
    else if (input.first / 100 == 1)
        option = _Nuke;
    else if (input.first / 10 == 1 && attackDelay <= 0)
    {
        NextWeapon();
        option = activeWeapon;
        attackDelay = 10;
    }
    else if (input.first / 1 == 1 && attackDelay <= 0)
    {
        PrevWeapon();
        option = activeWeapon;
        attackDelay = 10;
    }
    
    if ((input.first != 0 || input.second != 0) && attackDelay <= 0 )
    {
        attackDelay = GetWeaponProperties(option).GetFireRate();
        GetWeaponProperties(option).AddShotTaken();
        if (GetWeaponProperties(option).GetShotsTaken() == GetWeaponProperties(option).GetClipSize())
        {
            attackDelay += GetWeaponProperties(option).GetReloadRate();
        }
        switch (option)
        {
            case _None:
            case _Enemy:
                std::cerr << "Invalid active weapon for character\n";
                break;
            case _Gun:
            {
                AbstractGun *gun = new Gun(GetX(), GetY(), GetWeaponProperties(option), input.second, this);
                if (GetWeaponProperties(_WideShot).GetWeaponQuantity() != 0) 
                    gun = new WideShot(gun);
                if (GetWeaponProperties(_ExplodingShot).GetWeaponQuantity() != 0) 
                    gun = new ExplodingShot(gun);
                weapons.push_back(gun);
                break;
            }
            case _WideShot:
            case _ExplodingShot:
                std::cerr << "Specific Gun upgrades cannot be passed to Player:Attack\n";
                break;
            case _Grenade:
                if (GetWeaponProperties(option).GetWeaponQuantity() != 0)
                {
                    weapons.push_back(new Grenade(GetX(), GetY(), GetWeaponProperties(option), input.second, this));
                    weaponProperties[option].SetWeaponQuantity(weaponProperties[option].GetWeaponQuantity()-1);
                }
                break;
            case _Mine:
                if (GetWeaponProperties(option).GetWeaponQuantity() != 0)
                {
                    weapons.push_back(new Bomb(GetX(), GetY(), GetWeaponProperties(option), this));
                    weaponProperties[option].SetWeaponQuantity(weaponProperties[option].GetWeaponQuantity()-1);
                }
                break;
            case _Nuke:
                if (GetWeaponProperties(option).GetWeaponQuantity() != 0)
                {
                    weapons.push_back(new Nuke(GetX(), GetY(), GetWeaponProperties(option), this));
                    weaponProperties[option].SetWeaponQuantity(weaponProperties[option].GetWeaponQuantity()-1);
                }
                break;
            case _WallBreaker:
                if (GetWeaponProperties(option).GetWeaponQuantity() != 0)
                {
                    weapons.push_back(new WallBreaker(GetX(), GetY(), GetWeaponProperties(option), input.second, this));
                    weaponProperties[option].SetWeaponQuantity(weaponProperties[option].GetWeaponQuantity()-1);
                }
                break;
            default:
                std::cerr << "No mapping provided for Player::Attack for given WeaponType\n";
                break;
        }
    }
}

void Player::Move ()
{
    int input = Input::GetInstance()->GetMovement();
    Map *map = Map::GetInstance();
    int xChange = ((input / 1000) % 10) - ((input / 100) % 10);
    int yChange = ((input / 10) % 10) - (input % 10);
    
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

void Player::Draw(BITMAP *buffer, int midX, int midY)
{
    for (int i = 0; i < weapons.size(); i++)
        weapons[i]->Draw(buffer, midX, midY);
    circlefill (buffer, midX+GetX(), midY+GetY(), radius, makecol(0,0,255));
    if (initialHealth-health >= 0)
        circlefill (buffer, midX, midY, (initialHealth-health)/(initialHealth/radius), makecol(150,150,255)); 
    
}

bool Player::Visit (EnemyWeapon &enemyWeapon)
{
    if (InRange(enemyWeapon.GetX(), enemyWeapon.GetY(), enemyWeapon.GetProperties().GetRadius()))
    {
        Hit(enemyWeapon.GetProperties().GetDamage());
    }
    return false;
}

bool Player::Visit (Grenade &grenade)
{
    if (InRange(grenade.GetX(), grenade.GetY(), grenade.GetProperties().GetRadius()) && grenade.WillDestroy())
    {
        Hit(grenade.GetProperties().GetDamage());
    }
    return false;
}

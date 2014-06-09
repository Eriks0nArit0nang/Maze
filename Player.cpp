#include "Player.h"
#include "WeaponType.h"
#include "Map.h"

const int Player::HEALTH = 1000;
const int Player::RADIUS = 5;

Player::Player(double xPos, double yPos, WeaponProperties weaponProperties[WEAPON_TYPES]):
    Character(Player::HEALTH, xPos, yPos, Player::RADIUS, _Gun, weaponProperties){}

void Player::Attack ()
{
    WeaponType option = activeWeapon; //TODO extract value from input
    // TODO implement attacking for player based on keyboard input and current status
    // only need to create weapons.  movement is done in weapon classes themselves
    
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

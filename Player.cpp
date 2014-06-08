#include "Player.h"
#include "WeaponType.h"

Player::Player(int health, double xPos, double yPos, int radius, WeaponType activeWeapon, WeaponProperties weaponProperties[WEAPON_TYPES]):
    Character(health, xPos, yPos, radius, activeWeapon, weaponProperties){}

void Player::Attack ()
{
    WeaponType option = _None; //TODO extract value from input
    // TODO implement attacking for player based on keyboard input and current status
    // only need to create weapons.  movement is done in weapon classes themselves
    
}

void Player::Move ()
{
    // TODO get input into a singleton class to extract movement values
    // TODO create map class
    int grid[GRID_SIZE][GRID_SIZE];
    int xChange = 0, yChange = 0;
    
    xVel += xChange;
    yVel += yChange;
    xPos += xVel;
    if (CollideWithWall('x',grid))
    {
       xPos-=xVel;
       xVel/=3.0;
    }
    yPos += yVel;
    if (CollideWithWall('y',grid))
    {
       yPos-=yVel;
       yVel/=3.0;
    }
    xVel *= .8;
    yVel *= .8;
}

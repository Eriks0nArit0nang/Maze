// Player
#include <cmath>
#include <vector>
class Player
{
      private:
              double xPos,yPos;
              double xVel,yVel;
          //    int xRep,yRep;
              bool Collide (char xy, int grid[GRID_SIZE][GRID_SIZE]);
              int health, initialHealth, addedHealth;
              int clipSize;
              int money;
              int fireRate;
              int range;
              int weaponQuantities[6];
              int maxQuantities[6];
              int weaponCost[6];
              int activeWeapon;
              
      public:
           //  Bullet weapon;
             Player ();
             void Add_Money (int n);
             int Get_ClipSize() const;
             int Get_Health() const;
             int Get_InitialHealth() const;
             int Get_Money () const;
             int Get_X () const;
             int Get_Y () const;
             void Move (int xChange, int yChange, int grid[GRID_SIZE][GRID_SIZE]);
             void Set_XY (int x, int y);
             void Hit (int damage);
             void Add_Health (int h);
             int Get_Added_Health() const;
             int Get_Range () const;
             void Set_Range(int r);
             int Get_Rate() const;
             int Get_ActiveWeapon() const;
             void Set_ActiveWeapon(int a);
             void Set_Rate(int r);
             void Set_ClipSize(int c);
             bool Max_Quantity (int type);
             void Set_Quantity (int type, int value);
             int Get_Quantity (int type) const;
             int Get_Cost (int type) const;
             
              
};

Player::Player ()
{
    xVel = 0;
    yVel = 0;
    addedHealth = 0;
    activeWeapon = 0;
 //   xRep = 0;
   // yRep = 0;
   clipSize = 25;
   initialHealth = 1000;
   range = 120;
   money = 0;
    health = initialHealth;
    fireRate = 10;
    for (int i = 0; i < 6; i++)
        weaponQuantities[i] = 0;
    maxQuantities[0] = 1; // Nuke
    maxQuantities[1] = 1; // Wide Shot
    maxQuantities[2] = 500; // Grenade
    maxQuantities[3] = 1; // Exploding Shot
    maxQuantities[4] = 5; // Mine
    maxQuantities[5] = 3; // Wall Smasher
    weaponCost[0] = 10000;
    weaponCost[1] = 1000;
    weaponCost[2] = 300;
    weaponCost[3] = 8000;
    weaponCost[4] = 1000;
    weaponCost[5] = 5000;
}

void Player::Add_Money (int n)
{
     money += n;
}

bool Player::Collide (char xy, int grid[GRID_SIZE][GRID_SIZE])
{
     if ( abs (Get_X() % 60 - 30) > 25 && abs (Get_Y() % 60 - 30) > 25)
     {
        return (grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][Get_Y()/60] == 1 || 
                grid[Get_X()/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60] == 1 ||
                grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60]==1);//grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60] == 1;
     }
     if (xy == 'x' && xVel != 0)
        return grid[((int)round(xPos+xVel+xVel/abs(xVel)*5))/60][Get_Y()/60] == 1;
     else if (xy == 'y' && yVel != 0)
          return grid[Get_X()/60][((int)round(yPos+yVel+yVel/abs(yVel)*5))/60] == 1;
     return false;
}

int Player::Get_ActiveWeapon() const
{
    return activeWeapon;
}

int Player::Get_Added_Health() const
{
    return addedHealth;
}

int Player::Get_Cost(int type) const
{
    return weaponCost[type];
}

int Player::Get_ClipSize() const
{
    return clipSize;
}

int Player::Get_Health() const
{
    return health;
}

int Player::Get_InitialHealth() const
{
    return initialHealth;
}

int Player::Get_Money() const
{
    return money;
}

int Player::Get_Quantity (int type) const
{
    return weaponQuantities[type];
}

int Player::Get_Range () const
{
    return range;
}

int Player::Get_Rate () const
{
    return fireRate;
}

int Player::Get_X () const
{
    return (int)round (xPos);
}

int Player::Get_Y () const
{
    return (int)round(yPos);
}

void Player::Hit (int damage)
{
     health-= damage;
}

bool Player::Max_Quantity (int type)
{
     return weaponQuantities[type] == maxQuantities[type];
}

void Player::Move (int xChange, int yChange, int grid[GRID_SIZE][GRID_SIZE])
{
     xVel += xChange;
     yVel += yChange;
     xPos += xVel;
     if (Collide('x',grid))
     {
        xPos-=xVel;
        xVel/=3.0;
     }
     yPos += yVel;
     if (Collide('y',grid))
     {
        yPos-=yVel;
        yVel/=3.0;
     }
     xVel *= .8;
     yVel *= .8;
}

void Player::Add_Health (int h)
{
     addedHealth += h;
     health += h;
}

void Player::Set_ActiveWeapon(int a)
{
     activeWeapon = a;
}

void Player::Set_ClipSize (int c)
{
     clipSize = c;
}

void Player::Set_Quantity (int type, int value)
{
     weaponQuantities[type] = value;
}

void Player::Set_Rate (int r)
{
     fireRate = r;
}

void Player::Set_Range (int r)
{
     range = r;
}

void Player::Set_XY (int x1, int y1)
{
    xPos = x1;
    yPos = y1;
}


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
              int health, initialHealth;
              int clipSize;
              int money;
              int fireRate;
              int weaponQuantities[6];
              int maxQuantities[6];
              
      public:
             Player ();
             void Add_Money (int n);
             int Get_ClipSize();
             int Get_Health();
             int Get_InitialHealth();
             int Get_Money ();
             int Get_X ();
             int Get_Y ();
             void Move (int xChange, int yChange, int grid[GRID_SIZE][GRID_SIZE]);
             void Set_XY (int x, int y);
             void Hit (int damage);
             void Add_Health (int h);
             int Get_Rate();
             void Set_Rate(int r);
             void Set_ClipSize(int c);
             bool Max_Quantity (int type);
             void Set_Quantity (int type, int value);
             int Get_Quantity (int type);
             
              
};

Player::Player ()
{
    xVel = 0;
    yVel = 0;
 //   xRep = 0;
   // yRep = 0;
   clipSize = 25;
   initialHealth = 1000;
   money = 0;
    health = initialHealth;
    fireRate = 10;
    for (int i = 0; i < 6; i++)
        weaponQuantities[i] = 0;
    maxQuantities[0] = 1;
    maxQuantities[1] = 1;
    maxQuantities[2] = 500;
    maxQuantities[3] = 1;
    maxQuantities[4] = 5;
    maxQuantities[5] = 1;
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

int Player::Get_ClipSize()
{
    return clipSize;
}

int Player::Get_Health()
{
    return health;
}

int Player::Get_InitialHealth()
{
    return initialHealth;
}

int Player::Get_Money()
{
    return money;
}

int Player::Get_Quantity (int type)
{
    return weaponQuantities[type];
}

int Player::Get_Rate ()
{
    return fireRate;
}

int Player::Get_X ()
{
    return (int)round (xPos);
}

int Player::Get_Y ()
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
      //  health -= xRep/4;
        //xRep = 0;
     }
     yPos += yVel;
     if (Collide('y',grid))
     {
        yPos-=yVel;
        yVel/=3.0;
       // health -= yRep/4;
       // yRep = 0;
     }
     xVel *= .8;
     yVel *= .8;
     //xRep = (xRep+1)*(int)abs(xChange*1.0);
   //  yRep = (yRep+1)*(int)abs(yChange*1.0);
}

void Player::Add_Health (int h)
{
     health += h;
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

void Player::Set_XY (int x1, int y1)
{
    xPos = x1;
    yPos = y1;
}


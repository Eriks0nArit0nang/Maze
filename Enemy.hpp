#include <utility>
#include <queue>

class Enemy
{
      public:
             Enemy ();
             int Get_X();
             int Get_Y();
             void Set_Coords (int x, int y);
             bool Update (Player &p, int grid[GRID_SIZE][GRID_SIZE], int check[GRID_SIZE][GRID_SIZE]); // main function
             bool Shot (int bulletX, int bulletY, int damage, int width); // if it was hit
             bool Dead ();
             void Init (); // initialize values
             bool Attack (Player &p); // if able to attack player
             int Get_Rad ();
             int Get_Health ();
             int Get_InitialHealth ();
             int Get_Strength();
             int Get_Type();
             
      private:
              double xP,yP; // position
              double speed; // velocity
              int attackRadius, attackRate, wait; // rates of attack
              int health, initialHealth, strength;
              int ra; // enemy radius of self
              bool Dist (Player &p); // within close range
              void Move_1 (Player &p, int grid[GRID_SIZE][GRID_SIZE], int check[GRID_SIZE][GRID_SIZE]);
              void Move_2 (Player &p, int grid[GRID_SIZE][GRID_SIZE], int check[GRID_SIZE][GRID_SIZE]);
              void Move_3 (Player &p);
              void Move_4 (Player &p);
              bool Collide (Player &p); // run into player
              int type;
              
};

Enemy::Enemy ()
{
}

bool Enemy::Attack (Player &p)
{
     if (wait <= 0 && sqrt(pow(Get_X()-p.Get_X(),2.0)+pow(Get_Y()-p.Get_Y(),2.0)) <= attackRadius && type <= 4)
     {
        wait = attackRate;
        return true;
     }
     else if (wait <= 0 && type > 4 && ((abs(Get_X()-p.Get_X()) < ra + 5 && abs(Get_Y()-p.Get_Y()) <= attackRadius) || (abs(Get_X()-p.Get_X()) < attackRadius && abs(Get_Y()-p.Get_Y()) < ra + 5)))
     {
          wait = attackRate;
          return true;
     }
     return false;
}

bool Enemy::Collide (Player &p)
{
     return sqrt(pow(p.Get_X()-Get_X(),2.0)+pow(p.Get_Y()-Get_Y(),2.0)) < 10;
}

bool Enemy::Dead ()
{
     return health <= 0;
}

bool Enemy::Dist (Player &p)
{
            return sqrt(pow(Get_X()-p.Get_X(),2.0)+pow(Get_Y()-p.Get_Y(),2.0)) < 1500;
}

int Enemy::Get_Health()
{
    return health;
}

int Enemy::Get_InitialHealth ()
{
    return initialHealth;
}

int Enemy::Get_Rad()
{
    return ra;
}

int Enemy::Get_Strength()
{
    return strength;
}

int Enemy::Get_Type()
{
    return type;
}

int Enemy::Get_X ()
{
    return (int)round (xP);
}

int Enemy::Get_Y ()
{
    return (int)round (yP);
}

void Enemy::Init ()
{
     int t = rand () % 100 + 10;
     initialHealth = t;
     health = t;
     ra = health/10 + 1;
     strength = health/20 + 1;
     speed = 75.0/(1.0*t);
     t = rand () % 20 + 1;
     attackRate = 120/t;
     attackRadius = t + ra + 5;
     wait = 0;
     type = rand () % 6 + 1;
     if (type == 3 || type == 4)
        speed /= 2;
     if (type == 5 || type == 6)
     {
        attackRadius += t*4;
        strength *= 2;
     }
}

void Enemy::Move_1 (Player &p, int grid[GRID_SIZE][GRID_SIZE], int check[GRID_SIZE][GRID_SIZE])
{
     if (!(p.Get_X()/60==Get_X()/60&&p.Get_Y()/60==Get_Y()/60))
     {
        if (check[Get_X()/60][Get_Y()/60] > 0)
        {
           int i = Get_X()/60, j = Get_Y()/60;
           if (check[i-1][j] == check[i][j]-1)
           {
              if (abs(Get_Y() % 60 - 30) < 30 - ra)
                 xP-=speed;
              else
                  yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
           }
           else if (check[i+1][j] == check[i][j]-1)
           {
                if (abs(Get_Y() % 60 - 30) < 30-ra)
                   xP+=speed;
                else
                  yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
           }
           else if (check[i][j-1] == check[i][j]-1)
           {
                if (abs(Get_X() % 60 - 30) < 30-ra)
                   yP-=speed;
                else
                  xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
           }
           else if (check[i][j+1] == check[i][j]-1)
           {
                if (abs(Get_X() % 60 - 30) < 30-ra)
                   yP+=speed;
                else
                  xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
           }
        }
     }
     else
     {
         int x = -Get_X()+p.Get_X(), y = -Get_Y()+p.Get_Y();
         if (x != 0)
         {
            if (abs(Get_X() % 60 - 30) >= 30-ra)
               xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
            else
            {
                xP += x/abs(x)*min(speed,(double)abs(x));
                if (abs(Get_X() % 60 - 30) >= 30-ra)
                   xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
            }
         }
         if (y != 0)
         {
            if (abs(Get_Y() % 60 - 30) >= 30-ra)
               yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
            else
            {
                yP += y/abs(y)*min(speed,(double)abs(y));
                if (abs(Get_Y() % 60 - 30) >= 30-ra)
                   yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
            }
         }
     }
}

void Enemy::Move_2 (Player &p, int grid[GRID_SIZE][GRID_SIZE], int check[GRID_SIZE][GRID_SIZE])
{
     if (!(p.Get_X()/60==Get_X()/60&&p.Get_Y()/60==Get_Y()/60))
     {
        if (speed > 2)
        {
            if (abs (p.Get_X()-Get_X()) < 5+ra && abs (p.Get_Y()- Get_Y()) < 120)
               xP += (30 - Get_X() % 60)/abs (30.01 - Get_X() % 60)*speed;
            if (abs (p.Get_Y()- Get_Y()) < 5+ra && abs (p.Get_X()-Get_X()) < 120)
               yP += (30 - Get_Y() % 60)/abs (30.01 - Get_Y() % 60)*speed;
        }
        if (check[Get_X()/60][Get_Y()/60] > 0)
        {
           int i = Get_X()/60, j = Get_Y()/60;
           if (check[i-1][j] == check[i][j]-1)
           {
              if (abs(Get_Y() % 60 - 30) < 30 - ra)
                 xP-=speed;
              else
                  yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
           }
           else if (check[i+1][j] == check[i][j]-1)
           {
                if (abs(Get_Y() % 60 - 30) < 30-ra)
                   xP+=speed;
                else
                  yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
           }
           else if (check[i][j-1] == check[i][j]-1)
           {
                if (abs(Get_X() % 60 - 30) < 30-ra)
                   yP-=speed;
                else
                  xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
           }
           else if (check[i][j+1] == check[i][j]-1)
           {
                if (abs(Get_X() % 60 - 30) < 30-ra)
                   yP+=speed;
                else
                  xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
           }
        }
     }
     else
     {
         int x = -Get_X()+p.Get_X(), y = -Get_Y()+p.Get_Y();
         if (x != 0)
         {
            if (abs(Get_X() % 60 - 30) >= 30-ra)
               xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
            else
            {
                xP += x/abs(x)*min(speed,(double)abs(x));
                if (abs(Get_X() % 60 - 30) >= 30-ra)
                   xP += (30 - Get_X() % 60)/abs (30 - Get_X() % 60)*speed;
            }
         } 
         if (y != 0)
         {
            if (abs(Get_Y() % 60 - 30) >= 30-ra)
               yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
            else
            {
                yP += y/abs(y)*min(speed,(double)abs(y));
                if (abs(Get_Y() % 60 - 30) >= 30-ra)
                   yP += (30 - Get_Y() % 60)/abs (30 - Get_Y() % 60)*speed;
            }
         }
     }
}

void Enemy::Move_3 (Player &p)
{
     int x = -Get_X()+p.Get_X(), y = -Get_Y()+p.Get_Y();
     if (sqrt(pow(Get_X()-p.Get_X(),2.0)+pow(Get_Y()-p.Get_Y(),2.0)) < 425)
     {
         if (x != 0)
            xP += x/abs(x)*min(speed,(double)abs(x));
         if (y != 0)
            yP += y/abs(y)*min(speed,(double)abs(y));
     }
}

void Enemy::Move_4 (Player &p)
{
     int x = -Get_X()+p.Get_X(), y = -Get_Y()+p.Get_Y();
     if (sqrt(pow(Get_X()-p.Get_X(),2.0)+pow(Get_Y()-p.Get_Y(),2.0)) < 425)
     {
        if (x != 0)
           xP += x/abs(x)*min(speed,(double)abs(x));
        if (y != 0)
           yP += y/abs(y)*min(speed,(double)abs(y));
        int x = -Get_X()+p.Get_X(), y = -Get_Y()+p.Get_Y();
        if (speed > 2 && !(Get_X()/60 == p.Get_X()/60 && Get_Y()/60 == p.Get_Y()/60))
        {
            if (abs (x) < 5+ra && abs (y) < 120)
               xP += (30 - Get_X() % 60)/abs (30.01 - Get_X() % 60)*speed;
            if (abs (y) < 5+ra && abs (x) < 120)
               yP += (30 - Get_Y() % 60)/abs (30.01 - Get_Y() % 60)*speed;
        }
     }
}

void Enemy::Set_Coords (int x, int y)
{
     xP = x;
     yP = y;
}

bool Enemy::Shot (int bulletX, int bulletY, int damage, int width)
{
     if (sqrt(pow(bulletX-Get_X(),2.0)+pow(bulletY-Get_Y(),2.0)) <= ra+width)
     {
        health -= damage;
        strength = health/20 + 1;
        return true;
     }
     else
         return false;
}

bool Enemy::Update (Player &p, int grid[GRID_SIZE][GRID_SIZE], int bfs[GRID_SIZE][GRID_SIZE])
{
     wait--;
     if (Dist (p))
     {
        if (type == 1 || type == 5)
           Move_1 (p,grid,bfs);
        else if (type == 2 || type == 6)
             Move_2 (p,grid,bfs);
        else if (type == 3)
             Move_3 (p);
        else if (type == 4)
             Move_4 (p);
        if (Collide (p))
           return true;
        else
            return false;
     }
     else
         return false;
}

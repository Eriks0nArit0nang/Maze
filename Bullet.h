class Bullet
{
      public:
             Bullet ();
             int Shoot (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE]);
             int Grenade (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE]);
             int Walls (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE]);
             void Set_Range (int r);
             int Get_Range ();
             int Get_GrenadeX ();
             int Get_GrenadeY ();
             int Get_GrenadeTimer ();
             int Get_BombX (int n);
             int Get_BombY (int n);
             void Place_Bomb (int x, int y);
             int Hit_Bomb (vector <Enemy> E);
             void Trigger_Bomb (int n);
             int Number_of_Bombs ();
             
      private:
              int x,y, range;
              int grenadeTimer, direction, speed, grenadeX, grenadeY;
              vector <pair <int,int> > bombs;
};

Bullet::Bullet ()
{
     grenadeTimer = -1;
     direction = -1;
     range = 120;
     speed = 6;
}

void Bullet::Set_Range (int r)
{
     range = r;
}

int Bullet::Get_BombX (int n)
{
    return bombs[n].first;
}

int Bullet::Get_BombY (int n)
{
    return bombs[n].second;
}

int Bullet::Number_of_Bombs ()
{
    return bombs.size();
}

int Bullet::Get_Range ()
{
    return range;
}

int Bullet::Get_GrenadeTimer ()
{
    return grenadeTimer;
}

int Bullet::Get_GrenadeX ()
{
    return grenadeX;
}

int Bullet::Get_GrenadeY ()
{
    return grenadeY;
}

int Bullet::Shoot (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE])
{
     vector <Enemy> comp;
     x = P.Get_X();
     y = P.Get_Y();
     if (d == 0) // x+
     {
        for (int i = 0; i < E.size(); i++)
            if (E[i].Get_X() > x-E[i].Get_Rad() && abs(E[i].Get_Y()-y) < E[i].Get_Rad() + P.Get_Quantity(1)*3)
               comp.push_back(E[i]);
     }
     else if (d == 1) // x-
     {
          for (int i = 0; i < E.size(); i++)
            if (E[i].Get_X() < x+E[i].Get_Rad() && abs(E[i].Get_Y()-y) < E[i].Get_Rad() + P.Get_Quantity(1)*3)
               comp.push_back(E[i]);
     }
     else if (d == 2) // y+
     {
          for (int i = 0; i < E.size(); i++)
            if (E[i].Get_Y() > y-E[i].Get_Rad() && abs(E[i].Get_X()-x) < E[i].Get_Rad() + P.Get_Quantity(1)*3)
               comp.push_back(E[i]);
     }
     else if (d == 3) // y-
     {
           for (int i = 0; i < E.size(); i++)
            if (E[i].Get_Y() < y+E[i].Get_Rad() && abs(E[i].Get_X()-x) < E[i].Get_Rad() + P.Get_Quantity(1)*3)
               comp.push_back(E[i]);
     }
     if (comp.size() == 0)
        return -1;
     else
     {
         int damage = rand () % 10 + 1;
         while (grid[x/60][y/60] != 1 && abs (x - P.Get_X()) <= range  && abs (y - P.Get_Y()) <= range)
         {
               if (d == 0) // x+
               {
                     x+=2;
                     for (int i = 0; i < comp.size(); i++)
                         if (comp[i].Shot(x,y,damage,P.Get_Quantity(1)*3))
                            return x;
               }
               else if (d == 1) // x-
               {
                    x-=2;
                     for (int i = 0; i < comp.size(); i++)
                         if (comp[i].Shot(x,y,damage,P.Get_Quantity(1)*3))
                            return x;
               }
               else if (d == 2) // y+
               {
                    y+=2;
                     for (int i = 0; i < comp.size(); i++)
                         if (comp[i].Shot(x,y,damage,P.Get_Quantity(1)*3))
                            return y;
               }
               else if (d == 3) // y-
               {
                    y-=2;
                     for (int i = 0; i < comp.size(); i++)
                         if (comp[i].Shot(x,y,damage,P.Get_Quantity(1)*3))
                            return y;
               }
         }
     }
     return -1;
}

int Bullet::Grenade (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE])
{
    vector <Enemy> comp;
    x = P.Get_X();
    y = P.Get_Y();
    
    if (d == 0) // x+
    {
       for (int i = 0; i < E.size(); i++)
           if (E[i].Get_X() > x-E[i].Get_Rad() && abs(E[i].Get_Y()-y) < E[i].Get_Rad() + 3)
              comp.push_back(E[i]);
    }
    else if (d == 1) // x-
    {
         for (int i = 0; i < E.size(); i++)
             if (E[i].Get_X() < x+E[i].Get_Rad() && abs(E[i].Get_Y()-y) < E[i].Get_Rad() + 3)
                comp.push_back(E[i]);
    }
    else if (d == 2) // y+
    {
         for (int i = 0; i < E.size(); i++)
             if (E[i].Get_Y() > y-E[i].Get_Rad() && abs(E[i].Get_X()-x) < E[i].Get_Rad() + 3)
                comp.push_back(E[i]);
    }
    else if (d == 3) // y-
    {
          for (int i = 0; i < E.size(); i++)
           if (E[i].Get_Y() < y+E[i].Get_Rad() && abs(E[i].Get_X()-x) < E[i].Get_Rad() + 3)
              comp.push_back(E[i]);
    }
    if (grenadeTimer <= 0&&d > -1)
    {
       grenadeTimer = 40;
       direction = d;
       grenadeX = P.Get_X();
       grenadeY = P.Get_Y();
       speed = 6;
       return -1;
    }
    else
        grenadeTimer--;
    if (grenadeTimer == 0)
    {
       if (d/2==0)
          return grenadeX;
       else
           return grenadeY;
    }
    else if (grenadeTimer > 0)
    {
        for (int i = 0; i < speed/2; i++)
        {
            if (direction==0)
               grenadeX+=2;
            else if (direction==1)
                 grenadeX-=2;
            else if (direction==2)
                 grenadeY+=2;
            else if (direction==3)
                 grenadeY-=2;
            for (int i = 0; i < comp.size(); i++)
            {
                if (comp[i].Shot(x,y,0,comp[i].Get_Rad()))
                {
                   direction = (direction+2) % 4;
                   speed -= 2;
                }
            }
            if (grid[grenadeX/60][grenadeY/60] == 1)
            {
               direction = (direction+2) % 4;
               speed -= 2;
            }
        }
    }          
    return -2;
}

int Bullet::Walls (vector <Enemy> E, Player P, int d, int grid[GRID_SIZE][GRID_SIZE])
{
    int x = P.Get_X();
    int y = P.Get_Y();
    while (grid[x/60][y/60] != 1)
    {
          if (d == 0) // x+
                x+=60;
          else if (d == 1) // x-
               x-=60;
          else if (d == 2) // y+
               y+=60;
          else if (d == 3) // y-
               y-=60;
    }
    if (d/2==0)
       return x;
    else
        return y;
}

void Bullet::Place_Bomb (int x, int y)
{
     pair <int,int> n;
     n.first = x;
     n.second = y;
     bombs.push_back(n);
}

int Bullet::Hit_Bomb (vector <Enemy> E)
{
    for (int i = 0; i < bombs.size(); i++)
        for (int j = 0; j < E.size(); j++)
            if (sqrt(pow(bombs[i].first-E[j].Get_X(),2.0)+pow(bombs[i].second-E[j].Get_Y(),2.0) < E[j].Get_Rad()+3))
               return i;
    return -1;
}
    
void Bullet::Trigger_Bomb (int n)
{
     bombs.erase(bombs.begin()+n);
}

bool check_win (Player P, int finalpoints[4])
{
     return P.Get_X()/60==finalpoints[2] && P.Get_Y()/60==finalpoints[3];
}

pair <int,int[GRID_SIZE][GRID_SIZE]> bfs (int grid[GRID_SIZE][GRID_SIZE], Player p)
{
     pair <int,int[GRID_SIZE][GRID_SIZE]> check;
     pair <queue <int>,queue <int> > q;
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
             if (grid[i][j] == 1)
                check.second[i][j] = -1;
             else if (i == p.Get_X()/60 && j == p.Get_Y()/60)
             {
                  check.second[i][j] = 1;
                  q.first.push(i);
                  q.second.push(j);
             }
             else
                 check.second[i][j] = 0;
     int i,j;
     while (!q.second.empty())
     {
           i = q.first.front();
           j = q.second.front();
           if (check.second[i][j] == 30)
              break;
           if (check.second[i-1][j] == 0)
           {
              check.second[i-1][j] = check.second[i][j]+1;            
              q.first.push (i-1);
              q.second.push (j);
           }
           if (check.second[i+1][j] == 0)
           {
              check.second[i+1][j] = check.second[i][j]+1;
              q.first.push (i+1);
              q.second.push (j);
           }
           if (check.second[i][j-1] == 0)
           {
              check.second[i][j-1] = check.second[i][j]+1;
              q.first.push (i);
              q.second.push (j-1);
           }
           if (check.second[i][j+1] == 0)
           {
              check.second[i][j+1] = check.second[i][j]+1;
              q.first.push (i);
              q.second.push (j+1);
           }
           q.first.pop();
           q.second.pop();
     }
     return check;
}

vector <pair <string, int> > upgrade (Player p, Bullet b, int diff)
{
     pair <string, int> vals;
     vector <pair <string,int> > returnVals;
     while (key[KEY_U]) poll_keyboard();
     do {
          draw_upgrade(p,b);
         if (keypressed())
            readkey();
         if (key[KEY_F] && p.Get_Money() > 250*(11-p.Get_Rate())*(11-p.Get_Rate()) && p.Get_Rate() > 2)
         {
            vals.first = "rate";
            vals.second = -1;
            returnVals.push_back(vals);
            p.Add_Money (-250*(11-p.Get_Rate())*(11-p.Get_Rate()));
            p.Set_Rate (p.Get_Rate()+vals.second);
            while (key[KEY_F]) poll_keyboard();
         }
         if (key[KEY_C] && p.Get_Money() >= 5*p.Get_ClipSize())
         {
            vals.first = "clip";
            vals.second = 2;
            returnVals.push_back(vals);
            p.Add_Money (-5*p.Get_ClipSize());
            p.Set_ClipSize (p.Get_ClipSize()+vals.second);
            while (key[KEY_C]) poll_keyboard();
         }
         if (key[KEY_R] && p.Get_Money() >= b.Get_Range()*2 && b.Get_Range() < 300)
         {
            vals.first = "range";
            vals.second = 2;
            returnVals.push_back(vals);
            p.Add_Money (-b.Get_Range()*2);
            b.Set_Range (b.Get_Range()+vals.second);
            while (key[KEY_R]) poll_keyboard();
         }
         if (key[KEY_H] && p.Get_Money() >= 100 && p.Get_InitialHealth() + diff*300 - 320 > p.Get_Health())
         {
            vals.first = "health";
            vals.second = 20;
            returnVals.push_back(vals);
            p.Add_Money (-100);
            p.Add_Health (vals.second);
            while (key[KEY_H]) poll_keyboard();
         }
         if (key[KEY_N] && p.Get_Money() >= 10000 && !p.Max_Quantity(0))
         {
            vals.first = "weapon";
            vals.second = 1;
            returnVals.push_back(vals);
            p.Add_Money (-10000);
            p.Set_Quantity(0,p.Get_Quantity(0)+1);
            while (key[KEY_N]) poll_keyboard();
         }
         if (key[KEY_W] && p.Get_Money() >= 1000 && !p.Max_Quantity(1))
         {
            vals.first = "weapon";
            vals.second = 2;
            returnVals.push_back(vals);
            p.Add_Money (-1000);
            p.Set_Quantity(1,p.Get_Quantity(1)+1);
            while (key[KEY_W]) poll_keyboard();
         }
         if (key[KEY_G] && p.Get_Money() >= 300 && !p.Max_Quantity(2))
         {
            vals.first = "weapon";
            vals.second = 3;
            returnVals.push_back(vals);
            p.Add_Money (-300);
            p.Set_Quantity(2,p.Get_Quantity(2)+1);
            while (key[KEY_G]) poll_keyboard();
         }
         if (key[KEY_E] && p.Get_Money() >= 8000 && !p.Max_Quantity(3))
         {
            vals.first = "weapon";
            vals.second = 4;
            returnVals.push_back(vals);
            p.Add_Money (-8000);
            p.Set_Quantity(3,p.Get_Quantity(3)+1);
            while (key[KEY_E]) poll_keyboard();
         }
         if (key[KEY_M] && p.Get_Money() >= 1000 && !p.Max_Quantity(4))
         {
            vals.first = "weapon";
            vals.second = 5;
            returnVals.push_back(vals);
            p.Add_Money (-1000);
            p.Set_Quantity(4,p.Get_Quantity(4)+1);
            while (key[KEY_T]) poll_keyboard();
         }
         if (key[KEY_S] && p.Get_Money() >= 5000 && !p.Max_Quantity(5))
         {
            vals.first = "weapon";
            vals.second = 6;
            returnVals.push_back(vals);
            p.Add_Money (-5000);
            p.Set_Quantity(5,p.Get_Quantity(5)+1);
            while (key[KEY_S]) poll_keyboard();
         }
     }while (!key[KEY_U] && !close_button_pressed);
     vals.first = "money";
     vals.second = p.Get_Money();
     returnVals.push_back (vals);
     return returnVals;
}

int next_weapon (Player P, int active)
{
    if (active == 1 && P.Get_Quantity(5))
       return 2;
    else if (active == 0 && P.Get_Quantity(2))
         return 1;
    else if (active == 0 && P.Get_Quantity(5))
         return 2;
    else return 0;
}

int prev_weapon (Player P, int active)
{
    if (active == 2 && P.Get_Quantity(2))
       return 1;
    else if (active == 0 && P.Get_Quantity(5))
         return 2;
    else if (active == 0 && P.Get_Quantity(2))
         return 1;
    else return 0;
}

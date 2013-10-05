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

void upgrade (Player &p, Bullet &b, int diff)
{
     while (key[KEY_U]) poll_keyboard();
     do {
          draw_upgrade(p,b);
         if (keypressed())
            readkey();
         if (key[KEY_F] && p.Get_Money() > 250*(11-p.Get_Rate())*(11-p.Get_Rate()) && p.Get_Rate() > 2)
         {
            p.Add_Money (-250*(11-p.Get_Rate())*(11-p.Get_Rate()));
            p.Set_Rate (p.Get_Rate()+vals.second);
            while (key[KEY_F]) poll_keyboard();
         }
         if (key[KEY_C] && p.Get_Money() >= 5*p.Get_ClipSize())
         {
            p.Add_Money (-5*p.Get_ClipSize());
            p.Set_ClipSize (p.Get_ClipSize()+vals.second);
            while (key[KEY_C]) poll_keyboard();
         }
         if (key[KEY_R] && p.Get_Money() >= b.Get_Range()*2 && b.Get_Range() < 300)
         {
            p.Add_Money (-b.Get_Range()*2);
            b.Set_Range (b.Get_Range()+vals.second);
            while (key[KEY_R]) poll_keyboard();
         }
         if (key[KEY_H] && p.Get_Money() >= 100 && diff*200 - 20 > p.Get_Added_Health())
         {
            p.Add_Money (-100);
            p.Add_Health (vals.second);
            while (key[KEY_H]) poll_keyboard();
         }
         if (key[KEY_N] && p.Get_Money() >= p.Get_Cost(0) && !p.Max_Quantity(0))
         {
            p.Add_Money (-p.Get_Cost(0));
            p.Set_Quantity(0,p.Get_Quantity(0)+1);
            while (key[KEY_N]) poll_keyboard();
         }
         if (key[KEY_W] && p.Get_Money() >= p.Get_Cost(1) && !p.Max_Quantity(1))
         {
            p.Add_Money (-p.Get_Cost(1));
            p.Set_Quantity(1,p.Get_Quantity(1)+1);
            while (key[KEY_W]) poll_keyboard();
         }
         if (key[KEY_G] && p.Get_Money() >= p.Get_Cost(2) && !p.Max_Quantity(2))
         {
            p.Add_Money (-p.Get_Cost(2));
            p.Set_Quantity(2,p.Get_Quantity(2)+1);
            while (key[KEY_G]) poll_keyboard();
         }
         if (key[KEY_E] && p.Get_Money() >= p.Get_Cost(3) && !p.Max_Quantity(3))
         {
            p.Add_Money (-p.Get_Cost(3));
            p.Set_Quantity(3,p.Get_Quantity(3)+1);
            while (key[KEY_E]) poll_keyboard();
         }
         if (key[KEY_M] && p.Get_Money() >= p.Get_Cost(4) && !p.Max_Quantity(4))
         {
            p.Add_Money (-p.Get_Cost(4));
            p.Set_Quantity(4,p.Get_Quantity(4)+1);
            while (key[KEY_T]) poll_keyboard();
         }
         if (key[KEY_S] && p.Get_Money() >= p.Get_Cost(5) && !p.Max_Quantity(5))
         {
            p.Add_Money (-p.Get_Cost(5));
            p.Set_Quantity(5,p.Get_Quantity(5)+1);
            while (key[KEY_S]) poll_keyboard();
         }
     }while (!key[KEY_U] && !close_button_pressed);
     return;
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

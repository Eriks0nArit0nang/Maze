void survival (pair <int[4],int[GRID_SIZE][GRID_SIZE]> grid)  // TODO Implement Survival Mode in Update
{
     Player P1;
     Bullet B1;
     P1.Set_XY(grid.first[0]*60+30,grid.first[1]*60+30);
     vector <Enemy> E;
     Enemy newEnemy;
     newEnemy.Init();
     newEnemy.Set_Coords (grid.first[2]*60+30,grid.first[3]*60+30);
     E.push_back(newEnemy);
   /*  bool known[120][120];
     for (int i = 0; i < 120; i++)
         for (int j = 0; j < 120; j++)
         {
             known[i][j] = false;
             if (abs(P1.Get_X()/60-i) <= 5 && abs(P1.Get_Y()/60-j) <= 5)
                known[i][j] = true;
         }
     bool * pknown[120];
     for (int i = 0; i < 120; i++)
         pknown[i] = known[i];*/
    
     int shotX = -1, shotY = -1, shots = 0;
     bool shot;
     int xC, yC; // to determine player movement
     int shotCounter = 0; // to slow down shooting
     int rate=100,count=0,timing=0; // the rate that enemies will enter
     bool moved; // if player moved for update
     updateScreen(P1,E,B1,-1,-1,false,key);
     install_int (ticker, 25);
     int score = 0; // enemies killed
     pair <int,int[GRID_SIZE][GRID_SIZE]> Enemy_Squares;
    
     while (!close_button_pressed || key[KEY_ESC])
     {
           while (ticks > 0)
           {
               count++;
               timing++;
               if (count % rate == 0)
               {
                  newEnemy.Init();
                  E.push_back(newEnemy);
                  count = 0;
                  rate = 100 - timing/1000;
                  if (rate < 3)
                     rate = 3;
               }
               ticks--;
               Enemy_Squares = bfs (grid.second, P1);
               shot = false;
               for (int i = 0; i < E.size(); i++)
               {
                   E[i].Update(P1,grid.second,Enemy_Squares.second);
                   if (E[i].Dead())
                   {
                      score++;
                      E.erase(E.begin()+i);
                      i--;
                   }
                   if (E[i].Attack(P1))
                   {
                      P1.Hit(E[i].Get_Strength());
                      if (E[i].Get_Type() > 4)
                         shot = true;
                   }
               }
               if (keypressed())
                  readkey();
               poll_mouse();
             /*  if (mouse_x >= SCREEN_X && mouse_y >= 0 && mouse_x < SCREEN_X+240 && mouse_y < 240 && mouse_y >= 0)
               {
                  zoom (grid.second,known,(mouse_x-(SCREEN_X))/2,mouse_y/2,P1,E);
               }
               else
               {
                   zoom (grid.second,known,P1.Get_X()/60,P1.Get_Y()/60,P1,E);
               }*/
               xC = 0;
               yC = 0;
               moved = false;
               if (key[KEY_UP] || key[KEY_DOWN] || key[KEY_LEFT] || key[KEY_RIGHT])
                  moved = true;
               if (key[KEY_UP])
               {
                  yC -= 1;
               }
               if (key[KEY_DOWN])
               {
                  yC += 1;
               }
               if (key[KEY_LEFT])
               {
                  xC -= 1;
               }
               if (key[KEY_RIGHT])
               {
                  xC += 1;
               }
               P1.Move(xC,yC,grid.second);
               if (shotCounter <= 0)
               {
                   if (key[KEY_W])
                   {
                      shotY = B1.Shoot (E,P1,3,grid.second);
                      shotX = P1.Get_X();
                      shotCounter = 10;
                      shots++;
                   }
                   else if (key[KEY_S])
                   {
                      shotY = B1.Shoot (E,P1,2,grid.second);
                      shotX = P1.Get_X();
                      shotCounter = 10;
                      shots++;
                   }
                   else if (key[KEY_A])
                   {
                      shotX = B1.Shoot (E,P1,1,grid.second);
                      shotY = P1.Get_Y();
                      shotCounter = 10;
                      shots++;
                   }
                   else if (key[KEY_D])
                   {
                      shotX = B1.Shoot (E,P1,0,grid.second);
                      shotY = P1.Get_Y();
                      shotCounter = 10;
                      shots++;
                   }
                   if (shotX > -1 && shotY > -1)
                   {
                      for (int i = 0; i < E.size(); i++)
                          E[i].Shot (shotX, shotY, rand () % 10 + 1,P1.Get_Quantity(1)*3);
                      if (shots % P1.Get_ClipSize() == 0)
                         shotCounter = 60;
                   }
                   else if (shotX == -1 || shotY == -1)
                       shotCounter = 20;
               }
               else
               {
                   if (!(key[KEY_W]|| key[KEY_A] || key[KEY_S] || key[KEY_D]) && shotCounter <= 10)
                      shotCounter = 0;
                   shotCounter--;
                   shotX = -2;
                   shotY = -2;
               }
          /*     if (moved)
               {
                  update_known (pknown, P1.Get_X()/60, P1.Get_Y()/60);
                  update_map (grid.second,P1.Get_X()/60, P1.Get_Y()/60);
               }*/
               updateScreen(P1,E,B1, shotX, shotY,shot,key);
               rectfill (screen,SCREEN_X,0,SCREEN_X+GRID_SIZE*2,GRID_SIZE*4,makecol(0,0,0));
               rectfill (screen,SCREEN_X,540,SCREEN_X+GRID_SIZE*4,560,makecol(0,0,0));
               textprintf_ex(screen, font, 605, 540, makecol(255,0,0), -1, "Enemies Killed %d", score);
               if (P1.Get_Health() < 0)
                  break;
           }
           if (P1.Get_Health() < 0)
              break;
     }
     cout << "Congrats\n";
}

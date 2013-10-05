Player play_level (pair <int[4],int[GRID_SIZE][GRID_SIZE]> grid, Player P1, int diff = 6, int diffMult = 1)
{
    // Player P1;
     Bullet B1;
     B1.Set_Range(P1.Get_Range());
     P1.Set_XY(grid.first[0]*60+30,grid.first[1]*60+30);
     vector <Enemy> E;
     E.resize (GRID_SIZE*GRID_SIZE/200*diff*diffMult);
     int x1,y1;
     for (int i = 0; i < E.size(); i++)
     {
         E[i].Init();
         do 
         {
             x1 = rand () % GRID_SIZE;
             y1 = rand () % GRID_SIZE;
         } while (grid.second[x1][y1] == 1 || grid.second[x1][y1] == 2);
         E[i].Set_Coords (x1*60+30,y1*60+30);
     }
     
     bool known[GRID_SIZE][GRID_SIZE];
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
         {
             known[i][j] = false;
             if (abs(P1.Get_X()/60-i) <= 5 && abs(P1.Get_Y()/60-j) <= 5)
                known[i][j] = true;
         }
     bool * pknown[GRID_SIZE];
     for (int i = 0; i < GRID_SIZE; i++)
         pknown[i] = known[i];
    
     int shotX = -1, shotY = -1, shots = 0;
     int bombX, bombY, bombN;
     bool shot;
     vector <pair <string, int> > upgrades;
     int xC, yC; // to determine player movement
     int shotCounter = 0; // to slow down shooting
     bool moved; // if player moved for update
     int wallAnimate = 0, wallX, wallY;
     updateScreen(P1,E,B1,-1,-1,false,key);
     install_int (ticker, 25);
    
     pair <int,int[GRID_SIZE][GRID_SIZE]> Enemy_Squares;
    
     while (!(close_button_pressed || key[KEY_ESC]))
     {
           while (ticks > 0)
           {
               ticks--;
               Enemy_Squares = bfs (grid.second, P1);
               shot = false;
               if ((P1.Get_ActiveWeapon() == 1 && P1.Get_Quantity(2) == 0)||(P1.Get_ActiveWeapon() == 2 && P1.Get_Quantity(5) == 0))
                  P1.Set_ActiveWeapon ( 0);
               for (int i = 0; i < E.size(); i++)
               {
                   E[i].Update(P1,grid.second,Enemy_Squares.second);
                   if (E[i].Dead())
                   {
                      P1.Add_Money (E[i].Get_InitialHealth()*(E[i].Get_Type()%2+1)*(E[i].Get_Type()/5+1));
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
               if (key[KEY_U])
               {
                  upgrade (P1,B1,diff);
               /*   for (int i = 0; i < upgrades.size(); i++)
                  {
                      if (upgrades[i].first == "rate")
                         P1.Set_Rate (P1.Get_Rate()+upgrades[i].second);
                      else if (upgrades[i].first == "clip") 
                      {
                           P1.Set_ClipSize (P1.Get_ClipSize()+upgrades[i].second);
                           shots = P1.Get_ClipSize();
                      }
                      else if (upgrades[i].first == "range")
                           B1.Set_Range (B1.Get_Range()+upgrades[i].second);
                      else if (upgrades[i].first == "health")
                           P1.Add_Health (upgrades[i].second);
                      else if (upgrades[i].first == "weapon")
                      {
                           if (!P1.Max_Quantity(upgrades[i].second-1))
                              P1.Set_Quantity (upgrades[i].second-1,P1.Get_Quantity(upgrades[i].second-1)+1);
                      }
                      else if (upgrades[i].first == "money")
                           P1.Add_Money (upgrades[i].second-P1.Get_Money());
                  }*/
                  updateScreen (P1,E,B1,shotX, shotY,shot,key);
                  while (key[KEY_U]) poll_keyboard();
                  ticks = 0;
               }
               poll_mouse();
               if (mouse_x >= SCREEN_X && mouse_y >= 0 && mouse_x < SCREEN_X+GRID_SIZE*2 && mouse_y < GRID_SIZE*2 && mouse_y >= 0)
               {
                  zoom (grid.second,known,(mouse_x-(SCREEN_X))/2,mouse_y/2,P1,E);
               }
               else
               {
                   zoom (grid.second,known,P1.Get_X()/60,P1.Get_Y()/60,P1,E);
               }
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
               if (key[KEY_N] && P1.Get_Quantity(0) > 0)
               {
                  for (int i = 0; i < E.size(); i++)
                      if (abs (E[i].Get_X() - P1.Get_X()) < 300 && abs (E[i].Get_Y() - P1.Get_Y()) < 300)
                      {
                         P1.Add_Money (E[i].Get_InitialHealth()*(E[i].Get_Type()%2+1)*((E[i].Get_Type()+2)%3+1)/10);
                         E.erase(E.begin()+i);
                         i--;
                      }
                  P1.Set_Quantity(0,0);
                  nuke_animation ();
               }
               if (key[KEY_C] && P1.Get_Quantity(4) > 0)
               {
                  B1.Place_Bomb(P1.Get_X(),P1.Get_Y());
                  P1.Set_Quantity(4,P1.Get_Quantity(4)-1);
                  while (key[KEY_C]) poll_keyboard();
               }
               if (key[KEY_X])
               {
                  P1.Set_ActiveWeapon( next_weapon(P1,P1.Get_ActiveWeapon()));
                  while (key[KEY_X]) poll_keyboard();
               }
               else if (key[KEY_Z])
               {
                  P1.Set_ActiveWeapon( prev_weapon(P1,P1.Get_ActiveWeapon()));
                  while (key[KEY_Z]) poll_keyboard();
               }
               bombN = B1.Hit_Bomb(E);
               if (bombN > -1)
               {
                  bombY = B1.Get_BombY(bombN);
                  bombX = B1.Get_BombX(bombN);
                  for (int i = 0; i < E.size(); i++)
                      E[i].Shot (bombX, bombY, rand () % 20 + 20,40);
                  B1.Trigger_Bomb(bombN);
               }
               if (B1.Grenade(E,P1,-1,grid.second) > -1)
               {
                  shotX = B1.Get_GrenadeX();
                  shotY = B1.Get_GrenadeY();
                  for (int i = 0; i < E.size();i++)
                      E[i].Shot (shotX, shotY, rand () % 20 + 1,40);
                  P1.Set_ActiveWeapon (1);
               }
               else if (shotCounter <= 0)
               {
                    shotX = -2;
                    shotY = -2;
                  if (key[KEY_W])
                  {
                     if (P1.Get_ActiveWeapon() == 0)
                         shotY = B1.Shoot (E,P1,3,grid.second);
                     else if (P1.Get_ActiveWeapon() == 1)
                         shotY = B1.Grenade (E,P1,3,grid.second);
                     else if (P1.Get_ActiveWeapon() == 2)
                         shotY = B1.Walls (E,P1,3,grid.second);
                     shotX = P1.Get_X();
                     shotCounter = P1.Get_Rate();
                     shots++;
                  }
                  else if (key[KEY_S])
                  {
                     if (P1.Get_ActiveWeapon() == 0)
                         shotY = B1.Shoot (E,P1,2,grid.second);
                     else if (P1.Get_ActiveWeapon() == 1)
                         shotY = B1.Grenade (E,P1,2,grid.second);
                     else if (P1.Get_ActiveWeapon() == 2)
                         shotY = B1.Walls (E,P1,2,grid.second);
                     shotX = P1.Get_X();
                     shotCounter = P1.Get_Rate();
                     shots++;
                  }
                  else if (key[KEY_A])
                  {
                     if (P1.Get_ActiveWeapon() == 0)
                         shotX = B1.Shoot (E,P1,1,grid.second);
                     else if (P1.Get_ActiveWeapon() == 1)
                         shotX = B1.Grenade (E,P1,1,grid.second);
                     else if (P1.Get_ActiveWeapon() == 2)
                         shotX = B1.Walls (E,P1,1,grid.second);
                     shotY = P1.Get_Y();
                     shotCounter = P1.Get_Rate();
                     shots++;
                  }
                  else if (key[KEY_D])
                  {
                     if (P1.Get_ActiveWeapon() == 0)
                         shotX = B1.Shoot (E,P1,0,grid.second);
                     else if (P1.Get_ActiveWeapon() == 1)
                         shotX = B1.Grenade (E,P1,0,grid.second);
                     else if (P1.Get_ActiveWeapon() == 2)
                         shotX = B1.Walls (E,P1,0,grid.second);
                     shotY = P1.Get_Y();
                     shotCounter = P1.Get_Rate();
                     shots++;
                  }
                  if ((key[KEY_W]|| key[KEY_A] || key[KEY_S] || key[KEY_D])&&P1.Get_ActiveWeapon()==1&&shotX > -2&&shotY>-2)
                  {
                     P1.Set_Quantity (2,P1.Get_Quantity(2)-1);
                  }
                  if (shotX > -1 && shotY > -1 && P1.Get_ActiveWeapon() == 0)
                  {
                     if (!P1.Get_Quantity(3))
                     {
                         for (int i = 0; i < E.size(); i++)
                             E[i].Shot (shotX, shotY, rand () % 10 + 1,P1.Get_Quantity(1)*3);
                     }
                     else
                     {
                         for (int i = 0; i < E.size(); i++)
                             E[i].Shot (shotX, shotY, rand () % 10 + 1,30);
                     }
                     if (shots % P1.Get_ClipSize() == 0)
                        shotCounter = P1.Get_Rate()*6;
                  }
                  else if (shotX > -1 && shotY > -1 && P1.Get_ActiveWeapon() == 1)
                  {
                       P1.Set_Quantity(2,P1.Get_Quantity(2)-1);
                       for (int i = 0; i < E.size(); i++)
                             E[i].Shot (shotX, shotY, rand () % 10 + 1,40);
                  }
                  else if (shotX > -1 && shotY > -1 && P1.Get_ActiveWeapon() == 2)
                  {
                       grid.second[shotX/60][shotY/60] = 0;
                       P1.Set_Quantity(5,P1.Get_Quantity(5)-1);
                       rectfill (background, shotX/60*60, shotY/60*60, shotX/60*60+59, shotY/60*60+59, makecol (255,255,255));
                       wallX = SCREEN_X/2+shotX/60*60;
                       wallY = SCREEN_Y/2+shotY/60*60;
                       wallAnimate = 51;
                       ticks=0;
                  }
                  else if (shotX == -1 || shotY == -1)
                      shotCounter = P1.Get_Rate()*2;
              }
              else
              {
                  if (!(key[KEY_W]|| key[KEY_A] || key[KEY_S] || key[KEY_D]) && shotCounter <= P1.Get_Rate())
                     shotCounter = 0;
                  shotCounter--;
                  shotX = -2;
                  shotY = -2;
              }
              if (moved)
              {
                 update_known (pknown, P1.Get_X()/60, P1.Get_Y()/60);
                 update_map (grid.second,P1.Get_X()/60, P1.Get_Y()/60);
              }
              updateScreen(P1,E,B1,shotX, shotY,shot,key);
              if (wallAnimate > 0)
              {
                 wall_animation(wallX-P1.Get_X(), wallY-P1.Get_Y(), wallX-P1.Get_X()+59, wallY-P1.Get_Y()+59,51-wallAnimate);
                 wallAnimate--;
                 rest(5);
              }
              if (check_win(P1, grid.first)||P1.Get_Health() < 0)
                 break;
          }
          if (check_win(P1, grid.first)||P1.Get_Health() < 0)
             break;
     }
     P1.Set_Range(B1.Get_Range());
     if (close_button_pressed || key[KEY_ESC])
        return P1;
     if (!check_win(P1, grid.first))
         cout << "PLEASE TRY AGAIN NEXT TIME\n";
     return P1;
}

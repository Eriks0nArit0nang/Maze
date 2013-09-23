Player multiplayer ()
{
       cout << "How many players?\n";
       int n;
       cin >> n;
       Player players[n];
       int best_level[n];
       int diff = -1;
       cout << "Enter the difficulty you want to play at?\n1-Easy\n2-Medium\n3-Hard\n4-Expert\n5-Nightmare\n";
       while (diff < 0 || diff > 5)
             cin >> diff;
       int winner; // will store the index of the last player to play a level
       pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
       string t;
       for (int i = 0; i < 100; i++)
       {
           stringstream t2;
           t2 << i+1;
           t = "Multiplayer/Level_";
           t += t2.str();
           t += ".txt";
           level = input_level (t);
           set_background (level.second);
           for (int j = 0; j < n; j++)
           {
               if (close_button_pressed || key[KEY_ESC])
                  break;
                                        
               rectfill (map,0,0,GRID_SIZE*2,600,makecol(100,100,100));
               if (players[j].Get_Health() > 0)
               {
                  best_level[j] = i+1;
                  winner = j;
                  clear_keybuf();
                  cout << "Press any key to continue player " << j+1;
                  rest(100);
                  players[j]=play_level (level,players[j],(i+1)/2);
               }
           }
           if (close_button_pressed || key[KEY_ESC])
              break;
       }
       if (close_button_pressed || key[KEY_ESC])
          return players[winner];
       for (int j = 0; j < n; j++)
           printf ("Player %d reached Level %d before dying.\n", j, best_level[j]);
       printf ("Player %d is the winner\n", winner);
       return players[winner];
}

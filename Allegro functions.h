
BITMAP* map;
BITMAP* background;
BITMAP* buffer;
BITMAP* wall;
BITMAP* player;
BITMAP* upgradescreen;
volatile int ticks = 0;  // for timer
volatile int close_button_pressed = FALSE; // for close button
const int SCREEN_X = 600;
const int SCREEN_Y = 600;

void ticker ()
{
     ticks++;
}
END_OF_FUNCTION(ticker);

void close_button_handler(void)
{
     close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

int rotate_realligned_sprite (BITMAP* screen, BITMAP* sprite, int x, int y, int angle)
{
      int size_x = sprite -> w, size_y = sprite -> h; 
      if (abs(angle) == 64 || abs(angle) == 192)
         rotate_sprite (screen, sprite, x+(size_y-size_x)/2, y+(size_y-size_x)/2+60-size_y, itofix (angle));
      else
          rotate_sprite (screen, sprite, x, y+60-size_y, itofix (angle)); 
}

/*void music (bool& playing)
{     
     // Play Song
     if (playing)
     {
        stop_sample (song);
        playing = false;
     }
     else
     {
         play_sample (song,255,127,1000,1);
         playing = true;
     }
}*/

void updateScreen(Player P, vector <Enemy> E, Bullet B, int shotX, int shotY, bool shot, volatile char key[KEY_MAX], int activeWeapon)
{
     draw_sprite (buffer, background, -(P.Get_X()-SCREEN_X/2), -(P.Get_Y()-SCREEN_Y/2));
     draw_sprite (buffer, map, SCREEN_X, 0);
     circlefill (buffer, SCREEN_X+P.Get_X()/30, P.Get_Y()/30, 4, makecol (150,150,255));
     for (int i = 0; i < E.size(); i++)
         if (abs (E[i].Get_X () - P.Get_X()) < 300 && abs (E[i].Get_Y() - P.Get_Y()) < 300)
         {
            if (E[i].Get_Type() == 3 || E[i].Get_Type() == 4)
            {
               int x = SCREEN_X/2+E[i].Get_X()-P.Get_X(), y = SCREEN_Y/2+E[i].Get_Y()-P.Get_Y();
               triangle (buffer, x,y+E[i].Get_Rad()/2,x+3*E[i].Get_Rad()/2,y,x-3*E[i].Get_Rad()/2,y,makecol(255,0,0));
            }
            if (E[i].Get_Type() <= 4)
               circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,255,0));
            else
                circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,150,150));
            circlefill (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad()-E[i].Get_Health()/10-1, makecol (255,0,0));
            circle (buffer, SCREEN_X/2+E[i].Get_X()-P.Get_X() , SCREEN_Y/2+E[i].Get_Y()-P.Get_Y() , E[i].Get_Rad(), makecol (255,0,0));
         }
     if (shotX > -1 && shotY > -1 && activeWeapon == 0)
     {
        if (key[KEY_W] || key[KEY_S])
           for (int i = 0; i <= P.Get_Quantity(1)*3;i++)
           {
               vline (buffer, SCREEN_X/2+i, SCREEN_Y/2+shotY-P.Get_Y(), SCREEN_Y/2, makecol (255,0,0));
               vline (buffer, SCREEN_X/2-i, SCREEN_Y/2+shotY-P.Get_Y(), SCREEN_Y/2, makecol (255,0,0));
           }
        else if (key[KEY_A] || key[KEY_D])
             for (int i = 0; i <= P.Get_Quantity(1)*3;i++)
             {
                 hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2+shotX-P.Get_X(), makecol (255,0,0));
                 hline (buffer, SCREEN_X/2, SCREEN_Y/2-i, SCREEN_X/2+shotX-P.Get_X(), makecol (255,0,0));
             }
        if (P.Get_Quantity(3))
           circlefill (buffer, SCREEN_X/2+shotX-P.Get_X(), SCREEN_Y/2+shotY-P.Get_Y(), 30, makecol (255,0,0));
     }
     else if (shotX > -1 && shotY > -1 && activeWeapon == 1)
     {
          circlefill (buffer, SCREEN_X/2+shotX-P.Get_X(), SCREEN_Y/2+shotY-P.Get_Y(), 40, makecol (255,0,0));
     }
     else if (shotX == -1 || shotY == -1)
     {
          if (key[KEY_W])
             for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                 vline (buffer, SCREEN_X/2+i, SCREEN_Y/2, SCREEN_Y/2-B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_A])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2-B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_S])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   vline (buffer, SCREEN_X/2+i, SCREEN_Y/2, SCREEN_Y/2+B.Get_Range(), makecol (255,0,0));
          else if (key[KEY_D])
               for (int i = -P.Get_Quantity(1)*3; i <= P.Get_Quantity(1)*3;i++)
                   hline (buffer, SCREEN_X/2, SCREEN_Y/2+i, SCREEN_X/2+B.Get_Range(), makecol (255,0,0));
     }
     if (B.Number_of_Bombs() > 0)
     {
        for (int i = 0; i < B.Number_of_Bombs(); i++)
            circlefill (buffer, SCREEN_X/2+B.Get_BombX(i)-P.Get_X(), SCREEN_Y/2+B.Get_BombY(i)-P.Get_Y(), 3, makecol(255,150,0));
     }
     if (B.Get_GrenadeTimer() > 0)
        circlefill (buffer, SCREEN_X/2+B.Get_GrenadeX()-P.Get_X(), SCREEN_Y/2+B.Get_GrenadeY()-P.Get_Y(), 2, makecol (0,64,0));
     if (!shot)
        circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, 5, makecol(0,0,255));
     else
     {
         circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, 5, makecol(255,0,0));
     }
     if (P.Get_InitialHealth()-P.Get_Health() >= 0)
        circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, (P.Get_InitialHealth()-P.Get_Health())/(P.Get_InitialHealth()/5), makecol(150,150,255)); 
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 500, makecol(255,0,0), -1, "Health: %d", P.Get_Health());
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 520, makecol(255,0,0), -1, "Enemies: %d", E.size());
     textprintf_ex(buffer, font, 500+GRID_SIZE*2, 540, makecol(255,0,0), -1, "Money: %d", P.Get_Money());
    // textprintf_ex(buffer, font, 605, 560, makecol(255,0,0), -1, "%d %d %d %d %d %d", P.Get_Quantity (0), P.Get_Quantity (1), P.Get_Quantity (2), P.Get_Quantity (3), P.Get_Quantity (4), P.Get_Quantity (5));
        
     scare_mouse();
     acquire_screen();
     draw_sprite (screen, buffer,0,0);
     release_screen(); 
     unscare_mouse();
}

void draw_upgrade (Player P, Bullet B)
{
     draw_sprite (buffer,upgradescreen,0,0);
     textprintf_ex(buffer, font, 180, 162, makecol(255,255,255), -1, "%d", P.Get_Rate());
     textprintf_ex(buffer, font, 180, 201, makecol(255,255,255), -1, "%d", P.Get_ClipSize());
     textprintf_ex(buffer, font, 180, 240, makecol(255,255,255), -1, "%d", B.Get_Range());
     textprintf_ex(buffer, font, 180, 279, makecol(255,255,255), -1, "%d", P.Get_Health());
     textprintf_ex(buffer, font, 300, 162, makecol(255,255,255), -1, "Money: %d", P.Get_Money());
     textprintf_ex(buffer, font, 400, 355, makecol(255,255,255), -1, "N %d", P.Get_Quantity(0));
     textprintf_ex(buffer, font, 400, 394, makecol(255,255,255), -1, "W %d", P.Get_Quantity(1));
     textprintf_ex(buffer, font, 400, 433, makecol(255,255,255), -1, "G %d", P.Get_Quantity(2));
     textprintf_ex(buffer, font, 400, 472, makecol(255,255,255), -1, "E %d", P.Get_Quantity(3));
     textprintf_ex(buffer, font, 400, 511, makecol(255,255,255), -1, "M %d", P.Get_Quantity(4));
     textprintf_ex(buffer, font, 400, 550, makecol(255,255,255), -1, "S %d", P.Get_Quantity(5));
     draw_sprite (screen,buffer,0,0);
}

void level_create_draw (int n[GRID_SIZE][GRID_SIZE])
{
     rectfill(buffer,0,0,SCREEN_X,SCREEN_Y,makecol(0,0,0));
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
             if (n[i][j] == 0)
                rectfill (buffer,i*(int)floor(600/GRID_SIZE),j*(int)floor(600/GRID_SIZE),i*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE)-1,j*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE),makecol(255,255,255));
             else if (n[i][j] == 2)
                rectfill (buffer,i*(int)floor(600/GRID_SIZE),j*(int)floor(600/GRID_SIZE),i*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE)-1,j*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE),makecol(255,0,0));
             else if (n[i][j] == 3)
                rectfill (buffer,i*(int)floor(600/GRID_SIZE),j*(int)floor(600/GRID_SIZE),i*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE)-1,j*(int)floor(600/GRID_SIZE)+(int)floor(600/GRID_SIZE),makecol(0,255,0));
             
     textprintf_ex(buffer, font, 0, 0, makecol(255,255,255), -1, "Create Your Level");
     textprintf_ex(buffer, font, 300, 0, makecol(255,255,255), -1, "Press Enter to Confirm Your Choice");
     draw_sprite(screen,buffer,0,0);
}

void set_background (int n[GRID_SIZE][GRID_SIZE])
{
     rectfill(background,0,0,GRID_SIZE*60,GRID_SIZE*60,makecol(0,0,0));
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
             if (n[i][j] == 0)
                rectfill (background,i*60,j*60,i*60+59,j*60+59,makecol(255,255,255));
             else if (n[i][j] == 2)
                rectfill (background,i*60,j*60,i*60+59,j*60+59,makecol(255,0,254));
             else if (n[i][j] == 3)
                rectfill (background,i*60,j*60,i*60+59,j*60+59,makecol(0,255,0));
}

void update_map (int n[GRID_SIZE][GRID_SIZE], int x, int y)
{
     for (int i = x-5; i < x+5 && i >= 0 && i < GRID_SIZE; i++)
         for (int j = y-5; j < y+5 && j >= 0 && j < GRID_SIZE; j++)
             if (n[i][j] == 0)
                rectfill (map,i*2,j*2,i*2+1,j*2+1,makecol(255,255,255));
             else if (n[i][j] == 1)
                rectfill (map,i*2,j*2,i*2+1,j*2+1,makecol(0,0,0));
             else if (n[i][j] == 2)
                rectfill (map,i*2,j*2,i*2+1,j*2+1,makecol(255,0,254));
             else if (n[i][j] == 3)
                rectfill (map,i*2,j*2,i*2+1,j*2+1,makecol(0,255,0));
}

void zoom (int n[GRID_SIZE][GRID_SIZE], bool b[GRID_SIZE][GRID_SIZE], int x, int y, Player p, vector <Enemy> E)
{
     rectfill (map,0,GRID_SIZE*2,GRID_SIZE*2,GRID_SIZE*4,makecol (100,100,100));
     for (int i = -(int)floor(GRID_SIZE/10); i < (int)floor(GRID_SIZE/10); i++)
         for (int j = -(int)floor(GRID_SIZE/10); j < (int)floor(GRID_SIZE/10); j++)
             if (i+x >= 0 && i+x < GRID_SIZE  && j+y >= 0 && j+y < GRID_SIZE)
                 if (b[x+i][y+j])
                 {
                     if (n[x+i][y+j] == 0)
                        rectfill (map,(i+(int)floor(GRID_SIZE/10))*10,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10,(i+(int)floor(GRID_SIZE/10))*10+9,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10+9,makecol(255,255,255));
                     else if (n[x+i][y+j] == 1)
                        rectfill (map,(i+(int)floor(GRID_SIZE/10))*10,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10,(i+(int)floor(GRID_SIZE/10))*10+9,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10+9,makecol(0,0,0));
                     else if (n[x+i][y+j] == 2)
                        rectfill (map,(i+(int)floor(GRID_SIZE/10))*10,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10,(i+(int)floor(GRID_SIZE/10))*10+9,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10+9,makecol(255,0,254));
                     else if (n[x+i][y+j] == 3)
                        rectfill (map,(i+(int)floor(GRID_SIZE/10))*10,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10,(i+(int)floor(GRID_SIZE/10))*10+9,GRID_SIZE*2+(j+(int)floor(GRID_SIZE/10))*10+9,makecol(0,255,0));
                 }
     for (int i = 0; i < E.size(); i++)
         if ((E[i].Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10 >= 0 && (E[i].Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10 < GRID_SIZE*2 && b[E[i].Get_X()/60][E[i].Get_Y()/60])
             for (int j = 0; j < 2; j++)
                 rect (map,(E[i].Get_X()/60-x+(int)floor(GRID_SIZE/10))*10+j,GRID_SIZE*2+(E[i].Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10+j,(E[i].Get_X()/60-x+(int)floor(GRID_SIZE/10))*10+9-j,GRID_SIZE*2+(E[i].Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10+9-j,makecol(255,0,0));
     if ((p.Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10 >= 0 && (p.Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10 < GRID_SIZE*2)
         for (int i = 0; i < 2; i++)
             rect (map,(p.Get_X()/60-x+(int)floor(GRID_SIZE/10))*10+i,GRID_SIZE*2+(p.Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10+i,(p.Get_X()/60-x+(int)floor(GRID_SIZE/10))*10+9-i,GRID_SIZE*2+(p.Get_Y()/60-y+(int)floor(GRID_SIZE/10))*10+9-i,makecol(0,0,255));
     
}

void nuke_animation ()
{
     for (int i = 1; i < 45; i++)
     {
         circlefill (buffer, SCREEN_X/2, SCREEN_Y/2, i*10, makecol(255,i*8,0));
         draw_sprite (screen, buffer, 0, 0);
         rest (1);
     }
}

void wall_animation (int x1, int y1, int x2, int y2, int i)
{
     rectfill (screen,x1,y1,x2,y2,makecol(i*5,i*5,i*5));
}

void start_allegro()
{
     allegro_init();
     
     install_mouse();
     install_keyboard();
     install_timer();
     install_sound(DIGI_AUTODETECT,MIDI_NONE,NULL);
     
     LOCK_VARIABLE(ticks);
     LOCK_FUNCTION(ticker);
     LOCK_FUNCTION(close_button_handler);
     set_close_button_callback(close_button_handler);
     set_color_depth (desktop_color_depth());
     set_gfx_mode( GFX_AUTODETECT, SCREEN_X+GRID_SIZE*2, SCREEN_Y, 0, 0); 
     
     show_mouse(screen);
     upgradescreen = load_bmp ("Upgrade.bmp",NULL);
     buffer=create_bitmap(SCREEN_X+GRID_SIZE*2,SCREEN_Y);
     map = create_bitmap(GRID_SIZE*2,600);
     rectfill (map,0,0,GRID_SIZE*2,GRID_SIZE*4,makecol(100,100,100));
     set_keyboard_rate(20,0);
     //allegro_create_display(100,100);
     // load pics
     background=create_bitmap(SCREEN_X*12,SCREEN_Y*12);
}

void close_allegro()
{
    // destroy_sample (song);
     destroy_bitmap(buffer);
     destroy_bitmap(background);
    // destroy_bitmap(bla);
     allegro_exit();
}

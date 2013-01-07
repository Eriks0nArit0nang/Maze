#include <string>
#include <fstream>
//#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

// Create levels

void output_level (string filename, int data[GRID_SIZE][GRID_SIZE], int endpoints[4])
{
     ofstream o;
     o.open (filename.c_str());
     for (int i = 0; i < 4; i++)
         o << endpoints[i] << " ";
     o << endl;
     for (int i = 0; i < GRID_SIZE; i++)
     {
         for (int j = 0; j < GRID_SIZE; j++)
             o << data[i][j] << " ";
         o << endl;
     }
     o.close();
}

pair <int[4],int[GRID_SIZE][GRID_SIZE]> input_level (string filename)
{
     pair <int[4],int[GRID_SIZE][GRID_SIZE]> grid;
     ifstream o;
     o.open (filename.c_str());
     if (!o.is_open())
        cout << "???";
     for (int i = 0; i < 4; i++)
         o >> grid.first[i];
     for (int i = 0; i < GRID_SIZE; i++)
     {
         for (int j = 0; j < GRID_SIZE; j++)
             o >> grid.second[i][j];
     }
     o.close();
     set_background(grid.second);
     return grid;
}


pair <int[4], int[GRID_SIZE][GRID_SIZE]> generate_level ()
{
     pair <int[4], int[GRID_SIZE][GRID_SIZE]> info;
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
             info.second[i][j] = 1;
     level_create_draw(info.second);
     while (!key[KEY_ENTER] && !close_button_pressed)
     {
           poll_mouse();
           if (abs ((GRID_SIZE-1)/2-mouse_x/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5 && abs ((GRID_SIZE-1)/2-mouse_y/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5)
           {
               if (mouse_b & 1)
                  info.second[mouse_x/(int)floor(600/GRID_SIZE)][mouse_y/(int)floor(600/GRID_SIZE)] = 0;
               if (mouse_b & 2)
                  info.second[mouse_x/(int)floor(600/GRID_SIZE)][mouse_y/(int)floor(600/GRID_SIZE)] = 1;
               level_create_draw(info.second);
           }
     }
     for (int i = 0; i < 4; i++)
         info.first[i] = -1;
     while (mouse_b&1 ||key[KEY_ENTER]+1==0){poll_mouse();poll_keyboard();}
     clear_keybuf();
     do{
        poll_mouse();
        if (mouse_b & 1)
            if (abs ((GRID_SIZE-1)/2-mouse_x/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5 && abs ((GRID_SIZE-1)/2-mouse_y/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5)
            {
               if (!(info.first[0] == -1 && info.first[1] == -1))
                  info.second[info.first[0]][info.first[1]] = 0;
               info.second[mouse_x/(int)floor(600/GRID_SIZE)][mouse_y/(int)floor(600/GRID_SIZE)] = 2;
               info.first[0] = mouse_x/(int)floor(600/GRID_SIZE);
               info.first[1] = mouse_y/(int)floor(600/GRID_SIZE);
               level_create_draw(info.second);
            }
        if (keypressed())
           readkey();
     }while (info.first[0] == -1 || info.first[1] == -1 || key[KEY_ENTER]+1==1);
     
     while (mouse_b&1 ||key[KEY_ENTER]+1==0){poll_mouse();poll_keyboard();}
     clear_keybuf();
     do{
        poll_mouse();
        if (mouse_b & 1)
            if (abs ((GRID_SIZE-1)/2-mouse_x/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5 && abs ((GRID_SIZE-1)/2-mouse_y/(int)floor(600/GRID_SIZE)) <= GRID_SIZE/2-5)
            {
               if (!(info.first[2] == -1 && info.first[3] == -1))
                  info.second[info.first[2]][info.first[3]] = 0;
               info.second[mouse_x/(int)floor(600/GRID_SIZE)][mouse_y/(int)floor(600/GRID_SIZE)] = 3;
               info.first[2] = mouse_x/(int)floor(600/GRID_SIZE);
               info.first[3] = mouse_y/(int)floor(600/GRID_SIZE);
               level_create_draw(info.second);
            }
        if (keypressed())
           readkey();
     }while (info.first[2] == -1 || info.first[3] == -1 || key[KEY_ENTER]+1==1);
     clear_keybuf();
     set_background(info.second);
     return info;
}


bool verify_level (int se[4], int n[GRID_SIZE][GRID_SIZE])
{
     int p[GRID_SIZE][GRID_SIZE];
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
             p[i][j] = n[i][j];
     pair <queue <int>,queue<int> > que;
     que.first.push(se[0]);
     que.second.push(se[1]);
     while (!que.first.empty())
     {
           if (p[que.first.front()][que.second.front()] != 1)
           {
               if (p[que.first.front()][que.second.front()] == 3)
                  return true;
               p[que.first.front()][que.second.front()] = 1;
               if (p[que.first.front()+1][que.second.front()] == 0 || p[que.first.front()+1][que.second.front()] == 3)
               {
                  que.first.push(que.first.front()+1);
                  que.second.push(que.second.front());
               }
               if (p[que.first.front()-1][que.second.front()] == 0 || p[que.first.front()-1][que.second.front()] == 3)
               {
                  que.first.push(que.first.front()-1);
                  que.second.push(que.second.front());
               }
               if (p[que.first.front()][que.second.front()+1] == 0 || p[que.first.front()][que.second.front()+1] == 3)
               {
                  que.first.push(que.first.front());
                  que.second.push(que.second.front()+1);
               }
               if (p[que.first.front()][que.second.front()-1] == 0 || p[que.first.front()][que.second.front()-1] == 3)
               {
                  que.first.push(que.first.front());
                  que.second.push(que.second.front()-1);
               }
           }
           que.first.pop();
           que.second.pop();
     }
     return false;
}

void update_known (bool* known[GRID_SIZE], int xP, int yP)
{
     for (int i = -5; i <= 5; i++)
         for (int j = -5; j <= 5; j++)
             *(known[xP+i]+yP+j) = true;
}

struct Prim_Values
{
       public:
              int x;
              int y;
              int x2;
              int y2;
              int weight;
};

struct comp{
bool operator()(Prim_Values x, Prim_Values y)
{
     return x.weight > y.weight;
}};

pair <int[4],int[GRID_SIZE][GRID_SIZE]> auto_level ()
{
     pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
     bool tocheck[GRID_SIZE][GRID_SIZE];
     for (int i = 0; i < GRID_SIZE; i++)
         for (int j = 0; j < GRID_SIZE; j++)
         {
             tocheck[i][j] = false;
             level.second[i][j] = 1;
         }
     int t,t2;
     Prim_Values vals [(int)floor(GRID_SIZE/2)-5][(int)floor(GRID_SIZE/2)-5][4];
     do {
         for (int i = 0; i < 4; i++)
             level.first[i] = (rand () % ((int)floor(GRID_SIZE/2)-7))*2+7;
     } while (level.first[0] == level.first[2] && level.first[1] == level.first[3]);
     priority_queue <Prim_Values,vector <Prim_Values>,comp> nums;
     for (int i = 0; i < (int)floor(GRID_SIZE/2)-5; i++)
         for (int j = 0; j < (int)floor(GRID_SIZE/2)-5; j++)
             for (int k = 0; k < 4; k++)
             {
                 vals[i][j][k].weight = rand () % 100000;
                 vals[i][j][k].x = i*2+5;
                 vals[i][j][k].y = j*2+5;
                 if (k % 2 == 0)
                 {
                       vals[i][j][k].x2 = i*2+5;
                       vals[i][j][k].y2 = j*2+3+k*2;//up left down right
                 }
                 else
                 {
                       vals[i][j][k].x2 = i*2+1+k*2;
                       vals[i][j][k].y2 = j*2+5;
                 }
                 level.second[i*2+5][j*2+5] = 0;
                // nums.push (vals[i][j][k]);
             }
     level.second[level.first[0]][level.first[1]] = 2;
     level.second[level.first[2]][level.first[3]] = 3;
     for (int i = 0; i < 4; i++)
         nums.push(vals[(level.first[0]-5)/2][(level.first[1]-5)/2][i]);
     while (!nums.empty())
     {
          // level_create_draw(level.second);
           if (!(tocheck[nums.top().x2][nums.top().y2]))
           {
              tocheck[nums.top().x2][nums.top().y2] = true;
              level.second[(nums.top().x2+nums.top().x)/2][(nums.top().y2+nums.top().y)/2] = 0;
              t = (nums.top().x2-5)/2;
              t2 = (nums.top().y2-5)/2;
              nums.pop();
              for (int i = 0; i < 4; i++)
                  if (t >= 0 && t < (int)floor(GRID_SIZE/2)-5 && t2 >= 0 && t2 < (int)floor(GRID_SIZE/2)-5)
                  {
                     if (!(t == 0&&i==1)&&!(t==(int)floor(GRID_SIZE/2)-6&&i==3)&&!(t2==0&&i==0)&&!(t2==(int)floor(GRID_SIZE/2)-6&&i==2))
                        nums.push (vals[t][t2][i]);
                  }
           }
           else
               nums.pop();
     }
     set_background (level.second);
     cout << "Done\n";
     return level;
}

void create_game ()
{
     pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
     string t;
     for (int i = 0; i < 20; i++)
     {
         stringstream t2;
         t2 << i+1;
         t = "Game 6/Level_";
         t += t2.str();
         t+= ".txt";
         cout << t << endl;
         level = auto_level ();
         output_level (t,level.second,level.first);
     }
}

void play_game ()
{
     cout << "Enter the game you wish to play\n";
     string in,t;
     getline (cin, in);
     pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
     Player user;
     for (int i = 0; i < 20; i++)
     {
         stringstream t2;
         t2 << i+1;
         t = in + "/Level_";
         t += t2.str();
         t+= ".txt";
         level = input_level (t);
         set_background (level.second);
         rectfill (map,0,0,GRID_SIZE*2,600,makecol(100,100,100));
         if (user.Get_Health() > 0)
            user=play_level (level,user,i+1);
     }
     if (user.Get_Health() > 0 && !close_button_pressed)
        cout << "WINNER\n";
}

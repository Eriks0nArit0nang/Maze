#include "Game.h"
#include "Map.h"
#include "Display.h"
#include "Input.h"
#include "Player.h"
#include "StandardEnemy.h"
#include <sstream>
#include <iostream>
#include <ctime>

using namespace std;

Game *Game::instance = 0;

Game *Game::GetInstance()
{
    if (!instance)
        instance = new Game();
    return instance;
}
  
void Game::RemoveInstance()
{
    delete instance;
    instance = 0;
}

Player *Game::GetPlayer()
{
    return player;
}

std::vector<StandardEnemy *> &Game::GetEnemies()
{
    return enemies;
}

bool Game::GameEnd()
{
    if (player->Dead())
        return true;
    pair<int,int> end = Map::GetInstance()->GetEndLoc();
    if (end.first == player->GetX()/BOX_PIXEL_WIDTH && end.second == player->GetY()/BOX_PIXEL_WIDTH)
        return true;
    return false;
}

void Game::Play(std::string gameName, int diff)
{
    Map *map = Map::GetInstance();
    player = new Player(0,0);
    string t;
    for (int i = 0; i < 20; i++)
    {
        stringstream t2;
        t2 << i+1;
        t = gameName + "/Level_";
        t += t2.str();
        t+= ".txt";
        map->Load(t);
        Display::GetInstance()->SetBackground();
        
        if (player->GetHealth() > 0)
        {
            InitLevel(i+1,diff);
            PlayLevel();
            ResetLevel();
        }
        if (close_button_pressed || key[KEY_ESC])
            break;
     }
     if (player->GetHealth() > 0 && !close_button_pressed && !key[KEY_ESC])
        cout << "WINNER\n";
}

void Game::Create(std::string gameName)
{
    cout << "Creating game \"" << gameName << "\"...\n";
    Map *map = Map::GetInstance();
    string t;
    mkdir(gameName.c_str());
    for (int i = 0; i < 20; i++)
    {
        stringstream t2;
        t2 << i+1;
        t = gameName + "/Level_";
        t += t2.str();
        t+= ".txt";
        map->CreateAuto();
        map->Save(t);
    }
}
        
Game::Game():player(0){}

void Game::InitLevel(int level, int difficulty)
{
    srand(time(0));
    Map * mapInst = Map::GetInstance();
    mapInst->CreateAuto();
    pair<int,int> startLoc = mapInst->GetStartLoc();
    player->SetX(startLoc.first*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2);
    player->SetY(startLoc.second*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2);
    int numEnemies = level * difficulty * (GRID_SIZE/5);
    for (int i = 0; i < numEnemies; i++)
    {
        int x, y, health = (rand() % (MAX_ENEMY_HEALTH - 10)) + 10;
        do
        {
            x = rand() % mapInst->GetGridSize();
            y = rand() % mapInst->GetGridSize();
        } while (mapInst->GetGrid()[x][y] == 1 || (x == startLoc.first && y == startLoc.second));
        
        enemies.push_back(new StandardEnemy(health, x*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2, y*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2));
    }
    Display *display = display->GetInstance();
    display->SetBackground();
    display->UpdateMiniMap (player->GetX()/60,player->GetY()/60);
    display->Zoom(player->GetX()/60,player->GetY()/60);
    display->UpdateScreen();
}

void Game::ResetLevel()
{
    for (int i = 0; i < enemies.size(); i++)
        delete enemies[i];
    enemies.clear();
}

void Game::PlayLevel()
{
    Input * input = Input::GetInstance();
    Display * display = Display::GetInstance();
    display->UpdateScreen();
    while (!(close_button_pressed || key[KEY_ESC]))
    {
        while (input->GetTicks() > 0)
        {
            vector<Weapon *> playerWeapons;
            vector<Weapon *> enemyWeapons;
            input->ResetTicks();
            input->ReadInput();
            Map::GetInstance()->UpdateDistFromPlayer(player->GetX()/BOX_PIXEL_WIDTH,player->GetY()/BOX_PIXEL_WIDTH);
            
            if (input->GetMovement() >= 10000) // Upgrade
            {
                display->DrawUpgrade();
                display->UpdateScreen();;
                while (key[KEY_U]) poll_keyboard();
                input->ResetTicks();
            }
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Move();
                enemies[i]->Attack();
                
                vector<Weapon *> enemyWeapon = enemies[i]->GetWeapons();
                enemyWeapons.insert(enemyWeapons.end(),enemyWeapon.begin(), enemyWeapon.end());
            }
            player->Move();
            player->Attack();
            playerWeapons = player->GetWeapons();
            for(vector<Weapon *>::iterator weaponIt = enemyWeapons.begin(); weaponIt != enemyWeapons.end(); ++weaponIt)
            {
                (*weaponIt)->Action(player);
                (*weaponIt)->Update();
            }
            for(vector<Weapon *>::iterator weaponIt = playerWeapons.begin(); weaponIt != playerWeapons.end(); ++weaponIt)
            {
                for (int i = 0; i < enemies.size(); i++)
                    (*weaponIt)->Action(enemies[i]);
                if ((*weaponIt)->WillDestroy())
                {
                    (*weaponIt)->Notify();
                }
                (*weaponIt)->Update();
            }
            
            Map::GetInstance()->UpdateFog(player->GetX()/60, player->GetY()/60);

            pair<int, int> mouse_pos = input->GetMouse();
            if (mouse_pos.first >= SCREEN_X && mouse_pos.first < SCREEN_X+GRID_SIZE*2 && mouse_pos.second < GRID_SIZE*2 && mouse_pos.second >= 0)
                display->Zoom ((mouse_pos.first-(SCREEN_X))/2,mouse_pos.second/2);
            else
                display->Zoom (player->GetX()/60,player->GetY()/60);
            display->UpdateMiniMap (player->GetX()/60,player->GetY()/60);
            
            display->UpdateScreen();
            
            // TODO Identify if wall/nuke animations are implemented
            
            if (GameEnd())
                break;
                
          }
          if (GameEnd())
             break;
     }
}

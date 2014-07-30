#include "Game.h"
#include "Map.h"
#include "Display.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>

#define WINDOWS 1
#define LINUX 2

#define OS LINUX

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
    cerr << "Removing game instance\n";
    delete instance;
    instance = 0;
}

void Game::SetInstance(Game * game)
{
    if (instance)
        delete instance;
    instance = game;
}
        
Game::Game():player(0)
{
    ifstream in;
    in.open("valid_games.txt");
    string name;
    while(!in.fail())
    {
        getline(in, name);
        gameNames.push_back(name);
    }
}

Game::~Game()
{
    for (int i = 0; i < enemies.size(); i++)
        delete enemies[i];
    delete player;
}

Player *Game::GetPlayer()
{
    return player;
}

std::vector<Enemy *> &Game::GetEnemies()
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
        if (player->GetHealth() > 0)
        {
            InitLevel(i+1,diff,t);
            player->AddMoney(500*i);
            PlayLevel();
            ResetLevel();
        }
        if (close_button_pressed || key[KEY_ESC])
            break;
     }
     if (player->GetHealth() > 0 && !close_button_pressed && !key[KEY_ESC])
        cerr << "WINNER\n";
}

void Game::Create(std::string gameName)
{
    cerr << "Creating game \"" << gameName << "\"...\n";
    gameNames.push_back(gameName);
    Map *map = Map::GetInstance();
    string t;
    #if OS == WINDOWS
    mkdir(gameName.c_str());
    #elif OS == LINUX
    string t2 = "mkdir ";
    system((t2 + gameName).c_str());
    #endif
    
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
    
    ofstream out;
    out.open("valid_games.txt");
    string name;
    for (vector<string>::iterator it = gameNames.begin(); it < gameNames.end(); it++)
    {
        cerr << (*it) << endl;
        out << (*it) << endl;
    }
}

void Game::InitLevel(int level, int difficulty, string fileName)
{
    srand(time(0));
    EnemyFactory enemyFactory = EnemyFactory(difficulty);
    Map * mapInst = Map::GetInstance();
    if (fileName == "")
        mapInst->CreateAuto();
    else
        mapInst->Load(fileName);
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
        
        enemies.push_back(enemyFactory.Generate(health, x*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2, y*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2));
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
            Map::GetInstance()->UpdateDistFromPlayer(player->GetX()/BOX_PIXEL_WIDTH,player->GetY()/BOX_PIXEL_WIDTH, 30);
            
            if (input->GetMovement() >= 10000) // Upgrade
            {
                Upgrade();
                while (key[KEY_U]) poll_keyboard();
                input->ResetTicks();
            }
            for (int i = 0; i < enemies.size(); i++)
            {
                if (enemies[i]->Dead())
                {
                    player->AddMoney(enemies[i]->GetInitialHealth());
                    delete enemies[i];
                    enemies.erase(enemies.begin()+i);
                    i--;
                }
                else
                {
                    enemies[i]->Move();
                    enemies[i]->Attack();
                
                    vector<Weapon *> enemyWeapon = enemies[i]->GetWeapons();
                    enemyWeapons.insert(enemyWeapons.end(),enemyWeapon.begin(), enemyWeapon.end());
                }
            }
            player->Move();
            player->Attack();
            playerWeapons = player->GetWeapons();
            for(vector<Weapon *>::iterator weaponIt = enemyWeapons.begin(); weaponIt != enemyWeapons.end(); ++weaponIt)
            {
                if ((*weaponIt)->GetProperties().GetType() != _Gun)
                {
                    (*weaponIt)->Action(player);
                    if ((*weaponIt)->WillDestroy())
                    {
                        (*weaponIt)->Notify();
                    }
                    (*weaponIt)->Update();
                }
                else if ((*weaponIt)->WillDestroy())
                {
                    (*weaponIt)->Notify();
                    (*weaponIt)->Update();
                }
                else
                {
                    while (!(*weaponIt)->WillDestroy())
                    {
                        (*weaponIt)->Action(player);
                        if ((*weaponIt)->WillDestroy())
                            break;
                        (*weaponIt)->Update();
                    }
                }
            }
            for(vector<Weapon *>::iterator weaponIt = playerWeapons.begin(); weaponIt != playerWeapons.end(); ++weaponIt)
            {
                if ((*weaponIt)->GetProperties().GetType() != _Gun)
                {
                    (*weaponIt)->Action(player);
                    for (int i = 0; i < enemies.size(); i++)
                        (*weaponIt)->Action(enemies[i]);
                    if ((*weaponIt)->WillDestroy())
                    {
                        (*weaponIt)->Notify();
                    }
                    (*weaponIt)->Update();
                }
                else if ((*weaponIt)->WillDestroy())
                {
                    (*weaponIt)->Notify();
                    (*weaponIt)->Update();
                }
                else
                {
                    while (!(*weaponIt)->WillDestroy())
                    {
                        for (int i = 0; i < enemies.size(); i++)
                            (*weaponIt)->Action(enemies[i]);
                        if ((*weaponIt)->WillDestroy())
                            break;
                        (*weaponIt)->Update();
                    }
                }
            }
            
            Map::GetInstance()->UpdateFog(player->GetX()/60, player->GetY()/60);

            pair<int, int> mouse_pos = input->GetMouse();
            if (mouse_pos.first >= SCREEN_X && mouse_pos.first < SCREEN_X+GRID_SIZE*2 && mouse_pos.second < GRID_SIZE*2 && mouse_pos.second >= 0)
                display->Zoom ((mouse_pos.first-(SCREEN_X))/2,mouse_pos.second/2);
            else
                display->Zoom (player->GetX()/60,player->GetY()/60);
            display->UpdateMiniMap (player->GetX()/60,player->GetY()/60);
            
            display->UpdateScreen();
            
            if (GameEnd())
                break;
                
          }
          if (GameEnd())
             break;
     }
}

void Game::Upgrade()
{
    bool finished = false;
    int prevVals = 1;
    while (!finished && !close_button_pressed)
    {
        Display::GetInstance()->DrawUpgrade();
        Input::GetInstance()->ReadUpgrade();
        int upgradeVals = Input::GetInstance()->GetUpgrade();
        if (upgradeVals != prevVals && !close_button_pressed)
        {
            prevVals = upgradeVals;
            switch (upgradeVals)
            {
                case 1:
                    finished = true;
                    break;
                case 2:
                    player->UpgradeWeapon(_Gun, "rate");
                    break;
                case 4:
                    player->UpgradeWeapon(_Gun, "clip");
                    break;
                case 8:
                    player->UpgradeWeapon(_Gun, "range");
                    break;
                case 16:
                    player->UpgradeWeapon(_None, "health");
                    break;
                case 32:
                    player->UpgradeWeapon(_Nuke, "quantity");
                    break;
                case 64:
                    player->UpgradeWeapon(_WideShot, "quantity");
                    break;
                case 128:
                    player->UpgradeWeapon(_Grenade, "quantity");
                    break;
                case 256:
                    player->UpgradeWeapon(_ExplodingShot, "quantity");
                    break;
                case 512:
                    player->UpgradeWeapon(_Mine, "quantity");
                    break;
                case 1024:
                    player->UpgradeWeapon(_WallBreaker, "quantity");
                    break;
                default:
                    break;
            }
        }
    }
}

bool Game::Valid(std::string gameName)
{
    for (vector<string>::iterator it = gameNames.begin(); it < gameNames.end(); it++)
        if (*it == gameName)
            return true;
    return false;
}

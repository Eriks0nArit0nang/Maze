#include "SurvivalGame.h"
#include "EnemyFactory.h"
#include "Map.h"
#include "Display.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"

#include <utility>
#include <vector>

Game *SurvivalGame::NewInstance()
{
    Game::SetInstance(new SurvivalGame());
    return Game::GetInstance();
}

SurvivalGame::SurvivalGame():Game(),enemyFactory(0){}

SurvivalGame::~SurvivalGame()
{
    delete enemyFactory;
}

bool SurvivalGame::GameEnd()
{
    if (GetPlayer()->Dead())
        return true;
    return false;
}

void SurvivalGame::InitLevel(int level, int difficulty, std::string fileName)
{
    enemyFactory = new EnemyFactory(10);
    srand(time(0));
    Map * mapInst = Map::GetInstance();
    if (fileName == "")
        mapInst->CreateAuto(GRID_SIZE);
    else
        mapInst->Load(fileName);
    std::pair<int,int> startLoc = mapInst->GetStartLoc();
    GetPlayer()->SetX(startLoc.first*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2);
    GetPlayer()->SetY(startLoc.second*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2);
    int numEnemies = 3 * difficulty * (mapInst->GetGridSize()/5);
    for (int i = 0; i < numEnemies; i++)
    {
        int x, y, health = (rand() % (MAX_ENEMY_HEALTH - 10)) + 10;
        do
        {
            x = rand() % mapInst->GetGridSize();
            y = rand() % mapInst->GetGridSize();
        } while (mapInst->GetGrid()[x][y] == 1 || (x == startLoc.first && y == startLoc.second));
        
        GetEnemies().push_back(enemyFactory->Generate(health, x*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2, y*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2));
    }
    Display *display = display->GetInstance();
    display->SetBackground();
    display->UpdateMiniMap (GetPlayer()->GetX()/60,GetPlayer()->GetY()/60);
    display->Zoom(GetPlayer()->GetX()/60,GetPlayer()->GetY()/60);
    display->UpdateScreen();
}

void SurvivalGame::PlayLevel()
{
    Input * input = Input::GetInstance();
    Display * display = Display::GetInstance();
    display->UpdateScreen();
    int enemiesReleased = 0;
    int enemyDelay = 200;
    int nextEnemy = 800;
    std::pair<int,int> spawn = Map::GetInstance()->GetEndLoc();
    spawn.first = spawn.first*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2;
    spawn.second = spawn.second*BOX_PIXEL_WIDTH+BOX_PIXEL_WIDTH/2;
    while (!(input->IsClosed() || input->IsPressed(ALLEGRO_KEY_ESCAPE)))
    {
        input->ReadInput();
        while (input->Timer())
        {
            nextEnemy--;
            if (nextEnemy <= 0 || (GetEnemies().size() <= 3 && nextEnemy <= 50) || GetEnemies().size() == 0)
            {
                int health = (rand () % (MAX_ENEMY_HEALTH - 10)) + 10;
                GetEnemies().push_back(enemyFactory->Generate(health,spawn.first,spawn.second));
                enemiesReleased++;
                nextEnemy = enemyDelay;
                if (enemiesReleased % 50 == 0)
                {
                    enemyDelay = std::max(20,enemyDelay-10);
                }
            }
            
            std::vector<Weapon *> playerWeapons;
            std::vector<Weapon *> enemyWeapons;
            input->ReadInput();
            Map::GetInstance()->UpdateDistFromPlayer(GetPlayer()->GetX()/BOX_PIXEL_WIDTH,GetPlayer()->GetY()/BOX_PIXEL_WIDTH, 30);
            
            if (input->GetMovement() >= 10000) // Upgrade
            {
                Upgrade();
                while (input->IsPressed(ALLEGRO_KEY_U)) input->ReadInput();
                input->Timer();
            }
            for (unsigned int i = 0; i < GetEnemies().size(); i++)
            {
                if (GetEnemies()[i]->Dead())
                {
                    GetPlayer()->AddMoney(GetEnemies()[i]->GetInitialHealth());
                    delete GetEnemies()[i];
                    GetEnemies().erase(GetEnemies().begin()+i);
                    i--;
                }
                else
                {
                    GetEnemies()[i]->Move();
                    GetEnemies()[i]->Attack();
                
                    std::vector<Weapon *> enemyWeapon = GetEnemies()[i]->GetWeapons();
                    enemyWeapons.insert(enemyWeapons.end(),enemyWeapon.begin(), enemyWeapon.end());
                }
            }
            GetPlayer()->Move();
            GetPlayer()->Attack();
            playerWeapons = GetPlayer()->GetWeapons();
            for(std::vector<Weapon *>::iterator weaponIt = enemyWeapons.begin(); weaponIt != enemyWeapons.end(); ++weaponIt)
            {
                if ((*weaponIt)->GetProperties().GetType() != _Gun)
                {
                    (*weaponIt)->Action(GetPlayer());
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
                        (*weaponIt)->Action(GetPlayer());
                        if ((*weaponIt)->WillDestroy())
                            break;
                        (*weaponIt)->Update();
                    }
                }
            }
            for(std::vector<Weapon *>::iterator weaponIt = playerWeapons.begin(); weaponIt != playerWeapons.end(); ++weaponIt)
            {
                if ((*weaponIt)->GetProperties().GetType() != _Gun)
                {
                    (*weaponIt)->Action(GetPlayer());
                    for (unsigned int i = 0; i < GetEnemies().size(); i++)
                        (*weaponIt)->Action(GetEnemies()[i]);
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
                        for (unsigned int i = 0; i < GetEnemies().size(); i++)
                            (*weaponIt)->Action(GetEnemies()[i]);
                        if ((*weaponIt)->WillDestroy())
                            break;
                        (*weaponIt)->Update();
                    }
                }
            }
            
            Map::GetInstance()->UpdateFog(GetPlayer()->GetX()/60, GetPlayer()->GetY()/60);

            std::pair<int, int> mouse_pos = input->GetMouse();
            if (mouse_pos.first >= SCREEN_X && mouse_pos.first < SCREEN_X+MAX_GRID_SIZE*2 && mouse_pos.second < MAX_GRID_SIZE*2 && mouse_pos.second >= 0)
                display->Zoom ((mouse_pos.first-(SCREEN_X))/(2*MAX_GRID_SIZE/Map::GetInstance()->GetGridSize()),mouse_pos.second/(2*MAX_GRID_SIZE/Map::GetInstance()->GetGridSize()));
            else
                display->Zoom (GetPlayer()->GetX()/60,GetPlayer()->GetY()/60);
            display->UpdateMiniMap (GetPlayer()->GetX()/60,GetPlayer()->GetY()/60);
            
            display->UpdateScreen();
            
            if (GameEnd())
                break;
                
          }
          if (GameEnd())
             break;
     }
}

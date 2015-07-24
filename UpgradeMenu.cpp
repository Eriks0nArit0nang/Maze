#include "UpgradeMenu.h"
#include "Button.h"
#include "Player.h"
#include "Game.h"
#include "Globals.h"
#include "Input.h"
#include <iostream>

UpgradeMenu::UpgradeMenu(ALLEGRO_BITMAP *buffer)
{
	std::cerr << "initializing upgrade menu...\n";
    upgradeMenu = al_load_bitmap ("Upgrade.bmp");
    font=al_load_bitmap_font("a4_font.tga");
    std::cerr << "upgrade bitmap and font loaded\ninitializing init function...\n";
    Init(buffer);
    std::cerr << "upgrade menu initialized\n";
}

UpgradeMenu::~UpgradeMenu()
{
    al_destroy_bitmap(upgradeMenu);
    al_destroy_font(font);
}
 
void UpgradeMenu::Draw(ALLEGRO_BITMAP *buffer)
{
    Player &P = *Game::GetInstance()->GetPlayer();
    int rate = P.GetWeaponProperties(_Gun).GetFireRate();
    int clip = P.GetWeaponProperties(_Gun).GetClipSize();
    int range = P.GetWeaponProperties(_Gun).GetRange();
    int health = P.GetHealth();
    int money = P.GetMoney();
    WeaponProperties nuke = P.GetWeaponProperties(_Nuke);
    WeaponProperties wideShot = P.GetWeaponProperties(_WideShot);
    WeaponProperties grenade = P.GetWeaponProperties(_Grenade);
    WeaponProperties explodingShot = P.GetWeaponProperties(_ExplodingShot);
    WeaponProperties mine = P.GetWeaponProperties(_Mine);
    WeaponProperties wallBreaker = P.GetWeaponProperties(_WallBreaker);
    
    al_set_target_bitmap(buffer);
    al_draw_bitmap(upgradeMenu,0,0,0);
    
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-425, -1, "Current");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-425, -1, "Cost");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-425, -1, "Cost");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-425, -1, "Owned");
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-392, -1, "%d", health);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-392, -1, "%d", 100+P.GetAddedHealth()/4);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-342, -1, "%d", rate);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-342, -1, "%d", 500*(11-rate)*(11-rate));
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-292, -1, "%d", clip);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-292, -1, "%d", 10*clip);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-242, -1, "%d", range);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-242, -1, "%d", 100*(range/BOX_PIXEL_WIDTH));
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-392, -1, "%d", nuke.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-392, -1, "%d", nuke.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-342, -1, "%d", wideShot.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-342, -1, "%d", wideShot.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-292, -1, "%d", explodingShot.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-292, -1, "%d", explodingShot.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-242, -1, "%d", wallBreaker.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-242, -1, "%d", wallBreaker.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-192, -1, "%d", mine.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-192, -1, "%d", mine.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-142, -1, "%d", grenade.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-142, -1, "%d", grenade.GetCost());
       
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-500, SCREEN_Y-450, -1, "Money: %d", money);
    
    buttonManager.Update();
    buttonManager.Render(buffer);
    al_flip_display();
}

void UpgradeMenu::Init(ALLEGRO_BITMAP *buffer)
{
    Button *health = new Button();
    health->SetCaption("Add Health (H)");
    health->SetSize(100, 30);
    health->Create();
    health->OnClick = UpgradeMenu::Health;
    health->SetPosition(SCREEN_X-580, SCREEN_Y-405);
    buttonManager.AddButton(health);
    std::cerr << "health button created\n";
    Button *rate = new Button();
    rate->SetCaption("Fire Rate (F)");
    rate->SetSize(100, 30);
    rate->Create();
    rate->OnClick = UpgradeMenu::FireRate;
    rate->SetPosition(SCREEN_X-580, SCREEN_Y-355);
    buttonManager.AddButton(rate);
    std::cerr << "rate button created\n";
    Button *clip = new Button();
    clip->SetCaption("Larger Clip (C)");
    clip->SetSize(100, 30);
    clip->Create();
    clip->OnClick = UpgradeMenu::ClipSize;
    clip->SetPosition(SCREEN_X-580, SCREEN_Y-305);
    buttonManager.AddButton(clip);
    std::cerr << "clip button created\n";
    Button *range = new Button();
    range->SetCaption("Increase Range (R)");
    range->SetSize(100, 30);
    range->Create();
    range->OnClick = UpgradeMenu::Range;
    range->SetPosition(SCREEN_X-580, SCREEN_Y-255);
    buttonManager.AddButton(range);
    std::cerr << "range button created\n";
    Button *nuke = new Button();
    nuke->SetCaption("Buy Nuke (N)");
    nuke->SetSize(100, 30);
    nuke->Create();
    nuke->OnClick = UpgradeMenu::Nuke;
    nuke->SetPosition(SCREEN_X-280, SCREEN_Y-405);
    buttonManager.AddButton(nuke);
    std::cerr << "nuke button created\n";
    Button *wide = new Button();
    wide->SetCaption("Wider Shots (W)");
    wide->SetSize(100, 30);
    wide->Create();
    wide->OnClick = UpgradeMenu::WideShot;
    wide->SetPosition(SCREEN_X-280, SCREEN_Y-355);
    buttonManager.AddButton(wide);
    std::cerr << "wideshot button created\n";
    Button *explode = new Button();
    explode->SetCaption("Exploding Shots (E)");
    explode->SetSize(100, 30);
    explode->Create();
    explode->OnClick = UpgradeMenu::ExplodingShot;
    explode->SetPosition(SCREEN_X-280, SCREEN_Y-305);
    buttonManager.AddButton(explode);
    std::cerr << "exploding shot button created\n";
    Button *walls = new Button();
    walls->SetCaption("Buy WallBreaker (S)");
    walls->SetSize(100, 30);
    walls->Create();
    walls->OnClick = UpgradeMenu::WallBreaker;
    walls->SetPosition(SCREEN_X-280, SCREEN_Y-255);
    buttonManager.AddButton(walls);
    std::cerr << "wallbreaker button created\n";
    Button *mine = new Button();
    mine->SetCaption("Buy Mine (M)");
    mine->SetSize(100, 30);
    mine->Create();
    mine->OnClick = UpgradeMenu::Mine;
    mine->SetPosition(SCREEN_X-280, SCREEN_Y-205);
    buttonManager.AddButton(mine);
    std::cerr << "mine button created\n";
    Button *grenade = new Button();
    grenade->SetCaption("Buy Grenade (G)");
    grenade->SetSize(100, 30);
    grenade->Create();
    grenade->OnClick = UpgradeMenu::Grenade;
    grenade->SetPosition(SCREEN_X-280, SCREEN_Y-155);
    buttonManager.AddButton(grenade);
    std::cerr << "grenade button created\n";
    Button *resume = new Button();
    resume->SetCaption("Resume (U)");
    resume->SetSize(100, 30);
    resume->Create();
    resume->OnClick = UpgradeMenu::Resume;
    resume->SetPosition(SCREEN_X-530, SCREEN_Y-155);
    buttonManager.AddButton(resume);
    std::cerr << "resume button created\n";
}

ButtonManager &UpgradeMenu::GetButtonManager()
{
    return buttonManager;
}

void UpgradeMenu::Health(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_H);
}

void UpgradeMenu::FireRate(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_F);
}

void UpgradeMenu::ClipSize(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_C);
}

void UpgradeMenu::Range(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_R);
}

void UpgradeMenu::Nuke(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_N);
}

void UpgradeMenu::WideShot(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_W);
}

void UpgradeMenu::ExplodingShot(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_E);
}

void UpgradeMenu::WallBreaker(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_S);
}

void UpgradeMenu::Mine(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_M);
}

void UpgradeMenu::Grenade(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_G);
}

void UpgradeMenu::Resume(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_U);
}

#include "WideShot.h"
#include <cmath>

WideShot::WideShot(AbstractGun *gun):AbstractGunDecorator(gun)
{
    WeaponProperties properties(_WideShot, 0);
    GetProperties().radius = properties.GetRadius();
    GetProperties().damage += properties.GetDamage();
}

void WideShot::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    al_set_target_bitmap(buffer);
    al_draw_line (midX+GetX(), midY+GetY(), midX+(int)round(xPosOrig), midY+(int)round(yPosOrig), al_map_rgb (255,0,0), 3);
    gun->Draw(buffer, midX, midY);
}

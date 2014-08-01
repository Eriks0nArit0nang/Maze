#include "ExplodingShot.h"
#include <allegro5/allegro_primitives.h>

ExplodingShot::ExplodingShot(AbstractGun * gun):AbstractGunDecorator(gun)
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().damage += properties.GetDamage();
}

void ExplodingShot::Detonate()
{
    WeaponProperties properties(_ExplodingShot, 0);
    GetProperties().radius = properties.GetRadius();
    gun->GetProperties().radius = properties.GetRadius();
    destroyThis = true;
    gun->Detonate();
}

void ExplodingShot::Draw(ALLEGRO_BITMAP *buffer, int midX, int midY)
{
    al_set_target_bitmap(buffer);
    al_draw_filled_circle (midX+gun->GetX(), midY+gun->GetY(), GetProperties().GetRadius(), al_map_rgb (255,0,0));
    gun->Draw(buffer, midX, midY);
}

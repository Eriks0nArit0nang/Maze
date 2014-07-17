#include "AbstractGunDecorator.h"
#include <iostream>

AbstractGunDecorator::AbstractGunDecorator(AbstractGun *gun):AbstractGun(*gun),gun(gun){}

void AbstractGunDecorator::Update()
{
    if (destroyThis && gun->WillDestroy())
    {
        gun->Update();
        delete this;
        return;
    }
    if (destroyThis)
        std::cerr << "Gun decorator will be destroyed before gun\n";
    if (gun->WillDestroy())
    {
        Detonate();
        return;
    }
    gun->Update();
}

void AbstractGunDecorator::Detonate()
{
    destroyThis = true;
    gun->Detonate();
}

void AbstractGunDecorator::Action(Character * character)
{
    gun->Action(character);
}

int AbstractGunDecorator::GetX() const
{
    return gun->GetX();
}

int AbstractGunDecorator::GetY() const
{
    return gun->GetY();
}

WeaponProperties &AbstractGunDecorator::GetProperties()
{
    return gun->GetProperties();
}

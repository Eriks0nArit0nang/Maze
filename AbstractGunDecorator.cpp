#include "AbstractGunDecorator.h"

AbstractGunDecorator::AbstractGunDecorator(AbstractGun *gun):AbstractGun(*gun),gun(gun){}

void AbstractGunDecorator::Update()
{
    gun->Update();
}

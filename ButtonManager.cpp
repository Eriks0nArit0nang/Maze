
#include <allegro5/allegro.h>
#include "ButtonManager.h"
#include "Button.h"

ButtonManager::ButtonManager()
{
}

ButtonManager::~ButtonManager()
{
	for (unsigned int i = 0; i < buttons_.size(); i++)
	{
		delete buttons_[i];
		buttons_[i] = NULL;
	}
	buttons_.clear();
}

void ButtonManager::AddButton(Button *button)
{
	buttons_.push_back(button);
}

bool ButtonManager::Update()
{
    bool action = false;
    for (unsigned int i = 0; i < buttons_.size(); i++)
    {
        if (buttons_[i]->Update())
            action = true;
	}
	return action;
}

void ButtonManager::Render(ALLEGRO_BITMAP *destination)
{
	for (unsigned int i = 0; i < buttons_.size(); i++)
	{
		buttons_[i]->Render(destination);
	}
}

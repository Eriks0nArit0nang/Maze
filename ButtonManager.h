
#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

struct BITMAP;
class Button;

#include <vector>

class ButtonManager
{
public:
	ButtonManager();
	~ButtonManager();

	void Update();
	void Render(BITMAP* destination);

	void AddButton(Button* button);

private:
	std::vector<Button*> buttons_;
};

#endif

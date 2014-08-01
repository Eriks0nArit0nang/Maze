#ifndef BUTTON_H
#define BUTTON_H

#include <allegro5/allegro.h>

class Button
{
public:
	// constructor
	Button();

	// destructor
	~Button();

	// creates the button image
	void Create();

	// recreates the button image
	void Recreate();

	// updates the button
	bool Update();

	// renders the button
	void Render(ALLEGRO_BITMAP* destination);

	// callback functions
	void (*OnMouseOver)(Button* object, void* data);
	void (*OnMouseOut)(Button* object, void* data);
	void (*OnClick)(Button* object, void* data);

	void SetCaption(const char* caption);
	void SetSize(int width, int height);
	void SetPosition(int x, int y);
	void SetPosition(ALLEGRO_BITMAP* anchorBitmap, int x, int y);
	void SetTextColor(ALLEGRO_COLOR color);
	void SetShadowColor(ALLEGRO_COLOR color);
	void SetBorderColor(ALLEGRO_COLOR color);
	void SetFaceColor(ALLEGRO_COLOR color);

	// repositions the button in the center of the surface
	void CenterOn(ALLEGRO_BITMAP* surface);
	
	void SetMiscData(void* data);
	void* GetMiscData();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	ALLEGRO_COLOR GetTextColor();
	ALLEGRO_COLOR GetShadowColor();
	ALLEGRO_COLOR GetBorderColor();
	ALLEGRO_COLOR GetFaceColor();
	char* GetCaption();

private:

	// void data pointer for use with callbacks
	void* data_;

	// the button image
	ALLEGRO_BITMAP* image_;

	// the text on the button
	char* caption_;

	// the coloring of the button
	ALLEGRO_COLOR faceColor_;
	ALLEGRO_COLOR borderColor_;
	ALLEGRO_COLOR shadowColor_;
	ALLEGRO_COLOR textColor_;

	// the dimension of the button
	int w_;
	int h_;

	// the position of the button
	int x_;
	int y_;
};

#endif

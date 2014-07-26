#ifndef BUTTON_H
#define BUTTON_H

struct BITMAP;

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
	void Update();

	// renders the button
	void Render(BITMAP* destination);

	// callback functions
	void (*OnMouseOver)(Button* object, void* data);
	void (*OnMouseOut)(Button* object, void* data);
	void (*OnClick)(Button* object, void* data);

	void SetCaption(char* caption);
	void SetSize(int width, int height);
	void SetPosition(int x, int y);
	void SetPosition(BITMAP* anchorBitmap, int x, int y);
	void SetTextColor(int color);
	void SetShadowColor(int color);
	void SetBorderColor(int color);
	void SetFaceColor(int color);

	// repositions the button in the center of the surface
	void CenterOn(BITMAP* surface);
	
	void SetMiscData(void* data);
	void* GetMiscData();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	int GetTextColor();
	int GetShadowColor();
	int GetBorderColor();
	int GetFaceColor();
	char* GetCaption();

private:

	// void data pointer for use with callbacks
	void* data_;

	// the button image
	BITMAP* image_;

	// the text on the button
	char* caption_;

	// the coloring of the button
	int faceColor_;
	int borderColor_;
	int shadowColor_;
	int textColor_;

	// the dimension of the button
	int w_;
	int h_;

	// the position of the button
	int x_;
	int y_;
};

#endif

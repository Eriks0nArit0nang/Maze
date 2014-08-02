#include <algorithm>
#include <cstring>
#include <iostream>
#include "Button.h"
#include "Input.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// dummy function for callbacks
void dummyCallbackFunction(Button* object, void* data)
{
	if (data && object)
	{
	}
	/* dummy function does nothing */
}

Button::Button():
x_(0), y_(0),
w_(128), h_(24),
textColor_(al_map_rgb(0,0,0)),
faceColor_(al_map_rgb(192,192,192)),
borderColor_(al_map_rgb(96,96,96)),
shadowColor_(al_map_rgb(0,0,0)),
image_(NULL),
caption_(NULL),
OnClick(dummyCallbackFunction),
OnMouseOver(dummyCallbackFunction),
OnMouseOut(dummyCallbackFunction),
data_(0)
{}

Button::~Button()
{
    if (caption_ != NULL)
    {
        delete [] caption_;
        caption_ = NULL;
    }
	if (image_ != NULL)
	{
		al_destroy_bitmap(image_);
		image_ = NULL;
	}
}

void Button::Create()
{
	if (caption_ != NULL)
	{
	    ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
	    if (!font)
	        std::cerr << "Font a4_font.tga not loaded correctly\n";
		int width = al_get_text_width(font, caption_);
		w_ = std::max(w_, width + 8);
		h_ = std::max(h_, al_get_font_line_height(font) + 8);

		image_ = al_create_bitmap(w_, h_);
		al_set_target_bitmap(image_);

		al_clear_to_color(faceColor_);

		al_draw_rectangle(0, 0, w_-1, h_-1, borderColor_, 0);

		al_draw_textf(font, textColor_,
			w_ / 2 - width / 2,
			h_ / 2 - al_get_font_line_height(font) / 2, 0, caption_);
	}
}

void Button::Recreate()
{
	if (image_ != NULL)
	{
		al_destroy_bitmap(image_);
		image_ = NULL;
	}
	this->Create();
}

bool Button::Update()
{	
	std::pair<int,int> mouse = Input::GetInstance()->GetMouse();

	if (mouse.first >= x_ && mouse.first <= x_ + w_ &&
		mouse.second >= y_ && mouse.second <= y_ + h_)
	{
		this->OnMouseOver(this, data_);

		if (Input::GetInstance()->IsMouseClicked())
		{
			this->OnClick(this, data_);
			return true;
		}
	}
	else
	{
		this->OnMouseOut(this, data_);
	}
	return false;
}

void Button::Render(ALLEGRO_BITMAP* destination)
{
	if (image_ == NULL) return;
	al_set_target_bitmap(destination);
	al_draw_bitmap_region(image_, 0, 0, al_get_bitmap_width(image_),
	                      al_get_bitmap_height(image_), x_, y_, 0);
}

void Button::SetCaption(const char* caption)
{
    if (caption_ != NULL)
        delete caption_;
    caption_ = new char[strlen(caption)+1];
	strcpy(caption_, caption);
}

void Button::SetSize(int width, int height)
{
	// this function does not do anything if the button has already been created
	if (image_ != NULL) return;
	w_ = width;
	h_ = height;
}

void Button::SetPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}

void Button::SetPosition(ALLEGRO_BITMAP* anchorBitmap, int x, int y)
{
	if (x < 0)
		x_ = al_get_bitmap_width(anchorBitmap) - (w_ - x);
	else
		x_ = x;

	if (y < 0)
		y_ = al_get_bitmap_height(anchorBitmap) - (h_ - y);
	else
		y_ = y;
}

void Button::SetTextColor(ALLEGRO_COLOR color)
{
	textColor_ = color;
}

void Button::SetShadowColor(ALLEGRO_COLOR color)
{
	shadowColor_ = color;
}

void Button::SetBorderColor(ALLEGRO_COLOR color)
{
	borderColor_ = color;
}

void Button::SetFaceColor(ALLEGRO_COLOR color)
{
	faceColor_ = color;
}

void Button::CenterOn(ALLEGRO_BITMAP* surface)
{
	if (surface == NULL) return; // do nothing if no surface exists
	x_ = al_get_bitmap_width(surface) / 2 - w_ / 2;
	y_ = al_get_bitmap_height(surface) / 2 - h_ / 2;
}

int Button::GetX()
{
	return x_;
}

int Button::GetY()
{
	return y_;
}

int Button::GetWidth()
{
	return w_;
}

int Button::GetHeight()
{
	return h_;
}

ALLEGRO_COLOR Button::GetTextColor()
{
	return textColor_;
}

ALLEGRO_COLOR Button::GetShadowColor()
{
	return shadowColor_;
}

ALLEGRO_COLOR Button::GetBorderColor()
{
	return borderColor_;
}

ALLEGRO_COLOR Button::GetFaceColor()
{
	return faceColor_;
}

char* Button::GetCaption()
{
	return caption_;
}

void Button::SetMiscData(void* data)
{
	data_ = data;
}

void* Button::GetMiscData()
{
	return data_;
}

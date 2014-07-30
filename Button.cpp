#include <algorithm>
#include <allegro5/allegro.h>
#include "Button.h"

PALETTE palette;

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
textColor_(makecol(0,0,0)),
faceColor_(makecol(192,192,192)),
borderColor_(makecol(96,96,96)),
shadowColor_(makecol(0,0,0)),
image_(NULL),
caption_(NULL),
OnClick(dummyCallbackFunction),
OnMouseOver(dummyCallbackFunction),
OnMouseOut(dummyCallbackFunction),
data_(0)
{
   // font_ = load_font("Georgia.ttf", palette, NULL);
}

Button::~Button()
{
	if (image_ != NULL)
	{
		destroy_bitmap(image_);
		image_ = NULL;
	}
}

void Button::Create()
{
	if (caption_ != NULL)
	{
		int width = text_length(font, caption_);
		w_ = std::max(w_, width + 8);
		h_ = std::max(h_, text_height(font) + 8);

		image_ = create_bitmap(w_, h_);
		clear_bitmap(image_);

		clear_to_color(image_, faceColor_);

		rect(image_, 0, 0, w_-1, h_-1, borderColor_);

		textprintf_ex(image_, font,
			w_ / 2 - width / 2,
			h_ / 2 - text_height(font) / 2,
			textColor_, faceColor_, 
			caption_);
	}
}

void Button::Recreate()
{
	if (image_ != NULL)
	{
		destroy_bitmap(image_);
		image_ = NULL;
	}
	this->Create();
}

void Button::Update()
{
	if (mouse_needs_poll())
	{
		poll_mouse();
	}

	if (mouse_x >= x_ && mouse_x <= x_ + w_ &&
		mouse_y >= y_ && mouse_y <= y_ + h_)
	{
		this->OnMouseOver(this, data_);

		if (mouse_b & 1)
		{
			this->OnClick(this, data_);
		}
	}
	else
	{
		this->OnMouseOut(this, data_);
	}
}

void Button::Render(ALLEGRO_BITMAP *destination)
{
	if (image_ == NULL) return;
	blit(image_, destination, 0, 0, x_, y_, image_->w, image_->h);
}

void Button::SetCaption(char* caption)
{
	caption_ = caption;
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
		x_ = anchorBitmap->w - (w_ - x);
	else
		x_ = x;

	if (y < 0)
		y_ = anchorBitmap->h - (h_ - y);
	else
		y_ = y;
}

void Button::SetTextColor(int color)
{
	textColor_ = color;
}

void Button::SetShadowColor(int color)
{
	shadowColor_ = color;
}

void Button::SetBorderColor(int color)
{
	borderColor_ = color;
}

void Button::SetFaceColor(int color)
{
	faceColor_ = color;
}

void Button::CenterOn(ALLEGRO_BITMAP* surface)
{
	if (surface == NULL) return; // do nothing if no surface exists
	x_ = surface->w / 2 - w_ / 2;
	y_ = surface->h / 2 - h_ / 2;
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

int Button::GetTextColor()
{
	return textColor_;
}

int Button::GetShadowColor()
{
	return shadowColor_;
}

int Button::GetBorderColor()
{
	return borderColor_;
}

int Button::GetFaceColor()
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

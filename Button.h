#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Drawable.h"

class Button : public Drawable
{

	private:
		int x;
		int y;
		int width;
		int height;

		SDL_Texture* m_texture;
		SDL_Rect buttonRect;

	public:
		Button();
		Button(int w, int h);
		Button(int w, int h, int x, int y);

		void create(int w, int h, int x, int y);
		void move(int x, int y);
		void moveToLoc(int x, int y);
		void setTexture(const char* texturePath);
		void free();

		void draw(SDL_Renderer* render);
		bool resize(int w, int h);

		inline int getX() const { return x; }
		inline int getY() const { return y; }
		inline int getWidth() const { return buttonRect.w; }
		inline int getheight() const { return buttonRect.h; }
};

#endif /* _BUTTON_H_ */

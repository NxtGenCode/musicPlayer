#ifndef _UNIQUE_DRAW_H_
#define _UNIQUE_DRAW_H_

#include <SDL.h>

class Drawable
{

	public:
		Drawable();
		~Drawable();

		virtual void draw(SDL_Renderer* render) = 0;

};

#endif /* _UNIQUE_DRAW_H_ */
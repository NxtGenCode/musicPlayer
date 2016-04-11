#ifndef _TTF_MESSAGE_H_
#define _TTF_MESSAGE_H_

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class TtfMessage {

	public:
		std::string message;
		SDL_Rect messageBounds;
		SDL_Texture* messageTexture;
		int width;
		int height;

		TtfMessage();

		bool createMessage(std::string message, TTF_Font* font, SDL_Color textColor);
		void setPosition(int x, int y);
		void draw(SDL_Renderer* render);
		void free();

		int getWidth();
		int getHeight();

};

#endif /* _TTF_MESSAGE_H_ */
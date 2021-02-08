//
// EPITECH PROJECT, 2018
// LibSDL2
// File description:
// LibSDL2.hpp
//

#ifndef LIBSDL2_HPP__
#define LIBSDL2_HPP__

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "IGraphic.hpp"

namespace Arcade {
	class LibSDL2: public IGraphic {
		class Exception: public std::exception {
			std::string _message;
		public:
			Exception(const std::string &message)
				: _message("Error in LibSDL2: " + message)
			{}

			~Exception()
			{}

			const char *what() const throw()
			{ return _message.c_str(); }
		};

		static constexpr uint16_t _width = 640;
		static constexpr uint16_t _height = 800;
		static constexpr uint16_t _mapPos = 160;

		static constexpr float _cellX = 16;
		static constexpr float _cellY = 16;

		SDL_Window *_win;
		SDL_Renderer *_renderer;

		std::map<SDL_Scancode, Input> _input;

		TTF_Font *_font;
		SDL_Surface *_surfaceMenu;
		SDL_Texture *_textureMenu;
		std::vector<SDL_Surface *> _surfaces;
		std::vector<SDL_Texture *> _textures;

		void initInput();
		void cleanTexture();
	public:
		LibSDL2();
		~LibSDL2();

		void setGameName(const std::string &);
		void setGameMenu(const std::string &);
		void loadTextures(const Textures &);

		Input getInput();

		void drawMenu();
		void drawMap(const Map &);
		void drawEntities(const Entities &);
		void drawScore(const Score &);

		void display();
	};
}

#endif /* !LIBSDL2_HPP__ */

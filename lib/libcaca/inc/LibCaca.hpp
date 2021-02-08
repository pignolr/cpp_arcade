//
// EPITECH PROJECT, 2018
// libSFML
// File description:
// LibCaca.hpp
//

#ifndef LIBCACA_HPP__
#define LIBCACA_HPP__

#include <map>
#include <vector>
#include <caca.h>
#include "IGraphic.hpp"

namespace Arcade {
	class LibCaca: public IGraphic {
		class Exception: public std::exception {
			std::string _message;
		public:
			Exception(const std::string &message)
				: _message("Error in LibCaca: " + message)
			{}

			~Exception()
			{}

			const char *what() const throw()
			{ return _message.c_str(); }
		};

		static constexpr uint16_t _width = 80;
		static constexpr uint16_t _height = 50;
		// static constexpr uint16_t _mapPos = 160;
		// static constexpr float _cellX = 16;
		// static constexpr float _cellY = 16;

		caca_canvas_t *_cv;
		caca_display_t *_win;
		std::map<int, Input> _input;
		std::vector<AsciiTexture> _textures;

		void initInput();
	public:
		LibCaca();
		~LibCaca();

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

#endif /* !LIBCACA_HPP__ */

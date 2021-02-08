//
// EPITECH PROJECT, 2018
// libSFML
// File description:
// LibSFML.hpp
//

#ifndef LIBSFML_HPP__
#define LIBSFML_HPP__

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "IGraphic.hpp"

namespace Arcade {
	class LibSFML: public IGraphic {
		class Exception: public std::exception {
			std::string _message;
		public:
			Exception(const std::string &message)
				: _message("Error in LibSFML: " + message)
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

		sf::Font _font;

		sf::RenderWindow *_win;
		std::map<sf::Keyboard::Key, Input> _input;

		sf::Texture _textureMenu;
		sf::Sprite _menu;

		std::vector<sf::Texture> _textures;

		void initInput();
		void drawTextureMap(const Map &map, sf::Sprite &sprite,
			uint16_t id);
	public:
		LibSFML();
		~LibSFML();

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

#endif /* !LIBSFML_HPP__ */

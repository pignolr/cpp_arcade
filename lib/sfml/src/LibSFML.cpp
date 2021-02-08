//
// EPITECH PROJECT, 2018
// libSFML
// File description:
// LibSFML.cpp
//

#include <exception>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "LibSFML.hpp"

namespace Arcade {
	void LibSFML::initInput()
	{
		_input[sf::Keyboard::Key::Up] = Input::GO_UP;
		_input[sf::Keyboard::Key::Right] = Input::GO_RIGHT;
		_input[sf::Keyboard::Key::Down] = Input::GO_DOWN;
		_input[sf::Keyboard::Key::Left] = Input::GO_LEFT;
		_input[sf::Keyboard::Key::Num2] = Input::PREV_LIB;
		_input[sf::Keyboard::Key::Num3] = Input::NEXT_LIB;
		_input[sf::Keyboard::Key::Num4] = Input::PREV_GAME;
		_input[sf::Keyboard::Key::Num5] = Input::NEXT_GAME;
		_input[sf::Keyboard::Key::Num8] = Input::RESTART;
		_input[sf::Keyboard::Key::Num9] = Input::MENU;
		_input[sf::Keyboard::Key::Escape] = Input::EXIT;
		_input[sf::Keyboard::Key::Space] = Input::SHOOT;
		_input[sf::Keyboard::Key::Return] = Input::START_GAME;
	}

	LibSFML::LibSFML(): _font(), _textures(0)
	{
		initInput();
		_win = new sf::RenderWindow(sf::VideoMode(_width, _height), "");
		_win->clear();
		_font.loadFromFile("./font/arial.ttf");
	}

	LibSFML::~LibSFML()
	{ _win->close(); }

	void LibSFML::setGameName(const std::string &name)
	{ _win->setTitle(name); }

	void LibSFML::setGameMenu(const std::string &file)
	{
		if (!_textureMenu.loadFromFile(file))
			throw Exception("fail to load Menu from file");
		_menu.setTexture(_textureMenu);
		_menu.setScale((float)_width / _textureMenu.getSize().x,
			(float)_height / _textureMenu.getSize().y);
	}

	void LibSFML::loadTextures(const Textures &textures)
	{
		sf::Texture texture;

		_textures.clear();
		for (auto it = textures.begin(); it != textures.end(); ++it) {
			if (!texture.loadFromFile(it->texture2D))
				throw Exception("fail to load texture '"
					+ it->texture2D + "'");
			_textures.push_back(texture);
		}
	}

	Input LibSFML::getInput()
	{
		sf::Event event;

		while (_win->pollEvent(event))
			if (event.type == sf::Event::KeyPressed
				&& _input.find(event.key.code) != _input.end())
				return _input[event.key.code];
		return Input::NONE;
	}

	void LibSFML::drawMenu()
	{ _win->draw(_menu); }

	void LibSFML::drawTextureMap(const Map &map, sf::Sprite &sprite,
		uint16_t id)
	{
		for (size_t y = 0; y < map.size(); ++y)
			for (size_t x = 0; x < map[y].size(); ++x) {
				if (map[y][x] != id)
					continue;
				sprite.setPosition(
					sf::Vector2f(_cellX * x,
						_cellY * y + _mapPos));
				_win->draw(sprite);
			}
	}

	void LibSFML::drawMap(const Map &map)
	{
		if (!map.size() || !map[0].size())
			throw Exception("Invalid Map");
		for (size_t i = 0; i < _textures.size(); ++i) {
			if (i >= _textures.size())
				continue;
			sf::Sprite sprite;
			sprite.setTexture(_textures[i]);
			sprite.setScale(_cellX / _textures[i].getSize().x,
				_cellY / _textures[i].getSize().y);
			drawTextureMap(map, sprite, i);
		}
	}

	void LibSFML::drawEntities(const Entities &entities)
	{
		sf::Sprite sprite;
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if (it->texture >= _textures.size())
				continue;
			sprite.setTexture(_textures[it->texture]);
			sprite.setScale(
				_cellX / _textures[it->texture].getSize().x,
				_cellY / _textures[it->texture].getSize().y);
			sprite.setPosition(
				sf::Vector2f(_cellX * it->posX,
					_cellY * it->posY + _mapPos));
			if (it->dir == direction::RIGHT)
				sprite.move(sf::Vector2f(_cellX, 0));
			else if (it->dir == direction::DOWN)
				sprite.move(sf::Vector2f(_cellX, _cellY));
			else if (it->dir == direction::LEFT)
				sprite.move(sf::Vector2f(0, _cellY));
			sprite.setRotation(90 * it->dir);
			_win->draw(sprite);
		}
	}

	void LibSFML::drawScore(const Score &score)
	{
		sf::Text text("", _font);
		text.setCharacterSize(_cellY);
		text.setPosition(_cellX, 0);

		for (auto it = score.begin(); it != score.end(); ++it) {
			text.setString(it->first + ": " + it->second);
			text.move(0, _cellY);
			_win->draw(text);
		}
	}

	void LibSFML::display()
	{
		_win->display();
		_win->clear();
	}
}

extern "C" void *create()
{
	return new Arcade::LibSFML();
}

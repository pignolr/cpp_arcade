//
// EPITECH PROJECT, 2018
// libCaca
// File description:
// LibCaca.cpp
//

#include <exception>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "LibCaca.hpp"

namespace Arcade {
	void LibCaca::initInput()
	{
		_input[CACA_KEY_UP] = Input::GO_UP;
		_input[CACA_KEY_RIGHT] = Input::GO_RIGHT;
		_input[CACA_KEY_DOWN] = Input::GO_DOWN;
		_input[CACA_KEY_LEFT] = Input::GO_LEFT;
		_input['2'] = Input::PREV_LIB;
		_input['3'] = Input::NEXT_LIB;
		_input['4'] = Input::PREV_GAME;
		_input['5'] = Input::NEXT_GAME;
		_input['8'] = Input::RESTART;
		_input['9'] = Input::MENU;
		_input[CACA_KEY_ESCAPE] = Input::EXIT;
		_input[' '] = Input::SHOOT;
		_input[13] = Input::START_GAME;
	}

	LibCaca::LibCaca()
	{
		initInput();
		this->_cv = caca_create_canvas(this->_width, this->_height);
		this->_win = caca_create_display(this->_cv);
	}

	LibCaca::~LibCaca()
	{
		caca_free_display(this->_win);
	}

	void LibCaca::setGameName(const std::string &name)
	{
		caca_set_display_title(this->_win, name.c_str());
	}

	void LibCaca::setGameMenu(const std::string &file)
	{
		(void)file;
	}

	void LibCaca::loadTextures(const Textures &textures)
	{
		for (auto &it : textures) {
			this->_textures.push_back(it.ascii);
		}
	}

	Input LibCaca::getInput()
	{
		caca_event_t ev;

		while (caca_get_event(this->_win, CACA_EVENT_KEY_PRESS |
			CACA_EVENT_QUIT, &ev, 0))
			if (caca_get_event_type(&ev) == CACA_EVENT_QUIT)
				return Input::EXIT;
			else if (caca_get_event_type(&ev) ==
				CACA_EVENT_KEY_PRESS &&
				(_input.find(caca_get_event_key_ch(&ev))
					!= _input.end()))
				return _input[caca_get_event_key_ch(&ev)];
		return Input::NONE;
	}

	void LibCaca::drawMenu()
	{
		caca_put_str(this->_cv, 0, 0,
			     "LibCaca : Press enter to start game");
		this->display();
	}

	void LibCaca::drawMap(const Map &map)
	{
		size_t i = 0;
		if (!map.size() || !map[0].size())
			throw Exception("Invalid Map");
		for (auto &it : this->_textures) {
			caca_set_color_argb(this->_cv, it.color, it.colorBack);
			for (size_t y = 0; y < map.size(); ++y)
				for (size_t x = 0; x < map[y].size(); ++x) {
					if (map[y][x] != i)
						continue;
					char tmp[3];
					tmp[0] = it.character;
					tmp[1] = it.character;
					tmp[2] = 0;
					caca_put_str(this->_cv, x * 2, y, tmp);
				}
			++i;
		}
	}

	void LibCaca::drawEntities(const Entities &entities)
	{
		for (auto &it : entities) {
			caca_set_color_argb(this->_cv,
				this->_textures[it.texture].color,
				_textures[it.texture].colorBack);
			unsigned int tmpX = (unsigned int)it.posX;
			unsigned int tmpY = (unsigned int)it.posY;
			char tmp[3];
			tmp[0] = this->_textures[it.texture].character;
			tmp[1] = this->_textures[it.texture].character;
			tmp[2] = 0;
			caca_put_str(this->_cv, tmpX * 2, tmpY, tmp);
		}
	}

	void LibCaca::drawScore(const Score &score)
	{
		unsigned int i = 0;

		caca_set_color_ansi(this->_cv, CACA_WHITE, CACA_BLACK);
		for (auto &it : score) {
			std::string tmp = it.first + " : " + it.second;
			caca_put_str(this->_cv, 2, 41 + i, tmp.c_str());
			i++;
		}
	}

	void LibCaca::display()
	{
		caca_refresh_display(this->_win);
		caca_clear_canvas(this->_cv);
	}
}

extern "C" void *create()
{
	return new Arcade::LibCaca();
}

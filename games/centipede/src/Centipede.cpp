//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Centipede.hpp
//

#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "Centipede.hpp"

namespace Arcade {

	Centi::Centi()
	{
		move = true;
		vert = 1;
		hor = 1;
	}

	Centipede::Centipede()
	{
		_start = std::chrono::system_clock::now();
		std::srand(std::time(0));
		_name = "Centipede";
		_backgroundMenu = "games/centipede/textures/menu.png";
		_points = 0;
		_life = 3;
		_centipedes = 20;
		_isRunning = true;
		setTextures();
		createMap();
		createMushrooms();
		spawnCenti();
		_self = { 5, 20, 35, UP };
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	void Centipede::putInput(Input way)
	{
		switch (way) {
			case Input::GO_UP:
				if (_self.posY > 31)
					--_self.posY;
				break;
			case Input::GO_RIGHT:
				if (_self.posX < WIDTH - 1)
					++_self.posX;
				break;
			case Input::GO_DOWN:
				if (_self.posY < HEIGHT - 1)
					++_self.posY;
				break;
			default:
				setInput(way);
				break;
		}
	}

	void Centipede::setInput(Input way)
	{
		switch (way) {
			case Input::GO_LEFT:
				if (_self.posX > 1)
					--_self.posX;
				break;
			case Input::SHOOT:
				if (_shoot.posY < 1)
					_shoot = { 6, _self.posX,
						static_cast<float>
						((int)_self.posY), UP };
				break;
			default:
				addInput(way);
				break;
		}
	}

	void Centipede::addInput(Input way)
	{
		switch (way) {
			case Input::MENU:
				_isRunning = false;
				break;
			case Input::RESTART:
				reset();
				break;
			default:
				break;
		}
	}

	bool Centipede::runGameLoop()
	{
		bool ret;
		int elapsed;
		unsigned int i;

		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now() - _start).count();
		if (50000 - elapsed > 0)
			std::this_thread::sleep_for
			(std::chrono::microseconds(50000 - elapsed));
		for (i = 0; i < 10; ++i) {
			if (_centis[i].centi.size() == 1
				|| _centis[i].move == true)
				ret = moveSnake(i);
			else
				_centis[i].move = true;
			if (ret == false || checkCollision(_centis[i]) == false)
				return (false);
		}
		moveShot();
		setScore();
		setEntities();
		_start = std::chrono::system_clock::now();
		if (_isRunning == false)
			return (false);
		return (ret);
	}

	const std::string &Centipede::getNameGame() const
	{ return (_name); }

	const std::string &Centipede::getBackgroundMenu() const
	{ return (_backgroundMenu); }

	const Textures &Centipede::getTextures() const
	{ return (_textures); }

	const Map &Centipede::getMap() const
	{ return (_map); }

	const Entities &Centipede::getEntities() const
	{ return (_ret); }

	const Score &Centipede::getScore() const
	{ return (_score); }

	void Centipede::reset()
	{
		_start = std::chrono::system_clock::now();
		_points = 0;
		_life = 3;
		_centipedes = 20;
		_isRunning = true;
		setTextures();
		createMushrooms();
		spawnCenti();
		_self = { 5, 20, 35, UP };
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	void Centipede::createMap()
	{
		std::vector<uint16_t> border;
		std::vector<uint16_t> sides;
		int i;

		for (i = 0; i < WIDTH + 1; ++i)
			border.push_back(1);
		sides.push_back(1);
		for (i = 1; i < WIDTH; ++i)
			sides.push_back(0);
		sides.push_back(1);
		_map.push_back(border);
		for (i = 1; i < HEIGHT; ++i)
			_map.push_back(sides);
		_map.push_back(border);
	}

	void Centipede::setTextures()
	{
		Texture texture;

		texture.ascii.character = ' ';
		texture.ascii.color = 0x0000;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/ground.png";
		texture.texture3D = "games/centipede/textures/ground.png";
		_textures.push_back(texture);
		texture.ascii.character = 'X';
		texture.ascii.color = 0x03EF;
		texture.ascii.colorBack = 0xFFFF;
		texture.texture2D = "games/centipede/textures/brick.png";
		texture.texture3D = "games/centipede/textures/brick.png";
		_textures.push_back(texture);
		createTextures(texture);
	}

	void Centipede::createTextures(Texture texture)
	{
		texture.ascii.character = 'M';
		texture.ascii.color = 0x07E0;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/cookie.png";
		texture.texture3D = "games/centipede/textures/cookie.png";
		_textures.push_back(texture);
		texture.ascii.character = '0';
		texture.ascii.color = 0x07FF;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/head.png";
		texture.texture3D = "games/centipede/textures/head.png";
		_textures.push_back(texture);
		texture.ascii.character = '0';
		texture.ascii.color = 0x07FF;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/body.png";
		texture.texture3D = "games/centipede/textures/body.png";
		_textures.push_back(texture);
		addTextures(texture);
	}

	void Centipede::addTextures(Texture texture)
	{
		texture.ascii.character = 'A';
		texture.ascii.color = 0xF800;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/ship.png";
		texture.texture3D = "games/centipede/textures/ship.png";
		_textures.push_back(texture);
		texture.ascii.character = '*';
		texture.ascii.color = 0xFFE0;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/centipede/textures/fire.png";
		texture.texture3D = "games/centipede/textures/fire.png";
		_textures.push_back(texture);
	}

	void Centipede::createMushrooms()
	{
		int i;

		for (i = WIDTH; i < (HEIGHT - 10) * WIDTH; ++i)
			if (rand() % 100 > 92) {
				_node = { 2, static_cast<float>
					(i % (WIDTH - 1) + 1),
					static_cast<float>
					(i / (HEIGHT - 1) + 1), UP};
				_mush.push_back({ _node, 5});
			}
	}

	void Centipede::setEntities()
	{
		unsigned int i;
		unsigned int j;

		_ret.clear();
		for (i = 0; i < _centis.size(); ++i)
			for (j = 0; j < _centis[i].centi.size(); ++j)
				if (_centis[i].centi[j].posY > 0)
					_ret.push_back(_centis[i].centi[j]);
		for (i = 0; i < _mush.size(); ++i)
			_ret.push_back(_mush[i].mush);
		_ret.push_back(_self);
		if (_shoot.posY > 0)
			_ret.push_back(_shoot);
	}

	void Centipede::setScore()
	{
		_score.clear();
		_score.emplace("Score", std::to_string(_points));
		_score.emplace("Life", std::to_string(_life));
		_score.emplace("Centipede(s) left",
			std::to_string(_centipedes));
	}

	void Centipede::spawnCenti()
	{
		float x;
		float y;
		unsigned int i;

		for (i = 0; i < _centis.size(); ++i)
			_centis[i].centi.clear();
		y = 1;
		x = static_cast<float>(rand() % (WIDTH - 1) + 1);
		_centis[0].centi.push_back({ 3, x, y, RIGHT});
		for (i = 1; i < 10; ++i)
			_centis[0].centi.push_back({ 4, x, y - i, DOWN});
	}

	void Centipede::removeCentis()
	{
		unsigned int i;
		int j;

		--_centipedes;
		j = 0;
		for (i = 0; i < _centis.size(); ++i) {
			j += (_centis[i].centi.size() * 10);
			_centis[i].centi.clear();
		}
		j += (_mush.size() * 5);
		_points += j;
		spawnCenti();
	}

	bool Centipede::moveSnake(unsigned int i)
	{
		bool ret;

		ret = true;
		if (_centis[i].centi.empty())
			return (true);
		_node = _centis[i].centi.front();
		if (_node.dir == Arcade::RIGHT)
			++_node.posX;
		else if (_node.dir == Arcade::LEFT)
			--_node.posX;
		if (_node.posX < 1 || _node.posX > WIDTH - 1
			|| checkMush() >= 0)
			ret = goDown(i);
		_centis[i].centi.pop_back();
		_centis[i].centi.push_front(_node);
		_centis[i].centi[1].texture = 4;
		_centis[i].move = false;
		return (ret);
	}

	bool Centipede::goDown(unsigned int i)
	{
		_node = _centis[i].centi.front();
		_node.posY += _centis[i].vert;
		if (_node.posY == HEIGHT - 1)
			_centis[i].vert = -1;
		if (_node.dir == Arcade::RIGHT)
			_node.dir = Arcade::LEFT;
		else if (_node.dir == Arcade::LEFT)
			_node.dir = Arcade::RIGHT;
		if (_node.posY == 0 && _centis[i].vert == -1)
			_centis[i].centi.clear();
		return (checkAlive());
	}

	bool Centipede::checkAlive()
	{
		unsigned int i;
		unsigned int len;

		len = 0;
		for (i = 0; i < 10; ++i)
			len += _centis[i].centi.size();
		if (len == 0)
			spawnCenti();
		return (true);
	}

	void Centipede::moveShot()
	{
		int i;

		_node = _shoot;
		_shoot.dir = (Arcade::direction)(rand() % 4);
		--_shoot.posY;
		i = checkMush();
		if (i >= 0) {
			_shoot.posY = -1;
			--_mush[i].life;
			if (_mush[i].life == 0) {
				_mush.erase(_mush.begin() + i);
				++_points;
			}
			return ;
		}
		checkCentis();
	}

	bool Centipede::checkCollision(Centi cent)
	{
		unsigned int i;

		for (i = 0; i < cent.centi.size(); ++i)
			if (cent.centi[i].posX == _self.posX
				&& cent.centi[i].posY == _self.posY) {
				removeCentis();
				--_life;
				if (_life == 0)
					return (false);
			}
		return true;
	}

	void Centipede::checkCentis()
	{
		unsigned int i;
		unsigned int j;

		for (i = 0; i < 5; ++i) {
			for (j = 0; j < _centis[i].centi.size(); ++j)
				if (_shoot.posX == _centis[i].centi[j].posX
				&& _shoot.posY == _centis[i].centi[j].posY)
					removeHead(i, j);
		}
	}

	void Centipede::removeHead(int i, int j)
	{
		_node = { 2, _centis[i].centi[j].posX,
			_centis[i].centi[j].posY, UP};
		_mush.push_back({ _node, 5});
		if (j == 0) {
			_centis[i].centi.pop_front();
			_centis[i].centi[0].texture = 3;
			_points += 100 * (_centis[i].centi[j].posY / 10 + 1);
		} else
			removeNode(i, j);
		_shoot.posY = -1;
	}

	void Centipede::removeNode(int i, int j)
	{
		unsigned int shift;

		shift = 0;
		while (_centis[i + shift].centi.size() != 0)
			++shift;
		_points += 10 * (_centis[i].centi[j].posY / 10 + 1);
		_centis[i + shift].centi.assign(_centis[i].centi.begin() + j + 1,
			_centis[i].centi.end());
		_centis[i].centi.erase(_centis[i].centi.begin() + j,
			_centis[i].centi.end());
		_centis[i + 1].centi[0].texture = 3;
	}

	int Centipede::checkMush()
	{
		unsigned int i;

		for (i = 0; i < _mush.size(); ++i)
			if (_node.posX == _mush[i].mush.posX
				&& _node.posY == _mush[i].mush.posY)
				return i;
		return -1;
	}
}

extern "C" void *create()
{
	return new Arcade::Centipede();
}

//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.hpp
//

#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "Nibbler.hpp"

namespace Arcade {

	Nibbler::Nibbler()
	{
		_start = std::chrono::system_clock::now();
		std::srand(std::time(0));
		_name = "Nibbler";
		_backgroundMenu = "games/nibbler/textures/menu.png";
		_points = 0;
		setTextures();
		createMap();
		_node = { 2, WIDTH / 2, HEIGHT / 2, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2 + 1, HEIGHT / 2, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2 + 1, HEIGHT / 2 + 1, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2, HEIGHT / 2 + 1, LEFT };
		_snake.push_back(_node);
		_direction = direction::LEFT;
		createFruit();
		_isRunning = true;
	}

	void Nibbler::putInput(Input way)
	{
		switch (way) {
			case Input::GO_RIGHT:
				rightSide();
				break;
			case Input::GO_LEFT:
				leftSide();
				break;
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

	bool Nibbler::runGameLoop()
	{
		bool ret;
		int elapsed;

		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now() - _start).count();
		if (300000 - elapsed > 0)
			std::this_thread::sleep_for
			(std::chrono::microseconds(300000 - elapsed));
		ret = move();
		_ret.clear();
		_ret = _snake;
		_ret.push_back(_fruit);
		_score.clear();
		_score["Score"] = std::to_string(_points);
		_start = std::chrono::system_clock::now();
		if (_isRunning == false)
			return (false);
		return (ret);
	}

	const std::string &Nibbler::getNameGame() const
	{ return (_name); }

	const std::string &Nibbler::getBackgroundMenu() const
	{ return (_backgroundMenu); }

	const Textures &Nibbler::getTextures() const
	{ return (_textures); }

	const Map &Nibbler::getMap() const
	{ return (_map); }

	const Entities &Nibbler::getEntities() const
	{ return (_ret); }

	const Score &Nibbler::getScore() const
	{ return (_score); }

	void Nibbler::reset()
	{
		_start = std::chrono::system_clock::now();
		std::srand(std::time(0));
		_name = "Nibbler";
		_points = 0;
		_snake.clear();
		_node = { 2, WIDTH / 2, HEIGHT / 2, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2 + 1, HEIGHT / 2, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2 + 1, HEIGHT / 2 + 1, LEFT };
		_snake.push_back(_node);
		_node = { 3, WIDTH / 2, HEIGHT / 2 + 1, LEFT };
		_snake.push_back(_node);
		_direction = direction::LEFT;
		createFruit();
		_isRunning = true;
	}

	void Nibbler::createMap()
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

	void Nibbler::setTextures()
	{
		Texture texture;

		texture.ascii.character = ' ';
		texture.ascii.color = 0x0000;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/nibbler/textures/ground.png";
		texture.texture3D = "games/nibbler/textures/ground.png";
		_textures.push_back(texture);
		texture.ascii.character = 'X';
		texture.ascii.color = 0x03EF;
		texture.ascii.colorBack = 0XFFFF;
		texture.texture2D = "games/nibbler/textures/brick.png";
		texture.texture3D = "games/nibbler/textures/brick.png";
		_textures.push_back(texture);
		createTextures(texture);
	}

	void Nibbler::createTextures(Texture texture)
	{
		texture.ascii.character = '0';
		texture.ascii.color = 0x07E0;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/nibbler/textures/head.png";
		texture.texture3D = "games/nibbler/textures/head.png";
		_textures.push_back(texture);
		texture.ascii.character = 'O';
		texture.ascii.color = 0x07FF;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/nibbler/textures/body.png";
		texture.texture3D = "games/nibbler/textures/body.png";
		_textures.push_back(texture);
		texture.ascii.character = 'f';
		texture.ascii.color = 0xf800;
		texture.ascii.colorBack = 0x0000;
		texture.texture2D = "games/nibbler/textures/apple.png";
		texture.texture3D = "games/nibbler/textures/apple.png";
		_textures.push_back(texture);
	}

	void Nibbler::createFruit()
	{
		unsigned int i;
		float x;
		float y;
		bool isOK;

		isOK = true;
		while (isOK) {
			x = static_cast<float>((rand() %(WIDTH - 1)) + 1);
			y = static_cast<float>((rand() % (HEIGHT - 1)) + 1);
			for (i = 0; i < _snake.size(); ++i) {
				if (x == _snake[i].posX
					&& y == _snake[i].posY) {
					isOK = true;
					break;
				} else
					isOK = false;
			}
			if (isOK == false)
				_fruit = {4, x, y, UP};
		}
	}

	void Nibbler::leftSide()
	{
		switch (_direction) {
			case direction::UP:
				_direction = direction::LEFT;
				break;
			case direction::RIGHT:
				_direction = direction::UP;
				break;
			case direction::DOWN:
				_direction = direction::RIGHT;
				break;
			case direction::LEFT:
				_direction = direction::DOWN;
				break;
			default:
				break;
		}
	}

	void Nibbler::rightSide()
	{
		switch (_direction) {
			case direction::UP:
				_direction = direction::RIGHT;
				break;
			case direction::RIGHT:
				_direction = direction::DOWN;
				break;
			case direction::DOWN:
				_direction = direction::LEFT;
				break;
			case direction::LEFT:
				_direction = direction::UP;
				break;
			default:
				break;
		}
	}

	bool Nibbler::move()
	{
		_node = _snake.front();
		switch (_direction) {
			case direction::UP:
				_node.dir = UP;
				--_node.posY;
				break;
			case direction::RIGHT:
				_node.dir = RIGHT;
				++_node.posX;
				break;
			case direction::DOWN:
				_node.dir = DOWN;
				++_node.posY;
				break;
			case direction::LEFT:
				_node.dir = LEFT;
				--_node.posX;
				break;
		}
		return (checkCollide());
	}

	bool Nibbler::checkCollide()
	{
		if (_node.posX < 1 || _node.posY < 1
			|| _node.posX > WIDTH - 1 || _node.posY > HEIGHT - 1) {
			reset();
			return (false);
		}
		return (checkCollision());
	}

	bool Nibbler::checkCollision()
	{
		unsigned int i;

		if (_node.posX != _fruit.posX || _node.posY != _fruit.posY)
			_snake.pop_back();
		else {
			_points += 10;
			createFruit();
		}
		for (i = 0 ; i != _snake.size(); ++i)
			if (_node.posX == _snake[i].posX
				&& _node.posY == _snake[i].posY) {
				reset();
				return (false);
		}
		_snake.push_front(_node);
		_snake[1].texture = 3;
		return (true);
	}
}

extern "C" void *create()
{
	return new Arcade::Nibbler();
}

//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Nibbler.hpp
//

#pragma once

#include "IGame.hpp"

namespace Arcade {

	#define WIDTH 39
	#define HEIGHT 39

	enum class TileType : uint16_t
	{
		EMPTY = 0,
		BLOCK = 1,
		HEAD = 2,
		ENEMY = 3,
		FOOD = 4
	};

	class Nibbler : public IGame {
	public:
		Nibbler();
		~Nibbler() {}

		void putInput(Input);
		bool runGameLoop();

		const std::string &getNameGame() const;
		const std::string &getBackgroundMenu() const;
		const Textures &getTextures() const;
		const Map &getMap() const;
		const Entities &getEntities() const;
		const Score &getScore() const;

		void reset();

		void createMap();
		void setTextures();
		void createTextures(Texture texture);
		void createFruit();

		void leftSide();
		void rightSide();
		bool move();
		bool checkCollide();
		bool checkCollision();

	private:
		Map _map;
		Textures _textures;
		Entities _snake;
		std::string _name;
		std::string _backgroundMenu;
		int _points;
		bool _isRunning;
		direction _direction;
		Entity _node;
		Entity _fruit;
		Entities _ret;
		Score _score;
		std::chrono::time_point<std::chrono::system_clock> _start;
	};

	using IGamePtr = std::unique_ptr<IGame>;
}
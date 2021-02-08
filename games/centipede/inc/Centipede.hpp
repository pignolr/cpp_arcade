//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Centipede.hpp
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
		OBSTACLE = 2,
		HEAD = 3,
		ENEMY = 4,
		SELF = 5,
		SHOOT = 6
	};

	struct Mush {
		Entity mush;
		int life;
	};

	class Centi {
	public:
		Centi();
		~Centi() {};

		Entities centi;
		bool move;
		int vert;
		int hor;
	};

	class Centipede : public IGame {
	public:
		Centipede();
		~Centipede() {}

		void putInput(Input);
		void setInput(Input);
		void addInput(Input);
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
		void addTextures(Texture texture);
		void createMushrooms();
		void setEntities();
		void setScore();

		void spawnCenti();
		void removeCentis();

		bool moveSnake(unsigned int);
		bool goDown(unsigned int);
		bool checkAlive();
		bool checkCollision(Centi);

		void moveShot();
		void checkCentis();

		void removeHead(int, int);
		void removeNode(int, int);
		int checkMush();

	private:
		Map _map;
		Textures _textures;
		Entities _ret;
		Score _score;
		std::array<Centi, 10> _centis;
		std::deque<Mush> _mush;
		Entity _self;
		Entity _shoot;
		Entity _node;
		std::string _name;
		std::string _backgroundMenu;
		bool _isRunning;
		int _points;
		int _life;
		int _centipedes;
		std::chrono::time_point<std::chrono::system_clock> _start;
	};

	using IGamePtr = std::unique_ptr<IGame>;
}
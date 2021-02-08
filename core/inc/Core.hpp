//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Core.hpp
//

#pragma once

#include <map>
#include "IGame.hpp"
#include "IGraphic.hpp"
#include "DynamicLoader.hpp"

namespace Arcade {
	class Core {
		class Exception: public std::exception {
			std::string _message;
		public:
			Exception(const std::string &message)
				: _message("Error in Core: " + message)
			{}

			~Exception()
			{}

			const char *what() const throw()
			{ return _message.c_str(); }
		};

		using MapGraphic = std::map<std::string, funcCreate>;
		using MapGame = std::map<std::string, funcCreate>;

		DynamicLoader _loader;
		MapGraphic _graphics;
		MapGame _games;

		IGraphicPtr _actualGraphic;
		IGamePtr _actualGame;

		MapGraphic::iterator _itGraphic;
		MapGame::iterator _itGame;

	public:
		Core(const std::string &);
		~Core();

		funcCreate loadFuncCreate(const std::string &);
		void loadGraphic(const std::string &) noexcept;
		void loadGraphics() noexcept;
		void loadGame(const std::string &) noexcept;
		void loadGames() noexcept;
		void initializeGameAndGraphic();

		void changeGraphicLib();
		void changeGameLib();
		void loadGameDataInGraphicLib();
		void nextLib() noexcept;
		void prevLib() noexcept;
		void nextGame() noexcept;
		void prevGame() noexcept;

		bool doSwitchInputRun(Input input);
		void run();
		void displayGame();
		bool doSwitchInputGame(Input input);
		bool startGame();
	};
}

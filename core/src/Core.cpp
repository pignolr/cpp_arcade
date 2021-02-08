//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Core.cpp
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <glob.h>
#include "Core.hpp"

namespace Arcade {
	Core::Core(const std::string &graphic)
		: _loader(), _graphics(), _games(), _actualGraphic(nullptr),
		_actualGame(nullptr)
	{
		try {
			loadGraphics();
			if (!_graphics.count(graphic))
				loadGraphic(graphic);
			loadGames();
			if (!_graphics.size())
				throw Exception("No valid library graphic"
						" in directory 'lib'");
			if (!_games.size())
				throw Exception(
					"No valid game in directory 'games'");
			_itGraphic = _graphics.find(graphic);
			if (_itGraphic == _graphics.end())
				throw Exception(
					graphic + " is not a valid lib");
			_itGame = _games.begin();
			initializeGameAndGraphic();
		} catch (std::exception &e) {
			throw Exception(e.what());
		}
	}

	Core::~Core()
	{}

	funcCreate Core::loadFuncCreate(const std::string &lib)
	{
		void *symCreate;

		symCreate = _loader.getAddrSym(lib, "create");
		auto ptrCreate = reinterpret_cast<funcCreate>(symCreate);
		if (!ptrCreate)
			throw Exception(lib + " invalid sym");
		return ptrCreate;
	}

	void Core::loadGraphic(const std::string &graphicLib) noexcept
	{
		try {
			funcCreate ptrCreate = loadFuncCreate(graphicLib);
			_graphics[graphicLib] = ptrCreate;
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void Core::loadGame(const std::string &gameLib) noexcept
	{
		try {
			funcCreate ptrCreate = loadFuncCreate(gameLib);
			_games[gameLib] = ptrCreate;
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void Core::loadGraphics() noexcept
	{
		glob_t result;

		glob("lib/lib_arcade_*.so", GLOB_TILDE, nullptr,
			&result);
		for (size_t i = 0; i < result.gl_pathc; ++i)
			loadGraphic(result.gl_pathv[i]);
		globfree(&result);
	}

	void Core::loadGames() noexcept
	{
		glob_t result;

		glob("games/lib_arcade_*.so", GLOB_TILDE, nullptr,
			&result);
		for (size_t i = 0; i < result.gl_pathc; ++i)
			loadGame(result.gl_pathv[i]);
		globfree(&result);
	}

	void Core::initializeGameAndGraphic()
	{
		changeGraphicLib();
		while (!_actualGame && _games.size()) {
			try {
				changeGameLib();
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
			}
		}
		if (!_games.size())
			throw Exception("No valid game in directory 'games'");
		loadGameDataInGraphicLib();
	}

	void Core::loadGameDataInGraphicLib()
	{
		auto name = _actualGame->getNameGame();
		auto menu = _actualGame->getBackgroundMenu();
		auto texture = _actualGame->getTextures();
		_actualGraphic->setGameName(name);
		_actualGraphic->setGameMenu(menu);
		_actualGraphic->loadTextures(texture);
	}

	void Core::changeGraphicLib()
	{
		funcCreate func = _itGraphic->second;
		void *ptr = func();
		auto graphicPtr = static_cast<IGraphic *>(ptr);
		if (!graphicPtr)
			throw Exception(
				_itGraphic->first + " is not graphic library");
		_actualGraphic.reset(graphicPtr);
	}

	void Core::changeGameLib()
	{
		funcCreate func = _itGame->second;
		void *ptr = func();
		auto gamePtr = static_cast<IGame *>(ptr);
		if (!gamePtr)
			throw Exception(
				_itGame->first + " is not game library");
		_actualGame.reset(gamePtr);
	}

	void Core::nextLib() noexcept
	{
		if (_graphics.size() == 1)
			return;
		auto oldIt = _itGraphic;
		++_itGraphic;
		if (_itGraphic == _graphics.end())
			_itGraphic = _graphics.begin();
		try {
			changeGraphicLib();
			loadGameDataInGraphicLib();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			_itGraphic = oldIt;
		}
	}

	void Core::prevLib() noexcept
	{
		if (_graphics.size() == 1)
			return;
		auto oldIt = _itGraphic;
		if (_itGraphic == _graphics.begin())
			_itGraphic = _graphics.end();
		--_itGraphic;
		try {
			changeGraphicLib();
			loadGameDataInGraphicLib();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			_itGraphic = oldIt;
		}
	}

	void Core::nextGame() noexcept
	{
		if (_games.size() == 1)
			return;
		auto oldIt = _itGame;
		++_itGame;
		if (_itGame == _games.end())
			_itGame = _games.begin();
		try {
			changeGameLib();
			loadGameDataInGraphicLib();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			_itGame = oldIt;
		}
	}

	void Core::prevGame() noexcept
	{
		if (_games.size() == 1)
			return;
		auto oldIt = _itGame;
		if (_itGame == _games.begin())
			_itGame = _games.end();
		--_itGame;
		try {
			changeGameLib();
			loadGameDataInGraphicLib();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			_itGame = oldIt;
		}
	}

	void Core::displayGame()
	{
		_actualGraphic->drawMap(_actualGame->getMap());
		_actualGraphic->drawEntities(_actualGame->getEntities());
		_actualGraphic->drawScore(_actualGame->getScore());
		_actualGraphic->display();
	}

	bool Core::doSwitchInputGame(Input input)
	{
		switch (input) {
		case Input::EXIT:
			return true;
		case Input::MENU:
			return false;
		case Input::NEXT_GAME:
			nextGame();
			return false;
		case Input::PREV_GAME:
			prevGame();
			return false;
		case Input::NEXT_LIB:
			//nextLib();
			return false;
		case Input::PREV_LIB:
			//prevLib();
			return false;
		default:
			return false;
		}
	}

	bool Core::startGame()
	{
		while (_actualGame->runGameLoop()) {
			displayGame();
			auto input = _actualGraphic->getInput();
			_actualGame->putInput(input);
			if (doSwitchInputGame(input))
				return true;
		}
		return false;
	}

	bool Core::doSwitchInputRun(Input input)
	{
		switch (input) {
		case Input::NEXT_GAME:
			nextGame();
			return false;
		case Input::PREV_GAME:
			prevGame();
			return false;
		case Input::NEXT_LIB:
			//nextLib();
			return false;
		case Input::PREV_LIB:
			//prevLib();
			return false;
		case Input::START_GAME:
			return startGame();
		default:
			return false;
		}
	}

	void Core::run()
	{
		try {
			for (Input input = _actualGraphic->getInput();
				input != Input::EXIT;
				input = _actualGraphic->getInput()) {
				if (doSwitchInputRun(input))
					return;
				_actualGraphic->drawMenu();
				_actualGraphic->display();
				std::this_thread::sleep_for(
					std::chrono::milliseconds(10));
			}
		} catch (std::exception &e) {
			throw Exception(e.what());
		}
	}
}

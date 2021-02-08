//
// EPITECH PROJECT, 2018
// LibSDL2
// File description:
// LibSDL2.cpp
//

#include <exception>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "LibSDL2.hpp"

namespace Arcade {
	void LibSDL2::initInput()
	{
		_input[SDL_SCANCODE_UP] = Input::GO_UP;
		_input[SDL_SCANCODE_RIGHT] = Input::GO_RIGHT;
		_input[SDL_SCANCODE_DOWN] = Input::GO_DOWN;
		_input[SDL_SCANCODE_LEFT] = Input::GO_LEFT;
		_input[SDL_SCANCODE_2] = Input::PREV_LIB;
		_input[SDL_SCANCODE_3] = Input::NEXT_LIB;
		_input[SDL_SCANCODE_4] = Input::PREV_GAME;
		_input[SDL_SCANCODE_5] = Input::NEXT_GAME;
		_input[SDL_SCANCODE_8] = Input::RESTART;
		_input[SDL_SCANCODE_9] = Input::MENU;
		_input[SDL_SCANCODE_ESCAPE] = Input::EXIT;
		_input[SDL_SCANCODE_SPACE] = Input::SHOOT;
		_input[SDL_SCANCODE_RETURN] = Input::START_GAME;
	}

	LibSDL2::LibSDL2(): _win(0)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw Exception("Fail to init SDL2");
		if (IMG_Init(IMG_INIT_PNG) < 0)
			throw Exception("Fail to init IMG");
		if (TTF_Init() < 0) {
			std::cout << "C'est la merde noire" << std::endl;
			throw Exception("Fail to launch TTF");
		}
		_win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, _width, _height,
			SDL_WINDOW_SHOWN);
		if (_win == 0)
			throw Exception("Fail to create window");
		_renderer = SDL_CreateRenderer(_win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == 0)
			throw Exception("Fail to create renderer");
		_font = TTF_OpenFont("./font/arial.ttf", 14);
		if (!_font)
			throw Exception("Fail to arial.ttf");
		initInput();
	}

	void LibSDL2::cleanTexture()
	{
		for (auto it = _surfaces.begin(); it != _surfaces.end(); ++it)
			SDL_FreeSurface(*it);
		for (auto it = _textures.begin(); it != _textures.end(); ++it)
			SDL_DestroyTexture(*it);
		_surfaces.clear();
		_textures.clear();
	}

	LibSDL2::~LibSDL2()
	{
		if (_win != 0)
			SDL_DestroyWindow(_win);
		if (_renderer != 0)
			SDL_DestroyRenderer(_renderer);
		if (_font != 0)
			TTF_CloseFont(_font);
		if (_surfaceMenu != 0)
			SDL_FreeSurface(_surfaceMenu);
		if (_textureMenu != 0)
			SDL_DestroyTexture(_textureMenu);
		cleanTexture();
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	void LibSDL2::setGameName(const std::string &name)
	{ SDL_SetWindowTitle(_win, name.c_str()); }

	void LibSDL2::setGameMenu(const std::string &file)
	{
		_surfaceMenu = IMG_Load(file.c_str());
		if (!_surfaceMenu)
			throw Exception("fail to load Menu from file");
		_textureMenu =
			SDL_CreateTextureFromSurface(_renderer, _surfaceMenu);
		if (!_textureMenu)
			throw Exception("fail to load Menu from file");
	}

	void LibSDL2::loadTextures(const Textures &textures)
	{
		SDL_Surface *surface;
		SDL_Texture *texture;

		cleanTexture();
		for (auto it = textures.begin(); it != textures.end(); ++it) {
			surface = IMG_Load(it->texture2D.c_str());
			if (!surface)
				throw Exception("fail to load surface '"
					+ it->texture2D + "'");
			_surfaces.push_back(surface);
			texture = SDL_CreateTextureFromSurface(_renderer,
				surface);
			if (!texture)
				throw Exception("fail to load texture '"
					+ it->texture2D + "'");
			_textures.push_back(texture);
		}
	}

	Input LibSDL2::getInput()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN
				&& _input.find(event.key.keysym.scancode)
				!= _input.end())
				return (_input[event.key.keysym.scancode]);
		}
		return Input::NONE;
	}

	void LibSDL2::drawMenu()
	{
		SDL_Rect scale = { 0, 0, _width, _height };
		SDL_RenderCopyEx(_renderer, _textureMenu, &scale, nullptr, 0,
			nullptr, SDL_FLIP_NONE);
	}

	void LibSDL2::drawMap(const Map &map)
	{
		if (!map.size() || !map[0].size())
			throw Exception("Invalid Map");
		SDL_Rect pos = { 0, 0, static_cast<int>(_cellX),
			static_cast<int>(_cellY) };

		for (size_t y = 0; y < map.size(); ++y)
			for (size_t x = 0; x < map[y].size(); ++x) {
				if (map[y][x] >= _textures.size())
					continue;
				pos.x = _cellX * x;
				pos.y = _cellY * y + _mapPos;
				SDL_RenderCopyEx(_renderer,
					_textures[map[y][x]], nullptr, &pos, 0,
					nullptr, SDL_FLIP_NONE);
			}
	}

	void LibSDL2::drawEntities(const Entities &entities)
	{
		SDL_Rect pos = { 0, 0, static_cast<int>(_cellX),
			static_cast<int>(_cellY) };

		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if (it->texture >= _textures.size())
				continue;
			pos.x = _cellX * it->posX;
			pos.y = _cellY * it->posY + _mapPos;
			SDL_RenderCopyEx(_renderer, _textures[it->texture],
				nullptr, &pos, 90 * it->dir, nullptr,
				SDL_FLIP_NONE);
		}
	}

	void LibSDL2::drawScore(const Score &score)
	{
		SDL_Color color = { 255, 255, 255, 0 };
		SDL_Rect pos = { 16, 16, static_cast<int>(_cellY),
			static_cast<int>(_cellY) };

		for (auto it = score.begin(); it != score.end(); ++it) {
			std::string text(it->first + ": " + it->second);
			SDL_Surface *scoreSurface = TTF_RenderText_Solid(_font,
				text.c_str(), color);
			SDL_Texture *scoreText =
				SDL_CreateTextureFromSurface(_renderer,
					scoreSurface);
			pos.w = _cellY * text.size() / 2;
			SDL_RenderCopyEx(_renderer, scoreText,
				nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);
			SDL_RenderPresent(_renderer);
			SDL_FreeSurface(scoreSurface);
			SDL_DestroyTexture(scoreText);
			pos.y += 16;
		}
	}

	void LibSDL2::display()
	{
		SDL_RenderPresent(_renderer);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(_renderer, NULL);
	}
}

extern "C" void *create()
{
	return new Arcade::LibSDL2();
}

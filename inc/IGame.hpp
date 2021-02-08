//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGame.hpp
//

#pragma once

#include "IGraphic.hpp"

namespace Arcade {
	/*
	 * Interface pour les lib de jeu
	 */
	class IGame {
	public:
		virtual ~IGame() {}

		/* Récupère l'input donné en argument */
		virtual void putInput(Input) = 0;

		/*
		 * C'est la méthode qui va éxécuter un cycle de jeu
		 *
		 * retourne true tant que le jeu tourne
		 * retourne false quand il se termine
		 */
		virtual bool runGameLoop() = 0;

		/* Renvoi le nom du jeu */
		virtual const std::string &getNameGame() const = 0;

		/* Renvoi le chemin du ficher correspondant à l'image du menu */
		virtual const std::string &getBackgroundMenu() const = 0;

		/* Renvoi un vecteur contenant toutes les textures du jeu */
		virtual const Textures &getTextures() const = 0;

		/* Renvoi la map du jeu à afficher */
		virtual const Map &getMap() const = 0;

		/* Renvoi les entités à afficher du jeu */
		virtual const Entities &getEntities() const = 0;

		/* Renvoi le score à afficher */
		virtual const Score &getScore() const = 0;
	};

	/* using pour le unique_ptr de IGame */
	using IGamePtr = std::unique_ptr<IGame>;
}

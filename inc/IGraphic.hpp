//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGraphic.hpp
//

#pragma once

#include <memory>
#include <vector>
#include <deque>
#include <map>

namespace Arcade {
	/*
	 * Enum des inputs qui sont récupérées par la lib IGraphic :
	 *
	 * NONE : aucun input
	 * EXIT : quitte le programme
	 * NEXT_LIB, PREV_LIB : change la lib avec la précèdente/suivante
	 * NEXT_GAME, PREV_GAME : change le jeu avec le précèdent/suivant
	 * START_GAME : lance le jeu sélectioné
	 * RESTART : relance le jeu
	 * MENU : retourne au menu de sélection de jeu
	 * GO_* : flèches directionelles
	 * SHOOT : tire
	*/
	enum class Input: uint16_t {
		NONE = 0,
		EXIT,
		NEXT_LIB,
		PREV_LIB,
		NEXT_GAME,
		PREV_GAME,
		START_GAME,
		RESTART,
		MENU,
		GO_UP,
		GO_RIGHT,
		GO_DOWN,
		GO_LEFT,
		SHOOT
	};

	/*
	 * Structure qui gère une texture en ascii :
	 *
	 * character : charactere à afficher
	 * color : couleure du charactere
	 * colorBack : couleure du fond
	 */
	struct AsciiTexture {
		char character;
		uint16_t color;
		uint16_t colorBack;
	};

	/*
	 * Structure qui gère les textures d'une tile :
	 *
	 * ascii : la texture en ascii
	 * texture2D : chemin du fichier de texture 2D
	 * texture3D : chemin du fichier de texture 3D
	 */
	struct Texture {
		AsciiTexture ascii;
		std::string texture2D;
		std::string texture3D;
	};

	enum direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	/*
	 * Structure qui gère une entité :
	 *
	 * texture : id de la texture à utiliser
	 * posX : position x sur la map
	 * posY : position y sur la map
	 * dir : orientation du sprite
	 */
	struct Entity {
		uint16_t texture;
		float posX;
		float posY;
		enum direction dir;
	};

	/*
	 * Map : vecteur de vecteur d'unint16_t.
	 *
	 * Chaque uint16_t correspond à une case dans le jeu et contient l'id
	 * de la texture à afficher.
	 */
	using Map = std::vector<std::vector<uint16_t> >;

	/* Entities : deque d'entité */
	using Entities = std::deque<Entity>;

	/*
	 * Textures : vecteur de Texture.
	 *
	 * Elle doit contenir toutes les textures du jeu.
	 */
	using Textures = std::vector<Texture>;

	/*
	 * Score : map de score.
	 *
	 * Le premier correspond au type du score (ex : "Vie").
	 * Le deuxième correspond au score en lui même (ex : 3).
	 */
	using Score = std::map<std::string, std::string>;

	/*
	 * Interface pour les lib graphiques
	 */
	class IGraphic {
	public:
		virtual ~IGraphic()
		{}

		/*
		 * Fixe le nom du jeu actuel
		 * 	(pour par exemple changer le titre de la fenêtre).
		 */
		virtual void setGameName(const std::string &) = 0;

		/*
		 * Fixe l'image du jeu qui sert dans le menu de sélection de jeu
		 *
		 * Il prend en argument le chemin de l'image.
		 */
		virtual void setGameMenu(const std::string &) = 0;

		/*
		 * Charge les textures du vecture Textures donné en argument
		 *
		 * L'indexe d'une texture dans le vector doit correspondre
		 * 	à son id.
		 * Cette méthode doit décharger les textures précèdemment
		 * 	charger.
		 */
		virtual void loadTextures(const Textures &) = 0;

		/* Renvoi un input saisi par l'utilisateur */
		virtual Input getInput() = 0;

		/* Dessine l'image du menu dans la fenêtre */
		virtual void drawMenu() = 0;

		/* Dessine la map donnée en argument dans la fenêtre */
		virtual void drawMap(const Map &) = 0;

		/* Dessine les entités données en argument dans la fenêtre */
		virtual void drawEntities(const Entities &) = 0;

		/* Dessine le score donné en argument dans la fenêtre */
		virtual void drawScore(const Score &) = 0;

		/* affiche le contenu de la fenêtre à l'écran */
		virtual void display() = 0;
	};

	/* using pour le unique_ptr de IGraphic */
	using IGraphicPtr = std::unique_ptr<IGraphic>;

	/*
	 * typedef pour le pointeur sur fonction qui crée une lib
	 * (graphic ou jeu)
	 */
	typedef void *(*funcCreate)();

	/* globale qui sert pour le chargement de la lib avec dlsym */
	extern "C" {
	void *create();
	}
}

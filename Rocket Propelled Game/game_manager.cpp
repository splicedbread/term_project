#include "game_manager.h"
const int GameManager::MAX_CHARACTER_AMOUNT = 3;
const char * GameManager::GAME_NAME = "What a Racket";
const char * GameManager::SAVES_DIRECTORY_PATH_NAME = "./saves";
const char * GameManager::GSAVES_DIRECTORY_PATH_NAME = "./saves/game";
const char * GameManager::RESOURCE_DIRECTORY_PATH_NAME = "./resources";
namespace fs = std::experimental::filesystem;

/*//////////////////////////////////////////////////////////////////////////////////////
	Default Ctor
	Checks executable environment, will throw an error if resources folder doesnt exist
		or is empty (nothing could be loaded then)
	Starts the game after creation
*///////////////////////////////////////////////////////////////////////////////////////
GameManager::GameManager() : e_StartMode(MAIN)
{
	//As the game is starting, we will make sure we start at the main menu
	//using base # initialization
	//On creation of the object, we want to make sure the environment is setup
	fs::path pt = SAVES_DIRECTORY_PATH_NAME;
	//if that directory doesnt exist, then create one
	if (!fs::is_directory(pt))
	{
		std::cout << "Saves directory created.." << std::endl;
		fs::create_directory(pt);
	}
	else
	{
		std::cout << "Saves directory exists.." << std::endl;
	}

	pt = GSAVES_DIRECTORY_PATH_NAME;
	//if that directory doesnt exist, then create one
	if (!fs::is_directory(pt))
	{
		std::cout << "Game Saves directory created.." << std::endl;
		fs::create_directory(pt);
	}
	else
	{
		std::cout << "Game Saves directory exists.." << std::endl;
	}

	//if no resource folder is found, or it is empty, throw an error.
	pt = RESOURCE_DIRECTORY_PATH_NAME;
	if (!fs::is_directory(pt))
	{
		std::cout << "No resource folder found" << std::endl;
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	else if (fs::is_empty(pt))
	{
		std::cout << "resource folder empty" << std::endl;
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	else
	{
		//after the directory is created, or confirms it exists, then the constructor has
		//finished its job
		//due to its nature of needing to be called first, start the game
		GameStart();
	}
}

GameManager::~GameManager()
{
	GameSave();
}

/*
	GameStart
	Starts the game, if a window hasnt been opened, create one.

	If the game is paused, resume,

	Most of the graphical things will occur here
*/
void GameManager::GameStart()
{
	//check if the window is already open, if it is, resume, if it isnt then open it
	if (!window.isOpen())
	{
		window.create(sf::VideoMode(1000.0f, 1000.0f), GAME_NAME, sf::Style::Titlebar | sf::Style::Close);
	}

	//once the window has been created, we must manage what things to display
	switch (e_StartMode)
	{
	case GameManager::MAIN:
		//This will manage drawing the main menu, with options for a new game, resume last or load
		//it will also include an exit option
		std::cout << "Main Screen should display" << std::endl;
		while (window.isOpen())
		{

		}
		break;
	case GameManager::WORLD:
		//starting from pause will need to load the gamestate file associated with this character
		//resuming while in a fight seems problematic
		std::cout << "World Screen should display" << std::endl;
		break;
	case GameManager::FIGHT:
		//fight may be used recursively, calling GameStart() from MAIN switch, after
		//chaning e_StartMode to fight will bring it here, could be dangerous
		std::cout << "Fight Screen should display" << std::endl;
		break;
	case GameManager::SHOP:
		//Shop screen has the same issue as fight, but the idea is to open a shop
		//for upgrading the character.
		std::cout << "Shop Screen should display" << std::endl;
		break;
	default:
		break;
	}

}

void GameManager::GamePause()
{
}

void GameManager::GameSave()
{
}

void GameManager::GameExit()
{
}



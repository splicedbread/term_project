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
	while (window.isOpen())
	{
		switch (e_StartMode)
		{
		case GameManager::MAIN:
			//This will manage drawing the main menu, with options for a new game, resume last or load
			//it will also include an exit option
			m_menuRender();
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

void GameManager::m_menuRender()
{
	const int MENU_OPTIONS = 3;
	sf::Event event;
	float text_sp = 30.0f;
	bool windowControl = true;
	window.setVerticalSyncEnabled(true);
	float margin = 15;
	//create a rectange that has a "transparent" fill color, with a white border for thickness
	sf::RectangleShape margin_border;
	margin_border.setFillColor(sf::Color::Black);
	margin_border.setOutlineColor(sf::Color::White);
	margin_border.setOutlineThickness(margin);
	margin_border.setSize(sf::Vector2f(window.getSize().x - 4*margin, window.getSize().y - 4*margin));
	margin_border.setOrigin(-2*margin, -2*margin);

	//text pointer array for 3 elements, [0] is New Game, [1] is Load Game, [2] is Exit
	sf::Font font;
	font.loadFromFile("./comic.ttf");
	sf::Text textArray[MENU_OPTIONS];
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		textArray[i].setFont(font);
		textArray[i].setFillColor(sf::Color::White);
		textArray[i].setOutlineColor(sf::Color::White);
		textArray[i].setStyle(sf::Text::Bold);
		textArray[i].setOrigin(-1*(window.getSize().x/2.0f), -1*(window.getSize().y/2.0f + i*text_sp));
	}

	textArray[0].setString("New Game");
	textArray[1].setString("Load Game");
	textArray[2].setString("Exit");

	std::cout << "Main Screen should display" << std::endl;
	while (window.isOpen() && windowControl)
	{
		if (window.hasFocus())
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						break;
					case sf::Keyboard::Down:
						break;
					}
					break;
				}
			}
		}

		window.clear();
		window.draw(margin_border);
		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			window.draw(textArray[i]);
		}
		window.display();
	}
}

void GameManager::p_menuRender()
{
}

void GameManager::shopRender()
{
}

void GameManager::worldRender()
{
}



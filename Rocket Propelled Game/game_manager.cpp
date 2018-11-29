#include "game_manager.h"
const String GameManager::GAME_NAME = "Rock Paper Gun";
const String GameManager::SAVES_DIRECTORY_PATH_NAME = "./saves";
const String GameManager::GSAVES_DIRECTORY_PATH_NAME = "./saves/game";
const String GameManager::RESOURCE_DIRECTORY_PATH_NAME = "./resources";
const String GameManager::EnemyResourceArray[GameManager::NUM_ENEMY_TYPES] = {"/RPG_grub.png", "/RPG_eagle.png", "/RPG_goat.png", "/RPG_serphent.png", "/RPG_lion.png", "/RPG_goblin.png",
																			"/RPG_griffin.png", "/RPG_troll.png", "/RPG_boss.png" };
std::uniform_int_distribution<int> GameManager::health_distribution(Entity::STRD_HEALTH - 70, Entity::STRD_HEALTH + 30);
std::uniform_int_distribution<int> GameManager::strength_distribution(Entity::STRD_STRGTH - 1, Entity::STRD_STRGTH + 6);
std::uniform_int_distribution<int> GameManager::arm_distribution(0, 10);
std::uniform_int_distribution<int> GameManager::mana_distribution(Entity::STRD_MANA - 5, Entity::STRD_MANA + 25);
std::uniform_int_distribution<int> GameManager::dmg_distribution(1, String::ToInt(Entity::STRD_WEP.GetDmg()) + 3);


namespace fs = std::experimental::filesystem;

/*//////////////////////////////////////////////////////////////////////////////////////
	Default Ctor
	Checks executable environment, will throw an error if resources folder doesnt exist
		or is empty (nothing could be loaded then)
	Starts the game after creation
*///////////////////////////////////////////////////////////////////////////////////////
GameManager::GameManager() : e_StartMode(MAIN)
{
	isStartup = true;
	fileChange = false;
	loadLinkedList();
	//As the game is starting, we will make sure we start at the main menu
	//using base # initialization
	//On creation of the object, we want to make sure the environment is setup
	fs::path pt = SAVES_DIRECTORY_PATH_NAME.GetStr();
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

	pt = GSAVES_DIRECTORY_PATH_NAME.GetStr();
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
	pt = RESOURCE_DIRECTORY_PATH_NAME.GetStr();
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
		//GameStart();
	}

	//GameState setup for a freshgame
	m_Gstate.m_enemiesRemaining = 10;
	m_Gstate.m_enemiesKilled = 0;
	m_Gstate.m_currentEnemy = 1;
	m_Gstate.inFight = false;

	bool charLoad = false;
	charLoad = LoadFile(CHARLIST);
	//Now load both the gamestate file and the character list file
	if (charLoad)
	{
		cout << "Character List loaded" << endl;
	}
	else
	{
		cout << "Character List not loaded, using defaults" << endl;

		//Setup an empty Character_Info before loading it in
		for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
		{
			for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
			{
				Character_Info[j][i] = "NA";
			}
		}
		SaveFile(CHARLIST);
	}
	//setting up the seed for the random number generator
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point period = clock.now();
	std::chrono::high_resolution_clock::duration dur = std::chrono::high_resolution_clock::now() - period;
	unsigned seed = dur.count();
	gen.seed(seed);

	isStartup = false;
}

//default dtor, saves the game before the object disappears out of scope.
GameManager::~GameManager()
{
	GameSave();
}

/*//////////////////////////////////////////////////////////////
	GameStart
	Starts the game, if a window hasnt been opened, create one.

	If the game is paused, resume,

	Most of the graphical things will occur here
*//////////////////////////////////////////////////////////////
void GameManager::GameStart()
{
	//check if the window is already open, if it is, resume, if it isnt then open it
	if (!window.isOpen())
	{
		window.create(sf::VideoMode(1000.0f, 1000.0f), GAME_NAME.GetStr(), sf::Style::Titlebar | sf::Style::Close);
		window.setVerticalSyncEnabled(true);
	}

	//once the window has been created, we must manage what things to display
	while (window.isOpen())
	{
		switch (e_StartMode)
		{
		case GameManager::MAIN:
			//This will manage drawing the main menu, with options for a new game, resume last or load
			//it will also include an exit option
			try
			{
				m_menuRender();
			}
			catch (const int error)
			{
				if (error == RESOURCE_FILE_DIRECTORY_ERR)
				{
					String ERROR_STRING = "RESOURCE ERROR";
					throw ERROR_STRING;
				}
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
			GameSave();
			GameLoad();
			fightRender();
			break;
		case GameManager::SHOP:
			//Shop screen has the same issue as fight, but the idea is to open a shop
			//for upgrading the character.
			std::cout << "Shop Screen should display" << std::endl;
			break;
		case GameManager::EXIT:
			//GameSave();
			window.close();
			break;
		}
	}

}

/*///////////////////////////////////////////////////////////////////////////////////
	GamePause calls the pause menu render, realistically only called when in a fight
*///////////////////////////////////////////////////////////////////////////////////
void GameManager::GamePause()
{
	p_menuRender();
}

/*///////////////////////////////////////////////////////////////////////////////
	GameSave saves all the needed files for the game into their respective files.
*////////////////////////////////////////////////////////////////////////////////
void GameManager::GameSave()
{
	if (character.GetName() != "NA" )
	{
		character.Info(0);
		SaveFile(CHAR);
		SaveFile(CHAR_GAME);
	}

	bool isListEmpty = true;
	for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
	{
		if (Character_Info[0][1] != "NA")
		{
			isListEmpty = false;
		}
	}

	if (!isListEmpty)
	{
		SaveFile(CHARLIST);
	}
	else
	{
		DeleteFile(CHARLIST);
	}
}

/*/////////////////////////////////////////////////////////////
	GameLoad() loads appropiate files from the saves directory
*/////////////////////////////////////////////////////////////
void GameManager::GameLoad()
{
	if (character.GetName() != "NA")
	{
		LoadFile(CHAR);
		LoadFile(CHAR_GAME);
		character.Info(0);
	}
}

/*//////////////////////////////////////////////////////////////////////////
	m_menuRender()
	is a "helper" function that is called when the game starts,
	and when the main menu is specified. Its job is to provide an interface
	for the user to navigate the main menu
*///////////////////////////////////////////////////////////////////////////
void GameManager::m_menuRender()
{
	const int MENU_OPTIONS = 3;
	//used for events
	sf::Event event;

	//margin is for the gap between window and white border.
	float margin = 15;

	//text spacing
	float text_sp = 50.0f;

	//from 0.0-1.0, relative positioning for drawing objects
	float x_coord = 0;
	float y_coord = 0;

	//window control if an exit is needed without closing the window
	bool windowControl = true;

	//create a rectange that has a "transparent" fill color, with a white border for thickness
	sf::RectangleShape margin_border;
	margin_border.setFillColor(sf::Color::Black);
	margin_border.setOutlineColor(sf::Color::White);
	margin_border.setOutlineThickness(margin);
	margin_border.setSize(sf::Vector2f(window.getSize().x - 4*margin, window.getSize().y - 4*margin));
	margin_border.setOrigin(-2*margin, -2*margin);

	//text pointer array for 3 elements, [0] is New Game, [1] is Load Game, [2] is Exit
	//load the used font, I know, I'd doing comic sans as a joke
	sf::Font font;
	font.loadFromFile("./comic.ttf");
	sf::Text textArray[MENU_OPTIONS];
	//Position where the menu objects should be positioned related to the white border
	x_coord = 0.10f; //10% of the pixels away from the left side of the white border
	y_coord = 0.35f; //35% away from the top of the white border
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		textArray[i].setFont(font);
		textArray[i].setFillColor(sf::Color::White);
		textArray[i].setOutlineColor(sf::Color::White);
		textArray[i].setStyle(sf::Text::Bold);
		textArray[i].setOrigin(-1*(margin_border.getSize().x * x_coord), -1*((margin_border.getSize().y * y_coord) + i*text_sp));
	}
	textArray[0].setString("New Game");
	textArray[1].setString("Load Game");
	textArray[2].setString("Exit");

	//Create a new text for instructions at the bottom.
	sf::Text instructions;
	instructions.setFont(font);
	instructions.setFillColor(sf::Color::White);
	instructions.setOutlineColor(sf::Color::White);
	instructions.setStyle(sf::Text::Bold);
	instructions.setString("Arrow Keys to navigate, [Enter] to select highlighted");
	//set instructions origin
	x_coord = 0.10f;
	y_coord = 0.90f;
	instructions.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));

	//Load a fancy background for the main menu
	String str = RESOURCE_DIRECTORY_PATH_NAME;
	sf::Texture bg_texture;
	str = str + "/RPG_dungeon.png";
	if (!bg_texture.loadFromFile(str.GetStr()))
	{
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	//create the sprite for the bg
	sf::Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	x_coord = margin_border.getOrigin().x;
	y_coord = margin_border.getOrigin().y;
	bg_sprite.setOrigin(x_coord, y_coord);

	//Load in the title to display, first load a texture, then a create a sprite
	sf::Texture title_texture;
	str = RESOURCE_DIRECTORY_PATH_NAME;
	str = str + "/RPG_name.png";
	if (!title_texture.loadFromFile(str.GetStr()))
	{
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	//creating a sprite for the title
	sf::Sprite title_Sprite;
	title_Sprite.setTexture(title_texture);
	//position it
	x_coord = 0.05;
	y_coord = 0.05;
	title_Sprite.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));
	//lets scale it a little bigger
	title_Sprite.setScale(2.0, 2.0);

	std::cout << "Main Screen should display" << std::endl;
	
	int selection = 0;

	while (window.isOpen() && windowControl)
	{
		if (window.hasFocus() && windowControl)
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
						--selection;
						if (selection < 0)
						{
							selection = MENU_OPTIONS - 1;
						}
						break;
					case sf::Keyboard::Down:
						++selection;
						if (selection > MENU_OPTIONS - 1)
						{
							selection = 0;
						}
						break;
					case sf::Keyboard::Enter:
						switch (selection)
						{
						case 0: //New Game
							n_menuRender();
							break;
						case 1: //Load Game
							s_menuRender();
							break;
						case 2: //Exit
							e_StartMode = EXIT;
							break;
						}
						break;
					}
					break;
				}
			}
		}

		window.clear();
		window.draw(margin_border);
		window.draw(bg_sprite);
		window.draw(instructions);
		window.draw(title_Sprite);
		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			if (i == selection)
			{
				textArray[i].setFillColor(sf::Color::Yellow);
				textArray[i].setOutlineColor(sf::Color::Yellow);
			}
			else
			{
				textArray[i].setFillColor(sf::Color::White);
				textArray[i].setOutlineColor(sf::Color::White);
			}
			window.draw(textArray[i]);
		}
		window.display();
		if (e_StartMode != MAIN)
		{
			windowControl = false;
		}
	}
}

/*////////////////////////////////////////////////////////////////////////////////////
	brief: renders the new character menu

	renders the new character creation menu, which accepts a name (perhaps class type)
*/////////////////////////////////////////////////////////////////////////////////////
void GameManager::n_menuRender()
{
	//failure flag
	bool failure = false;
	//all for input, including timing
	String Input = "";
	String TempInput = "";
	String BottomText = "";

	bool inputing = false;
	bool input_wait = false;

	const int MENU_OPTIONS = 3;
	//used for events
	sf::Event event;

	//margin is for the gap between window and white border.
	float margin = 15;

	//text spacing
	float text_sp = 50.0f;

	//from 0.0-1.0, relative positioning for drawing objects
	float x_coord = 0;
	float y_coord = 0;

	//window control if an exit is needed without closing the window
	bool windowControl = true;

	//create a rectange that has a "transparent" fill color, with a white border for thickness
	sf::RectangleShape margin_border;
	margin_border.setFillColor(sf::Color::Black);
	margin_border.setOutlineColor(sf::Color::White);
	margin_border.setOutlineThickness(margin);
	margin_border.setSize(sf::Vector2f(window.getSize().x - 4 * margin, window.getSize().y - 4 * margin));
	margin_border.setOrigin(-2 * margin, -2 * margin);

	//text pointer array for 3 elements, [0] is New Game, [1] is Load Game, [2] is Exit
	//load the used font, I know, I'd doing comic sans as a joke
	sf::Font font;
	font.loadFromFile("./comic.ttf");
	sf::Text textArray[MENU_OPTIONS];
	//Position where the menu objects should be positioned related to the white border
	x_coord = 0.10; //10% of the pixels away from the left side of the white border
	y_coord = 0.35; //35% away from the top of the white border
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		textArray[i].setFont(font);
		textArray[i].setFillColor(sf::Color::White);
		textArray[i].setOutlineColor(sf::Color::White);
		textArray[i].setStyle(sf::Text::Bold);
		textArray[i].setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * ((margin_border.getSize().y * y_coord) + i * text_sp));
	}
	textArray[0].setString("Character Name: ");
	textArray[1].setString("Create Character");
	textArray[2].setString("Return");

	//Need to create a text for entered text
	sf::Text inputText;
	inputText.setFont(font);
	inputText.setFillColor(sf::Color::Yellow);
	inputText.setOutlineColor(sf::Color::Yellow);
	//inputText.setStyle(sf::Text::Bold);

	//set the position of the entered text right next to the character:
	x_coord = textArray[0].getOrigin().x - textArray[0].getGlobalBounds().width - margin;
	y_coord = textArray[0].getOrigin().y;
	inputText.setOrigin(x_coord, y_coord);

	//Create a new text for instructions at the bottom.
	sf::Text instructions;
	instructions.setFont(font);
	instructions.setFillColor(sf::Color::White);
	instructions.setOutlineColor(sf::Color::White);
	instructions.setStyle(sf::Text::Bold);
	BottomText = "Arrow Keys to navigate, [Enter] to select highlighted, [Enter] to clear";
	instructions.setString(BottomText.GetStr());
	//set instructions origin
	x_coord = 0.10;
	y_coord = 0.90;
	instructions.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));

	//Load in the title to display, first load a texture, then a create a sprite
	sf::Texture texture;
	String str = RESOURCE_DIRECTORY_PATH_NAME;
	str = str + "/RPG_charname.png";
	if (!texture.loadFromFile(str.GetStr()))
	{
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	//creating a sprite for the title
	sf::Sprite title_Sprite;
	title_Sprite.setTexture(texture);
	//position it
	x_coord = 0.05;
	y_coord = 0.05;
	title_Sprite.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));
	//lets scale it a little bigger
	title_Sprite.setScale(2.0, 2.0);

	std::cout << "Character Creation Screen should display" << std::endl;

	int selection = 0;

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
						--selection;
						if (selection < 0)
						{
							selection = MENU_OPTIONS - 1;
						}
						failure = false;
						break;
					case sf::Keyboard::Down:
						++selection;
						if (selection > MENU_OPTIONS - 1)
						{
							selection = 0;
						}
						failure = false;
						break;
					case sf::Keyboard::Enter:
						switch (selection)
						{
						case 0: //Character Name
							inputing = true;
							if (inputText.getString() != "")
							{
								inputText.setFillColor(sf::Color::Black);
								inputText.setOutlineColor(sf::Color::Black);
								inputText.setOutlineThickness(2.0f);
								window.draw(inputText);
								window.display();
								Input = "";
								TempInput = "";

								inputText.setString(Input.GetStr());
								inputText.setFillColor(sf::Color::Yellow);
								inputText.setOutlineColor(sf::Color::Yellow);
								inputText.setOutlineThickness(0.0f);
								window.draw(inputText);
								window.display();
								inputing = false;
							}

							while (inputing)
							{
								if (window.waitEvent(event))
								{
									textArray[0].setFillColor(sf::Color::Cyan);
									textArray[0].setOutlineColor(sf::Color::Cyan);
									textArray[0].setOutlineThickness(0.0f);
									window.draw(textArray[0]);
									TempInput = "";
									if (event.type == sf::Event::TextEntered && !(event.key.code == sf::Keyboard::BackSpace) && !(event.key.code == sf::Keyboard::Enter))
									{
										if (event.text.unicode < 128 && event.text.unicode > 31)
										{
											TempInput = static_cast<char>(event.text.unicode);
										}
									}
									
									if (event.type == sf::Event::KeyPressed)
									{
										if (event.key.code == sf::Keyboard::Enter)
										{
											inputing = false;
										}

										if (event.key.code == sf::Keyboard::BackSpace)
										{
											inputing = false;
											inputText.setFillColor(sf::Color::Black);
											inputText.setOutlineColor(sf::Color::Black);
											window.draw(inputText);
											window.display();
											Input = "";
											inputText.setString(Input.GetStr());
										}
									}
								}

								Input = Input + TempInput;
								inputText.setString(Input.GetStr());
								window.draw(inputText);
								window.display();
							}

							inputText.setString(Input.GetStr());
							window.draw(inputText);
							window.display();
							selection = 0;
							break;
						case 1: //Create Character
							//for now, test if the character could be made
							if (Input != "")
							{
								if (onCreateCharacter(Input))
								{
									cout << "character created successfully" << endl;

									GameSave();
									windowControl = false;
									//character.SetName("NA");
									//redirect to fight
									e_StartMode = FIGHT;
								}
								else
								{
									cout << "character creation failed" << endl;
									character.SetName("NA");
									failure = true;
								}
							}
							break;
						case 2: //Return
							windowControl = false;
							e_StartMode = MAIN;
							break;
						default:
							break;
						}
						break;
					}
					break;
				}
			}
		}



		window.clear();
		window.draw(margin_border);

		if (failure)
		{
			for (int i = 0; i < MENU_OPTIONS; i++)
			{
				if (i != 1)
				{
					if (i == selection)
					{
						textArray[i].setFillColor(sf::Color::Yellow);
						textArray[i].setOutlineColor(sf::Color::Yellow);
					}
					else
					{
						textArray[i].setFillColor(sf::Color::White);
						textArray[i].setOutlineColor(sf::Color::White);
					}
					window.draw(textArray[i]);
				}
			}
			BottomText = "Error: Character list is full";
			textArray[1].setFillColor(sf::Color::Red);
			textArray[1].setOutlineColor(sf::Color::Red);
			instructions.setString(BottomText.GetStr());
			window.draw(textArray[1]);
		}
		else
		{
			textArray[1].setString("Create Character");
			for (int i = 0; i < MENU_OPTIONS; i++)
			{
				if (i == selection)
				{
					textArray[i].setFillColor(sf::Color::Yellow);
					textArray[i].setOutlineColor(sf::Color::Yellow);
				}
				else
				{
					textArray[i].setFillColor(sf::Color::White);
					textArray[i].setOutlineColor(sf::Color::White);
				}
				window.draw(textArray[i]);
			}
			BottomText = "Arrow Keys to navigate, [Enter] to select highlighted, \n[Enter] to clear";
			instructions.setString(BottomText.GetStr());
		}

		window.draw(instructions);
		window.draw(inputText);
		window.draw(title_Sprite);
		window.display();
	}
}

/*/////////////////////////////////////////
	brief: renders the load character menu

	renders the load character menu 
*/////////////////////////////////////////
void GameManager::s_menuRender()
{
	String BottomText = "";
	//failure flag
	bool failure = false;
	//all for input, including timing
	bool inputing = false;

	bool fileDeleted = true;

	const int MENU_OPTIONS = 5;

	int selected = -1;
	//used for events
	sf::Event event;

	//margin is for the gap between window and white border.
	float margin = 15;

	//text spacing
	float text_sp = 110.0f;

	//from 0.0-1.0, relative positioning for drawing objects
	float x_coord = 0;
	float y_coord = 0;

	//window control if an exit is needed without closing the window
	bool windowControl = true;

	//load the used font, I know, I'd doing comic sans as a joke
	sf::Font font;
	font.loadFromFile("./comic.ttf");
	
	//Create a new text for instructions at the bottom.
	sf::Text instructions;

	//create a rectange that has a "transparent" fill color, with a white border for thickness
	sf::RectangleShape margin_border;
	margin_border.setFillColor(sf::Color::Black);
	margin_border.setOutlineColor(sf::Color::White);
	margin_border.setOutlineThickness(margin);
	margin_border.setSize(sf::Vector2f(window.getSize().x - 4 * margin, window.getSize().y - 4 * margin));
	margin_border.setOrigin(-2 * margin, -2 * margin);



	//text pointer array for 3 elements, [0] is New Game, [1] is Load Game, [2] is Exit
	//load the used font, I know, I'd doing comic sans as a joke
	sf::Text textArray[MENU_OPTIONS];
	sf::Text savesArray[2][MENU_OPTIONS - 2];
	//Position where the menu objects should be positioned related to the white border
	x_coord = 0.10; //10% of the pixels away from the left side of the white border
	y_coord = 0.35; //35% away from the top of the white border
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		textArray[i].setFont(font);
		textArray[i].setFillColor(sf::Color::White);
		textArray[i].setOutlineColor(sf::Color::White);
		textArray[i].setStyle(sf::Text::Bold);
		textArray[i].setLineSpacing(0.0f);
		textArray[i].setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * ((margin_border.getSize().y * y_coord) + i * text_sp));
	}

	textArray[0].setString("Save 1 : ");
	textArray[1].setString("Save 2 : ");
	textArray[2].setString("Save 3 : ");
	textArray[3].setString("Load Selected Character");
	textArray[4].setString("Return");

	//Create a new text for instructions at the bottom.
	instructions.setFont(font);
	instructions.setFillColor(sf::Color::White);
	instructions.setOutlineColor(sf::Color::White);
	instructions.setStyle(sf::Text::Bold);
	instructions.setString("Arrow Keys to navigate, [Enter] to select yellow\n[BackSpace] then [Enter] when red to delete a save\n[Esc] to cancel delete");
	//set instructions origin
	x_coord = 0.10;
	y_coord = 0.90;
	instructions.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));

	//Load in the title to display, first load a texture, then a create a sprite
	sf::Texture texture;
	String str = RESOURCE_DIRECTORY_PATH_NAME;
	str = str + "/RPG_loadc.png";
	if (!texture.loadFromFile(str.GetStr()))
	{
		throw RESOURCE_FILE_DIRECTORY_ERR;
	}
	//creating a sprite for the title
	sf::Sprite title_Sprite;
	title_Sprite.setTexture(texture);
	//position it
	x_coord = 0.05;
	y_coord = 0.05;
	title_Sprite.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));
	//lets scale it a little bigger
	title_Sprite.setScale(2.0, 2.0);

	std::cout << "Load Character Screen should display" << std::endl;

	int selection = 0;

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
						--selection;
						if (selection < 0)
						{
							selection = MENU_OPTIONS - 1;
						}
						failure = false;
						break;
					case sf::Keyboard::Down:
						++selection;
						if (selection > MENU_OPTIONS - 1)
						{
							selection = 0;
						}
						failure = false;
						break;
					case sf::Keyboard::Enter:
						if (!fileDeleted)
						{
							switch (selection)
							{
							case 0: //Save Slot 1
								if (selected == -1 || selected != selection)
								{
									selected = selection;
								}
								else if (selected == selection)
								{
									selected = -1;
								}
								break;
							case 1: //2
								if (selected == -1 || selected != selection)
								{
									selected = selection;
								}
								else if (selected == selection)
								{
									selected = -1;
								}
								break;
							case 2: //3
								if (selected == -1 || selected != selection)
								{
									selected = selection;
								}
								else if (selected == selection)
								{
									selected = -1;
								}
								break;
							case 3: //Load Character
								if (selected != -1 && Character_Info[0][selected] != "NA")
								{
									windowControl = false;
									e_StartMode = FIGHT;
									character.SetName(Character_Info[0][selected]);
									GameLoad();
								}
								break;
							case 4: //Return
								windowControl = false;
								e_StartMode = MAIN;
								break;
							}
						}
						break;
					case sf::Keyboard::BackSpace:
						if (selected != -1)
						{
							if (Character_Info[0][selected] != "NA")
							{
								textArray[selected].setFillColor(sf::Color::Red);
								textArray[selected].setOutlineColor(sf::Color::Red);
								textArray[selected].setOutlineThickness(2.0f);
								window.draw(textArray[selected]);
								window.display();
								inputing = true;
								while (inputing)
								{
									if (window.hasFocus())
									{
										if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
										{
											if (DeleteFile(Character_Info[0][selected]))
											{
												cout << "Chacter deleted" << endl;
												fileChange = true;
												SaveFile(CHARLIST);
												fileChange = false;
												textArray[selected].setOutlineThickness(0.0f);
												inputing = false;
												fileDeleted = true;
												selected = -1;
											}
										}

										if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
										{
											textArray[selected].setOutlineThickness(0.0f);
											inputing = false;
											selected = -1;
										}
									}
								}
							}
						}
						break;
					}
					break;
				}
			}
		}

		window.clear();

		if (fileDeleted)
		{
			fileChange = true;
			if (!LoadFile(CHARLIST))
			{
				cout << "Character List not loaded, using defaults" << endl;

				//Setup an empty Character_Info before loading it in
				for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
				{
					for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
					{
						Character_Info[j][i] = "NA";
					}
				}
				SaveFile(CHARLIST);
			}
			fileChange = false;

			x_coord = textArray[1].getOrigin().x - textArray[0].getGlobalBounds().width - margin;
			String stringName = "Name: [ ";
			for (int i = 0; i < MENU_OPTIONS - 2; i++)
			{

				for (int j = 0; j < 2; j++)
				{

					savesArray[j][i].setFont(font);
					savesArray[j][i].setFillColor(sf::Color::White);
					savesArray[j][i].setOutlineColor(sf::Color::White);
					savesArray[j][i].setStyle(sf::Text::Bold);
					savesArray[j][i].setLineSpacing(0.7f);

					if (j == 0)
					{
						if (Character_Info[j][i] != "NA")
						{
							y_coord = textArray[i].getOrigin().y + 2.5f*(margin);
							stringName = stringName + Character_Info[j][i] + " ]";
							savesArray[j][i].setString(stringName.GetStr());
						}
						else
						{
							y_coord = textArray[i].getOrigin().y;
							savesArray[j][i].setString("Empty Save Slot");
						}
					}
					else
					{
						if (Character_Info[j][i] != "NA")
						{
							y_coord = textArray[i].getOrigin().y + 0.5f*(margin);
							stringName = Character_Info[j][i];
							savesArray[j][i].setString(stringName.GetStr());
						}
						else
						{
							y_coord = textArray[i].getOrigin().y;
							savesArray[j][i].setString("Empty Save Slot");
						}
					}

					savesArray[j][i].setOrigin(x_coord, y_coord);
					stringName = "Name: [ ";
				}
			}
			fileDeleted = false;
		}

		window.draw(margin_border);
		window.draw(instructions);
		window.draw(title_Sprite);
		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			if (i == selected)
			{
				textArray[i].setFillColor(sf::Color::Cyan);
				textArray[i].setOutlineColor(sf::Color::Cyan);
			}
			else if (i == selection)
			{
				textArray[i].setFillColor(sf::Color::Yellow);
				textArray[i].setOutlineColor(sf::Color::Yellow);
			}
			else
			{
				textArray[i].setFillColor(sf::Color::White);
				textArray[i].setOutlineColor(sf::Color::White);
			}
			window.draw(textArray[i]);
		}

		for (int i = 0; i < MENU_OPTIONS - 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				window.draw(savesArray[j][i]);
			}
		}

		window.display();
	}
}

/*//////////////////////////////////////////////////////////////////
	p_menuRender(), shopRender, and worldRender were original plans,
	but they will be incorporated on my free time
*///////////////////////////////////////////////////////////////////
void GameManager::p_menuRender()
{
}

void GameManager::shopRender()
{
}

void GameManager::worldRender()
{
}

/*//////////////////////////////
	load Linked list on startup
*//////////////////////////////
void GameManager::loadLinkedList()
{
	enemyList.Insert(new Grub);
	enemyList.Insert(new Grub);
	enemyList.Insert(new Eagle);
	enemyList.Insert(new Goat);
	enemyList.Insert(new Serphent);
	enemyList.Insert(new Lion);
	enemyList.Insert(new Goblin);
	enemyList.Insert(new Griffin);
	enemyList.Insert(new Troll);
	enemyList.Insert(new Boss);
	enemyList.Display();
	if (enemyList.SetCurrentPos(0))
	{
		cout << "LinkedList Loaded and current pos is 0" << endl;
	}
}

/*///////////////////////////////////////////////////////////////////////////////////
	Fight Render is for managing both the menu for fighting and the turn based combat
*////////////////////////////////////////////////////////////////////////////////////
void GameManager::fightRender()
{
	//window control if an exit is needed without closing the window
	bool windowControl = true;
	//How many options are in the menu?
	const int MENU_OPTIONS = 4;
	//used for events
	sf::Event event;
	//setup current position in the enemy list
	if (!enemyList.SetCurrentPos(m_Gstate.m_currentEnemy - 1))
	{
		cout << "There was a problem getting the current enemy" << endl;
	}

	cout << "Gstate current enemy: " << m_Gstate.m_currentEnemy << endl;
	cout << "current enemy name: " << enemyList.GetData()->GetName().GetStr() << endl;
	cout << "current_pos value: " << enemyList.GetCurrentPos() << endl;

	//text pointer array for 3 elements, [0] is New Game, [1] is Load Game, [2] is Exit
	//load the used font, I know, I'd doing comic sans as a joke
	sf::Font font;
	font.loadFromFile("./comic.ttf");
	sf::Text textArray[MENU_OPTIONS];
	String contextArray[MENU_OPTIONS] = { "Fight", "Items", "Run", "Exit" };
	String fightArray[MENU_OPTIONS] = { "Attack", "Block", "Guts", "Return" };

	//data for managing 
	int damageD = 0;
	//get the health of the enemy
	Enemy * enemy = enemyList.GetData();
	float eOriginalHealth = static_cast<float>(enemy->GetHealth());
	float pOriginalHealth = static_cast<float>(character.GetHealth());
	//Create all necessary rectangles
		//margin is for the gap between window and white border.
		float margin = 15; //Margin in pixels
		float text_sp = 20.0f; //spacing that text shall use
		float x_coord = 0; //xcoordinate for use in orgins
		float y_coord = 0; //ycoordinate

		//create a rectange that has a "transparent" fill color, with a white border for thickness
		sf::RectangleShape margin_border;
		margin_border.setFillColor(sf::Color::Black);
		margin_border.setOutlineColor(sf::Color::White);
		margin_border.setOutlineThickness(margin);
		margin_border.setSize(sf::Vector2f(window.getSize().x - 4 * margin, window.getSize().y - 4 * margin));
		margin_border.setOrigin(-2 * margin, -2 * margin);

		//Second rectange to put the context menu in
		sf::RectangleShape context_menu;
		context_menu = margin_border;
		//resize it
		context_menu.setSize(sf::Vector2f(margin_border.getSize().x - 4*margin, margin_border.getSize().y * 0.15f));
		//position it
		//get the orgin from the margin, then subtract the height of the margin then add the height of your rectangle
		x_coord = margin_border.getOrigin().x - 2*margin;
		y_coord = margin_border.getOrigin().y - margin_border.getSize().y + context_menu.getSize().y + 2*margin;
		context_menu.setOrigin(x_coord, y_coord);
	//End Rectangle creation


	
	//Position where the menu objects should be positioned related to the white border of the context menu
	x_coord = context_menu.getOrigin().x; 
	y_coord = context_menu.getOrigin().y - 2*margin; 

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			textArray[i].setFont(font);
			textArray[i].setFillColor(sf::Color::White);
			textArray[i].setOutlineColor(sf::Color::White);
			textArray[i].setStyle(sf::Text::Bold);
			textArray[i].setString(contextArray[i].GetStr());
			if (i < 2)
			{
				textArray[i].setOrigin(x_coord - (context_menu.getSize().x * 0.1f), y_coord - (i * context_menu.getSize().y * 0.25f));
			}
			else
			{
				textArray[i].setOrigin(textArray[i-2].getOrigin().x - (context_menu.getSize().x * 0.5f), textArray[i-2].getOrigin().y);
			}
		}
	}

	//BackGround Setup
		//Load a fancy background for the main menu
		m_pathName = RESOURCE_DIRECTORY_PATH_NAME;
		sf::Texture bg_texture;
		m_pathName = m_pathName + "/RPG_dungeon.png";
		if (!bg_texture.loadFromFile(m_pathName.GetStr()))
		{
			throw RESOURCE_FILE_DIRECTORY_ERR;
		}
		//create the sprite for the bg
		sf::Sprite bg_sprite;
		bg_sprite.setTexture(bg_texture);
		x_coord = margin_border.getOrigin().x;
		y_coord = margin_border.getOrigin().y;
		bg_sprite.setOrigin(x_coord, y_coord);

	//Player Sprite Setup
		m_pathName = RESOURCE_DIRECTORY_PATH_NAME;
		sf::Texture player_texture;
		m_pathName = m_pathName + "/RPG_player.png";
		if (!player_texture.loadFromFile(m_pathName.GetStr()))
		{
			throw RESOURCE_FILE_DIRECTORY_ERR;
		}
		//create the sprite for the player
		sf::Sprite player_Sprite;
		player_Sprite.setTexture(player_texture);
		x_coord = margin_border.getOrigin().x - margin_border.getGlobalBounds().width + player_Sprite.getGlobalBounds().width + 2.0f*margin;
		y_coord = margin_border.getOrigin().y - margin_border.getGlobalBounds().height + player_Sprite.getGlobalBounds().height + context_menu.getGlobalBounds().height;
		player_Sprite.setOrigin(x_coord, y_coord);

	//Enemy Sprite Setup
		//Load in the title to display, first load a texture, then a create a sprite
		sf::Texture enemy_texture;
		m_pathName = RESOURCE_DIRECTORY_PATH_NAME;
		m_pathName = m_pathName + EnemyResourceArray[m_Gstate.m_currentEnemy -1];
		if (!enemy_texture.loadFromFile(m_pathName.GetStr()))
		{
			throw RESOURCE_FILE_DIRECTORY_ERR;
		}
		//creating a sprite for the title
		sf::Sprite enemy_Sprite;
		enemy_Sprite.setTexture(enemy_texture);
		//position it
		x_coord = margin_border.getOrigin().x - enemy_Sprite.getGlobalBounds().width*0.5f;
		y_coord = context_menu.getOrigin().y + enemy_Sprite.getGlobalBounds().height;
		enemy_Sprite.setOrigin(x_coord, y_coord);
		//enemy_Sprite.scale(0.35,0.35);

		float healthPercent = static_cast<float>(enemy->GetHealth())/eOriginalHealth;
		sf::Color green(150, 220, 180);
		//create a rectange that has ahealth bar
		sf::RectangleShape ehealth_green;
		ehealth_green.setFillColor(green);
		ehealth_green.setOutlineColor(sf::Color::Black);
		ehealth_green.setOutlineThickness(2.0f);
		ehealth_green.setSize(sf::Vector2f(enemy_Sprite.getGlobalBounds().width * healthPercent, margin));
		x_coord = enemy_Sprite.getOrigin().x;
		y_coord = enemy_Sprite.getOrigin().y + margin*2;
		ehealth_green.setOrigin(x_coord, y_coord);

		sf::RectangleShape ehealth_red;
		ehealth_red.setFillColor(sf::Color::Red);
		ehealth_red.setOutlineColor(sf::Color::Black);
		ehealth_red.setOutlineThickness(1.0f);
		ehealth_red.setSize(sf::Vector2f(enemy_Sprite.getGlobalBounds().width, margin));
		x_coord = enemy_Sprite.getOrigin().x;
		y_coord = enemy_Sprite.getOrigin().y + margin * 2;
		ehealth_red.setOrigin(x_coord, y_coord);

		//create copies of the health bar, but for player
		sf::RectangleShape phealth_green = ehealth_green;
		sf::RectangleShape phealth_red = ehealth_red;
		healthPercent = static_cast<float>(character.GetHealth()) / pOriginalHealth;
		phealth_green.setSize(sf::Vector2f(enemy_Sprite.getGlobalBounds().width * healthPercent, margin));
		phealth_red.setSize(sf::Vector2f(enemy_Sprite.getGlobalBounds().width, margin));
		x_coord = player_Sprite.getOrigin().x - 0.3f*player_Sprite.getGlobalBounds().width;
		y_coord = player_Sprite.getOrigin().y + margin * 2;
		phealth_green.setOrigin(x_coord, y_coord);
		phealth_red.setOrigin(x_coord, y_coord);

	std::cout << "Fight Screen should display" << std::endl;

	//Variables used for menu
	int selection = 0;
	int selected = -1;

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
						--selection;
						if (selection < 0)
						{
							selection = MENU_OPTIONS - 1;
						}
						break;
					case sf::Keyboard::Down:
						++selection;
						if (selection > MENU_OPTIONS - 1)
						{
							selection = 0;
						}
						break;
					case sf::Keyboard::Right:
						++selection;
						++selection;
						if (selection > MENU_OPTIONS - 1)
						{
							selection = 0;
						}
						break;
					case sf::Keyboard::Left:
						--selection;
						--selection;
						if (selection < 0)
						{
							selection = MENU_OPTIONS - 1;
						}
						break;
					case sf::Keyboard::Enter:
						switch (selection)
						{
						case 0: //Fight menu
							break;
						case 1: //Items menu
							break;
						case 2: //Run (reload fight)
							break;
						case 3: //Exit
							SaveFile(CHAR_GAME);
							windowControl = false;
							e_StartMode = MAIN;
							break;
						}
						break;
					}
					break;
				}
			}
		}

		//Draw Updates
		window.clear(); //clear the frame buffer and screen
		window.draw(margin_border); //first draw the first 
		window.draw(bg_sprite); //draw the background on top of the margin border
		window.draw(enemy_Sprite); //draw the enemy sprite
		window.draw(player_Sprite);
		//player sprite goes here
		//Check the current health of the enemy, and using that info, set the appropiate width for the green bar
		healthPercent = static_cast<float>(enemy->GetHealth()) / eOriginalHealth;
		ehealth_green.setSize(sf::Vector2f(enemy_Sprite.getGlobalBounds().width * healthPercent, margin));
		window.draw(ehealth_red); //draw the enemy red health bar
		window.draw(ehealth_green); //draw the green healthbar after
		//same for the player
		healthPercent = static_cast<float>(character.GetHealth()) / pOriginalHealth;
		window.draw(phealth_red); //draw the enemy red health bar
		window.draw(phealth_green); //draw the green healthbar after

		window.draw(context_menu); //draw the context menu on top of the sprites
		
		//this is where it is complicated
		//Depending on the selection provided by menu navigation, change the displayed text
		switch (selected)
		{
		case -1: //context menu (fight, items, run, exit)
			for (int i = 0; i < MENU_OPTIONS; i++)
			{
				textArray[i].setString(contextArray[i].GetStr()); //If context menu, use context menu strings
			}
			break;
		case 0: //Fight Menu (attack, block, guts, return)
			for (int i = 0; i < MENU_OPTIONS; i++)
			{
				textArray[i].setString(fightArray[i].GetStr()); //If fight menu, use fight menu strings
			}
			break;
		case 1: //Items Menu
			//not yet
			break;
		}

		for (int i = 0; i < MENU_OPTIONS; i++)
		{
			if (i == selection)
			{
				textArray[i].setFillColor(sf::Color::Yellow);
				textArray[i].setOutlineColor(sf::Color::Yellow);
			}
			else
			{
				textArray[i].setFillColor(sf::Color::White);
				textArray[i].setOutlineColor(sf::Color::White);
			}
			window.draw(textArray[i]); //based on the current selection, hightlight the text yellow
		}
		window.display();
	}
}

/*///////////////////////////////////////////////////////////////////////////////////
	onCreateCharacter checks if there is space for the character to inhabit without
	over-writing
	returns false if it could not do anything
*///////////////////////////////////////////////////////////////////////////////////
bool GameManager::onCreateCharacter(const String & name)
{
	String Health = "Health: [";
	String Remaining = "Enemies Remaining: [";
	String RemainingAmount = String::ToString(m_Gstate.m_enemiesRemaining);
	String Strength = "Strength: [";
	String Armour = "Armour: [";
	String Mana = "Mana: [";
	String buff = "";

	String coolNames[5] = {"DoomGuy", "GoblinSlayer", "Brock", "Kira", "KillerQueen"};

	bool flag = false;
	character.SetName(name);

	//dev mode names make the character op

	for (int i = 0; i < 5 && !flag; i++)
	{
		if (character.GetName() == coolNames[i])
		{
			cout << "You must be pretty cool: " << character.GetName() << endl;
			flag = true;
			character.SetStrength(999);
			character.SetArmour(999);
			character.SetMana(999);
			character.SetHealth(999);
		}
	}

	if (!flag)
	{
		//random character stats
		//health
		
		dice_roll = health_distribution(gen);
		health_distribution.reset();
		character.SetHealth(dice_roll);
		
		//strength
		dice_roll = strength_distribution(gen);
		strength_distribution.reset();
		character.SetStrength(dice_roll);

		//armour
		dice_roll = arm_distribution(gen);
		arm_distribution.reset();
		character.SetArmour(dice_roll);

		//mana
		dice_roll = mana_distribution(gen);
		mana_distribution.reset();
		character.SetMana(dice_roll);

		//Weapon Damage
		int wepDMG = String::ToInt(Entity::STRD_WEP.GetDmg());
		dice_roll = dmg_distribution(gen);
		dmg_distribution.reset();
		buff = String::ToString(dice_roll);
		Weapon tempWep("RNG Sword", "Sold as is", buff, "00.00.01.50");
		character.SetWep(tempWep);

	}

	//character.Info(0);


	flag = false;
	
	for (int i = 0; i < MAX_CHARACTER_AMOUNT && !flag; i++)
	{
		for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1 && !flag; j++)
		{
			if (Character_Info[0][i] == "NA")
			{
				flag = true;
				Character_Info[0][i] = character.GetName();
				Character_Info[1][i] = Health + String::ToString(character.GetHealth()) + "] " + Remaining + RemainingAmount + "]\n" +
										Strength + String::ToString(character.GetStrength()) + "] " + Armour + String::ToString(character.GetArmour()) + "]";
			}
		}
	}

	if (flag)
	{
		SaveFile(CHARLIST);
	}

	return flag;
}

/*//////////////////////////////////////////////////////////////////////////////////////////////
	SaveFile uses a enum switch for saving a specific type of file, wether that is the character
	gamestate, or the list of characters, it can do all, 

	LoadFile does all of that in reverse.
*///////////////////////////////////////////////////////////////////////////////////////////////
void GameManager::SaveFile(FileType type)
{
	String slash = "/";
	String extension = ".bin";
	String GSave = "_gsave";
	String List = "_list";
	String dir = SAVES_DIRECTORY_PATH_NAME;
	String name = this->character.GetName();
	if (character.GetName() != "NA" || isStartup || fileChange)
	{
		switch (type)
		{
		case GameManager::CHAR:
		{
			m_pathName = "";
			m_pathName = dir + slash + name + extension;
			this->m_FileOut.open(m_pathName.GetStr(), ios::out | ios::binary | ios::trunc | ios::ate);
			if (m_FileOut.is_open())
			{
				int length = 0;
				int elements = 0;
				/*
					Character Write Order: Name Size, Name, Health, Armour, Mana, Strength, m_inventory (Potions), m_inventory (Items) , m_wallet
				*/
				//name
				length = this->character.GetName().GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << this->character.GetName().GetStr();
				//health
				length = this->character.GetHealth();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				//armour
				length = this->character.GetArmour();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				//mana
				length = this->character.GetMana();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				//strength
				length = this->character.GetStrength();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));

				//wallet
				length = String::ToString(this->character.GetWallet().GetMoney()).GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << String::ToString(this->character.GetWallet().GetMoney()).GetStr();

				//Potions
				/*
					Potion info Write Order: PotionArraySize ,Name, Potency, Description, Cost, CostSize
				*/
				//Potion Array Elements
				elements = this->character.GetInv().GetPotions().GetElements();
				this->m_FileOut.write(reinterpret_cast<char *>(&elements), sizeof(int));

				for (int j = 0; j < elements; j++)
				{
					//Name
					length = this->character.GetInv().GetPotions()[j].GetName().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetPotions()[j].GetName().GetStr();

					//Potency
					length = this->character.GetInv().GetPotions()[j].GetPoten().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetPotions()[j].GetPoten().GetStr();

					//Description
					length = this->character.GetInv().GetPotions()[j].GetDesc().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetPotions()[j].GetDesc().GetStr();

					//CostSize
					length = this->character.GetInv().GetPotions()[j].GetCostSize().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetPotions()[j].GetCostSize().GetStr();
				}

				//Items
				/*
					Item info Write Order: ItemArraySize ,Name, Description, Cost, CostSize
				*/
				//Item Array Elements
				elements = this->character.GetInv().GetItems().GetElements();
				this->m_FileOut.write(reinterpret_cast<char *>(&elements), sizeof(int));

				for (int j = 0; j < elements; j++)
				{
					//Name
					length = this->character.GetInv().GetItems()[j].GetName().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetItems()[j].GetName().GetStr();

					//Description
					length = this->character.GetInv().GetItems()[j].GetDesc().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetItems()[j].GetDesc().GetStr();

					//CostSize
					length = this->character.GetInv().GetItems()[j].GetCostSize().GetLen();
					this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
					this->m_FileOut << this->character.GetInv().GetItems()[j].GetCostSize().GetStr();

				}

				//Weapon

				//Name
				length = this->character.GetWep().GetName().GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << this->character.GetWep().GetName().GetStr();

				//Description
				length = this->character.GetWep().GetDesc().GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << this->character.GetWep().GetDesc().GetStr();

				//damage
				length = this->character.GetWep().GetDmg().GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << this->character.GetWep().GetDmg().GetStr();

				//cost
				length = this->character.GetWep().GetCost().GetLen();
				this->m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
				this->m_FileOut << this->character.GetWep().GetCost().GetStr();

				//cout << "character " << i + 1 << ". written to file" << endl;
				m_FileOut.close();
				//	cout << "File written to and closed" << endl;
			}
			else
			{
				cout << "Could not open file" << endl;
			}
		}
		break;
		case GameManager::CHAR_GAME:
		{
			m_pathName = GSAVES_DIRECTORY_PATH_NAME;
			m_pathName = m_pathName + slash + name + GSave + extension;

			this->m_FileOut.open(m_pathName.GetStr(), ios::out | ios::binary | ios::trunc | ios::ate);
			if (m_FileOut.is_open())
			{
				GameState * state = &m_Gstate;
				m_FileOut.write(reinterpret_cast<char *>(state), sizeof(GameState));
				//cout << "character " << i + 1 << ". written to file" << endl;
				state = nullptr;
				m_FileOut.close();
				//	cout << "File written to and closed" << endl;
			}
			else
			{
				cout << "Could not open file" << endl;
			}
		}
		break;
		case GameManager::CHARLIST:
		{
			int length;
			m_pathName = GSAVES_DIRECTORY_PATH_NAME;
			m_pathName = m_pathName + slash + GAME_NAME + List + extension;
			this->m_FileOut.open(m_pathName.GetStr(), ios::out | ios::binary | ios::trunc | ios::ate);
			if (m_FileOut.is_open())
			{
				for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
				{
					for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
					{
						length = Character_Info[j][i].GetLen();
						m_FileOut.write(reinterpret_cast<char *>(&length), sizeof(int));
						m_FileOut << Character_Info[j][i].GetStr();
					}
				}
				m_FileOut.close();
			}
			else
			{
				cout << "could not open file" << endl;
			}
		}
		break;
		}
	}
}

bool GameManager::LoadFile(FileType type)
{
	String slash = "/";
	String extension = ".bin";
	String GSave = "_gsave";
	String List = "_list";
	String dir = SAVES_DIRECTORY_PATH_NAME;
	String name = this->character.GetName();
	char * buffer = nullptr;
	bool flag = false;
	if (character.GetName() != "NA" || isStartup || fileChange)
	{
		switch (type)
		{
		case GameManager::CHAR:
		{
			cout << "loading character... " << character.GetName() << endl;
			m_pathName = "";
			m_pathName = dir + slash + name + extension;
			if (FileExists(m_pathName))
			{
				this->m_FileIn.open(m_pathName.GetStr(), ios::in | ios::binary);
				if (m_FileIn.is_open())
				{
					int length = 0;
					int elements = 0;
					/*
						Character Write Order: Name Size, Name, Health, Armour, Mana, Strength, m_inventory (Potions), m_inventory (Items) , m_wallet
					*/
					//name
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					character.SetName(buffer);
					delete[] buffer;
					buffer = nullptr;
					//health
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					character.SetHealth(length);
					//armour
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					character.SetArmour(length);
					//mana
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					character.SetMana(length);
					//strength
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					character.SetStrength(length);

					//wallet
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					character.AddMoney(String::ToInt(buffer));
					delete[] buffer;
					buffer = nullptr;

					//Potions
					/*
						Potion info Write Order: PotionArraySize ,Name, Potency, Description, Cost, CostSize
					*/
					//Potion Array Elements
					m_FileIn.read(reinterpret_cast<char *>(&elements), sizeof(int));

					for (int j = 0; j < elements; j++)
					{
						Potion tempPt;
						//Name
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempPt.SetName(buffer);
						delete[] buffer;
						buffer = nullptr;

						//Potency
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempPt.SetPoten(buffer);
						delete[] buffer;
						buffer = nullptr;

						//Description
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempPt.SetDesc(buffer);
						delete[] buffer;
						buffer = nullptr;

						//CostSize
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempPt.SetCostSize(String::ToInt(buffer));
						delete[] buffer;
						buffer = nullptr;

						//add the potion to the character
						character.PickupObj(tempPt);
					}

					//Items
					/*
						Item info Write Order: ItemArraySize ,Name, Description, Cost, CostSize
					*/
					//Item Array Elements
					m_FileIn.read(reinterpret_cast<char *>(&elements), sizeof(int));

					//Items
					for (int j = 0; j < elements; j++)
					{
						Item tempItm;
						//Name
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempItm.SetName(buffer);
						delete[] buffer;
						buffer = nullptr;

						//Description
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempItm.SetDesc(buffer);
						delete[] buffer;
						buffer = nullptr;

						//CostSize
						m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
						buffer = new char[length + 1];
						m_FileIn.read(buffer, length);
						buffer[length] = '\0';
						tempItm.SetCostSize(String::ToInt(buffer));
						delete[] buffer;
						buffer = nullptr;

						//add item to player
						character.PickupObj(tempItm);
					}

					Weapon tmpWep;

					//Weapon

					//name
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					tmpWep.SetName(buffer);
					delete[] buffer;
					buffer = nullptr;

					//desc
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					tmpWep.SetDesc(buffer);
					delete[] buffer;
					buffer = nullptr;

					//damage
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					tmpWep.SetDmg(String::ToInt(buffer));
					delete[] buffer;
					buffer = nullptr;

					//cost
					m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
					buffer = new char[length + 1];
					m_FileIn.read(buffer, length);
					buffer[length] = '\0';
					tmpWep.SetCost(buffer);
					delete[] buffer;
					buffer = nullptr;


					character.SetWep(tmpWep);

					//cout << "character " << i + 1 << ". written to file" << endl;
					m_FileIn.close();
					//	cout << "File written to and closed" << endl;
				}
				else
				{
					cout << "Could not open file" << endl;
					flag = true;
				}
			}
			else
			{
			cout << "Character File does not exist" << endl;
			flag = true;
			}
		}
		break;
		case GameManager::CHAR_GAME:
		{
			m_pathName = GSAVES_DIRECTORY_PATH_NAME;
			m_pathName = m_pathName + slash + name + GSave + extension;
			if (FileExists(m_pathName))
			{
				this->m_FileIn.open(m_pathName.GetStr(), ios::in | ios::binary);
				if (m_FileIn.is_open())
				{
					GameState state;
					m_FileIn.read(reinterpret_cast<char *>(&state), sizeof(GameState));
					m_Gstate = state;
					m_FileIn.close();
				}
				else
				{
					cout << "Could not open file" << endl;
					flag = true;
				}
			}
			else
			{
				cout << "GameState File does not exist" << endl;
				flag = true;
			}
		}
		break;
		case GameManager::CHARLIST:
		{
			int length;
			m_pathName = GSAVES_DIRECTORY_PATH_NAME;
			m_pathName = m_pathName + slash + GAME_NAME + List + extension;
			if (FileExists(m_pathName))
			{
				this->m_FileIn.open(m_pathName.GetStr(), ios::in | ios::binary);
				if (m_FileIn.is_open())
				{
					for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
					{
						for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
						{
							m_FileIn.read(reinterpret_cast<char *>(&length), sizeof(int));
							buffer = new char[length + 1];
							m_FileIn.read(buffer, length);
							buffer[length] = '\0';
							Character_Info[j][i] = buffer;
							delete[] buffer;
							buffer = nullptr;
						}
					}
					m_FileIn.close();
				}
				else
				{
					cout << "could not open file" << endl;
					flag = true;
				}
			}
			else
			{
				cout << "Character List File does not exist" << endl;
				flag = true;
			}
		}
		break;
		}
	}
	else
	{
	flag = true;
	}
	return !flag;
}
/*
	DeleteFile removes files for the respective name
*/
bool GameManager::DeleteFile(String name)
{
	bool cf_flag = false;
	bool cg_flag = false;
	bool cl_flag = false;
	String slash = "/";
	String extension = ".bin";
	String GSave = "_gsave";
	String List = "_list";
	String dir = SAVES_DIRECTORY_PATH_NAME;
	//Delete the character file
	m_pathName = dir + slash + name + extension;
	if (FileExists(m_pathName))
	{
		remove(m_pathName.GetStr());
		cf_flag = FileExists(m_pathName);
	}
	//Delete the character game state file
	dir = GSAVES_DIRECTORY_PATH_NAME;
	m_pathName = dir + slash + name + GSave + extension;
	if (FileExists(m_pathName))
	{
		remove(m_pathName.GetStr());
		cg_flag = FileExists(m_pathName);
	}
	//remove the character from the character list
	cl_flag = true;
	bool emptyList = true;

	for (int i = 0; i < MAX_CHARACTER_AMOUNT && cl_flag; i++)
	{
			if (Character_Info[0][i] == name)
			{
				cl_flag = false;
				Character_Info[0][i] = "NA";
				Character_Info[1][i] = "NA";
			}
	}

	for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
	{
		if (Character_Info[0][i] != "NA")
		{
			emptyList = false;
		}
	}

	if (emptyList)
	{
		dir = GSAVES_DIRECTORY_PATH_NAME;
		m_pathName = dir + slash + GAME_NAME + List + extension;
		cout << "EmptyList Path name: " << m_pathName << endl;
		if (FileExists(m_pathName))
		{
			remove(m_pathName.GetStr());
			cl_flag = FileExists(m_pathName);
		}
	}

	//return the results of the flags
	return (!cf_flag && !cg_flag && !cl_flag);
}

/*///////////////////////////////////////////////////////////////////////////////
	Checks for a file at a given pathname, if it does not exist then return false
*///////////////////////////////////////////////////////////////////////////////
bool GameManager::FileExists(const String & pathname)
{
	bool flag = false;
	m_FileIn.open(pathname.GetStr(), ios::in | ios::binary);
	flag = m_FileIn.good();
	m_FileIn.close();
	return flag;
}



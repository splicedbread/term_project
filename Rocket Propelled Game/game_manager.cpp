#include "game_manager.h"
const char * GameManager::GAME_NAME = "Rock Paper Gun";
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
		//GameStart();
	}

	//GameState setup for a freshgame
	m_Gstate.m_enemiesRemaining = 20;
	m_Gstate.m_enemiesKilled = 0;
	m_Gstate.m_currentEnemy = 1;
	m_Gstate.inFight = false;

	//Setup an empty Character_Info before loading it in
	for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
	{
		for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
		{
			Character_Info[j][i] = "NA";
		}
	}
}

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
		window.create(sf::VideoMode(1000.0f, 1000.0f), GAME_NAME, sf::Style::Titlebar | sf::Style::Close);
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

void GameManager::GamePause()
{
}

void GameManager::GameSave()
{
	SaveFile(CHAR);
	SaveFile(CHAR_GAME);
	SaveFile(CHARLIST);
}

void GameManager::GameLoad()
{
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
	x_coord = 0.10; //10% of the pixels away from the left side of the white border
	y_coord = 0.35; //35% away from the top of the white border
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
	x_coord = 0.10;
	y_coord = 0.90;
	instructions.setOrigin(-1 * (margin_border.getSize().x * x_coord), -1 * (margin_border.getSize().y * y_coord));

	//Load in the title to display, first load a texture, then a create a sprite
	sf::Texture texture;
	String str = RESOURCE_DIRECTORY_PATH_NAME;
	str = str + "/RPG_name.png";
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

	std::cout << "Main Screen should display" << std::endl;

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
		if (e_StartMode == EXIT)
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
	bool inputing = true;
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
	inputText.setStyle(sf::Text::Bold);

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
	instructions.setString("Arrow Keys to navigate, [Enter] to select highlighted");
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
							Input = "";
							while (inputing)
							{
								if (window.waitEvent(event) && !input_wait);
								{
									input_wait = true;
									TempInput = "";
									if (event.type == sf::Event::TextEntered && !(event.key.code == sf::Keyboard::BackSpace) && !(event.key.code == sf::Keyboard::Enter))
									{
										if (event.text.unicode < 128 && event.text.unicode > 31)
										{
											TempInput = static_cast<char>(event.text.unicode);
										}
									}
									Input = Input + TempInput;

									if (event.type == sf::Event::KeyPressed)
									{
										if (event.key.code == sf::Keyboard::Enter)
										{
											inputing = false;
										}
									}
								}

								if (!(sf::Keyboard::isKeyPressed) && input_wait)
								{
										input_wait = false;
								}
							}
							cout << Input.GetStr() << endl;
							inputText.setString(Input.GetStr());
							selection = 0;
							break;
						case 1: //Create Character
							//for now, test if the character could be made
							if (onCreateCharacter(Input))
							{
								cout << "character created successfully" << endl;
								GameSave();
								windowControl = false;
								e_StartMode = MAIN;
							}
							else
							{
								cout << "character creation failed" << endl;
								character.SetName("NA");
								failure = true;
							}
							break;
						case 2: //Return
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


		window.clear();
		window.draw(margin_border);
		window.draw(instructions);
		window.draw(inputText);
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

		if (failure)
		{
			textArray[selection].setFillColor(sf::Color::Red);
			textArray[selection].setOutlineColor(sf::Color::Red);
		}

		window.display();
	}
}

void GameManager::s_menuRender()
{
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

/*///////////////////////////////////////////////////////////////////////////////////
	onCreateCharacter checks if there is space for the character to inhabit without
	over-writing
	returns false if it could not do anything
*///////////////////////////////////////////////////////////////////////////////////
bool GameManager::onCreateCharacter(const String & name)
{
	String Health = "Health: ";
	String Remaining = "Remaining Enemies: ";
	String RemainingAmount = String::ToString(m_Gstate.m_enemiesRemaining);

	bool flag = false;
	character.SetName(name);
	for (int i = 0; i < MAX_CHARACTER_AMOUNT && !flag; i++)
	{
		for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1 && !flag; j++)
		{
			if (Character_Info[0][i] == "NA")
			{
				flag = true;
				Character_Info[0][i] = character.GetName();
				Character_Info[1][i] = Health + character.GetHealth() + Remaining + RemainingAmount;
			}
		}
	}
	return flag;
}

void GameManager::SaveFile(FileType type)
{
	String slash = "/";
	String extension = ".bin";
	String GSave = "_gsave";
	String List = "_list";
	String dir = SAVES_DIRECTORY_PATH_NAME;
	String name = this->character.GetName();
	if (character.GetName() != "NA")
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
			m_pathName = GSAVES_DIRECTORY_PATH_NAME;
			m_pathName = m_pathName + slash + name + List + extension;
			this->m_FileOut.open(m_pathName.GetStr(), ios::out | ios::binary | ios::trunc | ios::ate);
			if (m_FileOut.is_open())
			{
				for (int i = 0; i < MAX_CHARACTER_AMOUNT; i++)
				{
					for (int j = 0; j < MAX_CHARACTER_AMOUNT - 1; j++)
					{
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
	return false;
}



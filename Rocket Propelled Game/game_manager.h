#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "dynamic_array.h"
#include "string.h"
#include "SFML/Graphics.hpp"
#include "character.h"

using std::cin;
using std::cout;
using std::endl;

using std::ofstream;
using std::ifstream;
using std::ios;
using std::fstream;

/*////////////////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 11/25/18
	FileName: game_manager.h
	Class: GameManager

	Purpose:
		GameManager does as the name implies, it manages the game,
		Its job is to be the interface between the user and the game logic
		this includes game logic, and updating the UI to represent changes

	Methods:
		GameStart is always called first, but then to resume games.
		GamePause is used when the user wants to pause the game,
			This will also allow for saving (when not in battle)
		GameSave is used when a save needs to occur, typically before a battle, or exit
		GameExit will save the current character, and gamestate.
*/////////////////////////////////////////////////////////////////////////////////////////
class GameManager
{
public:
	GameManager();
	~GameManager();

	void GameStart();

	static const int MAX_CHARACTER_AMOUNT = 3;
	static const int RESOURCE_FILE_DIRECTORY_ERR = -1;

	static const char * SAVES_DIRECTORY_PATH_NAME;
	static const char * GSAVES_DIRECTORY_PATH_NAME;
	static const char * RESOURCE_DIRECTORY_PATH_NAME;
	static const char * GAME_NAME;

	enum MenuMode
	{
		MAIN, WORLD, FIGHT, SHOP, EXIT
	};

	enum FileType
	{
		CHAR, CHAR_GAME, CHARLIST
	};

private:
	bool isRunningSave;

	void m_menuRender();
	void n_menuRender();
	void s_menuRender();
	void p_menuRender();
	void shopRender();
	void worldRender();

	bool onCreateCharacter(const String & name);
	void SaveFile(FileType type);
	bool LoadFile(FileType type);
	bool FileExists(const String & pathname);

	void GamePause();
	void GameSave();
	void GameLoad();

	struct GameState
	{
		int m_enemiesRemaining;
		int m_enemiesKilled;
		int m_currentEnemy;
		bool inFight;
	};

	GameState m_Gstate;

	//multidimensional array, [0][i] is for name, [1][i] is for character stats for display
	String Character_Info[MAX_CHARACTER_AMOUNT - 1][MAX_CHARACTER_AMOUNT];

	MenuMode e_StartMode;
	Character character;
	sf::RenderWindow window;
	sf::View display;
	sf::View action_bar;
	String m_pathName;
	ifstream m_FileIn;
	ofstream m_FileOut;
};
#endif // !GAME_MANAGER_H

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <iostream>
#include <random>
#include <chrono>
#include <experimental/filesystem>
#include <fstream>
#include "dynamic_array.h"
#include "string.h"
#include "SFML/Graphics.hpp"
#include "character.h"

#include "boss.h"
#include "eagle.h"
#include "goat.h"
#include "goblin.h"
#include "griffin.h"
#include "grub.h"
#include "lion.h"
#include "serphent.h"
#include "troll.h"
#include "linked_list.h"

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

	static const int NUM_ENEMY_TYPES = 9;
	static const int MAX_CHARACTER_AMOUNT = 3;
	static const int RESOURCE_FILE_DIRECTORY_ERR = -1;

	static const String EnemyResourceArray[NUM_ENEMY_TYPES];
	static const String SAVES_DIRECTORY_PATH_NAME;
	static const String GSAVES_DIRECTORY_PATH_NAME;
	static const String RESOURCE_DIRECTORY_PATH_NAME;
	static const String GAME_NAME;

	enum MenuMode
	{
		MAIN, WORLD, FIGHT, SHOP, EXIT
	};

	enum FileType
	{
		CHAR, CHAR_GAME, CHARLIST
	};

private:
	int dice_roll;
	std::default_random_engine gen;
	static std::uniform_int_distribution<int> health_distribution;
	static std::uniform_int_distribution<int> strength_distribution;
	static std::uniform_int_distribution<int> arm_distribution;
	static std::uniform_int_distribution<int> mana_distribution;
	static std::uniform_int_distribution<int> dmg_distribution;



	bool isStartup;
	bool fileChange;

	void m_menuRender();
	void n_menuRender();
	void s_menuRender();
	void p_menuRender();
	void shopRender();
	void worldRender();
	void loadLinkedList();

	void fightRender();

	bool onCreateCharacter(const String & name);
	void SaveFile(FileType type);
	bool LoadFile(FileType type);
	bool DeleteFile(String name);
	bool FileExists(const String & pathname);

	void GamePause();
	void GameSave();
	void GameLoad();

	struct GameState
	{
		int m_enemiesRemaining;
		int m_enemiesKilled;
		int m_currentEnemy;
		int generated_health;
	};

	GameState m_Gstate;

	//multidimensional array, [0][i] is for name, [1][i] is for character stats for display
	String Character_Info[MAX_CHARACTER_AMOUNT - 1][MAX_CHARACTER_AMOUNT];

	LinkedList<Enemy> enemyList;
	MenuMode e_StartMode;
	Character character;
	sf::RenderWindow window;
	String m_pathName;
	ifstream m_FileIn;
	ofstream m_FileOut;
};
#endif // !GAME_MANAGER_H

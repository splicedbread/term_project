#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "character.h"
#include "string.h"
#include "coin_pouch.h"
#include "game_manager.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <crtdbg.h>
using std::cin;
using std::cout;
using std::endl;
/*
	Project Name: Final_Term_Project (Rocket Propelled Game)
	Author: Jacob Vanderkarr
	Date: 11/25/18

	Purpose: RPG game with less actual RPG elements than a modern Bethesda Title
		Allows for the creation of a character, with random stats within a set range.
		Allows for up to 3 characters to exist in the files
		Allows for management of said characters via a graphics interface.
		Allows for an Arena style fighting that takes the generated character through 10 fights, ending in a boss
*/


void gameStub();
//Global scope variable, NEVER CHANGE UNLESS REDISGNING UI
const int MAX_NUM_CHARACTERS = 3;

/*///////////////////////////////////////////////////////////////////////////////////////
	Entrance Point to the application. Removes the console and then continues to gameStub
*///////////////////////////////////////////////////////////////////////////////////////
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "launching openGL application...." << endl;
	//Remove the console window
	FreeConsole(); //Comment out when needing the console for debugging
	gameStub();
	return 0;
}

void gameStub()
{
		GameManager game;
		try
		{
			game.GameStart();
		}
		catch (int error)
		{
			if (error == -1)
			{
				cout << "There was a problem with loading the resource" << endl;
				cin.ignore();
			}
		}
}

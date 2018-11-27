#include <iostream>
#include <fstream>
#include "character.h"
#include "string.h"
#include "coin_pouch.h"
#include "game_manager.h"
#include <SFML/Graphics.hpp>
#include <crtdbg.h>
using std::cin;
using std::cout;
using std::endl;

using std::ofstream;
using std::ifstream;
using std::ios;
using std::fstream;

void gameStub();
void TestStub();
void Stub();

const int MAX_NUM_CHARACTERS = 4;
const char * FILENAME = "character.bin";

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "launching openGL application...." << endl;
	//TestStub();
	//Stub();
	gameStub();
	//cin.ignore();
	return 0;
}

void gameStub()
{
		GameManager game;
		try
		{
			game.GameStart();
		}
		catch (String error)
		{
			if (error == "RESOURCE ERROR")
			{
				cout << "There was a problem with loading the resource" << endl;
				cin.ignore();
			}
		}
}

void Stub() 
{

}

void TestStub()
{
	
};
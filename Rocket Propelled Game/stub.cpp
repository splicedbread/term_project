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

void Stub2();
void TestStub();
void Stub();

const int MAX_NUM_CHARACTERS = 4;
const char * FILENAME = "character.bin";

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << "launching openGL application...." << endl;
	TestStub();
	//Stub();
	//Stub2();
	//cin.ignore();
	return 0;
}

void Stub2()
{
	GameManager game;
}

void Stub() 
{

	Potion pt1("Bone Hurting Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Mediocre", "10.25.88.109");

	Potion pt2("Bone Healing Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Supreme", "19.40.201.00");

	Potion pt3("Ains Oal Gown", "I couldn't even think of that!", "Demon Goat", "98.00.00.01");
	
	Potion pt4("Ivinsibility", "Whats the point if I cannot see my own face!", "Stronk", "00.05.92.01");

	Item itm1("Brown Stick", "There seems to be nothing interesting about this.", "00.00.00.05");

	String names[MAX_NUM_CHARACTERS] {("Phill"), ("Bob"), ("Tony"), ("Beck")};
	//seems redundant, but w/e, until "" is recognized for my custom string class, then this is how it will be
	Character * players[MAX_NUM_CHARACTERS] = {new Character(names[0]) , new Character(names[1]) , new Character(names[2]) , new Character(names[3])};

	cout << "Setting up characters as specified in Lab4 instructions. 1 broke character, 1 with an empty backpack," <<
		"\nand 2 characters with both potions and money" << endl << endl;

	//1 broke character, but some items
	players[0]->PickupObj(itm1);
	//1 with no items but give him like 5 coins though lmao, he probably sold the stick
	players[1]->AddMoney(5);

	//2 characters with both items and money
	players[2]->AddMoney(1250);
	players[2]->PickupObj(pt1);
	players[2]->PickupObj(pt2);
	players[2]->PickupObj(itm1);

	players[3]->AddMoney(400001);
	players[3]->PickupObj(pt4);
	players[3]->PickupObj(pt2);
	players[3]->PickupObj(pt3);

	cout << "Displaying all of the characters before writing them to a binary file" << endl << endl;

	for (int i = 0; i < MAX_NUM_CHARACTERS; i++)
	{
		cout << i + 1 << ". ";
		players[i]->Info(1);
	}

	cout << "Beginning to write characters to file" << endl;

	fstream file(FILENAME, ios::out | ios::binary | ios::ate | ios::trunc);

	if (file.is_open())
	{
		for (int i = 0; i < MAX_NUM_CHARACTERS; i++)
		{
			int length = 0;
			int elements = 0;
			char * buffer = nullptr;
			/*
				Character Write Order: Name Size, Name, Health, Armour, Mana, Strength, m_inventory (Potions), m_inventory (Items) , m_wallet
			*/
			//name
			length = players[i]->GetName().GetLen();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			buffer = new char[length + 1];
			strcpy(buffer, players[i]->GetName().GetStr());
			buffer[length] = '\0';
			file << buffer;
			delete[] buffer;
			buffer = nullptr;
			//health
			length = players[i]->GetHealth();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			//armour
			length = players[i]->GetArmour();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			//mana
			length = players[i]->GetMana();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			//strength
			length = players[i]->GetStrength();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			
			//wallet
			length = String::ToString(players[i]->GetWallet().GetMoney()).GetLen();
			file.write(reinterpret_cast<char *>(&length), sizeof(int));
			buffer = new char[length + 1];
			strcpy(buffer, String::ToString(players[i]->GetWallet().GetMoney()).GetStr());
			buffer[length] = '\0';
			file << buffer;
			delete[] buffer;
			buffer = nullptr;

			//Potions
			/*
				Potion info Write Order: PotionArraySize ,Name, Potency, Description, Cost, CostSize
			*/
			//Potion Array Elements
			elements = players[i]->GetInv().GetPotions().GetElements();
			file.write(reinterpret_cast<char *>(&elements), sizeof(int));

			for (int j = 0; j < elements; j++)
			{
				//Name
				length = players[i]->GetInv().GetPotions()[j].GetName().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetPotions()[j].GetName().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
				//Potency
				length = players[i]->GetInv().GetPotions()[j].GetPoten().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetPotions()[j].GetPoten().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
				//Description
				length = players[i]->GetInv().GetPotions()[j].GetDesc().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetPotions()[j].GetDesc().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
				//CostSize
				length = players[i]->GetInv().GetPotions()[j].GetCostSize().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetPotions()[j].GetCostSize().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
			}

			//Items
			/*
				Item info Write Order: ItemArraySize ,Name, Description, Cost, CostSize
			*/
			//Item Array Elements
			elements = players[i]->GetInv().GetItems().GetElements();
			file.write(reinterpret_cast<char *>(&elements), sizeof(int));

			for (int j = 0; j < elements; j++)
			{
				//Name
				length = players[i]->GetInv().GetItems()[j].GetName().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetItems()[j].GetName().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
				//Description
				length = players[i]->GetInv().GetItems()[j].GetDesc().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetItems()[j].GetDesc().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
				//CostSize
				length = players[i]->GetInv().GetItems()[j].GetCostSize().GetLen();
				file.write(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				strcpy(buffer, players[i]->GetInv().GetItems()[j].GetCostSize().GetStr());
				buffer[length] = '\0';
				file << buffer;
				delete[] buffer;
				buffer = nullptr;
			}

			cout << "character " << i + 1 << ". written to file" << endl;
		}

		file.close();
		cout << "File written to and closed" << endl;
	}
	else
	{
		cout << "Could not open file" << endl;
	}

	delete players[0];
	delete players[1];
	delete players[2];
	delete players[3];

	players[0] = nullptr;
	players[1] = nullptr;
	players[2] = nullptr;
	players[3] = nullptr;

	players[0] = new Character();
	players[1] = new Character();
	players[2] = new Character();
	players[3] = new Character();

	

	//reopen the file then read it into the array
	cout << "Re-opening the file to read into the array" << endl;

	file.open(FILENAME, ios::in | ios::binary);

	if (file.is_open())
	{
		int length = 0;
		int Elements = 0;
		char * buffer = nullptr;
		for (int i = 0; i < MAX_NUM_CHARACTERS; i++)
		{
			/*
				Character Read Order: Name Size, Name, Health, Armour, Mana, Strength, m_inventory (Potions), m_inventory (Items) , m_wallet
			*/
			//name
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			buffer = new char[length + 1];
			file.read(buffer, length);
			buffer[length] = '\0';
			players[i]->SetName(buffer);
			delete[] buffer;
			buffer = nullptr;
			//health
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			players[i]->SetHealth(length);
			//armour
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			players[i]->SetArmour(length);
			//mana
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			players[i]->SetMana(length);
			//strength
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			players[i]->SetStrength(length);

			//wallet
			file.read(reinterpret_cast<char *>(&length), sizeof(int));
			buffer = new char[length + 1];
			file.read(buffer, length);
			buffer[length] = '\0';
			players[i]->AddMoney(String::ToInt(buffer));
			delete[] buffer;
			buffer = nullptr;

			//Potions
			/*
				Potion info Write Order: PotionArraySize ,Name, Potency, Description, Cost, CostSize
			*/
			//Potion Array Elements
			file.read(reinterpret_cast<char *>(&Elements), sizeof(int));
			

			for (int j = 0; j < Elements; j++)
			{
				Potion tempPt;

				//Name
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempPt.SetName(buffer);
				delete[] buffer;
				buffer = nullptr;
				//Potency
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempPt.SetPoten(buffer);
				delete[] buffer;
				buffer = nullptr;
				//Description
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempPt.SetDesc(buffer);
				delete[] buffer;
				buffer = nullptr;
				//Cost
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempPt.SetCostSize(String::ToInt(buffer));
				delete[] buffer;
				buffer = nullptr;
				//CostSize (not size of cost string)
				//file.read(reinterpret_cast<char *>(&length), sizeof(int));
				//buffer = new char[length + 1];
				//file.read(buffer, length + 1);
				//tempPt.SetCost(buffer);
				//delete[] buffer;
				//buffer = nullptr;

				//add the potion to the dynamic array
				players[i]->PickupObj(tempPt);
			}


			/*
				Item info Write Order: ItemArraySize ,Name, Description, Cost, CostSize
			*/
			//Potion Array Elements
			file.read(reinterpret_cast<char *>(&Elements), sizeof(int));

			//Items
			for (int j = 0; j < Elements; j++)
			{
				Item tempItm;

				//Name
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempItm.SetName(buffer);
				delete[] buffer;
				buffer = nullptr;
				//Description
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempItm.SetDesc(buffer);
				delete[] buffer;
				buffer = nullptr;
				//Cost
				file.read(reinterpret_cast<char *>(&length), sizeof(int));
				buffer = new char[length + 1];
				file.read(buffer, length);
				buffer[length] = '\0';
				tempItm.SetCostSize(String::ToInt(buffer));
				delete[] buffer;
				buffer = nullptr;
				//CostSize (not size of cost string)
				//file.read(reinterpret_cast<char *>(&length), sizeof(int));
				//buffer = new char[length + 1];
				//file.read(buffer, length + 1);
				//tempPt.SetCost(buffer);
				//delete[] buffer;
				//buffer = nullptr;

				//add the potion to the dynamic array
				players[i]->PickupObj(tempItm);
			}

			cout << "character " << i + 1 << ". read from file" << endl;
		}

		file.close();
		cout << "File read from and closed" << endl;
	}
	else
	{
		cout << "Could not open file" << endl;
	}

	cout << "Displaying all of the characters after reading them from a binary file" << endl << endl;

	for (int i = 0; i < MAX_NUM_CHARACTERS; i++)
	{
		cout << i + 1 << ". ";
		players[i]->Info(1);
	}


	delete players[0];
	delete players[1];
	delete players[2];
	delete players[3];

	players[0] = nullptr;
	players[1] = nullptr;
	players[2] = nullptr;
	players[3] = nullptr;

}

void TestStub()
{
	float margin = 50;
	const float SPEED = 2.0f;
	sf::View view;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "TestStub GL", sf::Style::Titlebar | sf::Style::Close);
	sf::CircleShape shape(25.f);
	//adding a black border around the game
	view.setViewport(sf::FloatRect((margin/2.0)/window.getSize().x,
								(margin/2.0)/window.getSize().y,
								(window.getSize().x - margin) / window.getSize().x, 
								(window.getSize().y - margin) / window.getSize().y));
	window.setView(view);

	shape.setFillColor(sf::Color::Cyan);
	shape.setOutlineColor(sf::Color::Blue);
	shape.setOutlineThickness(3.f);

	shape.setOrigin(-1*(window.getSize().x/2.0f) + shape.getRadius(), -1*(window.getSize().y/2.0f) + shape.getRadius());
	window.setPosition(sf::Vector2i(10, 50));
	window.setVerticalSyncEnabled(true);

	sf::Time accel_time = sf::milliseconds(200);
	sf::Time drag_time = sf::seconds(1.5f);
	sf::Event event;
	sf::Clock a_clock;
	sf::Clock d_clock;
	bool activeElm = false;
	bool x_drag = false;
	bool y_drag = false;
	float x_motion = 0.0f;
	float y_motion = 0.0f;
	float m_dragcoefficient = 0.08f;
	float multiplier = 0.0f;

	while (window.isOpen())
	{
		if (window.hasFocus())
		{
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				if (event.type == sf::Event::KeyReleased && !activeElm)
				{
					multiplier = 0.0f;
					x_drag = true;
					y_drag = true;
					d_clock.restart();
				}

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				x_motion = SPEED;
				activeElm = true;

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					y_drag = true;
				}

				x_drag = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				x_motion = -SPEED;
				activeElm = true;

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					y_drag = true;
				}

				x_drag = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				y_motion = SPEED;
				activeElm = true;

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					x_drag = true;
				}

				y_drag = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				y_motion = -SPEED;
				activeElm = true;

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					x_drag = true;
				}

				y_drag = false;
			}

			if (!activeElm)
			{
				a_clock.restart();
			}

			if (activeElm && a_clock.getElapsedTime() >= accel_time && multiplier <= 2.0f)
			{
				multiplier += 0.1f;
			}

		}
		else
		{
			x_drag = true;
			y_drag = true;
			multiplier = 0.0f;
			d_clock.restart();
		}


		if (x_drag && !y_drag)
		{
			if (x_motion > 0.0f)
			{
				x_motion = x_motion - (x_motion * m_dragcoefficient);
			}
			else
			{
				x_motion = x_motion - (x_motion * m_dragcoefficient);
			}
		}
		else
		{
			if (y_motion > 0.0f)
			{
				y_motion = y_motion - (y_motion * m_dragcoefficient);
			}
			else
			{
				y_motion = y_motion - (y_motion * m_dragcoefficient);
			}
		}

		if (x_drag && y_drag)
		{
			if (d_clock.getElapsedTime() >= drag_time)
			{
				x_motion = 0.0f;
				y_motion = 0.0f;
				x_drag = false;
				y_drag = false;
			}

			if (x_motion > 0.0f)
			{
				x_motion = x_motion - (x_motion * m_dragcoefficient);
			}
			else
			{
				x_motion = x_motion - (x_motion * m_dragcoefficient);
			}

			if (y_motion > 0.0f)
			{
				y_motion = y_motion - (y_motion * m_dragcoefficient);
			}
			else
			{
				y_motion = y_motion - (y_motion * m_dragcoefficient);
			}


		}
		
		shape.move(x_motion + x_motion*multiplier, y_motion + y_motion*multiplier);
		window.clear();
		window.draw(shape);
		window.display();
		activeElm = false;
	}
};
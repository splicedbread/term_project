#include <iostream>
#include "potion.h"
#include "string.h"
#include "dynamic_array.h"
#include <crtdbg.h>
using std::cin;
using std::cout;
using std::endl;

void PotionStub();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	PotionStub();
	cin.ignore();
	return 0;
}


void PotionStub() 
{
	cout << "///////////////Testing Dynamic Array class Insert///////////////" << endl;


	cout << "///////////////Displaying Potions below///////////////" << endl;

	//Create a dynamic array obj

	DynamicArray PotionBelt;
	
	//create 3 potions

	Potion pt1("Bone Hurting Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Super tier", "10.25.88.109");

	Potion pt2("Bone Healing Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Super tier", "19.40.201.00");

	Potion pt3("Ains", "I couldn't even think of that!", "Goat tier", "98.00.00.01");

	PotionBelt.Insert(pt1);
	PotionBelt.Insert(pt2);
	PotionBelt.Insert(pt3);
	//Insert two duplicates, these will be deleted to show we only delete one of them
	PotionBelt.Insert(pt2);
	PotionBelt.Insert(pt1);

	cout << "Number of elements: " << PotionBelt.GetElements() << endl;

	for (int i = 0; i < PotionBelt.GetElements(); i++)
	{
		PotionBelt[i].Display();
		cout << endl;
	}


	cout << "///////////////Testing Dynamic Array class copy///////////////" << endl;

	DynamicArray PotionBelt2;

	PotionBelt2 = PotionBelt;

	cout << "Number of elements PB1: " << PotionBelt.GetElements() << endl;
	cout << "Number of elements PB2: " << PotionBelt2.GetElements() << endl;

	cout << "///////////////Displaying Belt copy///////////////" << endl;

	for (int i = 0; i < PotionBelt2.GetElements(); i++)
	{
		PotionBelt2[i].Display();
		cout << endl;
	}


	cout << "///////////////Testing Dynamic Array class Delete///////////////" << endl;
	cout << "///////////////Removing duplicate potions///////////////" << endl;

	PotionBelt2.Delete(pt2);
	PotionBelt2.Delete(pt1);

	cout << "///////////////Displaying Potions below///////////////" << endl;

	for (int i = 0; i < PotionBelt2.GetElements(); i++)
	{
		PotionBelt2[i].Display();
		cout << endl;
	}

}


#include <iostream>
#include "potion.h"
#include "backpack.h"
#include <crtdbg.h>
using std::cin;
using std::cout;
using std::endl;

void Stub();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Stub();
	cin.ignore();
	return 0;
}


void Stub() 
{

	Potion pt1("Bone Hurting Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Mediocre", "10.25.88.109");

	Potion pt2("Bone Healing Juice", "Oooo Ohhh, OWCH, this really hurts my bones!", "Supreme", "19.40.201.00");

	Potion pt3("Ains Oal Gown", "I couldn't even think of that!", "Demon Goat", "98.00.00.01");
	
	Potion pt4("Ains Oal Gown", "I couldn't even think of that!", "Demon Goat", "98.00.00.01");

	Potion pt5(pt3);

	BackPack bk1(10);

	if (pt3 == pt4)
	{
		cout << "pt3 = pt4" << endl;
	}

	if (pt5 == pt3)
	{
		cout << "pt5 = pt3" << endl;
	}

	if (&pt5 == &pt3)
	{
		cout << "pt5 address matches pt3" << endl;
	}

	bk1.Add(pt1);
	bk1.Add(pt2);
	bk1.Add(pt3);
	bk1.Add(pt1);
	bk1.Add(pt1);
	bk1.Add(pt1);
	bk1.Add(pt2);
	bk1.Add(pt3);
	bk1.Add(pt2);
	bk1.Add(pt3);

	bk1.Display();

	bk1.Remove(pt1);
	bk1.Remove(pt4);
	bk1.Remove(pt5);

	bk1.UpgradeBP();
	bk1.Display();

}


#ifndef EAGLE_H
#define EAGLE_H
#include "enemy.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: eagle.h
	Date: 11/28/18

	Class: enemy
	Purpose: A class that will be used to interact with the game

	Manager Functions:
		enemy();
		enemy(String name);
		enemy(const enemy & copy);
		~enemy();

	Methods:
		craftWeapon()
*/////////////////////////////////////////////////////////////////////////////
class Eagle : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Eagle();
	Eagle(String name);
	Eagle(const Eagle & copy);
	~Eagle();
	void craftWeapon();
};
#endif // !EAGLE_H

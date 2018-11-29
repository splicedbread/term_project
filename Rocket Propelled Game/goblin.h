#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemy.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.h
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
class Goblin : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Goblin();
	Goblin(String name);
	Goblin(const Goblin & copy);
	~Goblin();
	void craftWeapon();
	friend std::ostream & operator << (std::ostream & os, const Goblin & enemy);
};
#endif // !GRUB_H

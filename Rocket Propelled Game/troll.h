#ifndef TROLL_H
#define TROLL_H
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
class Troll : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Troll();
	Troll(String name);
	Troll(const Troll & copy);
	~Troll();
	void craftWeapon();
	friend std::ostream & operator << (std::ostream & os, const Troll & enemy);
};
#endif // !GRUB_H

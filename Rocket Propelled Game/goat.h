#ifndef GOAT_H
#define GOAT_H
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
class Goat : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Goat();
	Goat(String name);
	Goat(const Goat & copy);
	~Goat();
	void craftWeapon();
	friend std::ostream & operator << (std::ostream & os, const Goat & enemy);
};
#endif // !GRUB_H

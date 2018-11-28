#ifndef GRUB_H
#define GRUB_H
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
class Grub : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Grub();
	Grub(String name);
	Grub(const Grub & copy);
	~Grub();
	void craftWeapon();
};
#endif // !GRUB_H

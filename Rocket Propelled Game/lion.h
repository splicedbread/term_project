#ifndef LION_H
#define LION_H
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
class Lion : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Lion();
	Lion(String name);
	Lion(const Lion & copy);
	~Lion();
	void craftWeapon();
	friend std::ostream & operator << (std::ostream & os, const Lion & enemy);
};
#endif // !GRUB_H

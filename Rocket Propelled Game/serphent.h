#ifndef SERPHENT_H
#define SERPHENT_H
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
class Serphent : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Serphent();
	Serphent(String name);
	Serphent(const Serphent & copy);
	~Serphent();
	void craftWeapon();
	friend std::ostream & operator << (std::ostream & os, const Serphent & enemy);
};
#endif // !GRUB_H

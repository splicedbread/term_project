#ifndef BOSS_H
#define BOSS_H
#include "enemy.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: boss.h
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
class Boss : public Enemy
{
private:
	static const String WepName;
	static const String WepDesc;
	static const int WepDmg;
public:
	Boss();
	Boss(String name);
	Boss(const Boss & copy);
	~Boss();
	void craftWeapon();
};
#endif // !BOSS_H

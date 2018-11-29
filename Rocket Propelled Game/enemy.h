#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include "entity.h"
#include "backpack.h"
/*///////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: Enemy.h
	Date: 11/28/18

	Class: enemy
	Purpose: A class that will be used to interact with the game

	Manager Functions:
		enemy();
		enemy(String name);
		enemy(const enemy & copy);
		~enemy();

	Methods:
		enemyAttack();
*/////////////////////////////////////////////////////////////////////////////
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(String name);
	Enemy(const Enemy & copy);
	~Enemy();

	enum Moves
	{
		NORMAL, SPECIAL, RAGE, BLOCK, NOTHING
	};

	int enemyMoves(Moves type);
	Enemy & operator = (const Enemy & right);
	friend std::ostream& operator << (std::ostream& os, const Enemy& enemy);

	virtual void craftWeapon() = 0;

protected:

};
#endif // !Enemy_H

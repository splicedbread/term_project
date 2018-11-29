#include "enemy.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: enemy.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

//default ctor
Enemy::Enemy() : Entity()
{}

//one arg ctor
Enemy::Enemy(String name) : Entity(name)
{}

//copy ctor
Enemy::Enemy(const Enemy & copy) : Entity(copy)
{}

//dtor
Enemy::~Enemy()
{}

/*////////////////////////////////////
	allows for changing up the attack
	> 0, is attack
	< 0, is block
	= 0, is nothing
*/////////////////////////////////////
int Enemy::enemyMoves(Moves type)
{
	int dmg = 0;
	//If a postive number, then attack, if a negative then block
	switch (type)
	{
	case Enemy::NORMAL:
		dmg = this->m_strength * String::ToInt(this->m_wep.GetDmg());
		break;
	case Enemy::SPECIAL:
		dmg = this->m_strength * String::ToInt(this->m_wep.GetDmg()) * 2;
		break;
	case Enemy::RAGE:
		dmg = String::ToInt(this->m_wep.GetDmg()) * 10;
		break;
	case Enemy::BLOCK:
		dmg = -1*this->m_armour - (String::ToInt(this->m_wep.GetDmg().GetStr()));
		break;
	case Enemy::NOTHING:
		dmg = -1*this->m_armour;
		break;
	default:
		dmg = 0;
		break;
	}
	return dmg;
}

//op = overload
Enemy & Enemy::operator=(const Enemy & right)
{
	if (this != &right)
	{
		this->m_wallet = right.m_wallet;
		this->m_name = right.m_name;
		this->m_health = right.m_health;
		this->m_armour = right.m_armour;
		this->m_mana = right.m_mana;
		this->m_strength = right.m_strength;
	}
	return *this;
}

/*///////////////////////////////////////////////////////////////////////
	stream operator overload, which is used just for displaying the name.
*////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Enemy & enemy)
{
	os << enemy.GetName().GetStr();
	return os;
}

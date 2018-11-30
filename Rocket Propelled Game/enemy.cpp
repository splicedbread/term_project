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

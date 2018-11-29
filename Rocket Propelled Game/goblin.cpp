#include "goblin.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Goblin::WepName = "Dull Short Sword";
const String Goblin::WepDesc = "Picked up off a dead adventurer";
const int Goblin::WepDmg = 2;

//default ctor
Goblin::Goblin() : Enemy("Goblin")
{
	m_health = 70;
	m_armour = 4;
	m_strength = 3;
	craftWeapon();
}

//one arg ctor
Goblin::Goblin(String name) : Enemy(name)
{}

//copy ctor
Goblin::Goblin(const Goblin & copy) : Enemy(copy)
{}

//dtor
Goblin::~Goblin()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Goblin::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

/*///////////////////////////////////////////////////////////////////////
	stream operator overload, which is used just for displaying the name.
*////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Goblin & enemy)
{
	os << enemy.GetName().GetStr();
	return os;
}
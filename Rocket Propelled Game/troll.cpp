#include "troll.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Troll::WepName = "Stone Club";
const String Troll::WepDesc = "Probably just a rock";
const int Troll::WepDmg = 5;

//default ctor
Troll::Troll() : Enemy("Troll")
{
	m_health = 100;
	m_strength = 3;
}

//one arg ctor
Troll::Troll(String name) : Enemy(name)
{}

//copy ctor
Troll::Troll(const Troll & copy) : Enemy(copy)
{}

//dtor
Troll::~Troll()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Troll::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

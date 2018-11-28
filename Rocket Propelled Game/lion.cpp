#include "lion.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Lion::WepName = "Beast Claw";
const String Lion::WepDesc = "Used for sport when not hungry";
const int Lion::WepDmg = 3;

//default ctor
Lion::Lion() : Enemy("Lion")
{
	m_health = 60;
	m_strength = 3;
}

//one arg ctor
Lion::Lion(String name) : Enemy(name)
{}

//copy ctor
Lion::Lion(const Lion & copy) : Enemy(copy)
{}

//dtor
Lion::~Lion()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Lion::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

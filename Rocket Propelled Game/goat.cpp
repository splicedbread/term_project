#include "goat.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Goat::WepName = "Horns";
const String Goat::WepDesc = "It's not a ram, but you are in for a jam";
const int Goat::WepDmg = 2;

//default ctor
Goat::Goat() : Enemy("Kidder")
{
	m_health = 40;
	m_strength = 3;
}

//one arg ctor
Goat::Goat(String name) : Enemy(name)
{}

//copy ctor
Goat::Goat(const Goat & copy) : Enemy(copy)
{}

//dtor
Goat::~Goat()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Goat::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

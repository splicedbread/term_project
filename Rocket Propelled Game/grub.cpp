#include "grub.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Grub::WepName = "Slime Tendrils";
const String Grub::WepDesc = "Pores from the body excrete this harmful substance";
const int Grub::WepDmg = 1;

//default ctor
Grub::Grub() : Enemy("Grub")
{
	m_health = 15;
	m_strength = 1;
	m_armour = 6;
	craftWeapon();
}

//one arg ctor
Grub::Grub(String name) : Enemy(name)
{}

//copy ctor
Grub::Grub(const Grub & copy) : Enemy(copy)
{}

//dtor
Grub::~Grub()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Grub::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

/*///////////////////////////////////////////////////////////////////////
	stream operator overload, which is used just for displaying the name.
*////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Grub & enemy)
{
	os << enemy.GetName().GetStr();
	return os;
}
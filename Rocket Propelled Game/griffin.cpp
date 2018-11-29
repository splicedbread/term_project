#include "griffin.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Griffin::WepName = "Feather Storm";
const String Griffin::WepDesc = "A great thrust of air followed by steel like feather projectiles";
const int Griffin::WepDmg = 4;

//default ctor
Griffin::Griffin() : Enemy("Griffin")
{
	m_health = 50;
	m_armour = 2;
	craftWeapon();
}

//one arg ctor
Griffin::Griffin(String name) : Enemy(name)
{}

//copy ctor
Griffin::Griffin(const Griffin & copy) : Enemy(copy)
{}

//dtor
Griffin::~Griffin()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Griffin::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

/*///////////////////////////////////////////////////////////////////////
	stream operator overload, which is used just for displaying the name.
*////////////////////////////////////////////////////////////////////////
std::ostream & operator<<(std::ostream & os, const Griffin & enemy)
{
	os << enemy.GetName().GetStr();
	return os;
}
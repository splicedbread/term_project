#include "serphent.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Serphent::WepName = "Fangs";
const String Serphent::WepDesc = "Needle Like protrusions that drip a tinted substance";
const int Serphent::WepDmg = 1;

//default ctor
Serphent::Serphent() : Enemy("Serphent")
{
	m_health = 35;
	m_armour = 2;
	m_strength = 8;
}

//one arg ctor
Serphent::Serphent(String name) : Enemy(name)
{}

//copy ctor
Serphent::Serphent(const Serphent & copy) : Enemy(copy)
{}

//dtor
Serphent::~Serphent()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Serphent::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

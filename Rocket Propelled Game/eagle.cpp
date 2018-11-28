#include "eagle.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: grub.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Eagle::WepName = "Sharp Talons";
const String Eagle::WepDesc = "Nature's razors";
const int Eagle::WepDmg = 3;

//default ctor
Eagle::Eagle() : Enemy("Eagle")
{
	m_health = 20;
	m_mana = 0;
	m_strength = 1;
}

//one arg ctor
Eagle::Eagle(String name) : Enemy(name)
{}

//copy ctor
Eagle::Eagle(const Eagle & copy) : Enemy(copy)
{}

//dtor
Eagle::~Eagle()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Eagle::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

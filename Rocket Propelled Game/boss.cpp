#include "boss.h"
#include <iostream>
/*///////////////////////////
	Author: Jacob Vanderkarr
	FileName: boss.cpp
	Date: 11/12/18

	Modifications:
*///////////////////////////

const String Boss::WepName = "Cronk's Steel Club";
const String Boss::WepDesc = "Made by Cronk's people, this wrought iron weapon is dangerous to get close to";
const int Boss::WepDmg = 3;

//default ctor
Boss::Boss() : Enemy("Cronk")
{
	m_strength = 5;
	m_health = 200;
	m_armour = 10;
	m_mana = 0;
}

//one arg ctor
Boss::Boss(String name) : Enemy(name)
{}

//copy ctor
Boss::Boss(const Boss & copy) : Enemy(copy)
{}

//dtor
Boss::~Boss()
{}
/*/////////////////////////////////////////////////////////////////////
	craftWeapon is a forced method from the abstract class enemy.
	it also acts as a polymorphism, where the same thing does something
	different between the different types of enemies
*/////////////////////////////////////////////////////////////////////
void Boss::craftWeapon()
{
	this->m_wep.SetName(WepName);
	this->m_wep.SetDesc(WepDesc);
	this->m_wep.SetDmg(WepDmg);
}

#include "weapon.h"
#include <iostream>
/***************************************************
*
	Author: Jacob Vanderkarr
	Filename: Weapon.cpp
	Date Created: 10/28/18
	Modifications:
				10/4/18 (17.56pm), flushed out Getters and Setters
					   , added a Display method
				10/5/18 (00.03am), documentation updated,
				10/9/18, documentation updated, string replaced by String
				10/18/18, added operator == overload
				11/07/18, added more conditional operator overloads
						, changed Display Cost, added a costSize for doing
						 simpler things for money calculation
						, added GetCostSize(), returns the cost size in
							copper pieces, which ignores formatting
							ie. cc or ccc or cccc ....
						, subsequent changes to operator =; and copy ctor
							to include new attribute

	Assignment: Lab1

	Overview: The Weapon class implementation file
		Meant To be used as a description for a
		Weapon obj.

	Input: arguments passed To the ctors

	Output: A Weapon instanced object
*
***************************************************/


Weapon::Weapon() : Item(), m_damage(String::ToString(STRD_DMG))
{
}

Weapon::Weapon(String name, String desc, String dmg, String cost) : Item(name, desc, cost), m_damage(dmg)
{
	//std::cout << "1st Massive overloaded ctor called..." << std::endl;
	SetCost(cost);
}

Weapon::Weapon(String name, String desc, String dmg) : Item(name, desc, ""), m_damage(dmg)
{
	//std::cout << "2nd Massive overloaded ctor called..." << std::endl;
};

Weapon::Weapon(String name, String desc) : Item(name, desc, ""), m_damage(String::ToString(STRD_DMG))
{
	//std::cout << "3rd Massive overloaded ctor called..." << std::endl;

};

Weapon::Weapon(String name) : Item(name, "", ""), m_damage(String::ToString(STRD_DMG))
{
	//std::cout << "overloaded ctor called..." << std::endl;

};

Weapon::Weapon(const Weapon & pt) : Item(pt.m_name, pt.m_description), m_damage(pt.m_damage)
{
	//std::cout << "copy ctor called..." << std::endl;
	SetCost(pt.m_cost);
}

Weapon::~Weapon()
{
}

/**********************************************************************
* Purpose: This function utilizes the overloaded assignment operator
*
* Precondition:
* right is already defined
*
*
* Postcondition:
* left (this) is returned, with copied data from right
*
************************************************************************/
Weapon & Weapon::operator = (const Weapon & right)
{
	if (this != &right)
	{
		this->m_name = right.m_name;
		this->m_description = right.m_description;
		this->m_damage = right.m_damage;
		this->m_cost = right.m_cost;
		this->m_costSize = right.m_costSize;
	}
	return *this;
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload checks the contents of the obj to test for
			object equality

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if both objects are evauluated the same
*//////////////////////////////////////////////////////////////////////////////
bool Weapon::operator== (const Weapon & right) const
{
	return ((m_name == right.m_name)
		&& (m_description == right.m_description)
		&& (m_damage == m_damage)
		&& (m_cost == right.m_cost));
}

/*///////////////////////////////////////////////////
	Purpose: This function sets the dmgency string
*////////////////////////////////////////////////////
void Weapon::SetDmg(int dmg)
{
	this->m_damage = String::ToString(dmg);
}

/*//////////////////////////////////////////////////////
	Purpose: This function returns the dmgency string
*///////////////////////////////////////////////////////
const String Weapon::GetDmg() const
{
	return this->m_damage;
}

/**********************************************************************
* Purpose: This function Displays everything in the Weapon obj
*
* Precondition: This Weapon object is initialized
*
* Postcondition: Displays all information from the Weapon obj To the console
*
* Modifications:
************************************************************************/
void Weapon::Display() const
{
	std::cout << "Weapon Name: [DMG:" << this->m_damage << "] [ " << this->m_name << "]" << std::endl;
	std::cout << "Weapon Description: [" << this->m_description << "]" << std::endl;
	DisplayCost();
}


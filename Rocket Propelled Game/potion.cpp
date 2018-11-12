#include "potion.h"
#include <iostream>
/***************************************************
*
	Author: Jacob Vanderkarr
	Filename: Potion.cpp
	Date Created: 10/2/18
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

	Overview: The Potion class implementation file
		Meant To be used as a description for a 
		Potion obj.

	Input: arguments passed To the ctors

	Output: A Potion instanced object
*
***************************************************/


Potion::Potion() : Item(), m_potency("")
{
}

Potion::Potion(String name, String desc, String pot, String cost) : Item(name, desc, cost) , m_potency(String::ToUp(pot,1))
{
	//std::cout << "1st Massive overloaded ctor called..." << std::endl;
	SetCost(cost);
}

Potion::Potion(String name, String desc, String pot) : Item(name, desc, ""), m_potency(String::ToUp(pot,1))
{
	//std::cout << "2nd Massive overloaded ctor called..." << std::endl;

};

Potion::Potion(String name, String desc) : Item(name, desc, ""), m_potency("")
{
	//std::cout << "3rd Massive overloaded ctor called..." << std::endl;

};

Potion::Potion(String name) : Item(name, "", ""), m_potency("")
{
	//std::cout << "overloaded ctor called..." << std::endl;

};

Potion::Potion(const Potion & pt) : Item(pt.m_name, pt.m_description), m_potency(pt.m_potency) 
{
	//std::cout << "copy ctor called..." << std::endl;
	SetCost(pt.m_cost);
}

Potion::~Potion()
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
Potion & Potion::operator = (const Potion & right)
{
	if (this != &right)
	{
		this->m_name = right.m_name;
		this->m_description = right.m_description;
		this->m_potency = right.m_potency;
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
bool Potion::operator== (const Potion & right) const
{
	bool flag = true;
	if (this->m_name != right.m_name)
	{
		flag = false;
	}
	if (this->m_description != right.m_description)
	{
		flag = false;
	}
	if (this->m_potency != right.m_potency)
	{
		flag = false;
	}
	if (this->m_cost != right.m_cost)
	{
		flag = false;
	}

	return flag;
}

/*///////////////////////////////////////////////////
	Purpose: This function sets the potency string
*////////////////////////////////////////////////////
void Potion::SetPoten(String pot)
{
	String::ToUp(pot);
	this->m_potency = pot;
}

/*//////////////////////////////////////////////////////
	Purpose: This function returns the potency string
*///////////////////////////////////////////////////////
const String Potion::GetPoten() const
{
	return this->m_potency;
}

/**********************************************************************
* Purpose: This function Displays everything in the Potion obj
*
* Precondition: This Potion object is initialized
*
* Postcondition: Displays all information from the Potion obj To the console
*
* Modifications:
************************************************************************/
void Potion::Display() const
{
	std::cout << "Potion Name: [" << this->m_potency << "] [" << this->m_name << "]" << std::endl;
	std::cout << "Potion Description: [" << this->m_description << "]" << std::endl;
	DisplayCost();
}


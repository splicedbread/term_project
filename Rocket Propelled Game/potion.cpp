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


Potion::Potion() : m_name(""), m_description(""), m_potency(""), m_cost("")
{
}

Potion::Potion(String name, String desc, String pot, String cost) : m_name(name), m_description(desc), m_potency(String::ToUp(pot,1)), m_cost(cost)
{
	//std::cout << "1st Massive overloaded ctor called..." << std::endl;
	SetCost(cost);
}

Potion::Potion(String name, String desc, String pot) : m_name(name), m_description(desc), m_potency(String::ToUp(pot,1)), m_cost("")
{
	//std::cout << "2nd Massive overloaded ctor called..." << std::endl;

};

Potion::Potion(String name, String desc) : m_name(name), m_description(desc), m_potency(""), m_cost("")
{
	//std::cout << "3rd Massive overloaded ctor called..." << std::endl;

};

Potion::Potion(String name) : m_name(name), m_description(""), m_potency(""), m_cost("")
{
	//std::cout << "overloaded ctor called..." << std::endl;

};

Potion::Potion(Potion & pt) : m_name(pt.m_name), m_description(pt.m_description), m_potency(pt.m_potency), m_cost(pt.m_cost), m_costSize(pt.m_costSize)
{
	//std::cout << "copy ctor called..." << std::endl;

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
	this->m_name = right.m_name;
	this->m_description = right.m_description;
	this->m_potency = right.m_potency;
	this->m_cost = right.m_cost;
	this->m_costSize = right.m_costSize;
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
	if (!(this->m_name == right.m_name))
	{
		flag = false;
	}
	if (!(this->m_description == right.m_description))
	{
		flag = false;
	}
	if (!(this->m_potency == right.m_potency))
	{
		flag = false;
	}
	if (!(this->m_cost == right.m_cost))
	{
		flag = false;
	}

	return flag;
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload checks the contents of the obj to test for
			object equality

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if both objects are evauluated not the same
*//////////////////////////////////////////////////////////////////////////////
bool Potion::operator != (const Potion & right) const
{
	return !(this == &right);
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of potions

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is greater than right
*//////////////////////////////////////////////////////////////////////////////
bool Potion::operator > (const Potion & right) const
{
	return (String::ToInt(this->m_cost) > String::ToInt(right.m_cost));
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of potions

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is greater than or equal to right
*//////////////////////////////////////////////////////////////////////////////
bool Potion::operator >= (const Potion & right) const
{
	return (String::ToInt(this->m_cost) >= String::ToInt(right.m_cost));
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of potions

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is less than right
*//////////////////////////////////////////////////////////////////////////////
bool Potion::operator < (const Potion & right) const
{
	return (String::ToInt(this->m_cost) < String::ToInt(right.m_cost));
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of potions

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is less than or equal to the right
*//////////////////////////////////////////////////////////////////////////////
bool Potion::operator <= (const Potion & right) const
{
	return (String::ToInt(this->m_cost) <= String::ToInt(right.m_cost));
}

/**********************************************************************
* Purpose: This function Gets the Potion name
*
* Precondition:
* this object is initialized
*
* Postcondition:
* Returns the name as a String constant
*
************************************************************************/
const String Potion::GetName() const
{
	return this->m_name;
}

/**********************************************************************
* Purpose: This function Gets the Potion description
*
* Precondition: This Potion object is initialized
* 
* Postcondition: Returns this Potions description
* 
*
************************************************************************/
const String Potion::GetDesc() const
{
	return this->m_description;
}

/**********************************************************************
* Purpose: This function Gets the Potion potency
*
* Precondition: This Potion object is initialized
*
* Postcondition: Returns this Potions potency
*
*
************************************************************************/
const String Potion::GetPoten() const
{
	return this->m_potency;
}

/**********************************************************************
* Purpose: This function Gets the Potion cost as a String
*
* Precondition: This Potion object is initialized
*
* Postcondition: Returns this Potions cost
*
*
************************************************************************/
const String Potion::GetCost() const
{
	return this->m_cost;
}

/**********************************************************************
* Purpose: This function Gets the Potion costSize as a String
*
* Precondition: This Potion object is initialized
*
* Postcondition: Returns this Potions costSize
*
*
************************************************************************/
const String Potion::GetCostSize() const
{
	return String::ToString(this->m_costSize);
}

/**********************************************************************
* Purpose: This function Sets the Potion name
*
* Precondition: This Potion object is initialized
*
* Postcondition: Sets this Potions name
*
* Modifications:
************************************************************************/
void Potion::SetName(String nm)
{
	m_name = nm;
}

/**********************************************************************
* Purpose: This function Sets the Potion description
*
* Precondition: This Potion object is initialized
*
* Postcondition: Sets this Potions description
*
* Modifications:
************************************************************************/
void Potion::SetDesc(String dsc)
{
	m_description = dsc;
}

/**********************************************************************
* Purpose: This function Sets the Potion potency
*
* Precondition: This Potion object is initialized and a String is passed
*
* Postcondition: Sets this Potions potency
*
* Modifications:
************************************************************************/
void Potion::SetPoten(String pot)
{
	//Come back To this later with predifined potencies
	m_potency = String::ToUp(pot, 1);
}

/**********************************************************************
* Purpose: This function Sets the Potion cost
*
* Precondition: This Potion object is initialized
*               and the format of cost is pp.gg.ss.cc (pp.gggg.sss.ccccc works),
*               where it takes integers inside the String 
*
* Postcondition: Sets this Potions cost and then verifies and formats
*
* Modifications:
************************************************************************/
void Potion::SetCost(String cst)
{
	if (ValidateCost(cst))
	{
		FormatCost(cst);
	}
	else
	{
		std::cout << "Cost contains non int symbols" << std::endl;
	}
}

/**********************************************************************
* Purpose: This function validates the cost of a Potion
*
* Precondition: This Potion object is initialized
*
* Postcondition: returns false if there is a non int character
				in the String submitted
				 returns true if there is no issue with the input
*
* Modifications:
************************************************************************/
bool Potion::ValidateCost(String& cst)
{
	//cost format is To be pp.gg.ss.cc
	//Using t for the prefix, as a test varibale that exists only in this scope
	bool badInput = false;
	int t_sectionLength = 0;
	int t_startE = 0;
	int t_endE = 0;
	int t_dots = 0;

	//sanitize the input
	for (int i = 0; i < cst.GetLen(); i++)
	{
		switch (cst[i])
		{
		case '0': badInput = false;
			break;
		case '1': badInput = false;
			break;
		case '2': badInput = false;
			break;
		case '3': badInput = false;
			break;
		case '4': badInput = false;
			break;
		case '5': badInput = false;
			break;
		case '6': badInput = false;
			break;
		case '7': badInput = false;
			break;
		case '8': badInput = false;
			break;
		case '9': badInput = false;
			break;
		case '.': t_endE = i;
			if ((t_endE - t_startE) >= 1)
			{
				badInput = false;
			}
			t_dots += 1;
			if (t_dots > 3)
			{
				std::cout << "dot" << std::endl;
				badInput = true;
			}
			break;
		case '\0': std::cout << "just let me know this happened..." << std::endl;
			break;
		default: badInput = true;
			break;
		}

		t_startE = t_endE + 1;
	}

	return !badInput;
}

/**********************************************************************
* Purpose: This function formats the validated cost
*
* Precondition: This Potion object is initialized, and ValidateCost has
			been run at least once (all handled by Set cost)
*
* Postcondition: The cost String has been formated To the preferred format
					(pp.gg.ss.cc)
*
* Modifications:
************************************************************************/
void Potion::FormatCost(String& cst)
{
	int startE = 0;
	int endE = 0;
	int elm = 0;
	int copper = 0;
	int silver = 0;
	int gold = 0;
	int platnium = 0;
	int section = 0;
	char * temp = nullptr;
	

	//formate is pp.gg.ss.cc
	//need To convert the String To a int so we can operate math
	//preferably without using stdlib.h
	/*
		Starts with platnium in section 0, then gold in section 1, then silver in sec 2, copper in sec 3
		
	*/
	while (section < 4)
	{
		for (int i = startE; (i < cst.GetLen() + 1); ++i)
		{
			if (cst[i] == '.' || cst[i] == '\0')
			{
				endE = i;
				//using a switch for whatever section we are on.
				switch (section)
				{
				case 0:
					//platnium
					elm = 0;
					try
					{
						temp = new char[(endE - startE) + 1];
					}
					catch (std::bad_alloc except)
					{
						std::cout << "Exception in Potion: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						//A little complicated
						//ex, if we have 123, then it will add 100 To plat, then 20, then 3
						//because chars are just numbers that refrence the ascii table,
						//if we subtract '0', then we will return an int that is our int we
						//want To use

						temp[elm] = cst[j];
						elm++;
					}
					temp[endE - startE] = '\0';
					platnium = String::ToInt(temp);
					delete[] temp;
					temp = nullptr;
					break;
				case 1:
					//gold
					elm = 0;
					try
					{
						temp = new char[(endE - startE) + 1];
					}
					catch (std::bad_alloc except)
					{
						std::cout << "Exception in Potion: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						temp[elm] = cst[j];
						elm++;

					}
					temp[endE - startE] = '\0';
					gold = String::ToInt(temp);
					delete[] temp;
					temp = nullptr;
					break;
				case 2:
					//silver
					elm = 0;
					try
					{
						temp = new char[(endE - startE) + 1];
					}
					catch (std::bad_alloc except)
					{
						std::cout << "Exception in Potion: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						temp[elm] = cst[j];
						elm++;

					}
					temp[endE-startE] = '\0';
					silver = String::ToInt(temp);
					delete[] temp;
					temp = nullptr;
					break;
				case 3:
					//copper
					elm = 0;
					try
					{
						temp = new char[(endE - startE) + 1];
					}
					catch (std::bad_alloc except)
					{
						std::cout << "Exception in Potion: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						temp[elm] = cst[j];
						elm++;

					}
					temp[endE-startE] = '\0';
					copper = String::ToInt(temp);
					delete[] temp;
					temp = nullptr;
					break;
				}

				temp = nullptr;
				startE = endE + 1; //will make startE be the next element after a '.'
				section++;
			}
			
		}
	}
	
	//TEST BLOCK
	/*
	{
		std::cout << "Testing what each value is before bumping them" << std::endl;
		std::cout << "Platnium: " << platnium << std::endl;
		std::cout << "Gold: " << gold << std::endl;
		std::cout << "Silver: " << silver <<std::endl;
		std::cout << "Copper: " << copper <<std::endl;
	}
	*/

	//Round up things
	while (copper > 99)
	{
		silver++;
		copper -= 100;
	}



	while (silver > 99)
	{
		gold++;
		silver -= 100;
		
	}


	while (gold > 99)
	{
		platnium++;
		gold -= 100;
		
	}
	/*
		std::cout << "Platnium now: " << platnium << std::endl;
		//test
		std::cout << "Gold now: " << gold << std::endl;
		//test
		std::cout << "Silver now: " << silver << std::endl;
		//test
		std::cout << "Copper now: " << copper << std::endl;
	*/

	//convert back into a String
		//cst = String::ToString(platnium) + "." + String::ToString(gold) + "." + String::ToString(silver) + "." + String::ToString(copper);
	cst = String::ToString(platnium) + "." + String::ToString(gold) + "." + 
		String::ToString(silver) + "." + String::ToString(copper);

	
	//test
		//std::cout << cst << std::endl;
	this->m_costSize = (platnium * 1000000) + (gold * 10000) + (silver * 100) + (copper);
	this->m_cost = cst;
}


/**********************************************************************
* Purpose: This function Displays just the cost of a Potion
*
* Precondition: This Potion object is initialized
*
* Postcondition: Displays the cost of a Potion in the console
*
* Modifications:
************************************************************************/
void Potion::DisplayCost() const
{
	long int copper = 0;
	int silver = 0;
	int gold = 0;
	int platnium = 0;

	copper = this->m_costSize;
	while (copper > 99)
	{
		silver++;
		copper -= 100;
	}

	while (silver > 99)
	{
		gold++;
		silver -= 100;

	}

	while (gold > 99)
	{
		platnium++;
		gold -= 100;

	}

	std::cout << "Potion Cost: [" 
	<< platnium << "] Platnium, [" 
	<< gold << "] Gold, [" 
	<< silver << "] Silver, ["
	<< copper << "] Copper " 
	<< std::endl;
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

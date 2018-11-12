#include "item.h"
/*////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 11/11/18
	FileName: item.cpp

	Purpose: Implementation file for the Item class

	Modifications:
*//////////////////////////////////////////////////////
Item::Item() : m_name(""), m_description(""), m_cost("")
{}

Item::Item(String nm, String dsc, String cst) : m_name(nm), m_description(dsc)
{
	SetCost(cst);
}

Item::Item(String nm, String dsc) : m_name(nm), m_description(dsc), m_cost("")
{}

Item::Item(String nm) : m_name(nm), m_description(""), m_cost("")
{}

Item::~Item()
{}

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
Item & Item::operator = (const Item & right)
{
	if (this != &right)
	{
		this->m_name = right.m_name;
		this->m_description = right.m_description;
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
bool Item::operator== (const Item & right) const
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
bool Item::operator != (const Item & right) const
{
	return !(this == &right);
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of Items

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is greater than right
*//////////////////////////////////////////////////////////////////////////////
bool Item::operator > (const Item & right) const
{
	return (this->m_costSize > right.m_costSize);
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of Items

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is greater than or equal to right
*//////////////////////////////////////////////////////////////////////////////
bool Item::operator >= (const Item & right) const
{
	return (this->m_costSize >= right.m_costSize);
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of Items

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is less than right
*//////////////////////////////////////////////////////////////////////////////
bool Item::operator < (const Item & right) const
{
	return (this->m_costSize < right.m_costSize);
}

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload evaluates the costs of Items

	Plans: All conditional operators will also check for potency differences, TBA

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if this is less than or equal to the right
*//////////////////////////////////////////////////////////////////////////////
bool Item::operator <= (const Item & right) const
{
	return (this->m_costSize <= right.m_costSize);
}



/**********************************************************************
* Purpose: This function Gets the Item name
*
* Precondition:
* this object is initialized
*
* Postcondition:
* Returns the name as a String constant
*
************************************************************************/
const String Item::GetName() const
{
	return this->m_name;
}

/**********************************************************************
* Purpose: This function Gets the Item description
*
* Precondition: This Item object is initialized
*
* Postcondition: Returns this Items description
*
*
************************************************************************/
const String Item::GetDesc() const
{
	return this->m_description;
}

/**********************************************************************
* Purpose: This function Gets the Item cost as a String
*
* Precondition: This Item object is initialized
*
* Postcondition: Returns this Items cost
*
*
************************************************************************/
const String Item::GetCost() const
{
	return this->m_cost;
}

/**********************************************************************
* Purpose: This function Gets the Item costSize as a String
*
* Precondition: This Item object is initialized
*
* Postcondition: Returns this Items costSize
*
*
************************************************************************/
const String Item::GetCostSize() const
{
	return String::ToString(this->m_costSize);
}

/**********************************************************************
* Purpose: This function Sets the Item name
*
* Precondition: This Item object is initialized
*
* Postcondition: Sets this Items name
*
* Modifications:
************************************************************************/
void Item::SetName(String nm)
{
	m_name = nm;
}

/**********************************************************************
* Purpose: This function Sets the Item description
*
* Precondition: This Item object is initialized
*
* Postcondition: Sets this Items description
*
* Modifications:
************************************************************************/
void Item::SetDesc(String dsc)
{
	m_description = dsc;
}

/**********************************************************************
* Purpose: This function Sets the Item cost
*
* Precondition: This Item object is initialized
*               and the format of cost is pp.gg.ss.cc (pp.gggg.sss.ccccc works),
*               where it takes integers inside the String
*
* Postcondition: Sets this Items cost and then verifies and formats
*
* Modifications:
************************************************************************/
void Item::SetCost(String cst)
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
* Purpose: This function validates the cost of a Item
*
* Precondition: This Item object is initialized
*
* Postcondition: returns false if there is a non int character
				in the String submitted
				 returns true if there is no issue with the input
*
* Modifications:
************************************************************************/
bool Item::ValidateCost(String& cst)
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
* Precondition: This Item object is initialized, and ValidateCost has
			been run at least once (all handled by Set cost)
*
* Postcondition: The cost String has been formated To the preferred format
					(pp.gg.ss.cc)
*
* Modifications:
************************************************************************/
void Item::FormatCost(String& cst)
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
						std::cout << "Exception in Item: " << except.what() << std::endl;
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
						std::cout << "Exception in Item: " << except.what() << std::endl;
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
						std::cout << "Exception in Item: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						temp[elm] = cst[j];
						elm++;

					}
					temp[endE - startE] = '\0';
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
						std::cout << "Exception in Item: " << except.what() << std::endl;
					}
					for (int j = startE; j < endE; j++)
					{
						temp[elm] = cst[j];
						elm++;

					}
					temp[endE - startE] = '\0';
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
* Purpose: This function Displays just the cost of an Item
*
* Precondition: This Item object is initialized
*
* Postcondition: Displays the cost of a Item in the console
*
* Modifications:
************************************************************************/
void Item::DisplayCost() const
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

	std::cout << "Item Cost: ["
		<< platnium << "] Platnium, ["
		<< gold << "] Gold, ["
		<< silver << "] Silver, ["
		<< copper << "] Copper "
		<< std::endl;
}

/**********************************************************************
* Purpose: This function Displays everything in the Item obj
*
* Precondition: This Item object is initialized
*
* Postcondition: Displays all information from the Item obj To the console
*
* Modifications:
************************************************************************/
void Item::Display() const
{
	std::cout << "Item Name: [" << this->m_name << "]" << std::endl;
	std::cout << "Item Description: [" << this->m_description << "]" << std::endl;
	DisplayCost();
}
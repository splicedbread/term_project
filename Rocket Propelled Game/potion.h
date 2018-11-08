#pragma once
#ifndef Potion_H
#define Potion_H
#endif // !Potion_H
#include <iostream>
#include "string.h"
/////////////////////////////////////////////////////
/*
	Author: Jacob Vanderkarr
	Filename: Potion.h
	Date Created: 10/2/18
	Modifications:
				10/4/18, added a DisplayCost and Display method

	Class: Potion
	Purpose: This class creates a Potion object that
		represents an item To use.

	Manager Functions:
		-Potion();
			default ctor, does nothing.
		+Potion(Potion & pt);
			copy ctor, used To copy Potion objects
		+Potion(string name, string desc, string pot, string cost);
			largest overloaded ctor, takes a name, description, potency and cost
		+Potion(string name, string desc, string pot);
			2nd largest o ctor, takes a name, description and potency
		+Potion(string name, string desc);
			3rd largest o ctor, takes a name and description
		+Potion(string name);
			smallest overloaded ctor, takes just a name
		+~Potion();

	Methods:
		+const string GetName();
			returns the name of the Potion
		+const string GetDesc();
			returns the description of the Potion
		+const string GetPoten();
			returns the potency of the Potion
		+const string GetCost();
			returns the cost of the Potion
		+void SetName(string nm);
			takes a string parameter, Sets the name of the Potion
		+void SetDesc(string dsc);
			takes a string parameter, Sets the description of the Potion
		+void SetPoten(string pot);
			takes a string parameter, Sets the potency of the Potion
		+void SetCost(string cst);
			takes a string parameter, Sets the cost of the Potion
		-bool ValidateCost(string& cst);
			takes a string reference parameter, validates that the string uses integers and dots
		-void FormatCost(string& cst);
			takes a string reference parameter, formats the cost so that it matches specifications
		-void SaveCost(string & cst);
			takes a string reference parameter, saves a string To the member cost string
		+void DisplayCost();
			Displays the cost as a sentence
		+void Display();
			Displays the Potion object as text

*/
/////////////////////////////////////////////////////
class Potion
{
private:
	String m_name;
	String m_description;
	String m_potency;
	String m_cost;

	long int m_costSize;

	bool ValidateCost(String& cst);
	void FormatCost(String& cst);
	
public:
	Potion();
	Potion(Potion & pt);
	Potion(String name, String desc, String pot, String cost);
	Potion(String name, String desc, String pot);
	Potion(String name, String desc);
	Potion(String name);

	~Potion();

	Potion & operator = (const Potion & right);
	bool operator == (const Potion & right) const;
	bool operator != (const Potion & right) const;
	bool operator > (const Potion & right) const;
	bool operator >= (const Potion & right) const;
	bool operator < (const Potion & right) const;
	bool operator <= (const Potion & right) const;

	const String GetName() const;
	const String GetDesc() const;
	const String GetPoten() const;
	const String GetCost() const;
	const String GetCostSize() const;

	void SetName(String nm);
	void SetDesc(String dsc);
	void SetPoten(String pot);
	void SetCost(String cst);

	void DisplayCost() const;
	void Display() const;
};


#pragma once
#ifndef Potion_H
#define Potion_H
#endif // !Potion_H
#include <iostream>
#include "string.h"
#include "item.h"
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
		+void SetPoten(String pot);
		+const string GetPoten() const;
			returns the potency of the Potion
		+void Display();
			Displays the Potion object as text

*/
/////////////////////////////////////////////////////
class Potion : public Item
{
private:
	String m_potency;
public:
	Potion();
	Potion(const Potion & pt);
	Potion(String name, String desc, String pot, String cost);
	Potion(String name, String desc, String pot);
	Potion(String name, String desc);
	Potion(String name);

	~Potion();
	void SetPoten(String pot);
	const String GetPoten() const;
	Potion & operator = (const Potion & right);
	bool operator == (const Potion & right) const;

	void Display() const;
};


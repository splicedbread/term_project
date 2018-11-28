#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#endif // !Weapon_H
#include <iostream>
#include "string.h"
#include "item.h"
/////////////////////////////////////////////////////
/*
	Author: Jacob Vanderkarr
	Filename: Weapon.h
	Date Created: 10/2/18
	Modifications:
				10/4/18, added a DisplayCost and Display method

	Class: Weapon
	Purpose: This class creates a Weapon object that
		represents an item To use.

	Manager Functions:
		-Weapon();
			default ctor, does nothing.
		+Weapon(Weapon & pt);
			copy ctor, used To copy Weapon objects
		+Weapon(string name, string desc, string pot, string cost);
			largest overloaded ctor, takes a name, description, potency and cost
		+Weapon(string name, string desc, string pot);
			2nd largest o ctor, takes a name, description and potency
		+Weapon(string name, string desc);
			3rd largest o ctor, takes a name and description
		+Weapon(string name);
			smallest overloaded ctor, takes just a name
		+~Weapon();

	Methods:
		+void SetPoten(String pot);
		+const string GetPoten() const;
			returns the potency of the Weapon
		+void Display();
			Displays the Weapon object as text

*/
/////////////////////////////////////////////////////
class Weapon : public Item
{
private:
	String m_damage;
public:
	Weapon();
	Weapon(const Weapon & pt);
	Weapon(String name, String desc, String pot, String cost);
	Weapon(String name, String desc, String pot);
	Weapon(String name, String desc);
	Weapon(String name);

	~Weapon();
	void SetPoten(String pot);
	const String GetPoten() const;
	Weapon & operator = (const Weapon & right);
	bool operator == (const Weapon & right) const;

	void Display() const;
};


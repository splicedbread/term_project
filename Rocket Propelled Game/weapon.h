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
	Date Created: 10/28/18
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
		+Weapon(string name, string desc, string dmg, string cost);
			largest overloaded ctor, takes a name, description, dmgency and cost
		+Weapon(string name, string desc, string dmg);
			2nd largest o ctor, takes a name, description and dmgency
		+Weapon(string name, string desc);
			3rd largest o ctor, takes a name and description
		+Weapon(string name);
			smallest overloaded ctor, takes just a name
		+~Weapon();

	Methods:
		+void SetDmg(String dmg);
		+const string GetDmg() const;
			returns the dmgency of the Weapon
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
	Weapon(String name, String desc, int dmg, String cost);
	Weapon(String name, String desc, int dmg);
	Weapon(String name, String desc);
	Weapon(String name);

	~Weapon();
	void SetDmg(int dmg);
	const String GetDmg() const;
	Weapon & operator = (const Weapon & right);
	bool operator == (const Weapon & right) const;

	void Display() const;
	static const int STRD_DMG = 2;
};


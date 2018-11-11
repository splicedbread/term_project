#pragma once
#include "item.h"
///////////////////////////////////////////////////////////////
/*
	dynamic_array.h
	class specification for a dynamic array class
	made specifically To complete lab3 To demonstrate potions

	Author: Jacob Vanderkarr
	Date: 10/16/18
	Modifications: 
				10/16/18: added initial documentation. initial
						 methods and functions
*/
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
/*
	Class: DynamicArray

	Purpose: This class creates a container object To store 
			multiple potion objects

	Attributes:
			-Potion * m_array
			-int m_elements
	Manager Functions:
			+DynamicArray()
			+~DynamicArray()
			+DynamicArray(const DynamicArray & copy)
			+DynamicArray & operator = (const DynamicArray & right)

	Methods:
			+int GetElements()
			+void Insert(const Potion & to_add)
			+void Delete(const Potion & to_delete)
			-int Find(const Potion & target)

*/
///////////////////////////////////////////////////////////////


class DynamicArray
{
private:
	Item * m_array;
	int m_elements;

	int Find(const Item & target);
public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray & copy);
	DynamicArray & operator = (const DynamicArray & right);
	const Item& operator [] (const int i) const;

	int GetElements();
	void Insert(const Item & to_add);
	void Delete(const Item & to_delete);
};


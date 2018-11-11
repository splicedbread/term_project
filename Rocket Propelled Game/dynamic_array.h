#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include "item.h"
#include <new>
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

template <class T>
class DynamicArray
{
private:
	T * m_array;
	int m_elements;

	int Find(const T & target);
public:
	DynamicArray();
	~DynamicArray();
	DynamicArray(const DynamicArray & copy);
	DynamicArray & operator = (const DynamicArray & right);
	const T& operator [] (const int i) const;

	int GetElements();
	void Insert(const T & to_add);
	void Delete(const T & to_delete);
};

/////////////////////////////////////////////////////////////////////////////
/*
	String.cpp
	Class implementation for the DynamicArray class
			DynamicArray class is designed to dynamically create memory for
					Item objects

	Author: Jacob Vanderkarr
	Date: 10/16/18
	Modifcations:
			10/16/18: initialization of the implementation for manager functions
					and methods
			10/17/18: Implemented manager functions,
					Implemented GetElements, Insert
			10/18/18:
					Implemented Find, and Delete.
					Added an operator [] overload
*/
/////////////////////////////////////////////////////////////////////////////

/*
	Default constructor
*/
template <class T>
DynamicArray<T>::DynamicArray() : m_array(nullptr), m_elements(0)
{
}

/*
	Destructor
*/
template <class T>
DynamicArray<T>::~DynamicArray()
{
	//this should be okay, because it should call each Item destructor first
	//so we do not need to use delete to get rid of them first
	delete[] this->m_array;
	m_array = nullptr;
}

/*
	DyanmicArray(const DynamicArray & copy) is the copy constructor
*/
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray & copy) : m_elements(copy.m_elements), m_array(new T[copy.m_elements + 1])
{
	for (int i = 0; i < copy.m_elements; i++)
	{
		this->m_array[i] = copy.m_array[i];
	}
}

/*//////////////////////////////////////////////////////////
	overloaded manager function operator =
	Purpose: assigns values from the right obj to this obj
			using a deep copy

	Pre conditions: right object is initialized

	Post condition: this obj now contains right obj data
*//////////////////////////////////////////////////////////
template <class T>
DynamicArray<T> & DynamicArray<T>::operator = (const DynamicArray & right)
{
	//check if the right is this obj
	if (this != &right)
	{
		//purge the left
		delete[] this->m_array;
		this->m_array = nullptr;
		//allocate new memory
		this->m_elements = right.m_elements;
		try
		{
			this->m_array = new T[right.m_elements];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}
		//deep copy right data to this obj
		for (int i = 0; i < right.m_elements; i++)
		{
			this->m_array[i] = right.m_array[i];
		}
	}
	//return this obj
	return *this;
}

/*//////////////////////////////////////////////////////////
	overloaded manager function operator =
	Purpose: accesses the m_array to be able to convienently display
			data

	Pre conditions: this object is initialized

	Post condition: returns the index postion data in the array
*//////////////////////////////////////////////////////////
template <class T>
const T& DynamicArray<T>::operator [] (const int i) const
{
	return this->m_array[i];
}


/*/////////////////////////////////////////////
	Method Name: GetElements
	Purpose: returns the m_elements as integer

	Pre conditions: this obj is initialized
	Post conditions: m_elements is returned
*//////////////////////////////////////////////
template <class T>
int DynamicArray<T>::GetElements()
{
	return this->m_elements;
}

/*////////////////////////////////////////////////////////////////////////
	Method Name: Insert
	Purpose: Inserts the obj to the dynamic array at the backmost position

	Pre condition: arg object initialized

	Post condition: arg obj is added into the dynamic array
*/////////////////////////////////////////////////////////////////////////
template <class T>
void DynamicArray<T>::Insert(const T & to_add)
{
	//When working with dynamic memory, when adding to that section
	//There are multiple ways to handle it
	if (this->m_elements != 0 && this->m_array != nullptr)
	{
		//create a temporary buffer that is one larger than the current array
		//same size for a temp buffer
		T * buffer = nullptr;
		try
		{
			buffer = new T[this->m_elements];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}
		//copy m_array into buffer


		for (int i = 0; i < this->m_elements; i++)
		{
			buffer[i] = this->m_array[i];
		}

		//delete the current array
		delete[] this->m_array;
		m_array = nullptr;

		//allocate new memory for the array
		try
		{
			m_array = new T[this->m_elements + 1];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}
		//increment m_elements by 1, this will create space for the to_add
		this->m_elements++;

		//copy everything from the buffer to the new array, but remember the 
		//m_elements size changed
		for (int i = 0; i < this->m_elements - 1; i++)
		{
			this->m_array[i] = buffer[i];
		}
		//Finally everything is back into the original array, inset to_add to the last
		//element, which is at position m_element
		this->m_array[m_elements - 1] = to_add;
		//cleanup our temp buffer
		delete[] buffer;
		buffer = nullptr;

	}
	else
	{
		try
		{
			this->m_array = new T[this->m_elements + 1];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}
		this->m_elements++;
		this->m_array[0] = to_add;
	}

}

/*////////////////////////////////////////////////////////////////////////
	Method Name: Delete
	Purpose: Deletes the obj in the dynamic array that matches

	Pre condition: arg obj is initialized, doesnt have to be in array

	Post condition: arg obj is removed from the dynamic array
*/////////////////////////////////////////////////////////////////////////
template <class T>
void DynamicArray<T>::Delete(const T & to_delete)
{
	int t_element = Find(to_delete);
	//check if nothing was found in the Find function
	if (t_element == -1)
	{
		//temp cout until try and catch stuff is added
		std::cout << "item to delete does not exist in this array" << std::endl;
	}
	else
	{
		//similar to insert, but we need to remove one instead of adding 1.
		//but we need to be able take out of the middle of the array, and bump
		//everything into order
		//dont need to add an extra space in m_elements because we are removing one
		T * buffer = nullptr;
		try
		{
			buffer = new T[this->m_elements];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}

		for (int i = 0, j = 0; i < this->m_elements; i++, j++)
		{
			if (i == t_element)
			{
				//do no assigment, subtract from j before next loop, 
				//so buffer didnt increment its index
				j--;
			}
			else
			{
				buffer[j] = this->m_array[i];
			}
		}
		//after everything is in the buffer, purge this objects array
		//delete the current array
		delete[] this->m_array;
		m_array = nullptr;
		//allocate new memory for the array
		try
		{
			m_array = new T[this->m_elements - 1];
		}
		catch (std::bad_alloc except)
		{
			std::cout << "Exception in DArray: " << except.what() << std::endl;
		}

		//decrement m_elements by 1, this will create space for the to_add
		this->m_elements--;
		//copy everything from the buffer to the new array, but remember the 
		//m_elements size changed
		for (int i = 0; i < this->m_elements; i++)
		{
			this->m_array[i] = buffer[i];
		}

		//cleanup the temp buffer

		delete[] buffer;
		buffer = nullptr;
	}
}

/*//////////////////////////////////////////////////////////////////////////////////
	Method Name: Find
	Purpose: Finds the equivalent obj from the argument and returns the element pos
			If the object cannot be found, returns a -1, which indicates
			that it was not found

	Pre condition: arg obj is initialized

	Post condition: arg obj is found (or not) and the element position is returned
*///////////////////////////////////////////////////////////////////////////////////
template <class T>
int DynamicArray<T>::Find(const T & target)
{
	bool found = false;
	int t_element = 0;

	while (!found && (t_element < this->m_elements))
	{
		if (this->m_array[t_element] == target)
		{
			found = true;
		}
		else
		{
			t_element++;
		}
	}

	if (!found)
	{
		t_element = -1;
	}

	return t_element;
}
#endif
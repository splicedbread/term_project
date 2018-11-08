#pragma once
#ifndef STRING_H
#define STRING_H
#include <iostream>
///////////////////////////////////////////////////////////////
/*
	String.h
	class specification for a custom string class
	made specifically To complete inLab2, however will continue
	to grow in future projects

	Author: Jacob Vanderkarr
	Date: 9/28/18
	Modifications: 9/28/18 Reason: Adding base features
				   10/01/18: Completed all manager functions
							 and some overloaded operators
				   10/09/18: Added Display(), String(char), ToUp() and ToLow()
							and ToString() and ToInt()
*/
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
/*
	Class: String

	Purpose: This class creates a container object To store 
		string information.

	Manager Functions:
		+String ()
			Default ctor, char * m_mem = nullptr. 
		+~String ()
			Default dtor, will delete data at the pointer array
				address before Setting the ptr To nullprt.
		+String (const String&)
			Copy constructor, will manage the pointers and data
			between objects

	Methods:
		+String& operator=(const String&)
			Operator overload of the equate operator. Using in
			conjunction with the copy constructor
		-void mCpy(const String&)
			A function that copys the content from one char []
			to the objects own, taking a String& as an argument
		-void mCpy(const char*)
			A function that copys the content from one char []
			to the objects own, taking a char * as an argument
		+const char * GetStr()
			A function that returns a char ptr for the char data stored
		+const int GetInt()
			A function that returns an integer for the length of the data

*/
///////////////////////////////////////////////////////////////
class String
{
private:
	char * m_str;
	int m_length;
	void mCpy(const String& right);
	void mCpy(const char * right);
public:
	String();
	String(const String& cpy);
	String(const char * str);
	String(char);
	~String();
	String & operator = (const String & right);
	String & operator = (const char *);
	String & operator + (const String & right); //not implemented yet
	String & operator + (const char *); //not implemented yet
	bool operator == (const String & right) const;
	bool operator > (const String & right) const;
	bool operator < (const String & right) const;
	bool operator != (const String & right) const;
	bool operator >= (const String & right) const;
	bool operator <= (const String & right) const;
	friend std::ostream& operator << (std::ostream& os, const String& str);
	const char& operator [] (const int i) const;
	//char& operator [] (int i);
	char * GetStr() const;
	int GetLen() const;
	void Display();


	//static so the obj does not need To be initialized
	
	static void ToUp(String&);
	static String ToUp(String, bool flag);
	static void ToLow(String&);
	static String ToString(int);
	static int ToInt(const String&);
	static int ToInt(const char *);
};

#endif // !STRING_H
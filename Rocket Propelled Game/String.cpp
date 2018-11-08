#include "string.h"
#include <new>
#include <iostream>
using std::cout; 
using std::cin; 
using std::endl;
using std::ostream;
/////////////////////////////////////////////////////////////////////////////
/*
	String.cpp
	Class implementation for the custom string class
	made for inlab2, but can be used further To grow

	Author: Jacob Vanderkarr
	Date: 9/28/18
	Modifcations: 9/28/18 Reason: Adding base features
				  10/01/18: Completed all manager functions
						    and some overloaded operators
				  10/09/18: Added String(char), Display(), ToUp() & ToLow()
							and ToString, ToInt
							Updated +operator overloads
				  10/18/18: added a operator == overload
*/
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/*
* Purpose: default ctor
*
* Precondition: none
*
* Postcondition: string object is created with basic initialization
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String::String() : m_length(0), m_str(nullptr)
{
	//cout << "default String ctor" << endl;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: copy ctor
*
* Precondition: cpy argument is already initialized
*
* Postcondition: string object is created with m_length and m_str
				initialized from cpy
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String::String(const String& cpy) : m_length(cpy.m_length) , m_str(new char[cpy.m_length + 1])
{
	//The base number initialization already has created the character array using new
	//Using a function To cleanup the copying from one char array To the next,
	//without depending on strcpy() from sting.h or cstring's functions
	//cout << "using copy String ctor..." << endl;
	this->mCpy(cpy);
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: overloaded copy ctor
*
* Precondition: the given char array, or pointer To one, is initialized
*
* Postcondition: string object is created with determined length in m_length
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String::String(const char * str) : m_length(0), m_str(nullptr)
{
	//cout << "using overloaded char To String ctor..." << endl;
	this->mCpy(str);
};

////////////////////////////////////////////////////////////////////////
/*
* Purpose: overloaded ctor
*
* Precondition: the given char is initialized
*
* Postcondition: string object is created with length 2, one for the char
				one for the null terminating character
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String::String(char in) : m_length(1), m_str(new char[2])
{
	m_str[0] = in;
	m_str[1] = '\0';
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: dtor
*
* Precondition: the string object exists
*
* Postcondition: memory that was allocated is freed, and dangling pointer
				is removed
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String::~String()
{
	delete[] m_str;
	this->m_str = nullptr;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: = operator overload
*
* Precondition: right string object exists, this object exists
*
* Postcondition: right object is copied To this object
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String& String::operator= (const String& right)
{
	//cout << "entering overload operator=" << endl;
	//test To see if the right is the same object
		if (this != &right)
		{
			//purge the left
			delete[] this->m_str;

			//copy the length from the right
			this->m_length = right.m_length;
			//allocate memory for the new string
			try
			{
				this->m_str = new char[right.m_length + 1];
			}
			catch (std::bad_alloc except)
			{
				//Failed allocation
				cout << "Exception in String: " << except.what();
			}
			//Have the data in the char array copied over To this instance
			this->mCpy(right);
		}
	return *this;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: = operator overload, overload
*
* Precondition: the right pointer To a char array exists, this exists
*
* Postcondition: the char array is copied To this object
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String& String::operator= (const char * right)
{
		//cout << "entering overload operator=" << endl;
		if (this->m_str != right)
		{
			//cout << "They are the same" << endl;
			//purge the left ptr and Set m_length = 0
			delete[] this->m_str;
			this->m_str = nullptr;
			this->m_length = 0;
			//copy the length from the right, allocate, and have the data copied over
			//in this overloaded function for just this class.
			//My reason for this is it cleans up this area.
			mCpy(right);
		}
	return *this;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: concatenates the right String To this obj
*
* Precondition: right is initialized
*
* Postcondition: right is concatenated onto this obj
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String & String::operator + (const String & right) //not used yet
{
	//Get the length from the right
	int r_len = right.GetLen();
	//new length
	int len = this->m_length + r_len;
	//allocate a temp storage
	char * buffer = nullptr;
	try
	{
		buffer = new char[len + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//move everything from this To temp
	for (int i = 0; i < this->m_length + 1; i++) {
		buffer[i] = this->m_str[i];
	}

	//move everything from right To the end of temp
	for (int i = this->m_length, j = 0; j < r_len + 1; i++, j++) {
		buffer[i] = right[j];
	}
	//add a null termination character
	buffer[len] = '\0';

	//deallocate this memory To make room for the new allocation
	delete [] this->m_str;
	try 
	{
		this->m_str = new char[len + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//Set this length To equal the new Total
	this->m_length = len;

	//store everything from the temp storage back To this m_str
	for (int i = 0; i < this->m_length + 1; i++) {
		this->m_str[i] = buffer[i];
	}

	this->m_str[len] = '\0';


	//deallocate the temp memory allocation
	delete[] buffer;
	buffer = nullptr;

	return *this;
};

////////////////////////////////////////////////////////////////////////
/*
* Purpose: concatenates the right char[] To this obj
*
* Precondition: right is initialized
*
* Postcondition: right is concatenated onto this obj
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String & String::operator + (const char * right) //not used yet
{
	//create a temporary int for this scope
	int tempCount = 0;
	//determine the size of the char
	for (int i = 0; right[i] != '\0'; i++)
	{
		tempCount++;
	}

	//Get the length from the right
	int r_len = tempCount;
	//new length
	int len = this->m_length + r_len;
	//allocate a temp storage
	char * buffer = nullptr;
	try
	{
		buffer = new char[len + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//move everything from this To temp
	for (int i = 0; i < this->m_length + 1; i++) {
		buffer[i] = this->m_str[i];
	}

	//move everything from right To the end of temp
	for (int i = this->m_length, j = 0; j < r_len; i++, j++) {
		buffer[i] = right[j];
	}
	//add a null termination character
	buffer[len] = '\0';

	//deallocate this memory To make room for the new allocation
	delete[] this->m_str;
	try
	{
		this->m_str = new char[len + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//Set this length To equal the new Total
	this->m_length = len;

	//store everything from the temp storage back To this m_str
	for (int i = 0; i < this->m_length + 1; i++) {
		this->m_str[i] = buffer[i];
	}

	//deallocate the temp memory allocation
	delete[] buffer;
	buffer = nullptr;

	return *this;
};

/*/////////////////////////////////////////////////////////////////////////////
	Purpose: This operator overload checks the contents of the obj to test for
			object equality

	Precondition:
	right obj is initialized

	Postcondition:
	Returns true or false depending on if both objects are evauluated the same
*//////////////////////////////////////////////////////////////////////////////
bool String::operator == (const String & right) const
{
	bool flag = true;
	//if the lengths do not match, then they do not match at all
	if (this->m_length == right.m_length)
	{
		//iterate through the char array, if a char doesnt match, the flag is now false
		for (int i = 0; i < this->m_length + 1; i++)
		{
			if (this->m_str[i] != right.m_str[i])
			{
				flag = false;
			}
		}
	}
	else
	{
		flag = false;
	}
	
	return flag;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: ostream << operator overload
*
* Precondition: this object exists
*
* Postcondition: characters are properly read and Displayed
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& os, const String& str) 
{
	os << str.m_str;
	return os;
};

const char& String::operator [] (const int i) const
{
	return this->m_str[i];
};


////////////////////////////////////////////////////////////////////////
/*
* Purpose: Gets string
*
* Precondition: this object exists
*
* Postcondition: returns string
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
char* String::GetStr() const
{
	return this->m_str;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: Gets length of the string
*
* Precondition: this object is initialized with a length
*
* Postcondition: returns an integer
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
int String::GetLen() const
{
	return this->m_length;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: steps through right side elements To copy them into this obj
*
* Precondition: right is initialized
*
* Postcondition: m_str holds a copy of the right sides data
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
void String::mCpy(const String& right)
{
		for (int i = 0; i < right.m_length + 1; i++)
		{
			this->m_str[i] = right.m_str[i];
		}
		//Checking To see if the null terminating character was copied, if not, then Display a message
		//so I can fix this later
		if (this->m_str[m_length] != '\0')
		{
			std::cout << "Uh oh, your string doesnt have a terminating character" << std::endl;
		}
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: determines the length of the right array then
			steps through right side elements To copy them into this obj
*
* Precondition: right is initialized
*
* Postcondition: m_str hold a copy of the right side data
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
void String::mCpy(const char * right) 
{
		//create a temporary int for this scope
		int tempCount = 0;
		//determine the size of the char
		for (int i = 0; right[i] != '\0'; i++)
		{
			tempCount++;
		}

		//Testing To make sure things work right
		//////////////////////////////////////////////////
		this->m_length = tempCount;
		//////////////////////////////////////////////////

		//allocate memory for the data before transfering
		try
		{
			this->m_str = new char[this->m_length + 1];
		}
		catch (std::bad_alloc except)
		{
			//Failed allocation
			cout << "Exception in String: " << except.what();
		}
		//copy data from the char ptr To this char array as such.

		for (int i = 0; i < this->m_length + 1; i++)
		{
			this->m_str[i] = right[i];
			//cout << i << m_str[i] << endl;
		}

		this->m_str[this->m_length] = '\0';
		//Checking To see if the null terminating character was copied, if not, then Display a message
		//so I can fix this later
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: Display the string
*
* Precondition: object is initialized
*
* Postcondition: Displayed string
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
void String::Display()
{
	cout << this->m_str << endl;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: raises the entire string To UPPERCASE
*
* Precondition: a string obj is initialized
*
* Postcondition: all alphabetical characters are UPPERCASE
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
void String::ToUp(String& in)
{
	//allocate something To work with
	char * buff = nullptr;
	try
	{
		buff = new char[in.GetLen() + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//iterate through the argument looking for lowercase chars
	for (int i = 0; i < in.GetLen() + 1; i++)
	{
		//copy input into buffer
		buff[i] = in[i];
		//if lowercase, -32 uses uppercase characters from the ascii table
		if (in[i] >= 'a' && in[i] <= 'z')
		{
			buff[i] -= 32;
		}
	}
	//test
	//cout << "test " << buff << endl;

	//save the buffer 
	in = buff;

	//test
	//cout << in << endl;

	//deallocate memory borrowed
	delete[] buff;
	buff = nullptr;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: raises the entire string To UPPERCASE
*
* Precondition: a string obj is initialized
*
* Postcondition: all alphabetical characters are UPPERCASE and returns a string
				flag should always be 1, or 0 if a serious problem
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String String::ToUp(String in, bool flag)
{

	if (flag == true)
	{
		//allocate something To work with
		char * buff = nullptr;
		try
		{
			buff = new char[in.GetLen() + 1];
		}
		catch (std::bad_alloc except)
		{
			//Failed allocation
			cout << "Exception in String: " << except.what();
		}
		//iterate through the argument looking for lowercase chars
		for (int i = 0; i < in.GetLen() + 1; i++)
		{
			//copy input into buffer
			buff[i] = in[i];
			//if lowercase, -32 uses uppercase characters from the ascii table
			if (in[i] >= 'a' && in[i] <= 'z')
			{
				buff[i] -= 32;
			}
		}
		//test
		//cout << "test " << buff << endl;

		//save the buffer 
		in = buff;
	
		//test
		//cout << in << endl;
	
		//deallocate memory borrowed
		delete[] buff;
		buff = nullptr;
	}

	return in;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: lowers the entire string To lowercase
*
* Precondition: a string obj is initialized
*
* Postcondition: all alphabetical characters are lowercase
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
void String::ToLow(String& in)
{
	//allocate something To work with
	char * buff = nullptr;
	try
	{
		buff = new char[in.GetLen() + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}
	//iterate through the argument looking for uppercase chars
	for (int i = 0; i < in.GetLen() + 1; i++)
	{
		//copy input into buffer
		buff[i] = in[i];
		//if uppercase, +32 uses lowercase characters from the ascii table
		if (in[i] >= 'A' && in[i] <= 'Z')
		{
			buff[i] += 32;
		}
	}
	//test
	//cout << "test " << buff << endl;

	//save the buffer 
	in = buff;

	//test
	//cout << in << endl;

	//deallocate memory borrowed
	delete[] buff;
	buff = nullptr;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: turns an integer into a string
*
* Precondition: an int is passed as an argument
*
* Postcondition: returns the constructed string
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
String String::ToString(int num)
{
	int temp = num;
	int sigCount = 0;
	String buff = "";
	
	while (temp != 0)
	{
		temp /= 10;
		sigCount++;
	}

	temp = num;
	//allocate a temp thing
	char * buffer = nullptr;
	try
	{
		buffer = new char[sigCount + 1];
	}
	catch (std::bad_alloc except)
	{
		//Failed allocation
		cout << "Exception in String: " << except.what();
	}


	//start i at sigCount - 1 so its not at the last element counting down
	//because the last element is reserved for the null terminating character
	for (int i = sigCount - 1; i >= 0; i--)
	{
		buffer[i] = (temp % 10) + '0';
		temp /= 10;
	}
	//The above code just put the modulus results in backwards, because thats what it do
	//place a null terminator at the end
	buffer[sigCount] = '\0';
	//put the char pointer in a String object that exists just here=
	buff = buffer;
	//deallocate memory
	delete[] buffer;
	buffer = nullptr;

	return buff;
}

////////////////////////////////////////////////////////////////////////
/*
* Purpose: turns a string into a integer
*
* Precondition: string obj is initialized
*
* Postcondition: returns an integer
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
int String::ToInt(const String& in)
{
	int temp = 0;
	int sig = 0;
	for (int i = 0; i < in.GetLen(); i++)
	{
		sig = in[i] - '0';
		for (int j = in.GetLen() - i; j > 1; j--)
		{
			sig *= 10;
		}
		temp += sig;
	}
	return temp;
}


////////////////////////////////////////////////////////////////////////
/*
* Purpose: turns a char[] litteral or pointer into an integer
*
* Precondition: litteral, or initialized
*
* Postcondition:
*
* Modifications:
*/
////////////////////////////////////////////////////////////////////////
int String::ToInt(const char * arg)
{

	int temp = 0;
	int sig = 0;

	if (&arg != nullptr)
	{
		//create a temporary int for this scope
		int tempCount = 0;
		//determine the size of the char
		for (int i = 0; arg[i] != '\0'; i++)
		{
			tempCount++;
		}
	
		for (int i = 0; i < tempCount; i++)
		{
			sig = arg[i] - '0';
			for (int j = tempCount - i; j > 1; j--)
			{
				sig *= 10;
			}
			temp += sig;
		}
	}

	return temp;
}
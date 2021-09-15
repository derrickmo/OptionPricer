#ifndef Array_HPP
#define Array_HPP

#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Array				// Create a class called Array
{
private:									// Below functions and variables are only available in this class
	T* m_data;								// A private pointer points to a Point object
	int s;									// A private variable to represent size

public:
	Array();								// Default constructor - Allocates 10 elements
	Array(int size);						// Constructor with size argument. Allocate "size" elements
	Array(const Array<T>& arr);				// This is a copy constructor
	virtual ~Array();						// Destructor

	// Below are required functions
	int size() const; 						// return size 
	void setElement(int k, T input) const;	// This function sets an element
	T getElement(int k) const;				// This gets the kth element from the array

	// Operators
	Array<T>& operator = (const Array<T>& source);// Assignment operator
	T& operator[] (int k);
	const T& operator[] (int k) const;  //square bracket operator

};

class ArrayException
{
public:
	virtual string GetMessage() = 0;
};



class OutOfBoundsException : public ArrayException
{
private:
	int m_index; // Pirvate memeber - m_index

public:
	OutOfBoundsException(int i);

	// This function prints out error message with m_index variable
	string GetMessage()
	{
		std::stringstream strs;	// Create a new object called strs
		strs << "Error !!! Index OutOfBoundsException type " << m_index << endl;
		return strs.str();
	}
};

// OutOfBoundsException constructor
inline OutOfBoundsException::OutOfBoundsException(int i) : m_index(i)
{
}


#endif

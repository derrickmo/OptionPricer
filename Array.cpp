#ifndef Array_CPP
#define Array_CPP

#include <iostream>
#include <ostream>
#include "Array.hpp"

using namespace std;
static int defaultSize = 10; // Initialize static variable

// This is a default constrcutor and it allocates 10 elements at a time.
template <class T>
Array<T>::Array() : m_data(new T[defaultSize]), s(defaultSize)
{
	// cout << "--Array default constructor is called. Array size is " << this->size() << endl;
}

// This is a constructor that takes in size argument
template <class T>
Array<T>::Array(int size) : m_data(new T[size]), s(size)
{
	// cout << "--Array int constructor is called. input size is " << size << " and array size is " << this->size() << endl;
}

//This is a copy constructor
template <class T>
Array<T>::Array(const Array<T>& arr) // Use pass by reference approach to save memory on stack
{
	m_data = new T[arr.size()];
	s = arr.s;
	for (int i = 0; i < arr.s; i++)	// We Loop all elements and populate into the new array.
	{
		m_data[i] = arr.m_data[i]; // ith element's data is equal to target's ith element's data
	}

};

// This is a destructor. It helps to free up memory used.
template <class T>
Array<T>::~Array()
{
	delete[] m_data;
	//cout << "--Array destructor--" << endl;
}



// This is an access function to access a private value. It goes to the point object and reutrn y.
template <class T>
int Array<T>::size() const
{
	return s; // Return size
}

// Set the k element to the point passed in
template <class T>
void Array<T>::setElement(int k, T input) const
{
	try
	{
		if (k < 0 || s <= k) // check if index is outof bound
		{
			throw OutOfBoundsException(-1);
		}
		m_data[k] = input;	// Set kth element in the array to be pt
		// cout << "Try block is successfully executed!" << endl;
	}
	catch (ArrayException & a)
	{
		cout << a.GetMessage();
	}
}

// Set the k element to the point passed in
template <class T>
T Array<T>::getElement(int k) const
{
	try
	{
		if (k < 0 || s <= k) // check if index is outof bound
		{
			throw OutOfBoundsException(-1);
		}
		return m_data[k]; // Set kth element in the array to be pt
		// cout << "Try block is successfully executed!" << endl;
	}
	catch (ArrayException & a)
	{
		cout << a.GetMessage();	// Print out error message
	}
}



// Assign "=" operator.
template <class T>
Array<T>& Array<T>:: operator = (const Array<T>& source)
{
	if (this == &source)
	{
		return *this;
	}
	s = source.size();
	delete[] m_data;
	m_data = new T[s];
	for (int i = 0; i < s; i++)	
	{
		m_data[i] = source.m_data[i];
	}
	return *this;
}

template <class T>
T& Array<T>:: operator [] (int k)
{
	try
	{
		if (k < 0 || s <= k)
		{
			throw OutOfBoundsException(-1);
		}
		return m_data[k];
		// cout << "Try block is successfully executed!" << endl;
	}
	catch (ArrayException & a)
	{
		cout << a.GetMessage();
	}
}

// Assign "[]" oeprator using const version. Const is required so we can pass in and return const item.
template <class T>
const T& Array<T>:: operator [] (int k) const
{
	try
	{
		if (k < 0 || s <= k)
		{
			throw OutOfBoundsException(-1);
		}
		return m_data[k];
		// cout << "Try block is successfully executed!" << endl;
	}
	catch (ArrayException & a)
	{
		cout << a.GetMessage();	
	}
}



#endif
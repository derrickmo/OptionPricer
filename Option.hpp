#ifndef Option_hpp
#define Option_hpp
#include <string>
using namespace std;

class Option
{
private:				// Designed these private members for logistic purposes
	int id;				// Generate an id 
	double book;		// Purchase price
	double quan;		// Quantity of options
	string source;		// Source of option
	string fi;			// Financial institutions
	string dep;			// division

public:

	// Public functions
	Option();							
	virtual ~Option();					

	// Gaussian functions				
	double n(double x) const;
	double N(double x) const;

	// ID function
	int ID() const;	
	double Book() const;
	double Quan() const;
	string Source() const;
	void Source(string input);
	string FI() const;
	void FI(string input);
	string Dep() const;
	void Dep(string input);

};

#endif
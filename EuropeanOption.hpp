#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include <iostream>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include "Option.hpp"
#include "Array.cpp"
using namespace std;

class EuropeanOption : public Option
{
private:	// private functions for internal price calculation

	void init();								// Initialise all default values
	void copy(const EuropeanOption& o2);		// Copy constructor

private:	// Parameters specified in the instruction; Reorder to match with item sequences in the assignment instruction.
	string optType;	// Option name (call, put)														
	double T;		// Expiry date																	
	double K;		// Strike price																	
	double sig;		// Volatility																	
	double r;		// Interest rate																
	double S;		// Current stock price															
	double b;		// Cost of carry - Not required													
	string unam;	// Name of underlying asset														

public:	
	// Constructors
	EuropeanOption();																							// Default option constructor	
	EuropeanOption(double Exp, double Strike, double Sig, double rfr, double Spot);								// input w/o type constructor	
	EuropeanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot);				// input with type constructor	
	EuropeanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot, double Carry);	// input with type constructor	
	EuropeanOption(const EuropeanOption& option2);																// Copy constructor				
	virtual ~EuropeanOption();																					// Destructor					

	//Price functions
	double Price() const;			// To calculate the price of an option using BS
	double MasterPrice(string input) const;	// This is a supporting function to print among price and derivative functions
	double ParityPrice() const;		// To calculate the price based on put-call parity
	bool ParityCheck() const;		// Check if the parity condition is satisfied
	
	//Derivative functions
	double CallDelta() const;		// To calcualte call delta
	double PutDelta() const;		// To calculate put delta
	double Gamma() const;			// To calcualte gamma
	
	// Function to print out both call and put price tree
	Array<vector<double>> CPArray(double start, double end, double interval);	// MeshArray function - return an array of vector<double>
	void CPArrayPrint(double start, double end, double interval);				// Print out the meshArray for Call and Put
	
	// MeshArray function - This function returns an array of vector<double> and the print function prints them out in a nice format
	vector<vector<double>> MeshArray(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval);
	void MeshArrayPrint(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval);
	
	// MeshArray supporting functions
	void Increment(int condition, double intervalSize);			// This helps to increment size of an input
	int CaseCondition(string input) const;						// This function helps to determine what input is coming to the function
		
	// Divided differences
	double DiffDelta(double h) const;		// Diff Delta method
	double DiffGamma(double h) const;		// Diff Gamma method

	// Getter and Setter functions. Unlike Point class can use X() as function and x as member, name change is reuiqred for the function. 
	string Type() const;
	void Type(string input);	// This is equivalent to the original option type function
	double Exp() const;
	void Exp(double input);
	double Strike() const;
	void Strike(double input);
	double Sig() const;
	void Sig(double input);
	double rfr() const;
	void rfr(double input);
	double Spot() const;
	void Spot(double input);
	double Carry() const;
	void Carry(double input);
	void Unam(string input);
	string Unam() const;

	// Operator function
	EuropeanOption& operator = (const EuropeanOption& option2);

	// Modifier functions
	void Toggle();		// Change option type (C/P, P/C)
	
	// Print out member data
	string ToString() const;

};

#endif
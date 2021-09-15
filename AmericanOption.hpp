#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include <iostream>
#include <string>
#include <boost/numeric/ublas/vector.hpp>
#include "Option.hpp"
#include "Array.cpp"
using namespace std;

class AmericanOption : public Option
{
private:	// private functions for internal price calculation

	void init();								// Initialise all default values
	void copy(const AmericanOption& o2);		// Copy constructor

private:	// Parameters specified in the instruction; Reorder to match with item sequences in the assignment instruction.
	string optType;	// Option name (call, put)																						
	double T;		// Expiry date		// While this is not required in our formula but I want to kill it for potential future use	
	double K;		// Strike price																									
	double sig;		// Volatility																									
	double r;		// Interest rate																								
	double S;		// Current stock price																							
	double b;		// Cost of carry - Not required																					
	string unam;	// Name of underlying asset																						

public:	// Constructors
	AmericanOption();																							// Default option constructor	
	AmericanOption(double Exp, double Strike, double Sig, double rfr, double Spot);								// input w/o type constructor	
	AmericanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot);				// input with type constructor	
	AmericanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot, double Carry);	// input with type constructor	
	AmericanOption(const AmericanOption& option2);																// Copy constructor				
	virtual ~AmericanOption();																					// Destructor					

	//Price functions
	double Price() const; // Calculate the price of an option
	double MasterPrice(string input) const;	// Prints call prices

	// CPArray function to print both call and put price tree
	Array<vector<double>> CPArray(double start, double end, double interval); // MeshArray function - return an array of vector<double>
	void CPArrayPrint(double start, double end, double interval); // Print out the meshArray for Call and Put

	// MeshArray function - return an array of vector<double> which can be print out using print function
	vector<vector<double>> MeshArray(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval);
	void MeshArrayPrint(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval);

	void Increment(int condition, double intervalSize);
	int CaseCondition(string input) const;

	// Getter and Setter functions. Unlike Point class can use X() as function and x as member, name change is reuiqred for the function. 
	string Type() const;
	void Type(string input);
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

	AmericanOption& operator = (const AmericanOption& option2);

	// Print out member data
	string ToString() const;
};

#endif
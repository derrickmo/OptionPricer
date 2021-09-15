#ifndef AmericanOption_cpp
#define AmericanOption_cpp

#include "AmericanOption.hpp"
#include "Array.cpp"
#include <boost/math/distributions.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>

// Establish default situaiton for default constructor and allow user to change default value if needed.
static string default_optType = "C";
static double default_T = 1.0;
static double default_K = 100;
static double default_sig = 0.2;
static double default_r = 0.05;
static double default_S = 100;	// default spot price is equal to strike price
static double default_b = 0.05;	// default carry cost is equal to risk-free rate

void AmericanOption::init()
{	// Initialise all default values
	r = default_r;
	sig = default_sig;
	K = default_K;
	T = default_T;
	b = default_b;
	S = default_S;
	optType = default_optType;
}

void AmericanOption::copy(const AmericanOption& o)
{
	optType = o.optType;
	T = o.T;
	K = o.K;
	sig = o.sig;
	r = o.r;
	S = o.S;
	b = o.b;
	unam = o.unam;
}

AmericanOption::AmericanOption()
{ // Default call option
	init();
}

AmericanOption::AmericanOption(double Exp, double Strike, double Sig, double rfr, double Spot) : T(Exp), K(Strike), sig(Sig), r(rfr), S(Spot)
{
	// Default type is call	
	optType = "C";
	b = r;
}

AmericanOption::AmericanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot)
{
	// Default to call if enter type is invalid
	if (type == "C" || type == "P")
	{
		optType = type;
	}
	else
	{
		cout << "Invalid input, please enter \"C\" or \"P\" as option type. The option is initialized as a call option" << endl;
		optType = "C";
	}
	T = Exp;
	K = Strike;
	sig = Sig;
	r = rfr;
	S = Spot;
	b = r;
}

// Option constructor with type initiation
AmericanOption::AmericanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot, double Carry)
{
	// Default to call if enter type is invalid
	if (type == "C" || type == "P")
	{
		optType = type;
	}
	else
	{
		cout << "Invalid input, please enter \"C\" or \"P\" as option type. The option is initialized as a call option" << endl;
		optType = "C";
	}
	T = Exp;
	K = Strike;
	sig = Sig;
	r = rfr;
	S = Spot;
	b = Carry;
}

AmericanOption::AmericanOption(const AmericanOption& o)
{ // Copy constructor
	copy(o);
}

// Destructor
AmericanOption::~AmericanOption()
{
}

double AmericanOption::Price() const
{
	double sig2 = sig * sig;
	if (optType == "C")
	{
		double y1 = 0.5 - (b/sig2) + sqrt(pow(((b/sig2) - 0.5),2) + (2 * r)/sig2) ;	// y1
		return (K / (y1 - 1)) * pow((y1 - 1) / y1 * (S / K), y1);
	}
	else
	{
		double y2 = 0.5 - b/sig2 - sqrt(pow((b / sig2 - 0.5), 2) + 2 * r / sig2); // y2
		return (K / (1-y2)) * pow((y2 - 1) / y2 * (S / K), y2);	
	}
}

double AmericanOption::MasterPrice(string input) const
{
	if (input == "Price") 
	{ 
		return Price(); 
	}
	else 
	{ 
		return Price(); 
	}
}

Array<vector<double>> AmericanOption::CPArray(double start, double end, double interval)
{
	int size = (end - start) / interval + 1; // The height of this 2-D array is size 
	Array<vector<double>> arr(size); // Establish an array of vector with size
	AmericanOption copy = AmericanOption("C", T, K, sig, r, S,b);
	for (int i = 0; i < size; i++)
	{
		// vector stores 3 objects: Stock price, call price and put price
		copy.Spot(start + interval * i);			
		copy.Type("C");					
		double callPrice = copy.Price();
		copy.Type("P");					
		double putPrice = copy.Price();	
		arr.setElement(i, vector<double> {copy.Spot(), callPrice, putPrice});
	}
	return arr;
}

void AmericanOption::CPArrayPrint(double start, double end, double interval)
{
	Array<vector<double>> arr = CPArray(start, end, interval);
	cout << "Spot\tCall\t\tPut" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.getElement(i)[0] << "\t" << arr.getElement(i)[1] << "\t\t" << arr.getElement(i)[2] << endl;
	}
}

vector<vector<double>> AmericanOption::MeshArray(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval)
{
	int rows = (xEnd - xStart) / xInterval + 1;		
	int columns = (yEnd - yStart) / yInterval + 1;

	int switchX = CaseCondition(x);	
	int switchY = CaseCondition(y);	

	AmericanOption copy = AmericanOption(optType, T, K, sig, r, S, b);

	switch (switchX)
	{
	case 1: copy.Exp(xStart); break;
	case 2: copy.Strike(xStart); break;
	case 3: copy.Sig(xStart); break;
	case 4: copy.rfr(xStart); break;
	case 5: copy.Spot(xStart); break;
	}

	switch (switchY)
	{
	case 1: copy.Exp(yStart); break;
	case 2: copy.Strike(yStart); break;
	case 3: copy.Sig(yStart); break;
	case 4: copy.rfr(yStart); break;
	case 5: copy.Spot(yStart); break;
	}

	vector<vector<double>> vec(rows, vector<double>(columns));
	for (int i = 0; i < rows; i++)	
	{
		for (int j = 0; j < columns; j++)						
		{
			vec[i][j] = copy.MasterPrice(output);
			copy.Increment(switchY, yInterval);	
		}
		copy.Increment(switchX, xInterval);	
		copy.Increment(switchY, -yInterval * columns);	

	}
	return vec;
}

void AmericanOption::MeshArrayPrint(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval)
{
	vector<vector<double>> vec = MeshArray(output, x, y, xStart, xEnd, xInterval, yStart, yEnd, yInterval);
	int rows = (xEnd - xStart) / xInterval + 1;
	int columns = (yEnd - yStart) / yInterval + 1;
	cout << ToString() << endl;
	cout << "\t\t";
	for (int i = 0; i < columns; i++)
	{
		cout << yStart << "\t\t";
		yStart += yInterval;
	}
	cout << endl;

	for (int i = 0; i < rows; i++)
	{
		cout << xStart << "\t\t";
		xStart += xInterval;
		for (int j = 0; j < columns; j++)
		{
			cout << setprecision(4) << vec[i][j] << "\t\t";	
		}
		cout << endl;
	}
}

// This is a supporting function and will increment the data by 1 interval size
void AmericanOption::Increment(int condition, double intervalSize)
{
	int input = condition;
	switch (input)
	{
	case 1:	// Increment T by interval size
		Exp(T + intervalSize);
		break;
	case 2:	// Increment K by interval size
		Strike(K + intervalSize);
		break;
	case 3:	// Increment sig by interval size
		Sig(sig + intervalSize);
		break;
	case 4:	// Increment r by interval size
		rfr(r + intervalSize);
		break;
	case 5:	// Increment S by interval size
		Spot(S + intervalSize);
		break;
	default: // Increment b by interval size
		Carry(b + intervalSize);
		break;
	}
}

// Return the correct type as an integer
int AmericanOption::CaseCondition(string input) const
{
	if (input == "T") { return 1; }
	else if (input == "K") { return 2; }
	else if (input == "sig") { return 3; }
	else if (input == "r") { return 4; }
	else if (input == "S") { return 5; }
	else if (input == "b") { return 6; }
	else { cout << "Please enter valid syntax: T, K, sig, r, S, b"; exit; }
}

string AmericanOption::Type() const
{
	return optType;
}

void AmericanOption::Type(string input)
{
	if (input == "C" || input == "P")
	{
		optType = input;
	}
	else
	{
		cout << "Invalid input, please enter \"C\" or \"P\". No change is made with this execution." << endl;
	}
}

double AmericanOption::Exp() const
{
	return T;
}

void AmericanOption::Exp(double input)
{
	T = input;
}

double AmericanOption::Strike() const
{
	return K;
}

void AmericanOption::Strike(double input)
{
	K = input;
}

double AmericanOption::Sig() const
{
	return sig;
}

void AmericanOption::Sig(double input)
{
	sig = input;
}

double AmericanOption::rfr() const
{
	return r;
}

void AmericanOption::rfr(double input)
{
	r = input;
}

double AmericanOption::Spot() const
{
	return S;
}

void AmericanOption::Spot(double input)
{
	S = input;
}

double AmericanOption::Carry() const
{
	return b;
}

void AmericanOption::Carry(double input)
{
	b = input;
}

void AmericanOption::Unam(string input)
{
	unam = input;
}

string AmericanOption::Unam() const
{
	return unam;
}

AmericanOption& AmericanOption::operator = (const AmericanOption& option2)
{
	if (this == &option2) return *this;
	copy(option2);
	return *this;
}

string AmericanOption::ToString() const
{
	stringstream strs;	
	strs << "Type: " << optType << ", T: " << T << ", K: " << K << ", sig: " << sig << ", r: " << r << ", S: " << S << ", b: " << b << ", unam: " << unam;
	return strs.str();
}

#endif

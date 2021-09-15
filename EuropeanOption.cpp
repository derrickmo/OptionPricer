#ifndef EuropeanOption_cpp
#define EuropeanOption_cpp

#include "EuropeanOption.hpp"
#include "Array.cpp"
#include <boost/math/distributions.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>

// Establish default situaiton for default constructor. To allow user to change default value, the implementation is static, not #define.
static string default_optType = "C";
static double default_T = 1.0;
static double default_K = 100;
static double default_sig = 0.2;
static double default_r = 0.05;
static double default_S = 100;	
static double default_b = 0.05;	

void EuropeanOption::init()	
{	// Initialise all default values
	r = default_r;
	sig = default_sig;
	K = default_K;
	T = default_T;
	b = default_b;
	S = default_S;
	optType = default_optType;
}

void EuropeanOption::copy(const EuropeanOption& o)
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

EuropeanOption::EuropeanOption()
{ // Default call option
	init();
}

// Option constructor without type initiation - Use colon syntax
EuropeanOption::EuropeanOption(double Exp, double Strike, double Sig, double rfr, double Spot) : T(Exp), K(Strike), sig(Sig), r(rfr), S(Spot)
{
	optType = "C";
	b = r;
}

// Option constructor with type initiation - Cannot use colon syntax due to if/else type detection
EuropeanOption::EuropeanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot)
{
	// Control the input, if other string is entered, set them as call option
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

// Option constructor with type initiation - Cannot use colon syntax due to if/else type detection
EuropeanOption::EuropeanOption(string type, double Exp, double Strike, double Sig, double rfr, double Spot, double Carry)
{
	// Control the input, if other string is entered, set them as call option
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

EuropeanOption::EuropeanOption(const EuropeanOption& o)
{ // Copy constructor
	copy(o);
}

// Destructor
EuropeanOption::~EuropeanOption()
{
}

double EuropeanOption::Price() const
{
	// tmp, d1 and d2 are the same for both call and put options
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;	// Calculate d1
	double d2 = d1 - tmp;											// Calculate d2

	if (optType == "C")
	{
		return (S * exp((b - r) * T) * N(d1)) - (K * exp(-r * T) * N(d2)); // Calculate call price
	}
	else
	{
		return (K * exp(-r * T) * N(-d2)) - (S * exp((b - r) * T) * N(-d1)); // Calculate put price
	}
}

double EuropeanOption::MasterPrice(string input) const
{
	if (input == "Price") { return Price(); }					// Call price function
	else if (input == "CallDelta") { return CallDelta(); }		// Call call delta function
	else if (input == "PutDelta") { return PutDelta(); }		// Call Put Delta function
	else { return Gamma(); }									// Reminaing item is Gamma
}

double EuropeanOption::ParityPrice() const
{
	if (optType == "C")		// If it's a call
	{
		EuropeanOption pairedPrice = EuropeanOption("P", T, K, sig, r, S);		// Create a paired put using the same input
		return pairedPrice.Price() + S - K * exp(-r * T);						// Calculate pairedPrice using parity formula
	}
	else                   // If it's a put
	{
		EuropeanOption pairedPrice = EuropeanOption("C", T, K, sig, r, S);		// Create a paired put using the same input
		return pairedPrice.Price() - S + K * exp(-r * T);						// Calculate pairedPrice using parity formula
	}
}

bool EuropeanOption::ParityCheck() const
{
	if (abs(Price() - ParityPrice()) < 0.000001)								// If the price difference is less than 0.000001, return true
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Call delta function
double EuropeanOption::CallDelta() const
{
	double tmp = sig * sqrt(T);				
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return exp((b - r) * T) * N(d1);
}

double EuropeanOption::PutDelta() const	
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp; 
	return exp((b - r) * T) * (N(d1) - 1.0);
}

double EuropeanOption::Gamma() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return n(d1) * exp((b-r)*T) / (S * sig * sqrt(T));
}

Array<vector<double>> EuropeanOption:: CPArray(double start, double end, double interval)
{
	int size = (end - start) / interval + 1; 
	Array<vector<double>> arr(size); // Establish an array of vector with size
	EuropeanOption copy = EuropeanOption("C", T, K, sig, r, S);
	for (int i = 0; i < size; i++)
	{
		// vector stores 3 objects: Stock price, call price and put price
		copy.Spot(start + interval * i);	
		copy.Type("C");	
		double callPrice = copy.Price();
		copy.Type("P");	
		double putPrice = copy.Price();	
		arr.setElement(i, vector<double> {copy.Spot(), callPrice, putPrice});	// Create a vector<double> with three contents
	}
	return arr;
}

void EuropeanOption::CPArrayPrint(double start, double end, double interval)
{
	Array<vector<double>> arr = CPArray(start, end, interval);
	cout << "Spot\tCall\t\tPut" << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.getElement(i)[0] << "\t" << arr.getElement(i)[1] << "\t\t" << arr.getElement(i)[2] << endl;	// print out by order
	}
}

vector<vector<double>> EuropeanOption::MeshArray(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval)
{
	int rows = (xEnd - xStart) / xInterval + 1;			// Calculate number of rows required. Always +1 to include the last element
	int columns = (yEnd - yStart) / yInterval + 1;		// Calculate number of columns required. Always +1 to include the last element

	int switchX = CaseCondition(x);	// Set switch x
	int switchY = CaseCondition(y);	// Set switch y

	EuropeanOption copy = EuropeanOption(optType, T, K, sig, r, S);

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

	vector<vector<double>> vec(rows,vector<double>(columns));			// Establish an array of vector with size
	for (int i = 0; i < rows; i++)										// Loop row by row
	{
		for (int j = 0; j < columns; j++)								// Loop column by column
		{
			vec[i][j] = copy.MasterPrice(output);						// Call out master price which will call the appropriate price. Output is the initial type enetered
			copy.Increment(switchY, yInterval);							// Increment the input so it can calculate again
		}
		copy.Increment(switchX, xInterval);								// Increment x means it goes to next row
		copy.Increment(switchY, -yInterval * columns);					// Increment negative number to back to first column

	}
	return vec;
}

void EuropeanOption::MeshArrayPrint(string output, string x, string y, double xStart, double xEnd, double xInterval, double yStart, double yEnd, double yInterval)
{
	vector<vector<double>> vec = MeshArray(output, x, y, xStart, xEnd, xInterval, yStart, yEnd, yInterval);
	int rows = (xEnd - xStart) / xInterval + 1;			// Rows
	int columns = (yEnd - yStart) / yInterval + 1;		// Columns
	cout << ToString() << endl;
	cout << "\t\t";
	for (int i = 0; i < columns; i++)		// Populate column header
	{
		cout << yStart << "\t\t";
		yStart += yInterval;
	}
	cout << endl;

	for (int i = 0; i < rows; i++)			// Loop row by row
	{
		cout << xStart << "\t\t";
		xStart += xInterval;
		for (int j = 0; j < columns; j++)	// Loop column by column
		{
			cout << setprecision(4) << vec[i][j] << "\t\t";		// Set precision to 4 for print quality only. The array still consists real double number.
		}
		cout << endl;
	}
}

// This is a supporting function and will increment the data by 1 interval size
void EuropeanOption::Increment(int condition, double intervalSize)
{
	int input = condition;
	switch (input)
	{
	case 1:							// Increment T by interval size
		Exp(T + intervalSize); 
		break;			
	case 2:							// Increment K by interval size
		Strike(K + intervalSize); 
		break;	
	case 3:							// Increment sig by interval size
		Sig(sig + intervalSize); 
		break;			
	case 4:							// Increment r by interval size
		rfr(r + intervalSize); 
		break;
	case 5:							// Increment S by interval size
		Spot(S + intervalSize); 
		break;
	default:						// Increment b by interval size
		Carry(b + intervalSize); 
		break;	
	}
}

// This is a supporting function and will return the correct type as an integer
int EuropeanOption::CaseCondition(string input) const
{
	if (input == "T") { return 1; }
	else if (input == "K") { return 2; }
	else if (input == "sig") { return 3; }
	else if (input == "r") { return 4; }
	else if (input == "S") { return 5; }
	else if (input == "b") { return 6; }
	else { cout << "Please enter valid syntax: T, K, sig, r, S, b"; exit; }
}

double EuropeanOption::DiffDelta(double h) const
{
	EuropeanOption SPlush = EuropeanOption("C", T, K, sig, r, S + h);		// This is V(S+h)
	EuropeanOption SMInush = EuropeanOption("C", T, K, sig, r, S - h);		// This is V(S-h)
	return (SPlush.Price() - SMInush.Price()) / (2 * h);					// Return result directly
}

double EuropeanOption::DiffGamma(double h) const
{
	EuropeanOption SZero = EuropeanOption("C", T, K, sig, r, S + h);		// This is V(S+h)
	EuropeanOption SPlush = EuropeanOption("C", T, K, sig, r, S + h);		// This is V(S)
	EuropeanOption SMInush = EuropeanOption("C", T, K, sig, r, S - h);		// This is V(S+h)
	return (SPlush.Price() - 2 * SZero.Price() + SMInush.Price()) / (h * h);// Return directly
}

/*
	Below are getter and setter functions
*/

string EuropeanOption::Type() const
{
	return optType;
}

void EuropeanOption::Type(string input)
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

double EuropeanOption::Exp() const
{
	return T;
}

void EuropeanOption::Exp(double input)
{
	T = input;
}

double EuropeanOption::Strike() const
{
	return K;
}

void EuropeanOption::Strike(double input)
{
	K = input;
}

double EuropeanOption::Sig() const
{
	return sig;
}

void EuropeanOption::Sig(double input)
{
	sig = input;
}

double EuropeanOption::rfr() const
{
	return r;
}

void EuropeanOption::rfr(double input)
{
	r = input;
}

double EuropeanOption::Spot() const
{
	return S;
}

void EuropeanOption::Spot(double input)
{
	S = input;
}

double EuropeanOption::Carry() const
{
	return b;
}

void EuropeanOption::Carry(double input)
{
	b = input;
}

void EuropeanOption::Unam(string input)
{
	unam = input;
}

string EuropeanOption::Unam() const
{
	return unam;
}

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)
{
	if (this == &option2) return *this;
	copy(option2);
	return *this;
}

// Modifier functions
void EuropeanOption::Toggle()
{ // Change option type (C/P, P/C)

	if (optType == "C")
	{
		Type("P");		// Calling type setter function. Note it will automatically calculate call/put prices
	}
	else
	{
		Type("C");
	}
}

string EuropeanOption::ToString() const
{
	stringstream strs;
	strs << "Type: " << optType << ", T: " << T << ", K: " << K << ", sig: " << sig << ", r: " << r << ", S: " << S << ", b: " << b << ", unam: " << unam;
	return strs.str();
}

#endif

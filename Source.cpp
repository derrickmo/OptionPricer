#include "EuropeanOption.hpp"
#include "AmericanOption.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

int main()
{ 	
	// Test constructors
	cout << "Testing constructors:" << endl;
	EuropeanOption constructorTest1 = EuropeanOption();															// Default constructor
	cout << "Test1: " << constructorTest1.ToString() << "and price is " << constructorTest1.Price() << endl;
	EuropeanOption constructorTest2 = EuropeanOption(0.75, 95, 0.2, 0.05, 120);									// Constructor w/o type. Default Call
	cout << "Test2: " << constructorTest2.ToString() << "and price is " << constructorTest2.Price() << endl;
	EuropeanOption constructorTest3 = EuropeanOption("P",1.25, 145, 0.1, 0.02, 150);							// Constructor with type
	cout << "Test3: " << constructorTest3.ToString() << "and price is " << constructorTest3.Price() << endl;
	EuropeanOption constructorTest4 = EuropeanOption(constructorTest3);											// Copy constructor
	cout << "Test4: " << constructorTest4.ToString() << "and price is " << constructorTest4.Price() << endl;
	EuropeanOption constructorTest5 = EuropeanOption("Invalid input", 1.25, 145, 0.1, 0.02, 150);				// Constructor with invalid type input
	cout << "Test5: " << constructorTest5.ToString() << "and price is " << constructorTest5.Price() << endl << endl;

	// Test getter and setter function
	cout << "Testing constructors:" << endl;
	EuropeanOption gsTest = EuropeanOption();
	cout << "gsTest: " << gsTest.ToString() << "and price is " << gsTest.Price() << endl;
	gsTest.Type("P");
	cout << "New type is: " << gsTest.Type() << endl;
	gsTest.Exp(2);
	cout << "New T is: " << gsTest.Exp() << endl;
	gsTest.Strike(250);
	cout << "New Strike is: " << gsTest.Strike() << endl;
	gsTest.Sig(0.3);
	cout << "New Sigma is: " << gsTest.Sig() << endl;
	gsTest.rfr(0.02);
	cout << "New Risk-free rate is: " << gsTest.rfr() << endl;
	gsTest.Spot(300);
	cout << "New Spot is: " << gsTest.Spot() << endl;
	gsTest.Carry(0.03);
	cout << "New Carry is: " << gsTest.Carry() << endl;
	gsTest.Unam("c++ is awesome!!!");
	cout << "New unam is: " << gsTest.Unam() << endl;
	cout << "New price is: " << gsTest.Price() << endl;
	cout << "Final gsTest: " << gsTest.ToString() << "and price is " << gsTest.Price() << endl << endl;

	// Test for question a
	cout << "Test for question A1.a" << endl;
	EuropeanOption Batch1_C = EuropeanOption(0.25, 65, 0.30, 0.08, 60);
	EuropeanOption Batch2_C = EuropeanOption(1.0, 100, 0.2, 0.0, 100);
	EuropeanOption Batch3_C = EuropeanOption(1.0, 10, 0.50, 0.12, 5);
	EuropeanOption Batch4_C = EuropeanOption(30, 100, 0.30, 0.08, 100);
	EuropeanOption Batch1_P = EuropeanOption("P",0.25, 65, 0.30, 0.08, 60);
	EuropeanOption Batch2_P = EuropeanOption("P", 1.0, 100, 0.2, 0.0, 100);
	EuropeanOption Batch3_P = EuropeanOption("P", 1.0, 10, 0.50, 0.12, 5);
	EuropeanOption Batch4_P = EuropeanOption("P", 30, 100, 0.30, 0.08, 100);
	cout << "Batch 1's call price is " << Batch1_C.Price() << " and put price is " << Batch1_P.Price() << endl;
	cout << "Batch 2's call price is " << Batch2_C.Price() << " and put price is " << Batch2_P.Price() << endl;
	cout << "Batch 3's call price is " << Batch3_C.Price() << " and put price is " << Batch3_P.Price() << endl;
	cout << "Batch 4's call price is " << Batch4_C.Price() << " and put price is " << Batch4_P.Price() << endl << endl;

	//Test for question b
	cout << "Test for question A1.b" << endl;
	cout << "Batch 1's call price is " << Batch1_C.Price() << ", partiy price is " << Batch1_C.ParityPrice() << " and parity check is " << Batch1_C.ParityCheck() << endl;
	cout << "Batch 2's call price is " << Batch2_C.Price() << ", partiy price is " << Batch2_C.ParityPrice() << " and parity check is " << Batch2_C.ParityCheck() << endl;
	cout << "Batch 3's call price is " << Batch3_C.Price() << ", partiy price is " << Batch3_C.ParityPrice() << " and parity check is " << Batch3_C.ParityCheck() << endl;
	cout << "Batch 4's call price is " << Batch4_C.Price() << ", partiy price is " << Batch4_C.ParityPrice() << " and parity check is " << Batch4_C.ParityCheck() << endl;
	cout << "Batch 1's put price is " << Batch1_P.Price() << ", partiy price is " << Batch1_P.ParityPrice() << " and parity check is " << Batch1_P.ParityCheck() << endl;
	cout << "Batch 2's put price is " << Batch2_P.Price() << ", partiy price is " << Batch2_P.ParityPrice() << " and parity check is " << Batch2_P.ParityCheck() << endl;
	cout << "Batch 3's put price is " << Batch3_P.Price() << ", partiy price is " << Batch3_P.ParityPrice() << " and parity check is " << Batch3_P.ParityCheck() << endl;
	cout << "Batch 4's put price is " << Batch4_P.Price() << ", partiy price is " << Batch4_P.ParityPrice() << " and parity check is " << Batch4_P.ParityCheck() << endl << endl;

	//Test for question c
	cout << "Test for question A1.c" << endl;
	Batch1_C.CPArrayPrint(60, 70, 1);
	cout << endl;

	//Test for question d
	cout << "Test for question A1.d" << endl;
	cout << "Rows: T from 0.1 to 1.0, Columns: S from 60 to 65" << endl;
	Batch1_C.MeshArrayPrint("Price","T", "S", 0.1, 0.5, 0.05, 60, 65, 1);
	cout << endl << "Rows: S from 60 to 65, Columns: T from 0.05 to 0.3" << endl;
	Batch1_P.MeshArrayPrint("Price", "S", "T", 60, 65, 1, 0.05, 0.30, 0.05);
	cout << endl << "Rows: r from 0.15 to 0.25, Columns: K from 70 to 130" << endl;
	Batch2_C.MeshArrayPrint("Price", "r", "K", 0.15, 0.25, 0.01, 70, 130, 10);
	cout << endl;

	//Test for question a
	cout << "Test for question A2.a" << endl;
	EuropeanOption testA2a = EuropeanOption("C", 0.5, 100, 0.36, 0.1, 105, 0);		// All input constructor
	cout << testA2a.ToString() << endl;
	cout << "This option's call delta is " << testA2a.CallDelta() << endl;			//Call Delta
	testA2a.Toggle();																// Convert to put
	cout << "This option's put delta is " << testA2a.PutDelta() << endl;				// Put Delta
	cout << "This option's gamma is " << testA2a.Gamma() << endl << endl;			// Gamma

	// Test for question b/c
	cout << "Test for question A2.b/c" << endl;
	cout << "PutDelta:" << endl;
	testA2a.MeshArrayPrint("PutDelta", "r", "K", 0.06, 0.14, 0.02, 96, 104, 2);
	testA2a.Toggle();																// Convert to put
	cout << "\nCallDelta:" << endl;
	testA2a.MeshArrayPrint("CallDelta", "r", "K", 0.06, 0.14, 0.02, 96, 104, 2);
	cout << "\nGamma:" << endl; 
	testA2a.MeshArrayPrint("Gamma", "r", "K", 0.06, 0.14, 0.02, 96, 104, 2);
	cout << endl;

	// Test for question d
	cout << "Test for question A2.d" << endl;
	double h_input = 20;
	double result_D = Batch1_C.CallDelta();
	double result_G = Batch1_C.Gamma();
	cout << "Delta using formula is " << Batch1_C.CallDelta() << endl;
	cout << "Gamma using formula is " << Batch1_C.Gamma() << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setprecision(6) << "With h =" << h_input << " and delta is "  << Batch1_C.DiffDelta(h_input) 
			<< " and the difference is " << Batch1_C.DiffDelta(h_input)-result_D << endl;
		cout << setprecision(6) << "With h =" << h_input << " and gamma is " << Batch1_C.DiffGamma(h_input) 
			<< " and the difference is " << Batch1_C.DiffGamma(h_input) - result_G << endl;
		h_input *= 0.5;
	}
	cout << endl;

	// Test for question a/b
	AmericanOption Amer_C = AmericanOption("C", 0.5, 100, 0.1, 0.1, 110, 0.02);
	AmericanOption Amer_P = AmericanOption("P", 0.5, 100, 0.1, 0.1, 110, 0.02);
	cout << Amer_C.ToString() << endl;
	cout << "American Call's price is " << Amer_C.Price() << endl;
	cout << Amer_P.ToString() << endl;
	cout << "American Put's price is " << Amer_P.Price() << endl << endl;

	// Test for question c/d
	Amer_C.CPArrayPrint(90, 110, 2);
	cout << endl;
	cout << "Rows: S from 85 to 115, Columns: K from 90 to 110" << endl;
	Amer_C.MeshArrayPrint("Price", "S", "K", 85, 115, 5, 90, 110, 5);
	cout << endl << "Rows: S from 85 to 115, Columns: T from 90 to 110" << endl;
	Amer_P.MeshArrayPrint("Price", "S", "K", 85, 115, 5, 90, 110, 5);

	return 0;
}

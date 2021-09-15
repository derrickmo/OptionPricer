#ifndef Option_cpp
#define Option_cpp

#include "EuropeanOption.hpp"
#include "Array.cpp"
#include <boost/math/distributions.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>

static int id_s = 1;

Option::Option()
{
	id = id_s;
	id++;
}

Option::~Option()
{
}

double Option::n(double x) const
{
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

double Option::N(double x) const
{ // The approximation to the cumulative normal distribution
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return cdf(myNormal, x);
}

int Option::ID() const
{
	return id;
}

double Option::Book() const
{
	return book;
}

double Option::Quan() const
{
	return quan;
}

string Option::Source() const
{
	return source;
}

void Option::Source(string input)
{
	source = input;
}

string Option::FI() const
{
	return fi;
}

void Option::FI(string input)
{
	fi = input;
}

string Option::Dep() const
{
	return dep;
}

void Option::Dep(string input)
{
	dep = input;
}


#endif
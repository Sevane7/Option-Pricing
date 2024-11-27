#include "Option.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>


Option::Option(double expiry)
{
	if (expiry < 0)
	{
		throw std::invalid_argument("Date must be positive.");
	}

	_expiry = expiry;
}

double Option::getExpiry() const
{
	return _expiry;
}

 bool Option::isAsianOption() const
{
	return false;
}

 bool Option::isAmericanOption() const
{
	return false;
}

double Option::payoffPath(const std::vector<double>& prices) const
{
	if (prices.empty())
	{
		throw std::invalid_argument("Price vector cannot be empty.");
	}

	return payoff(prices.back()); // Retourne la dernière valeur du vecteur
}
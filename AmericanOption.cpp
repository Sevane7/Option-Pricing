#include "AmericanOption.h"
#include <stdexcept>

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry) {
	if (strike < 0) {
		throw std::invalid_argument("Can't be negative.");
	}
	_strike = strike;

};
double AmericanOption::getStrike() const {

	return _strike;
}

bool AmericanOption::isAmericanOption() const{
	return true;
}
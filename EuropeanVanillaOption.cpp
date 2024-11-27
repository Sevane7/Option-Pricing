#include "EuropeanVanillaOption.h"
#include <stdexcept>  

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry) {
	if (strike < 0) {
		throw std::invalid_argument("Can't be negative.");
	}
	_strike = strike;

};
double EuropeanVanillaOption::getStrike() const {

	return _strike;
}

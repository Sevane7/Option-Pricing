#include "EuropeanDigitalOption.h"
#include <stdexcept>  

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry) {
	if (strike < 0) {
		throw std::invalid_argument("The strike can't be negative.");
	}
	_strike = strike;

};
double EuropeanDigitalOption::getStrike() const {

	return _strike;
}
#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry, strike) {};
double EuropeanDigitalPutOption::payoff(double assetPrice) const {
	double strike = getStrike();
	if (assetPrice <= strike) {
		return 1;
	}
	else {
		return 0;
	}
}
EuropeanDigitalPutOption::optionType EuropeanDigitalPutOption::GetOptionType() const {
	return Put;
};
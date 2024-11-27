#include "CallOption.h"

CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {};


double CallOption::payoff(double underlyingPrice) const {
	double strike = getStrike();
	if (underlyingPrice >= strike) {
		return (underlyingPrice - strike);
	}
	else return 0.0;
};

EuropeanVanillaOption::optionType CallOption::GetOptionType() const {
	return Call;
};

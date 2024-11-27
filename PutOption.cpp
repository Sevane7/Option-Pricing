#include "PutOption.h"

PutOption::PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike) {};

double PutOption::payoff(double underlyingPrice) const {
	double strike = getStrike();
	if (underlyingPrice <= strike) {
		return(strike - underlyingPrice);
	}
	else return 0.0;
};

EuropeanVanillaOption::optionType PutOption::GetOptionType() const { return Put; };

#include "AmericanCallOption.h"


AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike) {};

double AmericanCallOption::payoff(double assetPrice) const {
	double strike = getStrike();
	if (assetPrice >= strike) {
		return assetPrice-strike;
	}
	else {
		return 0;
	}
}

AmericanCallOption::optionType AmericanCallOption::GetOptionType() const {
	return Call;
};
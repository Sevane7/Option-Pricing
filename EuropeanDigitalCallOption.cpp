#include "EuropeanDigitalCallOption.h"


EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike) :
	EuropeanDigitalOption(expiry, strike) {};


double EuropeanDigitalCallOption::payoff(double assetPrice) const
{
	double strike = getStrike();

	if (assetPrice >= strike)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

EuropeanDigitalCallOption::optionType EuropeanDigitalCallOption::GetOptionType() const
{
	return Call;
};

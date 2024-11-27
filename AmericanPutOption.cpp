#include "AmericanPutOption.h"


AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike) {};


double AmericanPutOption::payoff(double assetPrice) const
{
	double strike = getStrike();

	if (assetPrice <= strike)
	{
		return (strike - assetPrice);
	}
	else
	{
		return 0.0;
	}
}

AmericanPutOption::optionType AmericanPutOption::GetOptionType() const
{
	return Put;
};
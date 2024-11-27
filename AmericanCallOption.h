#pragma once
#include "AmericanOption.h"
class AmericanCallOption : public AmericanOption
{
public:
	AmericanCallOption(double expiry, double strike);

	double payoff(double assetPrice) const override;

	optionType GetOptionType() const override;

};





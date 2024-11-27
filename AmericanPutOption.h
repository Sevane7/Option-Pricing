#pragma once
#include "AmericanOption.h"
class AmericanPutOption : public AmericanOption
{

public:
	AmericanPutOption(double expiry, double strike);

	double payoff(double assetPrice) const override;

	optionType GetOptionType() const override;
};


#pragma once
#include "EuropeanDigitalOption.h"
class EuropeanDigitalCallOption : public EuropeanDigitalOption
{
public :
	EuropeanDigitalCallOption(double expiry, double strike);
	double payoff(double assetPrice) const override;
	optionType GetOptionType() const override;


};


#pragma once
#include "EuropeanDigitalOption.h"
class EuropeanDigitalPutOption : public EuropeanDigitalOption
{
public:
	EuropeanDigitalPutOption(double expiry, double strike);
	double payoff(double assetPrice) const override;
	optionType GetOptionType() const override;


};


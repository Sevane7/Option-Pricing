#pragma once

#include "Option.h"

class EuropeanVanillaOption : public Option {
private:
	double _strike;


public:
	EuropeanVanillaOption(double expiry, double strike);

	enum optionType {
		Call,
		Put
	};
	virtual optionType GetOptionType() const = 0;
	double getStrike() const;
	//virtual ~EuropeanVanillaOption() {}
	friend class BlackScholesPricer;
	friend class BlackScholesMCPricer;

};
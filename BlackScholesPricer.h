#pragma once

#include "Option.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
class BlackScholesPricer {
private:
	Option* _option;	
	double _asset_price;
	double _interest_rate;
	double _vol;

public:
	BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility);

	double operator()() const;

	double delta() const;
};

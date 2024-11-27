#include "BlackScholesPricer.h"
#include <cmath>
#include<iostream>



BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
	: _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _vol(volatility) {};

/// <summary>
/// Compute the cumulative distribution function of the normal law for a given value x
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
double cNorDis(double x) {
	return 0.5 * (1.0 + erf(x / std::sqrt(2.0)));
}
/// <summary>
/// Compute the price of an option regarding the Black Scholes formula for european vanilla option (call,put) and digital option (call,put)
/// </summary>
/// <returns></returns>
double BlackScholesPricer:: operator()()const {
	double T = _option->getExpiry();
	double d1;
	double d2;
	// We take an option and we apply different formula depending on its type
	if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) { //We try to convert _option into an EuropeanVanillaOption* and if it is done then vanillaOption is the result
		double K = vanillaOption->_strike; // We can access to that via the friend class in the .h
		d1 = (std::log(_asset_price / K) + (_interest_rate + 0.5 * _vol * _vol) * T) / (_vol * std::sqrt(T));
		d2 = d1 - _vol * std::sqrt(T);
		if (vanillaOption->GetOptionType() == EuropeanVanillaOption::Call) {
			return _asset_price * cNorDis(d1) - K * std::exp(-_interest_rate * T) * cNorDis(d2); // Payoff vanilla call
		}
		else {
			return K * std::exp(-_interest_rate * T) * cNorDis(-d2) - _asset_price * cNorDis(-d1);// Payoff vanilla put
		}
	}
	else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {
		double K = digitalOption->_strike;  // We can access to that via the friend class in the .h
		d1 = (std::log(_asset_price / K) + (_interest_rate + 0.5 * _vol * _vol) * T) / (_vol * std::sqrt(T));
		d2 = d1 - _vol * std::sqrt(T);

		if (digitalOption->GetOptionType() == EuropeanDigitalOption::Call) {
			return std::exp(-_interest_rate * T) * cNorDis(d2);  // Payoff digital call
		}
		else {
			return std::exp(-_interest_rate * T) * cNorDis(-d2);  // Payoff digital put
		}
	}
	return 0; //If the option type is unknown, we return nothing

}
/// <summary>
/// Compute the pdf of a N(0,1) for the delta. We define pi like that because the CMath library wasn't working for us
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
double pdf(double x) {
	double pi = 3.14159265358979323846;
	return (1 / std::sqrt(2 * pi)) * std::exp(-0.5 * x * x);  
}
/// <summary>
/// This method compute the delta for the european vanilla option (call,put) and digital option (call,put).
/// </summary>
/// <returns></returns>
double BlackScholesPricer::delta() const {
	double T = _option->getExpiry();
	double d1,d2;

	if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(_option)) {		
		double K = vanillaOption->_strike; // We can access to that via the friend class in the .h
		d1 = (std::log(_asset_price / K) + (_interest_rate + 0.5 * _vol * _vol) * T) / (_vol * std::sqrt(T));
		d2 = d1 - _vol * std::sqrt(T);
		if (vanillaOption->GetOptionType() == EuropeanVanillaOption::Call) {
			return cNorDis(d1);  // Formula of delta for a vanilla call
		}
		else {
			return cNorDis(d1) - 1;  // Formula of delta for a vanilla put
		}
	}
	else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)) {		
		double K = digitalOption->_strike;  // We can access to that via the friend class in the .h
		d2 = (std::log(_asset_price / K) + (_interest_rate - 0.5 * _vol * _vol) * T) / (_vol * std::sqrt(T));
		double discountFactor = std::exp(-_interest_rate * T);
		if (digitalOption->GetOptionType() == EuropeanDigitalOption::Call) {
			return discountFactor * pdf(d2) / (_asset_price * _vol * std::sqrt(T));  // Formula of delta for a digital call
		}
		else {
			return -discountFactor * pdf(d2) / (_asset_price * _vol * std::sqrt(T));  // Formula of delta for a digital put
		}
	}

	// Return 0 if the option is unvalid
	return 0.0;
}


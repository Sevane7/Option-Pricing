#pragma once
#include "Option.h"
class EuropeanDigitalOption : public Option
{
private :
	double _strike;


public :
	EuropeanDigitalOption(double expiry, double strike);
	enum optionType {
		Call, Put
	};
	virtual optionType GetOptionType() const = 0;
	double getStrike() const;	
	friend class BlackScholesPricer;
		


};


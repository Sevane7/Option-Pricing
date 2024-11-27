#pragma once
#include "Option.h"
class AmericanOption : public Option
{
private:
	double _strike;

public :
	AmericanOption(double expiry, double strike);

	enum optionType {
		Call,
		Put
	};
	virtual optionType GetOptionType() const = 0;

	double getStrike() const;

	bool isAmericanOption() const override;
	
	friend class BlackScholesPricer;


};


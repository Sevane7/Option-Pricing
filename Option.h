#pragma once
#include <vector>


class Option
{
private:

	double _expiry;

public:

	Option(double expiry);

	double getExpiry() const;

	virtual double payoff(double underlyingPrice) const = 0;

	virtual ~Option() {};

	virtual bool isAsianOption() const  ;

	virtual bool isAmericanOption() const;

	virtual double payoffPath(const std::vector<double>& prices) const ;

};
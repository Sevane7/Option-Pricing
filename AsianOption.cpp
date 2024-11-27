#include "AsianOption.h"
#include "Option.h"
#include <stdexcept>


AsianOption::AsianOption(const std::vector<double>& timeSteps, double strike, double expiry) : Option(expiry)
{
    _timeSteps = timeSteps;

    if (strike < 0)
    {
        throw std::invalid_argument("Can't be negative.");
    }

    _strike = strike;
}


const std::vector<double>& AsianOption::getTimeSteps() const
{
    return _timeSteps;
}

double AsianOption::getStrike() const
{
    return _strike;
}

bool AsianOption::isAsianOption() const 
{
    return true;
}
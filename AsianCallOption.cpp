#include <vector>
#include "AsianCallOption.h"


AsianCallOption::AsianCallOption(const std::vector<double>& timeSteps, double strike) : AsianOption(timeSteps, strike) {}


double AsianCallOption::payoff(double price) const
{
    return 0;
}


/// <summary>
/// The payoff of an asian option is the mean of the prices computed on every path - the strike for a call. 
/// That's why the payoff of the asian is 0, because we only use the payoffPath for the computation.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
double AsianCallOption::payoffPath(const std::vector<double>& path) const
{
    
    double sum = 0.0;

    for (double price : path)
    {
        sum += price;
    }

    double averagePrice = sum / path.size();
    if (averagePrice >= getStrike()) {
        return averagePrice - getStrike();
    }
    else { return 0; }
}

AsianCallOption::optionType AsianCallOption::GetOptionType() const
{
    return Call;
}


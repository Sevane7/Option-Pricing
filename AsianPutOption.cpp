#include "AsianPutOption.h"
#include <vector>
#include <numeric>


AsianPutOption::AsianPutOption(const std::vector<double>& timeSteps, double strike) : AsianOption(timeSteps, strike) {}


double AsianPutOption::payoff(double price) const
{    
    return 0;
}

/// <summary>
/// The payoff of an asian option is the strike - the mean of the prices computed on every path for a put. 
/// That's why the payoff of the asian is 0, because we only use the payoffPath for the computation.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
double AsianPutOption::payoffPath(const std::vector<double>& path) const
{
    // Calculer la moyenne des prix dans le chemin
    double sum = 0.0;

    for (double price : path)
    {
        sum += price;
    }

    double averagePrice = sum / path.size();
    if (averagePrice <= getStrike()) {
        return getStrike()-averagePrice;
    }
    else { return 0; }
}


AsianPutOption::optionType AsianPutOption::GetOptionType() const
{
    return Put;
}

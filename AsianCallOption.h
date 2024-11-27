#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption
{
private :
    double _strike;
    std::vector<double> _timeSteps;

public:

    AsianCallOption(const std::vector<double>& timeSteps, double strike);

    double payoff(double price) const override;

    double payoffPath(const std::vector<double>& path) const override;

    optionType GetOptionType() const override;

};
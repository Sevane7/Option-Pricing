#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption {

public:

    AsianPutOption(const std::vector<double>& timeSteps, double strike);

    double payoff(double price) const override;

    double payoffPath(const std::vector<double>& path) const override;

    optionType GetOptionType() const override;

};
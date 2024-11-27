#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option {

private:

    double _strike;

    std::vector<double> _timeSteps;

public:

    AsianOption(const std::vector<double>& timeSteps, double strike, double expiry = 1.0);

    const std::vector<double>& getTimeSteps() const;

    enum optionType {

        Call,

        Put
    };

    virtual optionType GetOptionType() const = 0;

    double getStrike() const;

    friend class BlackScholesPricer;       

    bool isAsianOption() const override; //We override this function to avoid issues like the computation of the wrong payoff

};
#pragma once
#include "Option.h" 
#include <vector>

class BlackScholesMCPricer
{

private:
    Option* _option;               
    double _initial_price;         
    double _interest_rate;         
    double _volatility;            
    int _nbPaths = 1;              //We generate at least one path    
    std::vector<double> prices;
    double _current_price = 0;      //Initialization to 0
    double _sum_payoff = 0;        //Initialization to 0
    double _sum_payoff_squares = 0;  //Initialization to 0

public:

    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    
    void generate(int nb_paths);

    
    double operator()() const;

    
    int getNbPaths() const;

    
    std::vector<double> confidenceInterval();
};
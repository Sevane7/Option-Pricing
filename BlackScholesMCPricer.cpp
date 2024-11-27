#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include "Option.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <iostream>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility) {}


int BlackScholesMCPricer::getNbPaths() const
{
    return _nbPaths;
}
/// <summary>
/// Method for the computation of a Monte-Carlo Black Scholes Pricer.
/// We choose to define a vector of vector for the simulated prices because if the option is asian, the price is compute with a 
/// vector. First we check if the option is European (vanilla of digital) and if it is the case, we compute the payoff of it.
/// If the option is Asian, we cast the option to have access to its method and we add its prices to the simulated prices to
/// apply the method payoffPath to it. When the computation is done, we change our current price with the formula given in the
/// statement
/// </summary>
/// <param name="nb_paths"></param>
void BlackScholesMCPricer::generate(int nb_paths) {
    double S = _initial_price;
    double T = _option->getExpiry();
    double r = _interest_rate;
    double sigma = _volatility;

    // Pré-calculs pour éviter les répétitions
    double drift = (r - 0.5 * sigma * sigma) * T;
    double diffusion = sigma * sqrt(T);

    // Vérification des types d'options en dehors de la boucle
    bool isAsian = _option->isAsianOption();
    AsianOption* asianOption = isAsian ? dynamic_cast<AsianOption*>(_option) : nullptr;

    _nbPaths += nb_paths;  // Mise à jour du nombre total de chemins simulés

    for (int k = 0; k < nb_paths; k++) {
        double payoff = 0.0;

        if (!isAsian) {
            // Simulation pour les options Vanilla ou Digital
            double z = MT::rand_norm();  // Variable aléatoire
            double S_T = S * exp(drift + diffusion * z);  // Prix simulé à maturité
            payoff = _option->payoff(S_T);  // Calcul du payoff
        }
        else {
            // Simulation pour les options asiatiques
            std::vector<double> t = asianOption->getTimeSteps();
            std::vector<double> prices;  // Stocke les prix simulés à chaque timestep

            // Premier timestep
            double z = MT::rand_norm();
            double first_price = S * exp((r - 0.5 * sigma * sigma) * t[0] + sigma * sqrt(t[0]) * z);
            prices.push_back(first_price);

            // Simulation des autres timesteps
            for (size_t j = 1; j < t.size(); j++) {
                z = MT::rand_norm();  // Nouvelle variable aléatoire pour chaque pas de temps
                double dt = t[j] - t[j - 1];
                double S_t = prices.back() * exp((r - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * z);
                prices.push_back(S_t);
            }

            payoff = _option->payoffPath(prices);  // Calcul du payoff sur la trajectoire
        }

        // Mise à jour des sommes pour le calcul du prix et de la variance
        _sum_payoff += payoff;
        _sum_payoff_squares += payoff * payoff;
    }

    // Calcul du prix actuel actualisé
    _current_price = exp(-r * T) * _sum_payoff / _nbPaths;
}



double BlackScholesMCPricer::operator()() const
{
    if (_nbPaths == 0)
    {
        throw std::runtime_error("Price estimate is undefined. No paths generated.");
    }

    return _current_price;
}


/// <summary>
/// This method compute the 95% confidence interval of our current price. We apply the formula for a N(0,1) distribution, 
/// with a z=1,96 for a 95% confidence interval
/// </summary>
/// <returns></returns>
std::vector<double> BlackScholesMCPricer::confidenceInterval()
{
    if (_nbPaths == 0)
    {
        throw std::runtime_error("Cannot calculate confidence interval. No paths generated.");
    }
    /*
    double stddev = std::sqrt(_current_price / _nbPaths);

    double margin_of_error = 1.96 * stddev / std::sqrt(_nbPaths); // 1.96 pour un intervalle de confiance à 95%

    return { _current_price - margin_of_error, _current_price + margin_of_error };
    */
    double var = (_sum_payoff_squares / _nbPaths) - pow(_sum_payoff / _nbPaths, 2);
    double lower_bound = _current_price - 1.96 * sqrt(var / _nbPaths);
    double upper_bound = _current_price + 1.96 * sqrt(var / _nbPaths);
    std::vector<double> ci = { lower_bound, upper_bound };
    return ci;
}

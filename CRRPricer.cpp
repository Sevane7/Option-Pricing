#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

/// <summary>
/// When we create a CRR Pricer, we check if the input option is Asian because the CRR can't deal with this kind of option. We also
/// check if there is no arbitrage and then we create the tree related to the pricer with the input depth.
/// </summary>
/// <param name="option"></param>
/// <param name="depth"></param>
/// <param name="asset_price"></param>
/// <param name="up"></param>
/// <param name="down"></param>
/// <param name="interest_rate"></param>
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
	: _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(depth), _exercise_condition(depth)
{

	if (option->isAsianOption()) throw std::invalid_argument("Option Asiatique impossible pour ce pricer.");

	checkArbitrage();

	_tree.setDepth(depth);

	_exercise_condition.setDepth(depth);
}
/// <summary>
/// This is the same constructor but without the up, down and interest rate in input so we compute them but our own.
/// </summary>
/// <param name="option"></param>
/// <param name="depth"></param>
/// <param name="asset_price"></param>
/// <param name="r"></param>
/// <param name="volatility"></param>
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
	: _option(option), _depth(depth), _asset_price(asset_price), _tree(depth), _exercise_condition(depth)
{

	if (option->isAsianOption()) throw std::invalid_argument("Option Asiatique impossible pour ce pricer.");

	

	double T = _option->getExpiry();

	double h = T / depth;


	_up = std::exp((r + 0.5 * volatility * volatility) * h + volatility * std::sqrt(h)) - 1;

	_down = std::exp((r + 0.5 * volatility * volatility) * h - volatility * std::sqrt(h)) - 1;

	_interest_rate = std::exp(r * h) - 1;

	checkArbitrage();
	

	_tree.setDepth(depth);

	_exercise_condition.setDepth(depth);


}

/// <summary>
/// We check if the interest rate is above the down and under the up because if it not the case, there is an arbitrage.
/// </summary>
void CRRPricer::checkArbitrage() const
{
	bool cond1 = _down < _interest_rate;
	bool cond2 = _interest_rate < _up;

	bool condition = cond1 && cond2;

	if (condition == false) throw std::invalid_argument("Il faut que down < interest rate < up");
}
/// <summary>
/// We compute the CRR Pricer with the formula given in the subject
/// </summary>
void CRRPricer::compute()
{
	double q = (_interest_rate - _down) / (_up - _down);

	// Etape 1 : Initiation de la dernière ligne des arbres (n = _depth)
	// _tree avec le payoff des stock price (formule donnée)
	// _exercise_condition avec false
	for (int i = 0; i <= _depth; ++i)
	{
		double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i);

		double payoff = _option->payoff(stock_price);

		_tree.setNode(_depth, i, payoff);

		_exercise_condition.setNode(_depth, i, false);
	}

	// Etape 2 : 
	// On remplit les H(n, i) avec la formule donnée par H(n + 1, i)
	

	for (int n = _depth - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);			

			// Valeur continue (attendue) de l'option
			double continious_value = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate);
			
			_tree.setNode(n, i, continious_value);
			if (_option->isAmericanOption())
			{
				double intrinsic_value = _option->payoff(stock_price);

				_tree.setNode(n, i, std::max(continious_value, intrinsic_value));

				_exercise_condition.setNode(n, i, intrinsic_value >= continious_value);
			}			

		}
	}
}


double CRRPricer::get(int n, int i) const
{
	return _tree.getNode(n, i);
}

bool CRRPricer::getExercise(int n, int i) const
{
	return _exercise_condition.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form)
{
	if (closed_form)
	{
		double q = (_interest_rate - _down) / (_up - _down);

		double option_price = 0.0;

		for (int i = 0; i <= _depth; i++)
		{
			double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i);

			double payoff = _option->payoff(stock_price);

			double binom_coef = std::tgamma(_depth + 1) / (std::tgamma(_depth - i + 1) * std::tgamma(i + 1));

			option_price += binom_coef * pow(q, i) * pow(1 - q, _depth - i) * payoff;
		}

		return option_price / pow(1 + _interest_rate, _depth);
	}
	else
	{
		compute();
		return get(0, 0);
	}
}


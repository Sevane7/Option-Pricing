#pragma once

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer
{

private:
	Option* _option;
	int _depth;
	double _asset_price;
	double _up;
	double _down;
	double _interest_rate;
	BinaryTree<double> _tree;
	BinaryTree<bool> _exercise_condition;
	void checkArbitrage() const;

public:
	CRRPricer(Option* option,
		int depth,
		double asset_price,
		double up,
		double down,
		double interest_rate);

	CRRPricer(Option* option,
		int depth,
		double asset_price,
		double r,
		double volatility);

	void compute();

	double get(int n, int i) const;

	double operator()(bool closed_form = false);

	bool getExercise(int n, int i) const;
};









/*
#include <cmath>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
	: _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(depth)
{
	checkArbitrage();

	_tree.setDepth(depth);
}

void CRRPricer::checkArbitrage() const
{
	bool cond1 = _down < _interest_rate;
	bool cond2 = _interest_rate < _up;

	bool condition = cond1 && cond2;

	if (!condition) throw std::invalid_argument("Il faut que down < interest rate < up");
}

void CRRPricer::compute()
{
	double q = (_interest_rate - _down) / (_up - _down);

	// Etape 1 : on remplit les noeuds de _tree (n = _depth) avec le payoff des stock price (formule donnée)
	for (int i = 0; i <= _depth; ++i)
	{
		double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i);

		double payoff = _option->payoff(stock_price);

		_tree.setNode(_depth, i, payoff);
	}

	// Etape 2 : maintenant que l'on connait les H(n + 1, i), on remplit les H(n, i) avec la formule donnée
	for (int n = _depth - 1; n >= 0; --n)
	{
		for (int i = 0; i < n; ++i)
		{
			double H_n_i = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate);

			_tree.setNode(n, i, H_n_i);
		}
	}
}

double CRRPricer::get(int n, int i) const
{
	return _tree.getNode(n, i);
}


/// <summary>
/// If Closed form is true we compute the nodes with the given formula, otherwise we use compute()
/// </summary>
/// <param name="closed_form"></param>
/// <returns>Returns option price at the recine</returns>
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

			double binom_coef = std::tgamma(_depth + 1) / (std::tgamma(_depth - i) * std::tgamma(i));

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
*/

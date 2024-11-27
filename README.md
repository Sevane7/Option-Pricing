# Options Pricing Project

This project implements a variety of options pricing models in C++ using object-oriented programming (OOP). The goal is to price different types of financial options using different pricing methods. The project includes the Black-Scholes model (with both formula-based and Monte Carlo simulation) and the Cox-Ross-Rubinstein (CRR) binomial tree model.

## Features
- **Black-Scholes (Formula)**: Price options based on the Black-Scholes formula.
- **Black-Scholes (Monte Carlo)**: Price Option using Monte Carlo simulation with the Black-Scholes formula.
- **CRR (Binomial Tree)**: Price option with an implementation of the CRR binomial model.
- **Option Types (Call & Put)**: 
  - European Vanilla Options 
  - Digital Options
  - American Options
  - Asian Options

## Object-Oriented Design
The project follows OOP principles:
- **Option Class**: The base class that defines common properties and methods for all options.
- **Call/Put Classes**: Derived classes for Call and Put options, implementing specific pricing logic for each type.
- **Inheritance**: The project demonstrates inheritance with different option types extending the base `Option` class.

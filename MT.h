#pragma once
#include <random>
#include <mutex>

class MT {

private:

    static std::mt19937 generator; // Instance statique du générateur de nombres aléatoires

    static std::mutex mtx;          // Mutex pour la protection des accès concurrents

    // Constructeur privé pour éviter la création d'instances
    MT() = default;

public:
    // Méthode pour obtenir un nombre aléatoire uniforme dans [0, 1]
    static double rand_unif();

    // Méthode pour obtenir un nombre aléatoire normalement distribué N(0, 1)
    static double rand_norm();
};

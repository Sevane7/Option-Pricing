#pragma once
#include <random>
#include <mutex>

class MT {

private:

    static std::mt19937 generator; // Instance statique du g�n�rateur de nombres al�atoires

    static std::mutex mtx;          // Mutex pour la protection des acc�s concurrents

    // Constructeur priv� pour �viter la cr�ation d'instances
    MT() = default;

public:
    // M�thode pour obtenir un nombre al�atoire uniforme dans [0, 1]
    static double rand_unif();

    // M�thode pour obtenir un nombre al�atoire normalement distribu� N(0, 1)
    static double rand_norm();
};

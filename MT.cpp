#include "MT.h"

// Initialisation de l'instance statique du g�n�rateur grace � un g�n�rateur de nombres al�atoires
std::mt19937 MT::generator(std::random_device{}());

// Mutex pour la protection des acc�s concurrents
std::mutex MT::mtx;

// M�thode pour obtenir un nombre al�atoire uniforme dans [0, 1]
double MT::rand_unif()
{
    std::lock_guard<std::mutex> lock(mtx); // Protection de l'acc�s concurrent

    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // Distribution uniforme

    return distribution(generator); // G�n�re et retourne le nombre al�atoire
}

// M�thode pour obtenir un nombre al�atoire normalement distribu� N(0, 1)
double MT::rand_norm()
{
    std::lock_guard<std::mutex> lock(mtx); // Protection de l'acc�s concurrent

    static std::normal_distribution<double> distribution(0.0, 1.0); // Distribution normale

    return distribution(generator); // G�n�re et retourne le nombre al�atoire
}

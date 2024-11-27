#include "MT.h"

// Initialisation de l'instance statique du générateur grace à un générateur de nombres aléatoires
std::mt19937 MT::generator(std::random_device{}());

// Mutex pour la protection des accès concurrents
std::mutex MT::mtx;

// Méthode pour obtenir un nombre aléatoire uniforme dans [0, 1]
double MT::rand_unif()
{
    std::lock_guard<std::mutex> lock(mtx); // Protection de l'accès concurrent

    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // Distribution uniforme

    return distribution(generator); // Génère et retourne le nombre aléatoire
}

// Méthode pour obtenir un nombre aléatoire normalement distribué N(0, 1)
double MT::rand_norm()
{
    std::lock_guard<std::mutex> lock(mtx); // Protection de l'accès concurrent

    static std::normal_distribution<double> distribution(0.0, 1.0); // Distribution normale

    return distribution(generator); // Génère et retourne le nombre aléatoire
}

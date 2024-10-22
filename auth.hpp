#ifndef AUTH_HPP
#define AUTH_HPP

#include <iostream>
#include <fstream>
#include <string>

// Fonction qui vérifie si l'utilisateur est connecté
bool isAuthenticated() {
    std::ifstream sessionFile("/tmp/session_auth.txt");
    std::string sessionStatus;

    if (sessionFile.is_open()) {
        sessionFile >> sessionStatus;
        sessionFile.close();
    }

    // Si l'utilisateur n'est pas authentifié, retourner false
    if (sessionStatus != "connected") {
        return false;
    }
    return true;
}

// Fonction pour rediriger l'utilisateur vers la page de connexion
void redirectToLogin() {
    std::cout << "Status: 302 Found\r\n";
    std::cout << "Location: ../index.html\r\n\r\n";
}

#endif // AUTH_HPP


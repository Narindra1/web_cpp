#include <iostream>
#include <fstream>
#include <string>
#include "Utils.hpp"
#include "auth.hpp" // Inclure le fichier d'authentification

int main() {
    // Vérifier si l'utilisateur est connecté
    if (!isAuthenticated()) {
        redirectToLogin();
        return 0; // Terminer l'exécution si non authentifié
    }
        // Désactiver le cache pour empêcher la navigation avec "Précédent"
    std::cout << "Cache-Control: no-store, no-cache, must-revalidate\r\n";
    std::cout << "Pragma: no-cache\r\n";
    std::cout << "Expires: 0\r\n";
    Utils utils;
    std::cout << "Content-Type: text/html; charset=UTF-8\n\n";
    std::string fileName = "data.txt";
    utils.display(fileName);
    return 0;
}

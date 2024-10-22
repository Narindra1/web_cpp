#include <iostream>
#include <cstdio>
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

    // Supprimer le fichier de session pour déconnecter l'utilisateur
    std::remove("/tmp/session_auth.txt");

    // Rediriger vers la page de connexion
    std::cout << "Status: 302 Found\r\n";
    std::cout << "Location: ../index.html\r\n\r\n";

    return 0;
}

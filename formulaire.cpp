#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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

    std::cout << "Content-Type: text/html; charset=UTF-8\n\n";
    std::cout << "<html><body>"
                << "<h1>Bienvenue sur la page d'accueil</h1>"
                << "<a href=\"logout.cgi\">Déconnexion</a>"
                << "<form method=\"POST\" action=\"adduser.cgi\">"
                << "    <label for=\"name\">Name:</label><input type=\"text\" name=\"name\" required><br>"
                << "    <label for=\"surname\">Surname:</label><input type=\"text\" name=\"surname\" required><br>"
                << "    <label for=\"address\">Address:</label><input type=\"text\" name=\"address\" required><br>"
                << "    <label for=\"email\">Email:</label><input type=\"email\" name=\"email\" required><br>"
                << "    <label for=\"birthDate\">Birth Date:</label><input type=\"date\" name=\"birthDate\" required><br>"
                << "    <label for=\"birthPlace\">Birth Place:</label><input type=\"text\" name=\"birthPlace\" required><br>"
                << "    <input type=\"submit\" value=\"Add User\">"
                << "</form>"
                << "<a href=\"view.cgi\">View User List</a>"
                << "</body>"
                << "</html>";
    return 0;

}
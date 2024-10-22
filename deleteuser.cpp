#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Utils.hpp"
#include <cstdlib>
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

    // Récupérer la requête envoyée (GET)
    std::string query_string = std::getenv("QUERY_STRING");
    std::vector<std::string> pairs = utils.split(query_string, '&');
    std::string name_to_delete;
    int i = 0;
    for (const auto& pair : pairs) {
        std::vector<std::string> keyValue = utils.split(pair, '=');
        
        if (keyValue.size() == 2 && keyValue[0] == "name") {
            name_to_delete = utils.urlDecode(keyValue[1]);
            break;
        }
        i++;
    }

    // Si aucun nom n'a été trouvé dans la requête, on arrête
    if (name_to_delete.empty()) {
        std::cout << "<html><body><h2>Error: No name provided</h2></body></html>";
        return 1;
    }

    // Lire le fichier existant
    std::ifstream infile("data.txt");
    std::ofstream outfile("temp.txt");
    std::string line;
    bool user_deleted = false;

    while (std::getline(infile, line)) {
        std::vector<std::string> userData = utils.split(line, ',');
        if (!userData.empty()) {
            if (userData[0] == name_to_delete) {
                user_deleted = true;
                continue;  // Ne pas écrire cette ligne dans le fichier temporaire
            }

        }
        outfile<<line<<"\n";
    }

    infile.close();
    outfile.close();

    // Remplacer l'ancien fichier par le nouveau
    std::ofstream saveData("data.txt");
    std::ifstream mvData("temp.txt");
    std::string save;
    while (std::getline(mvData, save)) {
        saveData<<save<<"\n";
    }
    saveData.close();
    mvData.close();




    // Afficher le résultat
    std::cout << "<html><body>";
    if (user_deleted) {
        utils.display("data.txt");
    } else {
        std::cout << "<h2>User '" << name_to_delete << "' not found</h2>";
    }
    std::cout << "</body></html>";

    return 0;
}

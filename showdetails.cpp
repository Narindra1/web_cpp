#include <iostream>
#include <fstream>
#include "Utils.hpp"
#include <sstream>
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
    
    // Lire le paramètre name depuis l'URL
    std::string query = std::getenv("QUERY_STRING");
    std::string decoded_query_string = utils.urlDecode(query);
    std::vector<std::string> params = utils.split(decoded_query_string, '&');
    std::string name;

    for (const auto& param : params) {
        std::vector<std::string> keyValue = utils.split(param, '=');
        if (keyValue.size() == 2 && keyValue[0] == "name") {
            name = keyValue[1];
        }
    }

    std::ifstream file("data.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(name) != std::string::npos) {
            std::vector<std::string> userDetails = utils.split(line, ',');
            if (userDetails.size() >= 6) {
                std::cout << "<html><body><h2>User Details</h2>\n"
                        <<"<table border=\"2\" cellpadding=\"2\" cellspacing=\"5\">"
                        << "<tr>"
                        << "<th>name</th>"
                        << "<th>surname</th>"
                        << "<th>address</th>"
                        << "<th>Email</th>"
                        << "<th>birth date</th>"
                        << "<th>birth place</th>"
                        << "</tr>"
                        << "<tr>"
                        << "<td>"<< userDetails[0] << "</td>"
                        << "<td>"<< userDetails[1] << "</td>"
                        << "<td>"<< userDetails[2] << "</td>"
                        << "<td>"<< userDetails[3] << "</td>"
                        << "<td>"<< userDetails[4] << "</td>"
                        << "<td>"<< userDetails[5] << "</td>"
                        << "</tr>"
                        << "</table>\n"
                        << "</body></html>";
                break;
            }
        }
    }
    return 0;
}



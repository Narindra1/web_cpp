#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
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

    std::map<std::string, std::string> formData = utils.getFormData();
    std::string query_string = std::getenv("QUERY_STRING") ? std::getenv("QUERY_STRING") : "";
    std::string decoded_query_string = utils.urlDecode(query_string);
    std::vector<std::string> queryPairs = utils.split(decoded_query_string, '=');
    std::string nameToEdit;
    bool isEditing = !formData.empty();

    if (isEditing) {
        nameToEdit = formData["original_name"];
    } else if (queryPairs.size() == 2 && queryPairs[0] == "name") {
        nameToEdit = queryPairs[1];
    }

    std::string filePath = "data.txt";
    std::string tempFilePath = "temporaire.txt";

    std::ifstream file(filePath);
    std::ofstream tempFile(tempFilePath);
    std::string line;
    bool found = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Erreur d'ouverture des fichiers." << std::endl;
        return 1;
    }
    bool verify = false;
    while (std::getline(file, line)) {
        std::vector<std::string> userData = utils.split(line, ',');
        
        if (userData[0] == nameToEdit) {
            found = true;
            if (isEditing && !formData["name"].empty() && !formData["surname"].empty() &&
                !formData["address"].empty() && !formData["email"].empty() &&
                !formData["birthdate"].empty() && !formData["birthplace"].empty() &&
                utils.isAlpha(formData["name"]) && utils.isAlpha(formData["surname"]) &&
                utils.mailCheck(formData["email"]) && utils.checkDate(formData["birthdate"])) {
                tempFile << formData["name"] << ","
                         << formData["surname"] << ","
                         << formData["address"] << ","
                         << formData["email"] << ","
                         << formData["birthdate"] << ","
                         << formData["birthplace"] << "\n";
                         verify = true;
            } 
            else 
            {
                utils.displayUpdate(userData);
                tempFile << line << "\n";
            }
        } else {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (isEditing) {
        if (found) {
            std::ifstream stock(tempFilePath);
            std::ofstream users(filePath);
            std::string parLigne;
            while (std::getline(stock, parLigne)) {
                users << parLigne << "\n";
            }
            stock.close();
            users.close();
            if(verify)
            {
                std::cout << "<p style='color:green;'>Modification avec succès.</p>";
                std::cout << "<a href='/cgi-bin/viewdetails.cgi'>Revenir</a>";
            }
            else if(!verify)
            {
                std::cout << "<p style='color:red;'>echec de modification.</p>";
                std::cout << "<a href='/cgi-bin/viewdetails.cgi'>Revenir</a>";
            }
        } else {
            std::cout << "<p>Utilisateur non trouvé.</p>";
        }
    }

    return 0;
}

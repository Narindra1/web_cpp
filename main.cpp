#include <iostream>
#include <fstream>
#include "Utils.hpp"
#include <string>
#include <cctype>
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
    std::cout << "Content-Type: text/html\n\n";

    // Lire les données POST envoyées par le formulaire
    std::map<std::string, std::string> formData = utils.getFormData();

    // Récupérer les informations spécifiques
    std::string name = utils.getFormValue("name", formData);
    std::string surname = utils.getFormValue("surname", formData);
    std::string address = utils.getFormValue("address", formData);
    std::string email = utils.getFormValue("email", formData);
    std::string birthDate = utils.getFormValue("birthDate", formData);
    std::string birthPlace = utils.getFormValue("birthPlace", formData);

    // Vérifier que les données sont complètes avant de les enregistrer
    if (!name.empty() && !surname.empty() && !address.empty() && !email.empty() && !birthDate.empty() && !birthPlace.empty()) {
        // Ouvrir le <fichier data.txt en mode append
        // //////////////////////////////////
        std::ifstream dt("data.txt");
        std::ofstream tp("tp.txt");
        int i=0;
        std::string append;
        std::string append2;
        int j=0;
        while (std::getline(dt, append)) {
            i = i+1;
            std::vector<std::string> userDetails = utils.split(append, ',');
            if (userDetails[3] != email){
                j=j+1;
            }
            else
            {
                continue;
            }
            tp<<append;
        }
        dt.close();
        tp.close();


        // /////////////////////////////////////////
        std::ofstream dataFile("data.txt", std::ios::app);
        if (dataFile.is_open() && i==j && utils.isAlpha(name) && utils.isAlpha(surname) && utils.mailCheck(email) && utils.checkDate(birthDate)) {
            // Enregistrer les données dans le fichier
            if(i==0)
            {
                dataFile << name << "," << surname << "," << address << "," << email << "," << birthDate << "," << birthPlace;
            }
            else if(i==1)
            {
                dataFile <<"\n"<< name << "," << surname << "," << address << "," << email << "," << birthDate << "," << birthPlace << "\n";
            }
            else
            {
                dataFile << name << "," << surname << "," << address << "," << email << "," << birthDate << "," << birthPlace << "\n";
            }
            dataFile.close();

            // Rediriger vers la page de visualisation des utilisateurs
            std::cout << "<html><body>";
            std::cout << "<h2>User added successfully!</h2>";
            std::cout << "<a href='/cgi-bin/view.cgi'>View User List</a>";
            std::cout << "</body></html>";
        } else if(!utils.isAlpha(name) || !utils.isAlpha(surname))
        {
                utils.displayFormWithError("Le nom ou le prenom ne peut pas valider. Veuillez entrer un nom valide.");
        }
        else if(i!=j)
        {
                utils.displayFormWithError("cet email existe deja.");
        }
        else if(!utils.mailCheck(email))
        {
                utils.displayFormWithError("la terminaison de mail incorrecte.");
        }
        else if(!utils.checkDate(birthDate))
        {
                utils.displayFormWithError("vieillez verifier votre date de naissance.");
        }

    } else {
        // En cas de données manquantes
        utils.displayFormWithError("Errer! il y a des cases vides .");
        
    }

    return 0;
}


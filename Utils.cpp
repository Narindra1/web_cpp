#include "Utils.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <fstream>

// Constructeur
Utils::Utils() {}

// Destructeur
Utils::~Utils() {}

// Fonction pour découper une chaîne de caractères selon un délimiteur
std::vector<std::string> Utils::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Décoder les chaînes encodées en URL
std::string Utils::urlDecode(const std::string& str) {
    std::string result;
    char ch;
    int i, j;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            result += ch;
            i += 2;
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

// Récupérer les données du formulaire
std::map<std::string, std::string> Utils::getFormData() {
    std::map<std::string, std::string> formData;
    std::string queryString;
    std::getline(std::cin, queryString);  // Lire les données POST du formulaire
    
    std::vector<std::string> pairs = split(queryString, '&');
    for (const std::string& pair : pairs) {
        size_t pos = pair.find('=');
        if (pos != std::string::npos) {
            std::string key = urlDecode(pair.substr(0, pos));
            std::string value = urlDecode(pair.substr(pos + 1));
            formData[key] = value;
        }
    }
    return formData;
}

// Récupérer une valeur spécifique dans les données du formulaire
std::string Utils::getFormValue(const std::string& key, const std::map<std::string, std::string>& formData) {
    auto it = formData.find(key);
    if (it != formData.end()) {
        return it->second;
    }
    return "";
}

// Vérifier si une chaîne ne contient que des caractères alphabétiques
bool Utils::isAlpha(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isalpha(c); });
}

// Vérifier la validité d'un email
bool Utils::mailCheck(const std::string& email) {
    const std::regex pattern("^[\\w.%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}

// Afficher le formulaire pour mettre à jour un utilisateur
void Utils::displayUpdate(std::vector<std::string> userData) {
    std::cout << "<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body>"
              << "<form method='POST' action=''>"
              << "<input type='hidden' name='original_name' value='" << userData[0] << "' />"
              << "<label>Nom: <input type='text' name='name' value='" << userData[0] << "' /></label><br>"
              << "<label>Prenom: <input type='text' name='surname' value='" << userData[1] << "' /></label><br>"
              << "<label>Adresse: <input type='text' name='address' value='" << userData[2] << "' /></label><br>"
              << "<label>Email: <input type='text' name='email' value='" << userData[3] << "' /></label><br>"
              << "<label>Date de naissance: <input type='text' name='birthdate' value='" << userData[4] << "' /></label><br>"
              << "<label>Lieu de naissance: <input type='text' name='birthplace' value='" << userData[5] << "' /></label><br>"
              << "<input type='submit' value='Update' />"
              << "</form></body></html>";
}

// Afficher le fichier
void Utils::display(const std::string& filename) {
    std::cout << "<html><body><h2>User List</h2>\n";
    
    // Tentative d'ouverture du fichier
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        std::cout << "<p style='color:red;'>Could not open the user data file.</p>";
        std::cout << "</body></html>";
        return;
    }
    
    std::string line;
    std::cout << "<table border=\"3\" cellpadding=\"2\" cellspacing=\"5\">";
    std::cout << "<tr>" 
              << "<th>Name</th>"
              << "<th>Options</th>"  
              << "</tr>\n";

    while (std::getline(file, line)) {
        // Découper la ligne pour extraire les détails de l'utilisateur
        std::vector<std::string> userDetails = split(line, ',');
        
        // Vérifier que les détails de l'utilisateur sont bien présents
        if (userDetails.size() >= 2) {
            std::string name = userDetails[0];
            
            // Affichage du nom et des options "Détails", "Supprimer" et "Modifier"
            std::cout << "<tr>" 
                      << "<td>" << name << "</td>"
                      << "<td>"
                      << "<a href='/cgi-bin/showdetails.cgi?name=" << name << "'>Details</a> "
                      << "<a href='/cgi-bin/deleteuser.cgi?name=" << name << "'>Delete</a> "
                      << "<a href='/cgi-bin/update.cgi?name=" << name << "'>Change</a>"
                      << "</td>"
                      << "</tr>\n";
        }
    }

    std::cout << "</table>\n";
    std::cout << "<br><a href='formulaire.cgi'>Add Another User</a>";
    std::cout << "</body></html>";

    file.close();  // Ne pas oublier de fermer le fichier après lecture
}


// Afficher un formulaire avec un message d'erreur
void Utils::displayFormWithError(const std::string& errorMessage) {
    std::cout << "<html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body>";
    std::cout << "<p style='color:red;'>" << errorMessage << "</p>";
    std::cout << "<form method='POST' action=''>"
              << "<label>Nom: <input type='text' name='name' /></label><br>"
              << "<label>Prenom: <input type='text' name='surname' /></label><br>"
              << "<label>Adresse: <input type='text' name='address' /></label><br>"
              << "<label>Email: <input type='text' name='email' /></label><br>"
              << "<label>Date de naissance: <input type='date' name='birthDate' /></label><br>"
              << "<label>Lieu de naissance: <input type='text' name='birthPlace' /></label><br>"
              << "<input type='submit' value='Submit' />"
              << "</form></body></html>";
}

bool Utils::checkDate(const std::string& birthDate)
{
    std::vector<std::string> date = split(birthDate, '-');
    bool bissextile = false;
    std::vector<int> jours_par_mois = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int year= std::stoi(date[0]);
    int month = std::stoi(date[1]);
    int day = std::stoi(date[2]);
    int valDay =jours_par_mois[month -1];

    if(year%4 ==0)
    {
        if(year%100 ==0 && year%400 !=0)
        {
            //n'est pas bissexitile
            bissextile =false;
        }
        else
        {
            // std::cout<<"est bissexitile";
            bissextile = true;
        }
    }

    if(bissextile)
    {
        jours_par_mois[1] = 29;
        valDay =jours_par_mois[month -1];
    }

        if(year>2010 || year<1950 || month<0 || month>12 || day<0 || day>valDay)
        {
            return false;
        }
    return true;
}

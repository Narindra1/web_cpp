#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {
    std::string username, password;

    // Lire les données POST
    std::string content;
    std::getline(std::cin, content);
    size_t pos = content.find("&");
    if (pos != std::string::npos) {
        username = content.substr(0, pos);
        password = content.substr(pos + 1);
    }
    
    username = username.substr(username.find('=') + 1);
    password = password.substr(password.find('=') + 1);

    // Définir les informations d'authentification
    std::string adminUsername = "admin";
    std::string adminPassword = "password123"; // Utilisez un hachage sécurisé dans un contexte réel

    // Vérifier les informations d'identification
    if (username == adminUsername && password == adminPassword) {
        std::cout << "Status: 302 Found\r\n";
        std::cout << "Location: formulaire.cgi\r\n\r\n";
        std::ofstream sessionFile("/tmp/session_auth.txt");
        if (sessionFile.is_open()) {
            sessionFile << "connected"; // Ecrire "connected" dans le fichier
            sessionFile.close();
        } else {
            std::cout << "Content-Type: text/plain\r\n\r\n";
            std::cout << "Erreur : Impossible d'ouvrir le fichier de session.";
            return 1;
        }

    } else {
        std::cout << "Content-Type: text/html\r\n\r\n";
        std::cout << "<html><body><p>Nom d'utilisateur ou mot de passe incorrect</p>";
        std::cout << "<a href='../index.html'>Retour à la connexion</a></body></html>";
    }

    return 0;
}


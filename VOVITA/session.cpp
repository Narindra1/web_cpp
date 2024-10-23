#include "../hpp/session.hpp"
SessionManager::SessionManager(const std::string& file) : filename(file) {}

void SessionManager::writeSession(const std::string& email) {
    std::ofstream outFile("session.txt", std::ios::app); // Append mode
    if (outFile.is_open()) {
        outFile << email << " connected" << std::endl;
        outFile.close();
        std::cout << "Log written successfully." << std::endl;
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}

    // Lecture pour vérifier si l'email existe
bool SessionManager::emailExists(const std::string& targetEmail) {
    std::ifstream inFile("session.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find(targetEmail) != std::string::npos) {
                inFile.close();
                return true; // L'email existe
            }
        }
        inFile.close();
    } else {
        std::cerr << "Error opening file for reading!" << std::endl;
    }
    return false; // L'email n'existe pas
}

    // Suppression de la ligne contenant l'email défini
void SessionManager::deleteEmail(const std::string& targetEmail) {
    std::ifstream inFile("session.txt");
    std::vector<std::string> lines;
    
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find(targetEmail) == std::string::npos) {
                lines.push_back(line); // Conserve les lignes qui ne contiennent pas l'email
            }
        }
        inFile.close();
    } else {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    // Écriture des lignes restantes dans le fichier
    std::ofstream outFile("session.txt");
    if (outFile.is_open()) {
        for (const auto& l : lines) {
            outFile << l << std::endl; // Réécrit les lignes restantes
        }
        outFile.close();
        std::cout << "Deleted entries for: " << targetEmail << std::endl;
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}


    //SessionManager session;

    // Exemple d'utilisation
    // session.writeSession("rakoto@gmail.com");
    // session.writeSession("john@example.com");

    // if (session.emailExists("rakoto@gmail.com")) {
    //     std::cout << "Email found!" << std::endl;
    // } else {
    //     std::cout << "Email not found!" << std::endl;
    // }

    // session.deleteEmail("rakoto@gmail.com");

    // if (!session.emailExists("rakoto@gmail.com")) {
    //     std::cout << "Email successfully deleted!" << std::endl;
    // }

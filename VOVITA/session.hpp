#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class SessionManager {
public:
    string filename;
    SessionManager(const std::string& file);

    // Écriture dans le fichier
    void writeSession(const std::string& email);

    // Lecture pour vérifier si l'email existe
    bool emailExists(const std::string& targetEmail);

    // Suppression de la ligne contenant l'email défini
    void deleteEmail(const std::string& targetEmail) ;        
};

#endif

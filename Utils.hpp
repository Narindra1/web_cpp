#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <map>
#include <vector>

class Utils 
{
    public:
        std::vector<std::string> split(const std::string& s, char delimiter);
        std::string urlDecode(const std::string& str);
        std::map<std::string, std::string> getFormData();
        std::string getFormValue(const std::string& key, const std::map<std::string, std::string>& formData);
        void display(const std::string& filename);
        void displayFormWithError(const std::string& errorMessage);
        void displayUpdate(std::vector<std::string> userData);
        bool isAlpha(const std::string& str);
        bool mailCheck(const std::string& email);
        bool checkDate(const std::string& birthDate);

        Utils();
        ~Utils();
};

#endif // UTILS_HPP


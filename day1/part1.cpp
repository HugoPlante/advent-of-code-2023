#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

std::vector<std::string> lireFichier(const std::string &nomFichier) {
    std::vector<std::string> lignes;
    std::string ligne;
    std::ifstream fichier(nomFichier);

    if (fichier.is_open()) {
        while (getline(fichier, ligne)) {
            lignes.push_back(ligne);
        }
        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    }

    return lignes;
}

int trouverIndexPremierChiffre(const std::string &mot) {
    for (int i = 0; i <= mot.length(); ++i) {
        if (std::isdigit(mot[i])) {
            return i;
        }
    }

    return -1;
}

int trouverIndexDeuxiemeChiffre(const std::string &mot) {
    for (int i = mot.length() - 1; i >= 0; --i) {
        if (std::isdigit(mot[i])) {
            return i;
        }
    }

    return -1;
}

int sommeDesNombresDansLesStrings(const std::vector<std::string> &lignes) {
    int total = 0;

    for (const auto &ligne: lignes) {
        int indexPremierDigit = trouverIndexPremierChiffre(ligne);
        int indexDeuxiemeDigit = trouverIndexDeuxiemeChiffre(ligne);

        if (indexPremierDigit != -1 && indexDeuxiemeDigit != -1) {
            auto d1 = ligne[indexPremierDigit];
            auto d2 = ligne[indexDeuxiemeDigit];

            std::string nombre = std::string() + d1 + d2;

            total += std::stoi(nombre); // Convertit la sous-chaîne en entier
        }
    }

    return total;
}

int main() {
    std::vector<std::string> lignes = lireFichier(
            R"(C:\Users\hugop\Desktop\personal_projects\advent-of-code\day1\input.txt)");

    std::cout << sommeDesNombresDansLesStrings(lignes) << std::endl;

    return 0;
}

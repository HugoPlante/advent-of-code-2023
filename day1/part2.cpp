#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <map>

std::map<std::string, int> chiffresEnTexte = {
        {"zero",  0},
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9}
};

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

int extraireChiffre(const std::string &ligne, int debut, int fin, bool rechercheArriere) {
    for (int i = debut; i != fin; (rechercheArriere ? i-- : i++)) {
        if (std::isdigit(ligne[i])) {
            return ligne[i] - '0';  // Convertir le caractère en chiffre
        }

        // Chercher les chiffres en texte
        for (const auto &paire: chiffresEnTexte) {
            const std::string &mot = paire.first;
            if (ligne.compare(i, mot.length(), mot) == 0) {
                return paire.second;
            }
        }
    }
    return -1;
}

int sommeDesNombresDansLesStrings(const std::vector<std::string> &lignes) {
    int total = 0;

    for (const auto &ligne: lignes) {
        int premierChiffre = extraireChiffre(ligne, 0, ligne.length(), false);
        int dernierChiffre = extraireChiffre(ligne, ligne.length() - 1, -1, true);

        if (premierChiffre != -1 && dernierChiffre != -1) {
            total += premierChiffre * 10 + dernierChiffre;
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

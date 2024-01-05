#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

int MAX_CUBES_ROUGE = 12;
int MAX_CUBES_VERT = 13;
int MAX_CUBES_BLEU = 14;

struct Revelation {
    int rouge;
    int vert;
    int bleu;

    Revelation(int r, int v, int b) : rouge(r), vert(v), bleu(b) {}
};

struct Game {
    int id;
    vector<Revelation> revelations;

    Game(int id) : id(id) {}

    void ajouterRevelation(int rouge, int vert, int bleu) {
        revelations.emplace_back(rouge, vert, bleu);
    }

    bool estValide(int maxRouge, int maxVert, int maxBleu) {
        for (const auto &rev: revelations) {
            if (rev.rouge > maxRouge || rev.vert > maxVert || rev.bleu > maxBleu) {
                return false;
            }
        }
        return true;
    }
};

vector<string> lireFichier(const string &nomFichier) {
    vector<string> lignes;
    string ligne;
    ifstream fichier(nomFichier);

    if (fichier.is_open()) {
        while (getline(fichier, ligne)) {
            lignes.push_back(ligne);
        }
        fichier.close();
    } else {
        cerr << "Impossible d'ouvrir le fichier" << endl;
    }

    return lignes;
}

vector<int> trouverToutesLesGamesValides(vector<Game> &games) {

    vector<int> gamesIds;

    for (Game game: games) {
        if (game.estValide(MAX_CUBES_ROUGE, MAX_CUBES_VERT, MAX_CUBES_BLEU)) {
            gamesIds.push_back(game.id);
        }
    }
    return gamesIds;
}

int trouverTotalGameIDValide(vector<Game> &games) {
    int total = 0;

    for (const auto &id: trouverToutesLesGamesValides(games)) {
        total += id;
    }

    return total;
}

vector<Game> transformerLignesEnGames(vector<string> lignes) {
    std::vector<Game> games;

    for (const auto &ligne: lignes) {
        std::istringstream iss(ligne);
        std::string partie;
        int id;
        iss >> partie >> id; // Lire "Game" et l'ID
        std::getline(iss, partie, ':'); // Ignorer jusqu'à ':'

        Game game(id);

        while (std::getline(iss, partie, ';')) { // Diviser en révélations
            std::istringstream iss_partie(partie);
            std::string revelation;
            while (std::getline(iss_partie, revelation, ',')) { // Diviser en couleurs
                std::istringstream iss_revelation(revelation);
                int nombre;
                std::string couleur;
                iss_revelation >> nombre >> couleur;

                // Assigner les valeurs aux couleurs
                int rouge = 0, vert = 0, bleu = 0;
                if (couleur == "red") rouge = nombre;
                else if (couleur == "green") vert = nombre;
                else if (couleur == "blue") bleu = nombre;
                else std::cerr << "Couleur inconnue: " << couleur << std::endl;

                game.ajouterRevelation(rouge, vert, bleu);
            }
        }
        games.push_back(game);
    }

    return games;
};

int main() {
    vector<string> lignes = lireFichier(
            R"(C:\Users\hugop\Desktop\personal_projects\advent-of-code\day2\input.txt)");

    auto games = transformerLignesEnGames(lignes);

    cout << trouverTotalGameIDValide(games) << endl;

    return 0;
}

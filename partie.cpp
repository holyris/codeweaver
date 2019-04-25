#include "partie.h"

Partie::Partie(Personnage* personnage, std::vector<std::vector<Case*>> cases)
{
    this->personnage = personnage;
    this->cases = cases;
}

Partie::~Partie()
{

}


void Partie::newPartie(std::string difficulty)
{
//    if(difficulty == "easy")
//        std::ifstream file("maps/easy.txt");
//    else if(difficulty == "medium")
//        std::ifstream file("maps/medium.txt");
//    else if(difficulty == "hard"){
//        std::ifstream file("maps/hard.txt");
//    }
    std::ifstream file("maps/easy.txt");

    if(!file) perror ("Error opening file");
    else
    {
        int number_of_lines=0;
        std::string line;
        std::stringstream ss;
        int i = -1;

        //  on compte le nombre de ligne dans le fichier
        while(std::getline(file, line))
            number_of_lines++;

        int rand_line = rand()% (number_of_lines-1);    //  on prend un numero aleatoire entre 0 et number_of_lines
        //boucle pour eviter de reprendre la meme map qu'avant
        while(rand_line == last_rand_line)
            rand_line = rand()% (number_of_lines-1);

        this->last_rand_line = rand_line;
        file.clear();
        file.seekg(std::ios::beg); //   on revient au debut du fichier

        //  on recup la ligne du numero aleatoire
        do{
            std::getline(file, line);
            i++;
        } while(i!=rand_line);

        ss << line;
        //  on complete plateformes
        for(int i = 0; i<8; i++) {
            ss >> plateformes[i];
        }

        //  on complete cristaux
        for(int i = 0; i<8; i++) {
            ss >> cristaux[i];
        }

        //  on set le perso
        for(int i = 0; i<3; i++) {
            if(i == 0)
                ss >> personnage_start_x;
            else if(i==1)
                ss >> personnage_start_y;
            else
                ss >> personnage_start_direction;
        }
        file.close();
        personnage->set(personnage_start_x, personnage_start_y, personnage_start_direction);
        setCases();
    }
}

void Partie::setPersonnage()
{
}


void Partie::setCases()
{
    for(unsigned int i = 0; i < 8; i++){
        for(unsigned int j = 0; j < 8; j++){

            //  si les coord de debut du personnage corresponde a i et j, alors cette case commence avec le personnage
            if(i == personnage_start_y && j == personnage_start_x){
                cases.at(i).at(j)->set(true, personnage_start_direction, false, true);
            }
            else if(((cristaux[i] >> j) & 1) ==1 ){
                cases.at(i).at(j)->set(false, personnage_start_direction, true, true);
            }
            else if(((plateformes[i] >> j) & 1) == 1 ){
                cases.at(i).at(j)->set(false, personnage_start_direction, false, true);
            }

            else {
                cases.at(i).at(j)->set(false, personnage_start_direction, false, false);
            }
        }
    }

}

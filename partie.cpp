#include "partie.h"

Partie::Partie(Personnage* personnage, std::vector<std::vector<Case*>> cases, QGraphicsView *plateau)
{
    this->personnage = personnage;
    this->cases = cases;
    this->plateau = plateau;
    level = 3;
}

Partie::~Partie()
{
    delete personnage;
    for(unsigned int i =0; i<cases.size();i++){
        for(unsigned int j = 0; j<cases.at(i).size(); j++)
            delete cases.at(i).at(j);
    }
}


void Partie::newPartie()
{

    std::ifstream file("maps/maps.txt");

    if(!file) perror ("Error opening file");
    else
    {
        std::string line;
        std::stringstream ss;
        int i = 0;
        int number_of_lines=0;

        //  on compte le nombre de ligne dans le fichier
        while(std::getline(file, line))
            number_of_lines++;
        this->number_of_level = number_of_lines;
        file.clear();
        file.seekg(std::ios::beg); //   on revient au debut du fichier

        //  on recup la ligne du numero
        do{
            std::getline(file, line);
            i++;
        } while(i!=this->level);

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
        personnage->set((plateau->size().width()/8) * personnage_start_x,
                        (plateau->size().height()/8) * personnage_start_y,
                        personnage_start_direction*90);
        setCases();
    }
}



void Partie::setCases()
{
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

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

void Partie::nextLevel()
{
    if(level == number_of_level)
        level = 1;
    else level++;
}

void Partie::previousLevel()
{
    if(level==1)
        level = number_of_level;
    else level--;
}

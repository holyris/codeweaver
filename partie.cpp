#include "partie.h"

Partie::Partie()
{
    level = 1;

    //  rempli cases avec des objets Case
    for(unsigned int i = 0; i < 8; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 8; j++){
            vector.push_back(new Case());
        }
        cases.push_back(vector);
    }
    personnage = new Personnage();
    plateau = new QGraphicsView();
    scene = new QGraphicsScene();

    scene->addItem(personnage);

}

Partie::~Partie()
{
    delete personnage;
    delete plateau;
    delete scene;
    cristaux.clear();
    for(unsigned int i =0; i<cases.size();i++)
        cases.at(i).clear();



}

Personnage* Partie::getPersonnage() const
{
    return this->personnage;
}

std::vector<std::vector<Case *> > Partie::getCases() const
{
    return this->cases;
}

QGraphicsView* Partie::getPlateau() const
{
    return this->plateau;
}

QGraphicsScene *Partie::getScene() const
{
    return this->scene;
}

std::vector<Cristal *> Partie::getCristaux() const
{
    return this->cristaux;
}

int Partie::getLevel() const
{
    return level;
}


void Partie::newPartie()
{
    //on enleve les cristaux deja present de la scene
    for(unsigned int i=0; i<cristaux.size();i++){
        scene->removeItem(cristaux.at(i));
    }
    cristaux.clear();


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
            ss >> plateforme[i];
        }

        //  on complete cristaux
        for(int i = 0; i<8; i++) {
            ss >> cristal[i];
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

            //on set les cristaux aussi
            if(((cristal[i] >> j) & 1) ==1 ){
                cases.at(i).at(j)->set(true);
                Cristal *cristal = new Cristal();
                scene->addItem(cristal);
                cristal->set(
                            (plateau->size().width()/8) * j,
                            (plateau->size().height()/8) * i);
                cristal->setScale( ((plateau->size().height()/8) / cristal->boundingRect().height()) );
                cristaux.push_back(cristal);
            }
            else if(((plateforme[i] >> j) & 1) == 1 ){
                cases.at(i).at(j)->set(true);
            }

            else {
                cases.at(i).at(j)->set(false);
            }
        }
    }

}

void Partie::nextLevel()
{
    if(level == number_of_level)
        level = 1;
    else level++;
    plateau->update();
}

void Partie::previousLevel()
{
    if(level==1)
        level = number_of_level;
    else level--;
    plateau->update();

}

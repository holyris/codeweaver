#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{
    srand (time(NULL));



//    int plateformes[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
//    int cristaux[8] = {1,0,0,0,0,0,0,0};
//    unsigned int personnage_x=3, personnage_y=4, personnage_direction=1;

    std::vector<std::vector<Case*>> cases;

    this->setWindowState(Qt::WindowFullScreen);     //  on met en fullscreen

    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions
    QGridLayout *grid_right = new QGridLayout();    //  grille de droite pour afficher le jeu

    QLabel *label = new QLabel();
//    label->setScaledContents( true );
//    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
//    label->setPixmap(QPixmap("images/background.jpg"));
    grid_main->addWidget(label, 0,1,2,2,0);

    //  rempli cases avec des objets Case, et les ajoute au layout de droite
    for(unsigned int i = 0; i < 8; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 8; j++){
            vector.push_back(new Case());
            grid_right->addWidget(vector.at(j), i, j);
        }
        cases.push_back(vector);
    }

    Personnage *personnage = new Personnage();

    std::vector<QLabel*> labels;
    QFont f("Arial",16);
    //il est peu probable que le nb de cartes depasse 15
    for(unsigned int i = 0; i<30 ; i++){
        labels.push_back(new QLabel(""));
        labels.at(i)->setFont(f);
        labels.at(i)->setIndent(100);
        grid_left->addWidget(labels.at(i),i,0);

    }


    controller = new Controller(personnage,cases);
    controller->setLabels(labels);
    grid_main->addLayout(grid_left, 0,0,1,1,0);
    grid_main->addLayout(grid_right, 0,1,2,2,0);
    this->setLayout(grid_main);



}

GameWindow::~GameWindow()
{

}


//  s'execute quand on appuie sur le clavier
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    controller->controlCartes();
//    this->controller->keyPressEvent(event);
}

#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{
    srand (time(NULL));
    std::vector<std::vector<Case*>> cases;

    this->setWindowState(Qt::WindowFullScreen);     //  on met en fullscreen

    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions

    QGridLayout *grille_layout = new QGridLayout();

    //  rempli cases avec des objets Case, et les ajoute au layout de droite
    for(unsigned int i = 0; i < 8; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 8; j++){
            vector.push_back(new Case());
            grille_layout->addWidget(vector.at(j), i, j);
        }
        cases.push_back(vector);
    }

    scene = new QGraphicsScene();
    QPixmap pixmap("images/personnage.png");
    personnage = new Personnage(pixmap);
    scene->addItem(personnage);

    plateau = new QGraphicsView(scene);
    plateau->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    QRect rcontent = plateau->contentsRect();
    plateau->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    grid_main->addWidget(plateau,0,1,2,2,0);


    std::vector<QLabel*> labels;
    QFont f("Arial",16);

    //ajoute au layout de gauche des labels (vides au debut)
    //il est peu probable que le nb de fonctions a afficher depasse 15
    for(unsigned int i = 0; i<30 ; i++){
        labels.push_back(new QLabel(""));
        labels.at(i)->setFont(f);
        labels.at(i)->setIndent(100);
        grid_left->addWidget(labels.at(i),i,0);

    }


    controller = new Controller(personnage,cases,plateau);
    controller->setLabels(labels);
    grid_main->addLayout(grid_left, 0,0,1,1,0);
//    grid_main->addLayout(grid_right, 0,1,2,2,0);
    this->setLayout(grid_main);


}

GameWindow::~GameWindow()
{
    delete controller;
    delete personnage;
    delete scene;
}


//  s'execute quand on appuie sur le clavier
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    controller->start();
//    this->controller->keyPressEvent(event);
}

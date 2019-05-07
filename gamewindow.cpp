#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{
    srand (time(NULL));
    std::vector<std::vector<Case*>> cases;

    this->setWindowState(Qt::WindowFullScreen);     //  on met en fullscreen

    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions
    QStackedLayout *stacked_layout = new QStackedLayout();
    QGridLayout *grille_plateau = new QGridLayout();

    std::vector<QLabel*> labels;

    scene = new QGraphicsScene();
//    QGraphicsGridLayout *graphic_layout = new QGraphicsGridLayout();


    //  rempli cases avec des objets Case, et les ajoute sur la scene puis dans la graphicslayout
    for(unsigned int i = 0; i < 8; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 8; j++){
            vector.push_back(new Case());
            grille_plateau->addWidget(vector.at(j), i, j);
//            QGraphicsProxyWidget *proxy = scene->addWidget(vector.at(j));
//            graphic_layout->addItem(proxy, i, j);
        }
        cases.push_back(vector);
    }
    grille_plateau->setMargin(0);

    //  ajout du layout dans la scene
    widget_grille_plateau = new QWidget();
    widget_grille_plateau->setLayout(grille_plateau);

    QPixmap pixmap("images/personnage.png");
    personnage = new Personnage(pixmap);
    scene->addItem(personnage);

    plateau = new QGraphicsView(scene);
    plateau->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    QRect rcontent = plateau->contentsRect();
    plateau->setSceneRect(0, 0, rcontent.height(), rcontent.height());
    plateau->setStyleSheet("background: transparent");

    stacked_layout->insertWidget(1,widget_grille_plateau);
    stacked_layout->insertWidget(2,plateau);

    // pour superposer le contenu (plateau et widget_grille_plateau)
    stacked_layout->setStackingMode(QStackedLayout::StackAll);

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
    grid_main->addLayout(stacked_layout, 0,1,2,2,0);
    this->setLayout(grid_main);

    //  demarre direction la fonction start()
    QTimer::singleShot(1000, this, SLOT(start()));
    qApp->processEvents();
}

GameWindow::~GameWindow()
{
    delete controller;
    delete personnage;
    delete scene;
    delete widget_grille_plateau;
}

void GameWindow::start()
{
    plateau->setFixedSize(plateau->size().height(),plateau->size().height());
    plateau->update();
    widget_grille_plateau->setFixedSize(plateau->size().height(),plateau->size().height());

    //change la taille du perso en fonction de la resolution
    personnage->setScale(personnage->boundingRect().height() / (plateau->size().height()/8));
    personnage->setTransformationMode(Qt::SmoothTransformation); //ajoute un antialiasing
    controller->start();
}


//  s'execute quand on appuie sur le clavier
//void GameWindow::keyPressEvent(QKeyEvent *event)
//{

//}


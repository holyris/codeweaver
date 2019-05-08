#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{
    std::vector<std::vector<Case*>> cases;

    this->setWindowState(Qt::WindowFullScreen);     //  on met en fullscreen

    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions
    stacked_layout = new QStackedLayout();
    QGridLayout *grille_plateau = new QGridLayout();

    std::vector<QLabel*> labels;
    QLabel *background = new QLabel();
    background->setPixmap(QPixmap("images/background.jpg"));
    scene = new QGraphicsScene();

    //  rempli cases avec des objets Case, et les ajoute a grille_plateau
    for(unsigned int i = 0; i < 8; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 8; j++){
            vector.push_back(new Case());
            grille_plateau->addWidget(vector.at(j), i, j);

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

    // pour superposer le contenu (plateau et widget_grille_plateau)
    stacked_layout->setStackingMode(QStackedLayout::StackAll);

    stacked_layout->addWidget(background);

    stacked_layout->insertWidget(1,widget_grille_plateau);
    stacked_layout->insertWidget(2,plateau);
    stacked_layout->setAlignment(widget_grille_plateau, Qt::AlignCenter);
    stacked_layout->setAlignment(plateau, Qt::AlignCenter);

//    std::cout << test << std::endl;

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
    background->setScaledContents( true );
    background->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
//    grid_main->addWidget(background, 0,0,2,3,0);

    grid_main->addLayout(grid_left, 0,0,1,1,0);
    grid_main->addLayout(stacked_layout, 0,1,2,2,0);
    grid_main->setMargin(0);
    this->setLayout(grid_main);

    //  demarre dans 1s la fonction start()
    QTimer::singleShot(1000, this, SLOT(start()));
    qApp->processEvents();
}

GameWindow::~GameWindow()
{
    delete controller;
    delete personnage;
    delete scene;
    delete widget_grille_plateau;
    delete stacked_layout;
}

void GameWindow::start()
{
    //  la view devient carree et le widget prend exactement la meme taille
    plateau->setFixedSize(plateau->size().height(),plateau->size().height());
    plateau->update();
    widget_grille_plateau->setFixedSize(plateau->size().height(),plateau->size().height());
//    stacked_layout->setSizeConstraint(QLayout::SetNoConstraint);
//    stacked_layout->setGeometry(stacked_layout->sizeHint().height(),stacked_layout->sizeHint().height());
//    stacked_layout->setGeometry(QRect(0,0,plateau->size().height(),plateau->size().height()));


    //change la taille du perso en fonction de la resolution
    personnage->setScale(personnage->boundingRect().height() / (plateau->size().height()/8));
    personnage->setTransformationMode(Qt::SmoothTransformation); //ajoute un antialiasing
    controller->start();
}


//  s'execute quand on appuie sur le clavier
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    controller->keyPressEvent(event);
}


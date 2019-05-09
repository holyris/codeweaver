#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{

    this->setWindowState(Qt::WindowFullScreen);     //  on met en fullscreen
    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    grid_main->setMargin(0);
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions
    stacked_layout = new QStackedLayout();          //  layout pour superposer plateau et grille_layout
    QGridLayout *grille_plateau = new QGridLayout();//  layout qui affiche les cases
    grille_plateau->setMargin(0);

    Partie *partie = new Partie();

    QGraphicsScene *scene = partie->getScene();
    std::vector<std::vector<Case*>> cases = partie->getCases();
    personnage = partie->getPersonnage();
    plateau = partie->getPlateau();
    plateau->setScene(scene);
    plateau->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    QRect rcontent = plateau->contentsRect();

    //  on ajoute les cases au layout de jeu
    for(unsigned int i = 0; i < 8; i++){
        for(unsigned int j = 0; j < 8; j++){
            grille_plateau->addWidget(cases.at(i).at(j), i, j);
        }
    }



    plateau->setSceneRect(0, 0, rcontent.height(), rcontent.height());
    plateau->setStyleSheet("background: transparent");

    // pour superposer le contenu (plateau et widget_grille_plateau)
    stacked_layout->setStackingMode(QStackedLayout::StackAll);

    widget_grille_plateau = new QWidget();          //container de grille_layout
    widget_grille_plateau->setLayout(grille_plateau);
    stacked_layout->insertWidget(1,widget_grille_plateau);
    stacked_layout->insertWidget(2,plateau);

    QFont f("Arial",16);
    std::vector<QLabel*> labels;

    //ajoute au layout de gauche des labels (vides au debut)
    //il est peu probable que le nb de fonctions a afficher depasse 15
    for(unsigned int i = 0; i<30 ; i++){
        labels.push_back(new QLabel(""));
        labels.at(i)->setFont(f);
        labels.at(i)->setIndent(100);
        grid_left->addWidget(labels.at(i),i,0);

    }
    //  config pour label qui affiche le niveau
    f.setPointSize(30);
    f.setItalic(true);
    f.setBold(true);
    labels.back()->setFont(f);
    labels.back()->setAlignment(Qt::AlignRight);


    controller = new Controller(partie);
    controller->setLabels(labels);

    QLabel *background = new QLabel();
    background->setPixmap(QPixmap(""));
    background->setScaledContents( true );
    background->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    grid_main->addWidget(background, 0,0,2,3,0);
    grid_main->addLayout(grid_left, 0,0,1,1,0);
    grid_main->addLayout(stacked_layout, 0,1,2,2,Qt::AlignRight);
    this->setLayout(grid_main);

    //  demarre dans 1s la fonction start()
    QTimer::singleShot(1000, this, SLOT(start()));
    qApp->processEvents();
}

GameWindow::~GameWindow()
{
    delete controller;
    delete personnage;
    delete widget_grille_plateau;
    delete stacked_layout;
}

void GameWindow::start()
{
    //  la view devient carree et le widget prend exactement la meme taille
    plateau->setFixedSize(plateau->size().height(),plateau->size().height());
    plateau->update();
    widget_grille_plateau->setFixedSize(plateau->size().height(),plateau->size().height());

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


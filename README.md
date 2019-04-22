# codeweaver
Programme ludique jouable sans souris et clavier.
Testé sur Ubuntu 18.04 LTS.

INSTALLATION:
Ouvrez un terminal et tapez les commandes suivantes:
- sudo apt-get install build-essential
- sudo apt-get install cmake
- sudo apt-get install libopencv-dev
- sudo apt-get install qt5-default


CONFIGURATION:
Ouvrez ce projet avec Qt creator (qui devrait être dans vos applications).
- Lors de la configuration du projet, si aucun kit n'est valable alors cliquez sur "manage kits" et selectionnez Desktop (il ne devrait y en avoir qu'un)
- En passant votre souris sur un kit, Qt vous montre quelles configurations n'ont pas été faites (par ex compilateur manquant). Il suffit simplement de les compléter (double clic pour accéder aux config du kit)


COMPILATION:
- executez qmake puis compilez avec Qt 


LANCEMENT:
- Munissez vous d'une webcam reconnue par Linux.
- Téléchargez les cartes dans codeweaver/cartes (coming soon) et imprimez les. Il est préférable de le faire avec du papier un peu robuste.
- C'est prêt.

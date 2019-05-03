#include "detection.h"

Detection::Detection()
{
    inputVideo.open(0);
//    inputVideo.set(CV_CAP_PROP_FPS, 10);

    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    frame = 0;

}

Detection::~Detection()
{
    for(unsigned int i =0; i<cartes.size();i++){
        delete cartes.at(i);
    }
}

std::vector<Carte*> Detection::launch(){
    while (inputVideo.grab())
    {
        std::vector<int> const vector_argument = {11,14,4,5,6};
        std::vector<int> const vector_function = {13,10, 9, 7};

        cv::Mat image, imageCopy;
        std::vector<int> ids, affinedIds;
        std::vector<std::vector<cv::Point2f> > corners, affinedCorners, sortedCorners;
        inputVideo.retrieve(image);
        double const angle = 90;
        image = rotateImage(image, angle);
        image.copyTo(imageCopy);

        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        affinedCorners = affinageCorners(corners);  //  permet d'annuler l'effet de scintillement
        affinedIds = affinageIds(ids);  //  pareil
        sortedIds = sortTrackers(affinedCorners, affinedIds); //  range les ids de haut en bas selon l'image
        sortedCorners = sortCorners(affinedCorners);
        cartes.clear();

        //  cree des objets carte dans le vector cartes
        for(unsigned int i = 0; i<sortedIds.size(); i++){
            if (std::find(vector_argument.begin(), vector_argument.end(),sortedIds.at(i))!=vector_argument.end())
                cartes.push_back(new Carte(sortedIds.at(i), getCenter(sortedCorners.at(i)), "argument"));
            else if (std::find(vector_function.begin(), vector_function.end(),sortedIds.at(i))!=vector_function.end())
                cartes.push_back(new Carte(sortedIds.at(i), getCenter(sortedCorners.at(i)), "function"));
            else cartes.push_back(new Carte(sortedIds.at(i), getCenter(sortedCorners.at(i))));
        }

        detectOptions();
        frame++;
        if(frame == 30 /*&& affinedIds.size() > 0*/){
            frame = 0;
            return cartes;
        }
//        //  checkStartGoal permet d'avoir la condition de lancement de maniere fiable
//        if(checkStartGoal()){
//            manyGoalChecked.clear();
//            manyGoalChecked2.clear();
//            manyCorners.clear();
//            manyIds.clear();
//            final_cartes = cartes;
//            cartes.clear();
//            break;
//        }

        // if at least one marker detected
//        if (ids.size() > 0)
//        {
//            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
//        }
//        cv::imshow("out", imageCopy);
//        char key = (char)cv::waitKey(10);
//        if (key == 27)
//            break;
    }
}
std::vector<int> Detection::sortTrackers(const std::vector<std::vector<cv::Point2f> > &affinedCorners, std::vector<int> const &affinedIds)
{
    std::vector<int> vect_y;
    std::vector<int> sortedIds;
    //  on stock toutes les coordonnees y dans vect_y
    for (unsigned int i = 0; i < affinedCorners.size(); i++)
    {
        vect_y.push_back(getCenter(affinedCorners.at(i)).y); //prend le y du centre
    }

    // cette boucle permet de mettre dans sortedIds les id des trackers mais tries de haut en bas selon l'image
    // donc du plus petit au plus grand y
    for (int i = 0; i < vect_y.size(); i++)
    {
        //si l'element est le plus grand du vector, alors push l'id ayant cette position (les coordonnees sont rangees dans le meme ordre que les ids)
        if (vect_y.at(i) == *max_element(vect_y.begin(), vect_y.end()) && vect_y.at(i) != -1)
        {
            sortedIds.push_back(affinedIds.at(i));
            vect_y.at(i) = -1; // on met a -1 pour eviter que max_element le trouve et que la boucle recommence

            i = -1; // on recommence la boucle pour revenir au debut du vector

        }
    }
    std::reverse(sortedIds.begin(), sortedIds.end()); //c'est range de maniere decroissante à la base
    return sortedIds;
}

std::vector<std::vector<cv::Point2f> > Detection::sortCorners(const std::vector<std::vector<cv::Point2f> > &input)
{
    std::vector<std::vector<cv::Point2f>> sortedCorners;
    std::vector<int> vect_y;
    for (unsigned int i = 0; i < input.size(); i++)
        vect_y.push_back(getCenter(input.at(i)).y); //prend le y du centre



    // cette boucle permet de mettre dans sortedCorners les coord des trackers mais tries de haut en bas selon l'image
    // donc du plus petit au plus grand y
    for (int i = 0; i < vect_y.size(); i++)
    {
        //si l'element est le plus grand du vector, alors push les coord
        if (vect_y.at(i) == *max_element(vect_y.begin(), vect_y.end()) && vect_y.at(i) != -1)
        {
            sortedCorners.push_back(input.at(i));
            vect_y.at(i) = -1; // on met a -1 pour eviter que max_element le trouve et que la boucle recommence

            i = -1; // on recommence la boucle pour revenir au debut du vector

        }
    }
    std::reverse(sortedCorners.begin(), sortedCorners.end()); //c'est range de maniere decroissante à la base
    return sortedCorners;
}


cv::Point2f Detection::getCenter(std::vector<cv::Point2f> const &input)
{

    int milieu_x = input.at(0).x + input.at(1).x + input.at(2).x + input.at(3).x;
    int milieu_y = input.at(0).y + input.at(1).y + input.at(2).y + input.at(3).y;
    cv::Point2f center(milieu_x / 4, milieu_y / 4);

    return center;
}
//  affine la condition de lancement
bool Detection::affinageStartGoal(){

    bool check = false;

    if(!sortedIds.empty()){
        check = true;
        //  si l'element tout en bas est goal et que celui tout en haut est start alors push true
        if(sortedIds.back() == 15)
            manyGoalChecked.push_back(true);
        else
            manyGoalChecked.push_back(false);

        //pour limiter la taille du vector
        if(manyGoalChecked.size() >= 3)
            manyGoalChecked.erase(manyGoalChecked.begin());

        //  regarde dans le vector pour voir si il y a un false
        for(unsigned int i = 0; i < manyGoalChecked.size(); i++){
            //  s'il y a un false alors on est pas assez sur que la condition de lancement de jeu soit remplie
            if(manyGoalChecked.at(i) == false)
                check = false;

        }

    }
    return check;
}
//  cette fonction permet encore plus d'affiner la condition de lancement
bool Detection::checkStartGoal(){
    int j=0;

    manyGoalChecked2.push_back(affinageStartGoal());
    if(manyGoalChecked2.size() >= 30){
        manyGoalChecked2.erase(manyGoalChecked2.begin());
    }
    for(unsigned int i = 0; i < manyGoalChecked2.size(); i++){
        if(manyGoalChecked2.at(i) == true){
            j++;
        }
    }
    if(j>=15) return true;
    else return false;
}

/*
 * quand on cherche l'ordre des cartes sur l'image, il arrive que certaines ne soient pas captées
 * alors sur 10 frame on sort le tableau possedant le plus de cartes, car c'est surement le plus vrai
 *
*/
std::vector<int> Detection::affinageIds(std::vector<int> const &input){
    std::vector<int> tampon;
    manyIds.push_back(input);

    //  limite la taille du vector
    if(manyIds.size() >=10){
        manyIds.erase(manyIds.begin());
    }

    //  met les tailles des vector dans tampon
    for(unsigned int i = 0; i < manyIds.size(); i++)
        tampon.push_back(manyIds.at(i).size());

    //  trouve le vector le plus grand en taille dans manyIds
    for(unsigned int i = 0; i < manyIds.size(); i++)
        if (tampon.at(i) == *max_element(tampon.begin(), tampon.end()))
            return manyIds.at(i);

    return manyIds.at(0);
}

std::vector<std::vector<cv::Point2f>> Detection::affinageCorners(std::vector<std::vector<cv::Point2f> > const &input){
    std::vector<int> tampon;

    manyCorners.push_back(input);

    //  limite la taille
    if(manyCorners.size() >=10){
        manyCorners.erase(manyCorners.begin());
    }

    for(unsigned int i = 0; i < manyCorners.size(); i++)
        tampon.push_back(manyCorners.at(i).size());

    for(unsigned int i = 0; i < manyCorners.size(); i++)
        if (tampon.at(i) == *max_element(tampon.begin(), tampon.end()))
               return manyCorners.at(i);

    return manyCorners.at(0);
}

//  detecte et associe les arguments avec leur fonction
void Detection::detectOptions()
{
    for(unsigned int i = 0 ; i < cartes.size() ; i++){

        //  cherche uniquement les cartes fonction
        if(cartes.at(i)->getType() == "function"){

            //  maintenant recherche dans toutes les cartes
            for(unsigned int j = 0 ; j < cartes.size() ; j++){

                //cherche uniquement les cartes argument
                if(cartes.at(j)->getType() == "argument"){

                    // verif si yen a une a droite
                    if(cartes.at(i)->getX()-100 <= cartes.at(j)->getX() && cartes.at(j)->getX() <= cartes.at(i)->getX()+100){
                        // verif si c'est a peu pres a la meme hauteur
                        if(cartes.at(j)->getY() <= cartes.at(i)->getY()+30 && cartes.at(j)->getY() >= cartes.at(i)->getY()-30){

                            //ce if permet de ne pas attribuer autre chose que x2 pour tourner droite et gauche
                            if(cartes.at(i)->getId() != 10 && cartes.at(i)->getId() != 7){
                                cartes.at(i)->setArgumentId(cartes.at(j)->getId());
                                break;
                            } else if(cartes.at(j)->getId() ==11 ){
                                cartes.at(i)->setArgumentId(cartes.at(j)->getId());
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


/*
 * fonction pour tourner l'image prise par la camera
*/
cv::Mat Detection::rotateImage(cv::Mat image, double angle)
{
    cv::Mat imageRotate;
    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((image.cols-1)/2.0, (image.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), image.size(), angle).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - image.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - image.rows/2.0;

    cv::warpAffine(image, imageRotate, rot, bbox.size());

    return imageRotate;
}

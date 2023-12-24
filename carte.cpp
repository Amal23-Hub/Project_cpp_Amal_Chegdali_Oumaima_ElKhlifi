// carte.cpp
#include "carte.h"

Carte::Carte() {

}

Carte::Carte(const QString& nom, int valeur, const QPixmap& image)
    : nom(nom), valeur(valeur), image(image) {}

QString Carte::getNom() const {
    return nom;
}

int Carte::getValeur() const {
    return valeur;
}

QPixmap Carte::getImage() const {
    return image;
}
bool Carte :: operator==(const Carte& other) const{
    return other.valeur==valeur;
}
bool Carte ::  Comparer(const Carte& autreCarte) const{
    if(valeur>autreCarte.valeur){
        return 1;
    }
    else if(valeur < autreCarte.valeur){
        return -1;
    }
    else return 0;
}

QPixmap Carte::getDefaultImage() const {
    // Remplacez ce chemin avec le chemin correct vers votre image générique par défaut
    return QPixmap(":/images/back1.png");
}

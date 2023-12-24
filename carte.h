// carte.h
#ifndef CARTE_H
#define CARTE_H

#include <QString>
#include <QPixmap>

class Carte {
public:
    Carte();
    Carte(const QString& nom, int valeur, const QPixmap& image);
    QPixmap getDefaultImage() const;
    QString getNom() const;
    int getValeur() const;
    QPixmap getImage() const;
    bool operator==(const Carte& other) const;
    bool Comparer(const Carte& autreCarte) const;



private:
    QString nom;
    int valeur;
    QPixmap image;
};

#endif

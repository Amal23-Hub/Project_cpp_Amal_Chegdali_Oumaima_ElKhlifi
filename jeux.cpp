// Jeu.cpp
#include "jeux.h"
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include<QMessageBox>
#include <QDebug>


Jeu::Jeu(QObject *parent) : QObject(parent), indexCarteCourante(0) {
    // Initialiser le deck avec 40 cartes
        for (int i = 1; i <=4; i++) {
            QString nom;

          QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 1, image));

        }

        for (int i = 5; i <=8; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 2, image));

        }

        for (int i = 9; i <=12; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 3, image));

        }

        for (int i = 13; i <=16; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 4, image));

        }

        for (int i = 17; i <=20; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 5, image));

        }

        for (int i = 21; i <=24; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 6, image));

        }

        for (int i = 25; i <=28; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 7, image));

        }
        for (int i = 29; i <=32; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 10, image));

        }

        for (int i = 33; i <=36; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 11, image));

        }

        for (int i = 37; i <=40; i++) {
            QString nom;

            QPixmap image(":cpp/" + QString::number(i) + ".gif");
            // Ajouter une seule fois chaque carte
            cartes.append(Carte(nom, 12, image));

        }

}



void Jeu::melangerCartes() {
    // mélanger les cartes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);

    indexCarteCourante = 0;
}

Carte Jeu::tirerCarte() {
    if (!cartes.isEmpty()) {

        std::srand(std::time(0));
        int randomIndex = std::rand() % cartes.size();

        Carte carteTiree = cartes.takeAt(randomIndex);

        return carteTiree;
    }   else {
        qDebug() << "Ceci est un message de débogage.";

    }
}
void Jeu::remettreCartes() {
    // Réinitialisez les cartes du jeu dans l'ordre initial
    cartes.clear();
    Jeu jeu ;
    for (int i = 1; i <=4; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 1, image));

    }

    for (int i = 5; i <=8; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 2, image));

    }

    for (int i = 9; i <=12; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 3, image));

    }

    for (int i = 13; i <=16; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 4, image));

    }

    for (int i = 17; i <=20; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 5, image));

    }

    for (int i = 21; i <=24; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 6, image));

    }

    for (int i = 25; i <=28; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 7, image));

    }
    for (int i = 29; i <=32; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 10, image));

    }

    for (int i = 33; i <=36; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 11, image));

    }

    for (int i = 37; i <=40; i++) {
        QString nom;

        QPixmap image(":cpp/" + QString::number(i) + ".gif");
        // Ajouter une seule fois chaque carte
        cartes.append(Carte(nom, 12, image));

    }

    // Mélangez les cartes après les avoir réinitialisées
     melangerCartes();


    indexCarteCourante = 0;
}

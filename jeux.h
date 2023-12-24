// jeux.h
#ifndef JEUX_H
#define JEUX_H

#include <QObject>
#include <QList>
#include "carte.h"

class Jeu : public QObject {
    Q_OBJECT

public:
    explicit Jeu(QObject *parent = nullptr);
    void melangerCartes();
    Carte tirerCarte();
    void remettreCartes();

private:
    void initialiserDeck();

    QList<Carte> cartes;
    int indexCarteCourante;
};

#endif // JEUX_H

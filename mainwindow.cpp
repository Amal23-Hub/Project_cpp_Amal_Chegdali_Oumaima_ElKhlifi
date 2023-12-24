#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMediaPlayer>
#include <QStackedWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include<QPushButton>
#include<QTimer>
#include<QTime>
#include "jeux.h"
#include<QMessageBox>
#include<QPixmap>
#include <QLabel>
#include<QIcon>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaPlaylist>

//En initialisant des variables
int gag=0;
int MainWindow::nombreTotalDeCartes = 40;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , tempsEcoule(0)

{
    ui->setupUi(this);
    playmusic();
    chronometre.setInterval(1000);
    connect(&chronometre, SIGNAL(timeout()), this, SLOT(chronometreTimeout()));
    scoreJoueur1=0;
    scoreAI=0;
    completedAnimationsCount=0 ;
        //les button ou je vais distrubuer les cartes
        boutonsCartes[0] = ui->pushButton1;
        boutonsCartes[1] = ui->pushButton2;
        boutonsCartes[2] = ui->pushButton3;
        boutonsCartes[3] = ui->pushButton4;
        boutonsCartes[4] = ui->pushButton5;
        boutonsCartes[5] = ui->pushButton6;
        boutonsCartes[6] = ui->pushButton7;
        boutonsCartes[7] = ui->pushButton8;

    //les buttons ou je vais cacher les cartes de la deuxieme joueurs IA
        boutonsCaches[0] = nullptr;
        boutonsCaches[1] = nullptr;
        boutonsCaches[2] = nullptr;
        boutonsCaches[3] = nullptr;
        boutonsCaches[4] =  ui->pushButton5;
        boutonsCaches[5] =  ui->pushButton6;
        boutonsCaches[6] =  ui->pushButton7;
        boutonsCaches[7] = ui->pushButton8;

    // fonction pour distrubuer les carets a chaque joueur
        afficherCarteSiBoutonsCaches();
        BloquerButton();
        connect(ui->q_4, SIGNAL(clicked()), this, SLOT(demarrerChronometre()));
        connect(&chronometre, SIGNAL(timeout()), this, SLOT(demarrerChronometre()));
        connect(ui->input, SIGNAL(editingFinished()), this, SLOT(onNameEntered()));

        connect(ui->input, SIGNAL(editingFinished()), this, SLOT(onNameEntered()));
        setupUi();
        startAnimations();
        animation = new QPropertyAnimation(ui->imageLabel, "pos");
        animation->setStartValue(ui->imageLabel->pos());
        animation->setEndValue(ui->imageLabel->pos() + QPoint(100, 0));
        animation->setDuration(1000);

        QPropertyAnimation *reverseAnimation = new QPropertyAnimation(ui->imageLabel, "pos");
        reverseAnimation->setStartValue(ui->imageLabel->pos() + QPoint(100, 0));
        reverseAnimation->setEndValue(ui->imageLabel->pos());
        reverseAnimation->setDuration(1000);

        QSequentialAnimationGroup *sequence = new QSequentialAnimationGroup;
        sequence->addAnimation(animation);
        sequence->addAnimation(reverseAnimation);
        sequence->setLoopCount(-1);
        sequence->start();
        //partie 2
        animation = new QPropertyAnimation(ui->imageimoji, "pos");
        animation->setStartValue(ui->imageimoji->pos());
        animation->setEndValue(ui->imageimoji->pos() + QPoint(100, 0));
        animation->setDuration(300);

        QPropertyAnimation *reverseAnimation1 = new QPropertyAnimation(ui->imageimoji, "pos");
        reverseAnimation1->setStartValue(ui->imageimoji->pos() + QPoint(100, 0));
        reverseAnimation1->setEndValue(ui->imageimoji->pos());
        reverseAnimation1->setDuration(300);

        QSequentialAnimationGroup *sequence1 = new QSequentialAnimationGroup;
        sequence1->addAnimation(animation);
        sequence1->addAnimation(reverseAnimation);
        sequence1->setLoopCount(-1);
        sequence1->start();

}


void MainWindow::playmusic(){
    playlist = new QMediaPlayer;
    mediaPlaylist = new QMediaPlaylist;
   mediaPlaylist->addMedia(QUrl("‪qrc:/audio/a.mp3"));
    // Add other audio files if needed
    mediaPlaylist->setCurrentIndex(0);

    // Set infinite loop
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

    // Set the playlist to the player
    playlist->setPlaylist(mediaPlaylist);

    // Create a new QAudioOutput
    audioOutput = new QAudioOutput;

    // Set the audio output for the player via the constructor
    playlist = new QMediaPlayer(audioOutput);

    // Set the volume
    playlist->setVolume(60);  // The value is from 0 to 100

    // Start playback
    playlist->play();
}
MainWindow::~MainWindow()
{

}
//start game
void MainWindow::on_pushButton_clicked(){
    ui->pushButton->setStyleSheet("QPushButton:hover {"
                                  "    background-color: red;"
                                  "    color: yellow;"

                                  "}"
                                  "QPushButton {"          "background-color:yellow;"
                                                           "    color: red;"
                                                           "    font-weight: 900;"
                                                           "    font-size: 20px;"
                                                           "    font-style: italic;"
                                                           "    border-radius: 24px;"

                                                           "}");

    QTimer* timer = new QTimer(this);
   connect(timer, &QTimer::timeout, [=]() {
        //progress bar
        static int i = 0;
        ui->progressBar->setValue(i);
        if (i == 100) {
        ui->stackedWidget->setCurrentIndex(1);
            timer->stop();
            timer->deleteLater();
        } else {
            i++;
        }
    });

    timer->start(100);

}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_pushButton_10_clicked()
{
     QApplication::quit();
}
void MainWindow::setupUi() {

    labels[0] = ui->label1_2;
    labels[1] = ui->label2;
    labels[2] = ui->label3;
    labels[3] = ui->label4;
    labels[4] = ui->label5;
    labels[5] = ui->label6;
    labels[6] = ui->label7;
}



void MainWindow::startAnimations() {
    for (int i = 0; i < 7; ++i) {
        QPoint currentPosition = labels[i]->pos();
        QPropertyAnimation *animation = new QPropertyAnimation(labels[i], "pos");
        animation->setDuration(1000);
        animation->setEndValue(currentPosition + QPoint(100, 100));
        animation->setLoopCount(-1);
        animation->start();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_14_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::onNameEntered() {
    QString enteredName = ui->input->text();
    ui->label_20->setText(enteredName);
    ui->label_121->setText(enteredName);
}


//pour demarrer le chronometre
void MainWindow::demarrerChronometre()
{
    chronometre.start();
}

// pour arreter le chronometre
void MainWindow::arreterChronometre()
{
    if (chronometre.isActive())
    {
        chronometre.stop();
    }

}

void MainWindow::chronometreTimeout(){

    tempsEcoule++;
    int heures = tempsEcoule / 3600;
    int minutes = (tempsEcoule % 3600) / 60;
    int secondes = tempsEcoule % 60;

    ui->labelChronometre->setText(QString("%1:%2:%3")
                                      .arg(heures, 2, 10, QChar('0'))
                                      .arg(minutes, 2, 10, QChar('0'))
                                      .arg(secondes, 2, 10, QChar('0')));
}

void MainWindow::stopperChronometre(){

    arreterChronometre();
}

//fonction pour bloquer les bouttons du joueur AI
void MainWindow::BloquerButton(){
    ui->pushButton5->setEnabled(false);
    ui->pushButton7->setEnabled(false);
    ui->pushButton6->setEnabled(false);
    ui->pushButton8->setEnabled(false);
}

void MainWindow::creerBoutonCarte(QPushButton *bouton, const Carte &carte){

    bouton->setIcon(carte.getImage());
    bouton->setIconSize(QSize(150, 150));
}

void MainWindow::creerBoutonCache(QPushButton *boutonCache, const Carte &carte) {
    boutonCache->setIcon(carte.getDefaultImage());
    boutonCache->setIconSize(QSize(430, 130));
}

void MainWindow::on_btnAfficherCarte_clicked(){

    ui->btnAfficherCarte->setEnabled(false);
    for (QPushButton* bt : boutonsCartes) {
        Affiche(bt);
 }

    // pour obtennir une carte
    Carte cartesTirees[] = {
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte(),
        deck.tirerCarte()
    };


    for (int i = 0; i < 8; ++i) {
        QTimer::singleShot(i * 500, [this, boutonCarte = boutonsCartes[i], boutonCache = boutonsCaches[i], carte = cartesTirees[i], i]() {
            if (boutonCarte != nullptr) {
                creerBoutonCarte(boutonCarte, carte);
                MainWindow::nombreTotalDeCartes--;
                ui->counterLabel->setText(QString("%1").arg(nombreTotalDeCartes));
                cartesAssociees[i] = carte;
            }

            if (boutonCache != nullptr) {
                Carte carteInstance;  // Créez une instance de Carte
                creerBoutonCache(boutonCache, carteInstance);  // Utilisez l'image par défaut
            }
        });
    }


}

void MainWindow::effectuerAnimationInverse(QPushButton *bouton, QRect positionInitiale, int duree)
{
    QPropertyAnimation *animationInverse = new QPropertyAnimation(bouton, "geometry");
    animationInverse->setStartValue(bouton->geometry());
    animationInverse->setEndValue(positionInitiale);
    animationInverse->setDuration(duree);

    // Connecter le signal finished de l'animation à une fonction pour effectuer des actions après l'animation
    connect(animationInverse, &QPropertyAnimation::finished, [this, bouton]() {
        // Appeler la fonction Bloque après l'animation inverse
        Bloque(bouton);

        // Augmenter le compteur d'animations inverses terminées
        completedAnimationsCount++;

        // Vérifier si toutes les animations inverses sont terminées
        if (completedAnimationsCount == 8) {
            // Réinitialiser le compteur
            completedAnimationsCount = 0;

            // Débloquer le bouton que vous souhaitez
            ui->btnAfficherCarte->setEnabled(true);
        }
    });

    // Démarrer l'animation inverse
    animationInverse->start();

    // Effacer l'icône du bouton
    bouton->setIcon(QIcon());
}


void MainWindow::Bloque(QPushButton *bt){
  //  fonction pour hider la button apres l'utilisation
    bt->hide() ;
}

void MainWindow::Affiche(QPushButton *bt) {
  bt->show();
}


void MainWindow::on_pushButtonClicked(QPushButton *bouton) {
    // pour obtenir l'index du bouton dans le tableau boutonsCartes
    int index = -1;
    for (int i = 0; i < 8; ++i) {
        if (bouton == boutonsCartes[i]) {
            index = i;
            break;
        }
    }

    // Vérifiant si la carte associée à ce bouton est cachée
    if (index != -1 && boutonsCaches[index] != nullptr) {
        // on affiche l'image de la carte uniquement si elle est cachée
        creerBoutonCarte(bouton, cartesAssociees[index]);
    }
}

void MainWindow::afficherCarteSiBoutonsCaches() {
    // Vérifiant si tous les boutons sont cachés
    if (ui->pushButton1->isHidden() && ui->pushButton2->isHidden() && ui->pushButton3->isHidden() &&
        ui->pushButton4->isHidden() && ui->pushButton5->isHidden() && ui->pushButton6->isHidden() &&
        ui->pushButton7->isHidden() && ui->pushButton8->isHidden()) {
        on_btnAfficherCarte_clicked();
    } else {
        qDebug() << "Certains boutons ne sont pas cachés.";
    }
}

// pour comparer les numéros de cartes
bool MainWindow::comparerNumerosCartes(QPushButton *bouton1, QPushButton *bouton2) {
    // Obtenez les indices associés aux boutons
    int index1 = -1, index2 = -1;

    for (int i = 0; i < 8; ++i) {
        if (bouton1 == boutonsCartes[i]) {
            index1 = i;
        }

        if (bouton2 == boutonsCartes[i]) {
            index2 = i;
        }
    }

    if (index1 != -1 && index2 != -1) {
        // Obtenant les numéros des cartes associées aux indices
        int numeroCarte1 = cartesAssociees[index1].getValeur();
        int numeroCarte2 = cartesAssociees[index2].getValeur();

        // Comparant les numéros des cartes
        if (numeroCarte1 > numeroCarte2) {
            scoreJoueur1 += 2;
            ui->scoreJoueur1->setText(QString("%1").arg(scoreJoueur1));
        } else if (numeroCarte1 < numeroCarte2) {
            scoreAI += 2;
            ui->scoreJoueur2->setText(QString("%1").arg(scoreAI));
        } else if (numeroCarte1 == numeroCarte2) {
            scoreJoueur1 += 1;
            ui->scoreJoueur1->setText(QString("%1").arg(scoreJoueur1));
            scoreAI += 1;
            ui->scoreJoueur2->setText(QString("%1").arg(scoreAI));
        }
    return false;  // Gestion d'erreur, par exemple si les indices ne sont pas valides
}

}

// button 1
void MainWindow::on_pushButton1_clicked()
{
    on_pushButton7_clicked();
          gag++;
    QPropertyAnimation *animationX1 = new QPropertyAnimation(ui->pushButton1, "geometry");
    animationX1->setStartValue(ui->pushButton1->geometry());
    animationX1->setEndValue(QRect(625, 320, ui->pushButton1->width(), ui->pushButton1->height()));  // Nouvelle position (200, 50)
    animationX1->setDuration(1000);
    // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX1->start();
    comparerNumerosCartes(ui->pushButton1, ui->pushButton7);

    // Planifiant l'animation inverse après 4 secondes
    QTimer::singleShot(5000, [this, bouton = ui->pushButton1, positionInitiale = ui->pushButton1->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);
        // Dure 1 seconde pour revenir à la position initiale
        if (gag==20 && MainWindow::nombreTotalDeCartes==0) {
            // Vérifiant si toutes les cartes ont été distribuées
            stopperChronometre();

                // Réinitialisez le chronomètre à son état initial
                tempsEcoule = 0;
                ui->labelChronometre->setText("00:00:00");
            afficherGagnant();

        }
    });

}
//button 2
void MainWindow::on_pushButton2_clicked()
{
     on_pushButton5_clicked();
     gag++;
    QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton2, "geometry");
    animationX2->setStartValue(ui->pushButton2->geometry());
    animationX2->setEndValue(QRect(625, 320, ui->pushButton2->width(), ui->pushButton2->height()));  // Nouvelle position (100, 250)
    animationX2->setDuration(2000);  // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX2->start();
    comparerNumerosCartes(ui->pushButton2, ui->pushButton5);

    // Planifiant l'animation inverse après 4 secondes
    QTimer::singleShot(5000, [this, bouton = ui->pushButton2, positionInitiale = ui->pushButton2->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);
        // Dure 1 seconde pour revenir à la position initiale
        if (gag==20 && MainWindow::nombreTotalDeCartes==0) {
            // Vérifiant si toutes les cartes ont été distribuées
            stopperChronometre();

                // Réinitialisez le chronomètre à son état initial
                tempsEcoule = 0;
                ui->labelChronometre->setText("00:00:00");
            afficherGagnant();
        }

    } );

}

//button 3
void MainWindow::on_pushButton3_clicked()
{
    on_pushButton8_clicked();
    gag++;
    QPropertyAnimation *animationX1 = new QPropertyAnimation(ui->pushButton3, "geometry");
    animationX1->setStartValue(ui->pushButton3->geometry());
    animationX1->setEndValue(QRect(625, 320, ui->pushButton3->width(), ui->pushButton3->height()));  // Nouvelle position (200, 50)
    animationX1->setDuration(1000);  // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX1->start();
    comparerNumerosCartes(ui->pushButton3, ui->pushButton8);

    // Planifiant l'animation inverse après 4 secondes
    QTimer::singleShot(5000, [this, bouton = ui->pushButton3, positionInitiale = ui->pushButton3->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);
        // Dure 1 seconde pour revenir à la position initiale

        if (gag==20 && MainWindow::nombreTotalDeCartes==0) {
            // Vérifiant si toutes les cartes ont été distribuées
            stopperChronometre();

                // Réinitialisant le chronomètre à son état initial
                tempsEcoule = 0;
                ui->labelChronometre->setText("00:00:00");
            afficherGagnant();
        }
    });

}
// button 4
void MainWindow::on_pushButton4_clicked()
{
    on_pushButton6_clicked();
gag++;
    QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton4, "geometry");
    animationX2->setStartValue(ui->pushButton4->geometry());
    animationX2->setEndValue(QRect(625, 320, ui->pushButton4->width(), ui->pushButton4->height()));
    // Nouvelle position (100, 250)
    animationX2->setDuration(2000);  // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX2->start();
    comparerNumerosCartes(ui->pushButton4, ui->pushButton6);
   // Planifiant l'animation inverse après 4 secondes
    QTimer::singleShot(5000, [this, bouton = ui->pushButton4, positionInitiale = ui->pushButton4->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);
      // Dure 1 seconde pour revenir à la position initiale

        if (gag==20 && MainWindow::nombreTotalDeCartes==0) {
            // Vérifiant si toutes les cartes ont été distribuées
            stopperChronometre();

                // Réinitialisant le chronomètre à son état initial
                tempsEcoule = 0;
                ui->labelChronometre->setText("00:00:00");
            afficherGagnant();
        }
    } );

}

//button 5
void MainWindow::on_pushButton5_clicked(){
    on_pushButtonClicked(ui->pushButton5);
    QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton5, "geometry");
    animationX2->setStartValue(ui->pushButton5->geometry());
    animationX2->setEndValue(QRect(540,320, ui->pushButton5->width(), ui->pushButton5->height()));  // Nouvelle position (200, 50)
    animationX2->setDuration(1000); // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX2->start();

    // Planifier l'animation inverse après 4 secondes
    QTimer::singleShot(4000, [this, bouton = ui->pushButton5, positionInitiale = ui->pushButton5->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);  // Dure 2 secondes pour revenir à la position initiale
    });
}
//button 6
void MainWindow::on_pushButton6_clicked()

    {

    on_pushButtonClicked(ui->pushButton6);
    QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton6, "geometry");
    animationX2->setStartValue(ui->pushButton6->geometry());
    animationX2->setEndValue(QRect(540,320, ui->pushButton6->width(), ui->pushButton6->height()));  // Nouvelle position (200, 50)
    animationX2->setDuration(1000); // Durée de l'animation en millisecondes

    // Démarrer l'animation
    animationX2->start();

    // Planifier l'animation inverse après 4 secondes
    QTimer::singleShot(4000, [this, bouton = ui->pushButton6, positionInitiale = ui->pushButton6->geometry()] {
        effectuerAnimationInverse(bouton, positionInitiale, 900);  // Dure 2 secondes pour revenir à la position initiale
    });
}

//button 7
void MainWindow::on_pushButton7_clicked(){
        on_pushButtonClicked(ui->pushButton7);
        QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton7, "geometry");
        animationX2->setStartValue(ui->pushButton7->geometry());
        animationX2->setEndValue(QRect(540,320, ui->pushButton7->width(), ui->pushButton7->height()));  // Nouvelle position (200, 50)
        animationX2->setDuration(1000); // Durée de l'animation en millisecondes

        // Démarrer l'animation
        animationX2->start();

        // Planifier l'animation inverse après 4 secondes
        QTimer::singleShot(4000, [this, bouton = ui->pushButton7, positionInitiale = ui->pushButton7->geometry()] {
            effectuerAnimationInverse(bouton, positionInitiale, 900);  // Dure 2 secondes pour revenir à la position initiale

        });

}
//button 8
void MainWindow::on_pushButton8_clicked()
{

        on_pushButtonClicked(ui->pushButton8);
        QPropertyAnimation *animationX2 = new QPropertyAnimation(ui->pushButton8, "geometry");
        animationX2->setStartValue(ui->pushButton8->geometry());
        animationX2->setEndValue(QRect(540,320, ui->pushButton8->width(), ui->pushButton8->height()));  // Nouvelle position (200, 50)
        animationX2->setDuration(1000); // Durée de l'animation en millisecondes

        // Démarrer l'animation
        animationX2->start();

        // Planifier l'animation inverse après 4 secondes
        QTimer::singleShot(4000, [this, bouton = ui->pushButton8, positionInitiale = ui->pushButton8->geometry()] {
            effectuerAnimationInverse(bouton, positionInitiale, 900);  // Dure 2 secondes pour revenir à la position initiale
        });
    }




void MainWindow::on_q_6_clicked()
{     ui->stackedWidget->setCurrentIndex(2);
    QLabel *label=ui->label_21;
    QIcon icon(":images/p1");
    label->setPixmap(icon.pixmap(label->size()));
    QLabel *labell=ui->label_117;
    labell->setPixmap(icon.pixmap(label->size()));
    //hover
    ui->q_6->setStyleSheet("QPushButton:hover {"
                                  "    background-color: red;"
                                  "    color: white;"
                                  "}"
                                  "QPushButton{"          "background-color:white;"
                                                           "    color: red;"
                                                           "    font-weight: 900;"
                                                           "    font-size: 20px;"
                                                           "    font-style: italic;"
                                                           "    border-radius: 24px;"
                                                           "}");
}

// Pour afficher le gagnant
void MainWindow::afficherGagnant() {
        int scoreJoueur11 = scoreJoueur1;
        int scoreAI1 = scoreAI;

        if (scoreJoueur11 > scoreAI1) {

            ui->gangant->setText(ui->input->text());
            QLabel *label = ui->LabelImage;
            QIcon icon(":images/p1.png");
            label->setPixmap(icon.pixmap(QSize(100, 100)));
            ui->stackedWidget->setCurrentIndex(9);
        } else if (scoreJoueur11 < scoreAI1) {
            QLabel *label = ui->LabelImage;
            QIcon icon(":images/ai.png");

            label->setPixmap(icon.pixmap(QSize(100, 85)));
            ui->stackedWidget->setCurrentIndex(9);

        } else {
            ui->scoreJoueur1_2->setText(QString::number(scoreJoueur11));
                ui->scoreJoueur2_2->setText(QString::number(scoreAI1));
                ui->stackedWidget->setCurrentIndex(10);

        }
    }

void MainWindow::on_q_3_clicked()
{
      BloquerButton();
     // Réinitialisant le chronomètre à son état initial
         tempsEcoule = 0;
         ui->labelChronometre->setText("00:00:00");
          demarrerChronometre();
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_q_4_clicked()
{
        BloquerButton();
    // Réinitialisant le chronomètre à son état initial
        tempsEcoule = 0;
        ui->labelChronometre->setText("00:00:00");
    demarrerChronometre();
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QLabel *label=ui->label_21;
    QIcon icon(":images/p3.png");
    label->setPixmap(icon.pixmap(label->size()));
   //hover
    ui->pushButton_33->setStyleSheet("QPushButton:hover {"
                                  "    background-color: red;"
                                  "    color: white;"
                                  "}"
                                  "QPushButton {"          "background-color:white;"
                                                           "    color: red;"
                                                           "    font-weight: 900;"
                                                           "    font-size: 20px;"
                                                           "    font-style: italic;"
                                                           "    border-radius:24px;"
                                                           "}");
}






void MainWindow::rejouer() {
    // Reset all ongoing animations
    for (QPushButton* bouton : boutonsCartes) {
        if (bouton != nullptr) {
            // Stop any ongoing animations
            QVariant animationVariant = bouton->property("animation");
            if (animationVariant.isValid()) {
                QPropertyAnimation* animation = qvariant_cast<QPropertyAnimation*>(animationVariant);
                if (animation) {
                    animation->stop();
                }
            }

            bouton->setEnabled(true);  // Enable the button
            bouton->setIcon(QIcon());  // Clear the icon
        }
    }

    // Reset deck and total number of cards
    deck.remettreCartes();
    MainWindow::nombreTotalDeCartes = 40;

    // Reset scores
    scoreJoueur1 = 0;
    scoreAI = 0;
    ui->scoreJoueur1->setText(QString("%1").arg(scoreJoueur1));
    ui->scoreJoueur2->setText(QString("%1").arg(scoreAI));

    // Show the card counter
    ui->counterLabel->setText(QString("%1").arg(MainWindow::nombreTotalDeCartes));

    // Display cards to start a new game
    on_btnAfficherCarte_clicked();
}

void MainWindow::on_q_8_clicked()
{
       BloquerButton();
    // Réinitialisant le chronomètre à son état initial
        tempsEcoule = 0;
        ui->labelChronometre->setText("00:00:00");
        demarrerChronometre();
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_37_clicked()
{
    // Réinitialisant le chronomètre à son état initial
        tempsEcoule = 0;
        ui->labelChronometre->setText("00:00:00");
        demarrerChronometre();
        rejouer();
        BloquerButton();

}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pushButton_25_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_q_clicked()
{    playmusic();
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_26_clicked()
{
       QApplication::quit();
}
void MainWindow::on_pushButton_27_clicked()
{
      QApplication::quit();
}
void MainWindow::on_pushButton_3_clicked()
{
      ui->stackedWidget->setCurrentIndex(6);
}
void MainWindow::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_34_clicked()
{
     QApplication::quit();
}
void MainWindow::on_pushButton_29_clicked()
{
 ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    rejouer();
}



void MainWindow::on_pushButton_9_clicked()
{
 ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_20_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_28_clicked()
{
    QApplication::quit();
}
void MainWindow::on_push9_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_21_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_23_clicked()
{
    QApplication::quit();
}


void MainWindow::on_label_25_linkActivated(const QString &link)
{
    QApplication::quit();
}
void MainWindow::on_pushButton_17_clicked()
{
     QApplication::quit();
}


void MainWindow::on_pushButton_16_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_15_clicked()
{
     QApplication::quit();
}

void MainWindow::on_q_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_19_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_18_clicked()
{
    QApplication::quit();
}

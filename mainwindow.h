#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsDropShadowEffect>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include<QLabel>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QList>
#include "jeux.h"
#include<QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//replay

        void stopperChronometre();

        void creerBoutonCarte(QPushButton *bouton, const Carte &carte);

        void onAnimationFinished();

        void creerBoutonCache(QPushButton *boutonCache, const Carte &carte);

        void on_pushButtonClicked(QPushButton *bouton);

        void Affiche(QPushButton *bt) ;

        QPushButton *boutonsCartes[8];

        QPushButton * boutonsCaches[8];

        bool comparerNumerosCartes(QPushButton *bouton1, QPushButton *bouton2);

        void afficherGagnant();

        void BloquerButton();

private slots:
     void playmusic();

     void rejouer();

    void on_push9_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_25_clicked();

    void on_q_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_3_clicked();

    void startAnimations();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

     void onNameEntered();

     void on_pushButton_17_clicked();

     void on_pushButton_16_clicked();

     void on_pushButton_15_clicked();

     void on_q_2_clicked();

     void on_q_3_clicked();

     void on_q_4_clicked();

     void on_pushButton_19_clicked();

     void on_pushButton_18_clicked();

     void demarrerChronometre();

     void setupUi();
     // jeux
     void on_pushButton1_clicked();

         void on_pushButton2_clicked();

         void on_pushButton3_clicked();

         void on_pushButton4_clicked();

         void on_btnAfficherCarte_clicked();

         void effectuerAnimationInverse(QPushButton *bouton, QRect positionInitiale, int duree);

         void on_pushButton5_clicked();

         void Bloque(QPushButton *bt1 ) ;


         void afficherCarteSiBoutonsCaches();

         void on_pushButton8_clicked();

         void on_pushButton7_clicked();

         void on_pushButton6_clicked();


         void on_pushButton_21_clicked();

         void on_pushButton_22_clicked();

         void on_pushButton_11_clicked();

         void on_q_6_clicked();


         void on_pushButton_23_clicked();


         void on_label_25_linkActivated(const QString &link);

         void on_pushButton_2_clicked();

         void on_pushButton_9_clicked();

         void on_pushButton_20_clicked();

         void on_pushButton_28_clicked();

         void on_pushButton_29_clicked();

         void on_pushButton_24_clicked();

         void on_pushButton_30_clicked();

         void on_pushButton_31_clicked();

          void on_pushButton_33_clicked();


          void on_pushButton_35_clicked();

          void on_pushButton_36_clicked();

          void on_pushButton_34_clicked();

        // Slot pour démarrer le chronomètre
              void arreterChronometre();
              // Slot pour arrêter le chronomètre
              void chronometreTimeout();

              void on_q_8_clicked();

              void on_pushButton_37_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QTime targetTime;
    bool gameRunning;
    QLabel *labels[7];
    QTimer *timer;
    int elapsedTenths;
    QTimer chronometre;
    int tempsEcoule;
    // les variables de jeux
       Jeu deck;
        QList<QPushButton*> cardButtons;
        static int nombreTotalDeCartes;
        Carte cartesAssociees[8];
        int scoreJoueur1;
        int scoreAI;
        int completedAnimationsCount;

        //pour ajouter la music
        QMediaPlayer *playlist;
        QMediaPlaylist *mediaPlaylist;
        QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H

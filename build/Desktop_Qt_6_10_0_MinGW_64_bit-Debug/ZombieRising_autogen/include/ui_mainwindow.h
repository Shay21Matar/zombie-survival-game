/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "gameview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stack;
    QWidget *MainMenuPage;
    QPushButton *startButton;
    QPushButton *infinityButton;
    QPushButton *exitButton;
    QLabel *titleLabel;
    QWidget *StartPage;
    QLabel *startTitleLabel;
    QPushButton *startGameButton;
    QPushButton *backToMenuButton;
    QWidget *GamePage;
    GameView *gameArea;
    QLabel *slot0;
    QLabel *slot1;
    QPushButton *pauseButton;
    QLabel *levelLabel;
    QProgressBar *healthBar;
    QLabel *killsLabel;
    QLabel *scoreLabel;
    QLabel *slot2;
    QWidget *PauseMenuPage;
    QLabel *gamePausedLabel;
    QPushButton *resumeButton;
    QPushButton *mainMenuPauseButton;
    QPushButton *exitPauseButton;
    QLabel *pauseScoreLabel;
    QWidget *Level2Page;
    QLabel *level2Label;
    QLabel *weaponImageLabel;
    QLabel *weaponNameLabel;
    QPushButton *continueButton;
    QWidget *youWonPage;
    QLabel *youWonLabel;
    QPushButton *restartLevelsButton;
    QPushButton *mainMenuWonButton;
    QPushButton *exitGameButton;
    QWidget *YouLostPage;
    QPushButton *restartButton;
    QLabel *label;
    QLabel *finalScoreLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stack = new QStackedWidget(centralwidget);
        stack->setObjectName("stack");
        stack->setGeometry(QRect(9, -10, 781, 561));
        MainMenuPage = new QWidget();
        MainMenuPage->setObjectName("MainMenuPage");
        MainMenuPage->setStyleSheet(QString::fromUtf8("QWidget { background-color: rgb(120, 0, 22) }"));
        startButton = new QPushButton(MainMenuPage);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(280, 230, 200, 50));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        startButton->setFont(font);
        startButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(255, 47, 68); color: white; }"));
        startButton->setIconSize(QSize(30, 30));
        infinityButton = new QPushButton(MainMenuPage);
        infinityButton->setObjectName("infinityButton");
        infinityButton->setGeometry(QRect(280, 290, 200, 50));
        infinityButton->setFont(font);
        infinityButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(255, 127, 0); color: white; }"));
        exitButton = new QPushButton(MainMenuPage);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(280, 350, 200, 50));
        exitButton->setFont(font);
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(255, 47, 68); color: white; }"));
        titleLabel = new QLabel(MainMenuPage);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(260, 170, 261, 51));
        QFont font1;
        font1.setPointSize(28);
        font1.setBold(true);
        titleLabel->setFont(font1);
        titleLabel->setStyleSheet(QString::fromUtf8("QLabel { color: white; }"));
        stack->addWidget(MainMenuPage);
        StartPage = new QWidget();
        StartPage->setObjectName("StartPage");
        StartPage->setStyleSheet(QString::fromUtf8("QWidget { background-color: rgb(120, 0, 22) }"));
        startTitleLabel = new QLabel(StartPage);
        startTitleLabel->setObjectName("startTitleLabel");
        startTitleLabel->setGeometry(QRect(10, 180, 761, 80));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(true);
        startTitleLabel->setFont(font2);
        startTitleLabel->setStyleSheet(QString::fromUtf8("QLabel { color: white; }"));
        startTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        startGameButton = new QPushButton(StartPage);
        startGameButton->setObjectName("startGameButton");
        startGameButton->setGeometry(QRect(280, 300, 220, 60));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        startGameButton->setFont(font3);
        startGameButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 200, 50); color: white; border-radius: 10px; }\n"
"QPushButton:hover { background-color: rgb(70, 220, 70); }"));
        backToMenuButton = new QPushButton(StartPage);
        backToMenuButton->setObjectName("backToMenuButton");
        backToMenuButton->setGeometry(QRect(280, 380, 220, 60));
        backToMenuButton->setFont(font3);
        backToMenuButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(200, 50, 50); color: white; border-radius: 10px; }\n"
"QPushButton:hover { background-color: rgb(220, 70, 70); }"));
        stack->addWidget(StartPage);
        GamePage = new QWidget();
        GamePage->setObjectName("GamePage");
        GamePage->setStyleSheet(QString::fromUtf8("QWidget { background-color: rgb(120, 120, 120) }"));
        gameArea = new GameView(GamePage);
        gameArea->setObjectName("gameArea");
        gameArea->setGeometry(QRect(20, 80, 751, 391));
        gameArea->setStyleSheet(QString::fromUtf8("QWidget { border: 3px solid black; }"));
        slot0 = new QLabel(GamePage);
        slot0->setObjectName("slot0");
        slot0->setGeometry(QRect(10, 480, 61, 61));
        slot0->setFrameShape(QFrame::Shape::Box);
        slot0->setLineWidth(2);
        slot0->setPixmap(QPixmap(QString::fromUtf8(":/images/heal.png")));
        slot0->setScaledContents(true);
        slot1 = new QLabel(GamePage);
        slot1->setObjectName("slot1");
        slot1->setGeometry(QRect(80, 480, 61, 61));
        slot1->setFrameShape(QFrame::Shape::Box);
        slot1->setLineWidth(2);
        slot1->setPixmap(QPixmap(QString::fromUtf8(":/images/shield.png")));
        slot1->setScaledContents(true);
        pauseButton = new QPushButton(GamePage);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setGeometry(QRect(640, 30, 121, 31));
        pauseButton->setFont(font3);
        pauseButton->setStyleSheet(QString::fromUtf8("background-color: rgb(53, 53, 53);\n"
"color: rgb(225, 0, 4);"));
        levelLabel = new QLabel(GamePage);
        levelLabel->setObjectName("levelLabel");
        levelLabel->setGeometry(QRect(340, 30, 91, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("MV Boli")});
        font4.setPointSize(18);
        font4.setBold(false);
        levelLabel->setFont(font4);
        healthBar = new QProgressBar(GamePage);
        healthBar->setObjectName("healthBar");
        healthBar->setGeometry(QRect(10, 20, 211, 23));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("MV Boli")});
        font5.setPointSize(12);
        font5.setBold(false);
        healthBar->setFont(font5);
        healthBar->setStyleSheet(QString::fromUtf8("QProgressBar { background-color: gray; }\n"
"QProgressBar::chunk { background-color: rgb(16, 244, 0); }"));
        healthBar->setValue(100);
        killsLabel = new QLabel(GamePage);
        killsLabel->setObjectName("killsLabel");
        killsLabel->setGeometry(QRect(10, 50, 101, 16));
        killsLabel->setFont(font5);
        scoreLabel = new QLabel(GamePage);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setGeometry(QRect(600, 500, 171, 31));
        scoreLabel->setFont(font4);
        slot2 = new QLabel(GamePage);
        slot2->setObjectName("slot2");
        slot2->setGeometry(QRect(150, 480, 61, 61));
        slot2->setFrameShape(QFrame::Shape::Box);
        slot2->setLineWidth(2);
        slot2->setPixmap(QPixmap(QString::fromUtf8(":/images/powerup.png")));
        slot2->setScaledContents(true);
        stack->addWidget(GamePage);
        PauseMenuPage = new QWidget();
        PauseMenuPage->setObjectName("PauseMenuPage");
        PauseMenuPage->setStyleSheet(QString::fromUtf8("background-color: rgb(120, 120, 120);"));
        gamePausedLabel = new QLabel(PauseMenuPage);
        gamePausedLabel->setObjectName("gamePausedLabel");
        gamePausedLabel->setGeometry(QRect(290, 200, 191, 41));
        QFont font6;
        font6.setPointSize(22);
        font6.setBold(true);
        gamePausedLabel->setFont(font6);
        resumeButton = new QPushButton(PauseMenuPage);
        resumeButton->setObjectName("resumeButton");
        resumeButton->setGeometry(QRect(330, 280, 111, 41));
        resumeButton->setFont(font);
        resumeButton->setStyleSheet(QString::fromUtf8("color: rgb(235, 0, 0);\n"
"background-color: rgb(72, 72, 72);"));
        mainMenuPauseButton = new QPushButton(PauseMenuPage);
        mainMenuPauseButton->setObjectName("mainMenuPauseButton");
        mainMenuPauseButton->setGeometry(QRect(320, 330, 131, 41));
        mainMenuPauseButton->setFont(font);
        mainMenuPauseButton->setStyleSheet(QString::fromUtf8("color: rgb(235, 0, 0);\n"
"background-color: rgb(72, 72, 72);"));
        exitPauseButton = new QPushButton(PauseMenuPage);
        exitPauseButton->setObjectName("exitPauseButton");
        exitPauseButton->setGeometry(QRect(330, 380, 111, 41));
        exitPauseButton->setFont(font);
        exitPauseButton->setStyleSheet(QString::fromUtf8("color: rgb(235, 0, 0);\n"
"background-color: rgb(72, 72, 72);"));
        pauseScoreLabel = new QLabel(PauseMenuPage);
        pauseScoreLabel->setObjectName("pauseScoreLabel");
        pauseScoreLabel->setGeometry(QRect(230, 460, 300, 40));
        pauseScoreLabel->setFont(font3);
        pauseScoreLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        pauseScoreLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stack->addWidget(PauseMenuPage);
        Level2Page = new QWidget();
        Level2Page->setObjectName("Level2Page");
        Level2Page->setStyleSheet(QString::fromUtf8("background-color: rgb(113, 113, 113);"));
        level2Label = new QLabel(Level2Page);
        level2Label->setObjectName("level2Label");
        level2Label->setGeometry(QRect(320, 100, 151, 31));
        level2Label->setFont(font);
        level2Label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        weaponImageLabel = new QLabel(Level2Page);
        weaponImageLabel->setObjectName("weaponImageLabel");
        weaponImageLabel->setGeometry(QRect(180, 70, 421, 351));
        weaponImageLabel->setScaledContents(true);
        weaponNameLabel = new QLabel(Level2Page);
        weaponNameLabel->setObjectName("weaponNameLabel");
        weaponNameLabel->setGeometry(QRect(250, 390, 311, 31));
        QFont font7;
        font7.setPointSize(12);
        font7.setBold(true);
        weaponNameLabel->setFont(font7);
        continueButton = new QPushButton(Level2Page);
        continueButton->setObjectName("continueButton");
        continueButton->setGeometry(QRect(320, 430, 151, 51));
        continueButton->setFont(font2);
        continueButton->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 61, 61);\n"
"color: rgb(236, 0, 4);"));
        stack->addWidget(Level2Page);
        weaponImageLabel->raise();
        level2Label->raise();
        weaponNameLabel->raise();
        continueButton->raise();
        youWonPage = new QWidget();
        youWonPage->setObjectName("youWonPage");
        youWonPage->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 100, 0);"));
        youWonLabel = new QLabel(youWonPage);
        youWonLabel->setObjectName("youWonLabel");
        youWonLabel->setGeometry(QRect(190, 140, 400, 100));
        QFont font8;
        font8.setPointSize(36);
        font8.setBold(true);
        youWonLabel->setFont(font8);
        youWonLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        youWonLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        restartLevelsButton = new QPushButton(youWonPage);
        restartLevelsButton->setObjectName("restartLevelsButton");
        restartLevelsButton->setGeometry(QRect(250, 250, 280, 60));
        restartLevelsButton->setFont(font3);
        restartLevelsButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 200, 50); color: white; border-radius: 10px; }\n"
"QPushButton:hover { background-color: rgb(70, 220, 70); }"));
        mainMenuWonButton = new QPushButton(youWonPage);
        mainMenuWonButton->setObjectName("mainMenuWonButton");
        mainMenuWonButton->setGeometry(QRect(250, 330, 280, 60));
        mainMenuWonButton->setFont(font3);
        mainMenuWonButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(100, 100, 200); color: white; border-radius: 10px; }\n"
"QPushButton:hover { background-color: rgb(120, 120, 220); }"));
        exitGameButton = new QPushButton(youWonPage);
        exitGameButton->setObjectName("exitGameButton");
        exitGameButton->setGeometry(QRect(250, 410, 280, 60));
        exitGameButton->setFont(font3);
        exitGameButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(200, 50, 50); color: white; border-radius: 10px; }\n"
"QPushButton:hover { background-color: rgb(220, 70, 70); }"));
        stack->addWidget(youWonPage);
        YouLostPage = new QWidget();
        YouLostPage->setObjectName("YouLostPage");
        YouLostPage->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 127, 127);"));
        restartButton = new QPushButton(YouLostPage);
        restartButton->setObjectName("restartButton");
        restartButton->setGeometry(QRect(320, 280, 131, 51));
        restartButton->setFont(font);
        restartButton->setStyleSheet(QString::fromUtf8("color: rgb(232, 0, 0);\n"
"background-color: rgb(70, 70, 70);"));
        label = new QLabel(YouLostPage);
        label->setObjectName("label");
        label->setGeometry(QRect(320, 210, 141, 41));
        QFont font9;
        font9.setPointSize(24);
        font9.setBold(true);
        font9.setItalic(true);
        label->setFont(font9);
        finalScoreLabel = new QLabel(YouLostPage);
        finalScoreLabel->setObjectName("finalScoreLabel");
        finalScoreLabel->setGeometry(QRect(210, 370, 351, 40));
        QFont font10;
        font10.setPointSize(20);
        font10.setBold(true);
        finalScoreLabel->setFont(font10);
        finalScoreLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        finalScoreLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stack->addWidget(YouLostPage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        infinityButton->setText(QCoreApplication::translate("MainWindow", "INFINITY", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Zombie Rising", nullptr));
        startTitleLabel->setText(QCoreApplication::translate("MainWindow", "Survive 3 levels to beat the game", nullptr));
        startGameButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        backToMenuButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        slot0->setText(QString());
        slot1->setText(QString());
        pauseButton->setText(QCoreApplication::translate("MainWindow", "PAUSE", nullptr));
        levelLabel->setText(QCoreApplication::translate("MainWindow", "Level 1", nullptr));
        killsLabel->setText(QCoreApplication::translate("MainWindow", "Kills: 0/30", nullptr));
        scoreLabel->setText(QCoreApplication::translate("MainWindow", "Score:", nullptr));
        slot2->setText(QString());
        gamePausedLabel->setText(QCoreApplication::translate("MainWindow", "Game Paused", nullptr));
        resumeButton->setText(QCoreApplication::translate("MainWindow", "RESUME", nullptr));
        mainMenuPauseButton->setText(QCoreApplication::translate("MainWindow", "MAIN MENU", nullptr));
        exitPauseButton->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
        pauseScoreLabel->setText(QCoreApplication::translate("MainWindow", "Score: 0", nullptr));
        level2Label->setText(QCoreApplication::translate("MainWindow", "Level Up! Level 2", nullptr));
        weaponImageLabel->setText(QString());
        weaponNameLabel->setText(QCoreApplication::translate("MainWindow", "New Weapon Unlocked: The Blaster", nullptr));
        continueButton->setText(QCoreApplication::translate("MainWindow", "CONTINUE", nullptr));
        youWonLabel->setText(QCoreApplication::translate("MainWindow", "You Won!", nullptr));
        restartLevelsButton->setText(QCoreApplication::translate("MainWindow", "Restart Levels", nullptr));
        mainMenuWonButton->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        exitGameButton->setText(QCoreApplication::translate("MainWindow", "Exit Game", nullptr));
        restartButton->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "You Lost!", nullptr));
        finalScoreLabel->setText(QCoreApplication::translate("MainWindow", "Final Score: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#pragma once
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void goToGamePage();
    void goToStartPage();
    void goToInfinityStartPage();
    void startNormalGame();
    void startInfinityGame();
    void goToPausePage();
    void resumeGame();
    void restartGame();
    void restartFromLevel1();
    void backToMainMenu();
    void exitGame();
    void checkGameOver();
    void checkLevelUp();
    void continueToLevel2();
    void continueToLevel3();

private:
    Ui::MainWindow *ui;
    bool isInfinityMode;
};

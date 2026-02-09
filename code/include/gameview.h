// incredibly temporary, just testing

#pragma once
#include <QWidget>
#include <QTimer>

class GameController;

class GameView : public QWidget {
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);

    void startGame();
    void pauseGame();
    void resumeGame();
    void resetGame();
    
    GameController* getController() { return controller; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QTimer timer;
    GameController *controller;
};

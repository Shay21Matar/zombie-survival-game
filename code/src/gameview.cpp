#include "gameview.h"
#include "gamecontroller.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

GameView::GameView(QWidget *parent)
    : QWidget(parent), controller(new GameController(this))
{
    setMouseTracking(true);

    connect(&timer, &QTimer::timeout, this, [this]() {
        controller->update();   // game logic step
        update();               // redraw
    });
}

void GameView::startGame() {
    controller->startLevel(1);
    timer.start(16);  // ~60 FPS
}

void GameView::pauseGame() {
    timer.stop();
}

void GameView::resumeGame() {
    timer.start(16);
}

void GameView::resetGame() {
    timer.stop();
    controller->resetGame();
}

void GameView::paintEvent(QPaintEvent *) {
    QPainter p(this);
    controller->draw(p);  // Let controller draw everything
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    // Pass mouse position to controller for head rotation
    controller->setMousePosition(event->pos());
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    // Pass click position to controller for powerup handling
    if (event->button() == Qt::LeftButton) {
        controller->handleClick(event->pos());
    }
}

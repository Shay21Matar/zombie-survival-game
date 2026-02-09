#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontroller.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isInfinityMode(false)
{
    ui->setupUi(this);

    // -------- BUTTON CONNECTIONS -------- //

    // Main Menu Start → go to Start Page (normal mode)
    connect(ui->startButton, &QPushButton::clicked,
            this, &MainWindow::goToStartPage);
    
    // Main Menu Infinity → go to Start Page (infinity mode)
    connect(ui->infinityButton, &QPushButton::clicked,
            this, &MainWindow::goToInfinityStartPage);

    // Main Menu Exit → quit app
    connect(ui->exitButton, &QPushButton::clicked,
            this, &MainWindow::exitGame);
    
    // Start Page Start → start game
    connect(ui->startGameButton, &QPushButton::clicked,
            this, &MainWindow::startNormalGame);
    
    // Start Page Back → back to main menu
    connect(ui->backToMenuButton, &QPushButton::clicked,
            this, &MainWindow::backToMainMenu);

    // Game Page Pause → go to Pause Menu
    connect(ui->pauseButton, &QPushButton::clicked,
            this, &MainWindow::goToPausePage);

    // Pause Menu Resume → return to game
    connect(ui->resumeButton, &QPushButton::clicked,
            this, &MainWindow::resumeGame);

    // Pause Menu Main Menu → return to main menu
    connect(ui->mainMenuPauseButton, &QPushButton::clicked,
            this, &MainWindow::backToMainMenu);

    // Pause Menu Exit → quit app
    connect(ui->exitPauseButton, &QPushButton::clicked,
            this, &MainWindow::exitGame);
    
    // You Lost Page Restart → restart game
    connect(ui->restartButton, &QPushButton::clicked,
            this, &MainWindow::restartGame);
    
    // Level 2 Page Continue → continue to level 2
    connect(ui->continueButton, &QPushButton::clicked,
            this, &MainWindow::continueToLevel2);
    
    // You Won Page Restart Levels → restart from level 1
    connect(ui->restartLevelsButton, &QPushButton::clicked,
            this, &MainWindow::restartFromLevel1);
    
    // You Won Page Main Menu → return to main menu
    connect(ui->mainMenuWonButton, &QPushButton::clicked,
            this, &MainWindow::backToMainMenu);
    
    // You Won Page Exit → quit app
    connect(ui->exitGameButton, &QPushButton::clicked,
            this, &MainWindow::exitGame);
    
    // Connect game controller signals to HUD
    auto* controller = ui->gameArea->getController();
    connect(controller, &GameController::killCountChanged, this, [this](int kills, int goal) {
        if (!isInfinityMode) {
            ui->killsLabel->setText(QString("Kills: %1/%2").arg(kills).arg(goal));
        }
        checkLevelUp();  // Check if player reached kill goal
    });
    connect(controller, &GameController::scoreChanged, this, [this](int score) {
        ui->scoreLabel->setText(QString("Score: %1").arg(score));
        ui->pauseScoreLabel->setText(QString("Score: %1").arg(score));
    });
    connect(controller, &GameController::healthChanged, this, [this](int health) {
        ui->healthBar->setValue(health);
        if (health <= 0) {
            checkGameOver();
        }
    });

    // Set initial page to Main Menu
    ui->stack->setCurrentWidget(ui->MainMenuPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToStartPage()
{
    isInfinityMode = false;
    ui->startTitleLabel->setText("Survive 3 levels to beat the game");
    ui->stack->setCurrentWidget(ui->StartPage);
}

void MainWindow::goToInfinityStartPage()
{
    isInfinityMode = true;
    ui->startTitleLabel->setText("Survive as long as possible and beat your highscore!");
    ui->stack->setCurrentWidget(ui->StartPage);
}

void MainWindow::startNormalGame()
{
    if (isInfinityMode) {
        startInfinityGame();
    } else {
        auto* controller = ui->gameArea->getController();
        controller->startLevel(1);
        ui->levelLabel->setText("Level 1");
        ui->killsLabel->setVisible(true);
        ui->stack->setCurrentWidget(ui->GamePage);
        ui->gameArea->resumeGame();
    }
}

void MainWindow::startInfinityGame()
{
    auto* controller = ui->gameArea->getController();
    controller->startInfinityMode();
    ui->levelLabel->setText("Infinity");
    ui->killsLabel->setVisible(false);
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->resumeGame();
}

void MainWindow::backToMainMenu()
{
    ui->stack->setCurrentWidget(ui->MainMenuPage);
}

void MainWindow::goToGamePage()
{
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->startGame();  // Actually start the game!
}

void MainWindow::goToPausePage()
{
    ui->gameArea->pauseGame();  // Actually pause the game
    ui->stack->setCurrentWidget(ui->PauseMenuPage);
}

void MainWindow::resumeGame()
{
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->resumeGame();  // Resume the game
}

void MainWindow::restartGame()
{
    auto* controller = ui->gameArea->getController();
    
    // Stop any existing timer first
    ui->gameArea->pauseGame();
    
    // Check if in infinity mode
    if (isInfinityMode) {
        controller->startInfinityMode();
        ui->levelLabel->setText("Infinity");
        ui->killsLabel->setVisible(false);
    } else {
        int currentLevel = controller->getLevel();  // Remember what level player was on
        
        // Call startLevel which does the reset
        if (currentLevel >= 3) {
            // If died on level 3, restart level 3
            controller->startLevel(3);
            ui->levelLabel->setText("Level 3");
        } else if (currentLevel >= 2) {
            // If died on level 2, restart level 2
            controller->startLevel(2);
            ui->levelLabel->setText("Level 2");
        } else {
            // Otherwise restart level 1
            controller->startLevel(1);
            ui->levelLabel->setText("Level 1");
        }
        ui->killsLabel->setVisible(true);
    }
    
    // Switch to game page AFTER resetting the game
    ui->stack->setCurrentWidget(ui->GamePage);
    
    // Start the game timer
    ui->gameArea->resumeGame();
}

void MainWindow::restartFromLevel1()
{
    auto* controller = ui->gameArea->getController();
    
    // Stop any existing timer first
    ui->gameArea->pauseGame();
    
    // Always restart from level 1
    controller->startLevel(1);
    ui->levelLabel->setText("Level 1");
    
    // Return to game page and resume
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->resumeGame();
}

void MainWindow::checkGameOver()
{
    ui->gameArea->pauseGame();  // Stop the game
    
    // Update final score label
    auto* controller = ui->gameArea->getController();
    int finalScore = controller->getScore();  // Get actual score from scoreboard
    ui->finalScoreLabel->setText(QString("Final Score: %1").arg(finalScore));
    
    // Show/hide the score label based on mode
    if (isInfinityMode) {
        ui->finalScoreLabel->setVisible(true);
    } else {
        ui->finalScoreLabel->setVisible(false);
    }
    
    ui->stack->setCurrentWidget(ui->YouLostPage);  // Show game over screen
}

void MainWindow::checkLevelUp()
{
    auto* controller = ui->gameArea->getController();
    
    // Don't trigger level up in infinity mode
    if (isInfinityMode) {
        return;
    }
    
    if (controller->shouldLevelUp()) {
        ui->gameArea->pauseGame();  // Pause the game
        
        int currentLevel = controller->getLevel();
        
        // If we just beat level 3, show you won page
        if (currentLevel == 3) {
            ui->stack->setCurrentWidget(ui->youWonPage);
            return;
        }
        
        // Otherwise show level up page
        int nextLevel = currentLevel + 1;
        ui->level2Label->setText(QString("Level Up! Level %1").arg(nextLevel));
        
        // Set weapon image and name based on next level
        if (nextLevel == 2) {
            QPixmap weaponImage(":/images/weapon2.png");
            if (weaponImage.isNull()) {
                weaponImage.load("images/weapon2.png");
            }
            ui->weaponImageLabel->setPixmap(weaponImage);
            ui->weaponNameLabel->setText("New Weapon Unlocked: The Blaster");
        } else if (nextLevel == 3) {
            QPixmap weaponImage(":/images/weapon3.png");
            if (weaponImage.isNull()) {
                weaponImage.load("images/weapon3.png");
            }
            ui->weaponImageLabel->setPixmap(weaponImage);
            ui->weaponNameLabel->setText("New Weapon Unlocked: The NLE Choppa");
        }
        
        ui->stack->setCurrentWidget(ui->Level2Page);  // Show level up screen
    }
}

void MainWindow::continueToLevel2()
{
    auto* controller = ui->gameArea->getController();
    
    // Check if we're advancing from level 1 to 2, or level 2 to 3
    if (controller->getLevel() == 1) {
        controller->advanceToLevel2();  // Setup level 2
        ui->levelLabel->setText("Level 2");
    } else if (controller->getLevel() == 2) {
        controller->advanceToLevel3();  // Setup level 3
        ui->levelLabel->setText("Level 3");
    }
    
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->resumeGame();  // Resume gameplay
}

void MainWindow::continueToLevel3()
{
    auto* controller = ui->gameArea->getController();
    controller->advanceToLevel3();  // Setup level 3
    ui->levelLabel->setText("Level 3");  // Update level label
    ui->stack->setCurrentWidget(ui->GamePage);
    ui->gameArea->resumeGame();  // Resume gameplay
}

void MainWindow::exitGame()
{
    this->close();
}

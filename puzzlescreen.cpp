#include "puzzlescreen.h"
#include "puzzlemodel.h"
#include "randomaialgorithm.h"
#include "greedyaialgorithm.h"
#include "astaraialgorithm.h"

#include <QMessageBox>
#include <QApplication>
#include <QRandomGenerator>

using namespace std;

PuzzleScreen::PuzzleScreen(class PuzzleModel *model, PlayerManager* playerManager, QWidget *parent)
    : QWidget(parent), PuzzleModel(model), playerManager(playerManager) {
    // Create the grid layout, place buttons (tiles) inside, assign them according values and tie them to the click handler
    mainLayout = new QVBoxLayout(this);

    boardLayout = new QGridLayout();
    boardLayout->setSpacing(0);
    boardLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(boardLayout);

    statsLayout = new QHBoxLayout();
    movesLabel = new QLabel("Moves: 0");
    timerLabel = new QLabel("Time: 0 s");
    statsLayout->addWidget(movesLabel);
    statsLayout->addWidget(timerLabel);
    mainLayout->addLayout(statsLayout);

    setLayout(mainLayout);
}

void PuzzleScreen::displayPuzzle(QString algorithm) {
    QLayoutItem *child;
    while ((child = boardLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    statsHandler = new StatsHandler(this);
    connect(statsHandler, &StatsHandler::movesUpdated, this, &PuzzleScreen::updateMovesDisplay);
    connect(statsHandler, &StatsHandler::timeUpdated, this, &PuzzleScreen::updateTimeDisplay);
    statsHandler->startTimer();

    int boardSize = PuzzleModel->getBoardSize();
    buttons.clear();
    buttons.resize(boardSize, QVector<QPushButton*>(boardSize));
    int tileSize = min(300/boardSize, 100);

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(tileSize, tileSize);
            boardLayout->addWidget(button, row, col);
            buttons[row][col] = button;

            connect(button, &QPushButton::clicked, this, &PuzzleScreen::handleButtonClick);
        }
    }

    updateView();

    if (playerManager->getCurrentPlayerIsAI()) {
        if (algorithm == "Random") {
            aiAlgorithm = new RandomAIAlgorithm();
        } else if (algorithm == "Greedy") {
            aiAlgorithm = new GreedyAIAlgorithm();
        } else if (algorithm == "A*") {
            aiAlgorithm = new AStarAIAlgorithm();
        }

        QTimer::singleShot(100, this, [this]() {
            makeAIMove();
        });
    }
}

void PuzzleScreen::updateView() {
    // Update the view based on the model and check if the puzzle is solved
    QVector<QVector<int>> board = PuzzleModel->getBoard();
    int boardSize = PuzzleModel->getBoardSize();

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            int value = board[row][col];
            if (value == 0) {
                buttons[row][col]->setText("");
                buttons[row][col]->setEnabled(false);
            } else {
                buttons[row][col]->setText(QString::number(value));
                buttons[row][col]->setEnabled(true);
            }
        }
    }

    checkIfSolved();
}

void PuzzleScreen::handleButtonClick() {
    // Buttons' click handler - call the moveTile() method on the clicked tile
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int boardSize = PuzzleModel->getBoardSize();
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            if (buttons[row][col] == clickedButton) {
                if (PuzzleModel->moveTile(PuzzleModel->getBoard()[row][col])) {
                    statsHandler->increaseMoveCount();
                    updateView();
                }
                return;
            }
        }
    }
}

void PuzzleScreen::checkIfSolved() {
    // Handle solved puzzle
    if (PuzzleModel->isSolved()) {
        statsHandler->stopTimer();
        emit puzzleCompleted(statsHandler->getMoveCount(), statsHandler->getElapsedTime(), PuzzleModel->getBoardSize());
        QMessageBox msgBox;
        msgBox.setWindowTitle("Puzzle Solved");
        msgBox.setText("Congratulations! You solved the puzzle!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int result = msgBox.exec();

        switch(result) {
            case QMessageBox::Ok:
                emit goBackToHomeScreen();
                break;
        }
    }
}

void PuzzleScreen::updateMovesDisplay(int moves) {
    movesLabel->setText(QString("Moves: %1").arg(moves));
}

void PuzzleScreen::updateTimeDisplay(int timeElapsed) {
    timerLabel->setText(QString("Time: %1 s").arg(timeElapsed));
}

void PuzzleScreen::makeAIMove() {
    if (PuzzleModel->isSolved()) {
        return;
    }


    if (aiAlgorithm) {
        int move = aiAlgorithm->chooseMove(*PuzzleModel);
        if (move != -1) {
            PuzzleModel->moveTile(move);
            statsHandler->increaseMoveCount();
            QTimer::singleShot(0, this, &PuzzleScreen::makeAIMove);
        }
    }

    updateView();
}

#include "puzzlescreen.h"
#include "puzzlemodel.h"

#include <QMessageBox>
#include <QApplication>
#include <iostream>

using namespace std;

PuzzleScreen::PuzzleScreen(class PuzzleModel *model, QWidget *parent) : QWidget(parent), PuzzleModel(model) {
    // Create the grid layout, place buttons (tikes) inside, assign them according values and tie them to the click handler
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);
}

void PuzzleScreen::displayPuzzle() {
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    statsHandler = new StatsHandler(this);
    connect(statsHandler, &StatsHandler::movesUpdated, this, &PuzzleScreen::updateMovesDisplay);
    connect(statsHandler, &StatsHandler::timeUpdated, this, &PuzzleScreen::updateTimeDisplay);
    statsHandler->startTimer();

    statsLabel = new QLabel("Moves: 0");
    timerLabel = new QLabel("Time: 0 s");

    gridLayout->addWidget(statsLabel, PuzzleModel->getBoardSize(), 0, 1, PuzzleModel->getBoardSize());
    gridLayout->addWidget(timerLabel, PuzzleModel->getBoardSize() + 1, 0, 1, PuzzleModel->getBoardSize());

    int boardSize = PuzzleModel->getBoardSize();
    buttons.clear();
    buttons.resize(boardSize, QVector<QPushButton*>(boardSize));

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(80, 80);
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;

            connect(button, &QPushButton::clicked, this, &PuzzleScreen::handleButtonClick);
        }
    }

    updateView();
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
    statsLabel->setText(QString("Moves: %1").arg(moves));
}

void PuzzleScreen::updateTimeDisplay(int timeElapsed) {
    timerLabel->setText(QString("Time: %1 s").arg(timeElapsed));
}

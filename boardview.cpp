#include "boardview.h"
#include "boardmodel.h"

#include <QMessageBox>
#include <QApplication>
#include <iostream>

using namespace std;

BoardView::BoardView(BoardModel *model, QWidget *parent) : QWidget(parent), boardModel(model) {
    // Create the grid layout, place buttons (tikes) inside, assign them according values and tie them to the click handler
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    statsHandler = new StatsHandler(this);
    connect(statsHandler, &StatsHandler::movesUpdated, this, &BoardView::updateMovesDisplay);
    connect(statsHandler, &StatsHandler::timeUpdated, this, &BoardView::updateTimeDisplay);
    statsHandler->startTimer();

    statsLabel = new QLabel("Moves: 0");
    timerLabel = new QLabel("Time: 0 s");

    gridLayout->addWidget(statsLabel, boardModel->getBoardSize(), 0, 1, boardModel->getBoardSize());
    gridLayout->addWidget(timerLabel, boardModel->getBoardSize() + 1, 0, 1, boardModel->getBoardSize());

    int boardSize = boardModel->getBoardSize();
    buttons.resize(boardSize, QVector<QPushButton*>(boardSize));

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            QPushButton *button = new QPushButton();
            button->setFixedSize(80, 80);
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;

            connect(button, &QPushButton::clicked, this, &BoardView::handleButtonClick);
        }
    }

    updateView();
}

void BoardView::updateView() {
    // Update the view based on the model and check if the puzzle is solved
    QVector<QVector<int>> board = boardModel->getBoard();
    int boardSize = boardModel->getBoardSize();

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

void BoardView::handleButtonClick() {
    // Buttons' click handler - call the moveTile() method on the clicked tile
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int boardSize = boardModel->getBoardSize();
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            if (buttons[row][col] == clickedButton) {
                if (boardModel->moveTile(boardModel->getBoard()[row][col])) {
                    updateView();
                    statsHandler->increaseMoveCount();
                }
                return;
            }
        }
    }
}

void BoardView::checkIfSolved() {
    // Handle solved puzzle
    if (boardModel->isSolved()) {
        statsHandler->stopTimer();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Puzzle Solved");
        msgBox.setText("Congratulations! You solved the puzzle!");
        cout << statsHandler->getMoveCount() << " moves" << endl;
        cout << statsHandler->getElapsedTime() << " s" << endl;
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        int result = msgBox.exec();

        switch(result) {
            case QMessageBox::Ok:
                emit backToLandingPage();
                break;
        }
    }
}

void BoardView::updateMovesDisplay(int moves) {
    statsLabel->setText(QString("Moves: %1").arg(moves));
}

void BoardView::updateTimeDisplay(int timeElapsed) {
    timerLabel->setText(QString("Time: %1 s").arg(timeElapsed));
}

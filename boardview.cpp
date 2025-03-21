#include "boardview.h"
#include "boardmodel.h"

#include <QMessageBox>
#include <QApplication>

using namespace std;

BoardView::BoardView(BoardModel *model, QWidget *parent) : QWidget(parent), boardModel(model) {
    // Create the grid layout, place buttons (tikes) inside, assign them according values and tie them to the click handler
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

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
                boardModel->moveTile(boardModel->getBoard()[row][col]);
                updateView();
                return;
            }
        }
    }
}

void BoardView::checkIfSolved() {
    // Handle solved puzzle
    if (boardModel->isSolved()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Puzzle Solved");
        msgBox.setText("Congratulations! You solved the puzzle!");
        msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
        msgBox.setDefaultButton(QMessageBox::Retry);

        int result = msgBox.exec();

        switch(result) {
            case QMessageBox::Retry:
                boardModel->shuffle();
                updateView();
                break;
            case QMessageBox::Close:
                QApplication::quit();
                break;
        }
    }
}

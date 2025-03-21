#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>

#include <boardmodel.h>


class BoardView : public QWidget {
    Q_OBJECT

private:
    BoardModel *boardModel;
    QGridLayout *gridLayout;
    QVector<QVector<QPushButton*>> buttons;

public:
    explicit BoardView(BoardModel *model, QWidget *parent = nullptr);
    void updateView();

private slots:
    void handleButtonClick();
    void checkIfSolved();
};

#endif // BOARDVIEW_H

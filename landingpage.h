#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

class LandingPage : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout *layout;
    QComboBox *boardSizeDropdown;
    QPushButton *startButton;

public:
    explicit LandingPage(QWidget *parent = nullptr);

signals:
    void boardSizeSelected(int boardSize);

private slots:
    void onStartClicked();
};

#endif // LANDINGPAGE_H

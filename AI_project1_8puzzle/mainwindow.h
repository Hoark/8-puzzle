#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<QTime>
#include<QCoreApplication>
#include<QEventLoop>
#include<QSlider>
#include<QDoubleSpinBox>
#include "solve.h"

#define N 3

class QLabel;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);
    virtual ~mainWindow(){};

private slots:
    void tilesRandom();
    void tilesSet();
    void startSolve();
    void updateSliderSpeed(int position);
    void updateBoxSpeed(double value);

private:
    void setupMenu();
    void setupTiles();
    void showTiles();
    void printPath(Node* end);
    void setupStart();
    void showStart(int matrix[N][N]);
    void setupGoal();
    void showGoal(int matrix[N][N]);

    int matrix[N][N] = {{0,1,2},{3,4,5},{6,7,8}};
    double speed = 0.1;

    QLabel* tiles[9];
    QPushButton* buttonRandom;
    QPushButton* buttonSetTiles;
    QPushButton* buttonSolve;
    QTextEdit* inputArea;
    QLabel *tipInputArea;
    QLabel* startState;
    QLabel* tilesStart[9];
    QLabel* endState;
    QLabel* tilesGoal[9];
    QLabel* status;
    QLabel* labelSpeed;
    QSlider* sliderSpeed;
    QDoubleSpinBox* boxSpeed;
};

void delay(unsigned milliseconds);

#endif // MAINWINDOW_H

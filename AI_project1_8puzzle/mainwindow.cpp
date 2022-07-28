#include "mainwindow.h"
#include <QString>
#include<QList>
#include<QThread>

#define N 3

mainWindow::mainWindow(QWidget*parent):QMainWindow(parent)
{
    setupTiles();
    setupMenu();

    setupStart();
    setupGoal();


    for (int i =0; i<3 ;i++ )
    {
        for (int j =0;j<3 ;j++ )
        {
            tiles[(i*3)+j]->setGeometry(190+(145*j),10+(145*i),135,135);
        }
    }

    connect(buttonRandom, SIGNAL(clicked(bool)),this, SLOT(tilesRandom()));
    connect(buttonSetTiles, SIGNAL(clicked(bool)), this, SLOT(tilesSet()));
    connect(buttonSolve, SIGNAL(clicked(bool)), this, SLOT(startSolve()));
    connect(sliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(updateSliderSpeed(int)));
    connect(boxSpeed, SIGNAL(valueChanged(double)), this, SLOT(updateBoxSpeed(double)));
}

void mainWindow::setupMenu()
{
    buttonRandom = new QPushButton("随机生成一个九宫排列",this);
    buttonRandom->setGeometry(10,440,150,30);

    buttonSetTiles = new QPushButton("自定一个九宫排列",this);
    buttonSetTiles->setGeometry(10,380,150,30);

    inputArea = new QTextEdit(this);
    inputArea->setGeometry(10,220,150,150);
    inputArea->setText("1 2 3\n8 0 4\n7 6 5");
    QFont font = inputArea->font();
    font.setPointSize(24);
    inputArea->setFont(font);

    tipInputArea = new QLabel("请按以下格式输入九宫排列",this);
    tipInputArea->setGeometry(10,200,150,20);

    buttonSolve = new QPushButton("求解",this);
    buttonSolve->setGeometry(480,440,135,30);

    status = new QLabel("请设计一个九宫排列",this);
    status->setGeometry(245,440,150,30);
    status->setStyleSheet("color: red");
    status->setAlignment(Qt::AlignCenter);

    sliderSpeed = new QSlider(Qt::Horizontal, this);
    sliderSpeed->setGeometry(10,170,150,20);
    sliderSpeed->setMinimum(1); //0.1个操作每秒
    sliderSpeed->setMaximum(1000); //100个操作每秒

    boxSpeed = new QDoubleSpinBox(this);
    boxSpeed->setGeometry(50,140,100,20);
    boxSpeed->setRange(0.1,100);
    boxSpeed->setValue(0.1);
    boxSpeed->setSingleStep(1);
    boxSpeed->setSuffix("个操作/s");

    labelSpeed = new QLabel("速度：",this);
    labelSpeed->setGeometry(10,140,50,20);
}

void mainWindow::setupTiles()
{
    for (int i = 0; i<9; i++ )
    {
      tiles[i] = new QLabel(this);
      tiles[i]->setText(QString::number(matrix[0][i]));
      QFont font = tiles[i]->font();
      font.setPointSize(72);
      font.setBold(true);
      tiles[i]->setFont(font);
      tiles[i]->setStyleSheet("border: 1px solid black");
    }
    showTiles();
}

void mainWindow::showTiles()
{
    for (int i = 0; i<9; i++ )
    {
      tiles[i]->setText(QString::number(matrix[0][i]));
    }
}

void mainWindow::tilesRandom()
{

    int array[N*N];
        for (int i = 0; i < N*N; i++)
        {
            array[i] = i;
        }

        for (int i = 0; i < N*N; i++)
        {
            int j = rand()%(N*N);
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }

        for (int i = 0; i < N*N; i++)
        {
            matrix[0][i] = array[i];
        }
    showTiles();
}

void mainWindow::tilesSet()
{
    //QList< QList<double> > matrix;
    int i=0,j=0,n=0; int array[9]; int matrix2[N][N]; bool flag =true;

    foreach( QString row, inputArea->toPlainText().split("\n") )
    {
        j=0;
        foreach( QString val, row.split(" ") )
        {
            if(val<'0'||val>'8')
            {
                flag = false;
                break;
            }

            int x = val.toUInt();

            for (int k =0;k<n ;k++ )
            {
                if(array[k] == x)
                {
                    flag = false;
                    break;
                }
            }

            if(flag)
            {
                matrix2[i][j] = x;
                array[n] = x;
                n++;
                if (n>N*N)
                {
                    flag = false;
                    break;
                }
            }

            if (!flag)
                break;

            j++;
        }
        i++;
        if (!flag)
            break;
    }

    if(n != N*N)
        flag = false;

    if(flag)
    {
      copyMatrix(matrix,matrix2);
      showTiles();
    }else{
        inputArea->setText("Invalid Input!");
    }

}

void mainWindow::updateSliderSpeed(int position)
{
    boxSpeed->setValue(double(double(position)/double(10)));
    speed=position/10;
}

void mainWindow::updateBoxSpeed(double value)
{
    sliderSpeed->setValue(value*10);
    speed=value;
}

int goal1[N][N] ={{1,2,3},{8,0,4},{7,6,5}};
int goal2[N][N] ={{2,1,3},{8,0,4},{7,6,5}};

void mainWindow::startSolve()
{
    status->setText("正在求解中");
    status->setStyleSheet("color: orange");

    Node *end;
    int row0 ,col0;
    getZero(row0, col0, matrix);

    if (getGoal(matrix))
    {
        showStart(this->matrix); showGoal(goal1);
            end = Solve(matrix, row0,col0,goal1);
    }else
    {
        showStart(this->matrix); showGoal(goal2);
            end = Solve(matrix, row0,col0,goal2);
    }
    printPath(end);

    status->setText("求解完成！");
    status->setStyleSheet("color: green");
}

void mainWindow::printPath(Node *current)
{
    if (current == NULL)
            return;
    printPath(current->parent);

    copyMatrix(this->matrix, current->matrix);
    delay(double(1000)/double(speed));
    showTiles();
    this->update();
}

void delay(unsigned milliseconds)
{
    QTime dieTime= QTime::currentTime().addMSecs(milliseconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void mainWindow::setupStart()
{
    startState = new QLabel("初始状态",this);
    startState->setGeometry(10,10,60,20);

    for (int i = 0; i<9; i++ )
    {
      tilesStart[i] = new QLabel(this);
      tilesStart[i]->setText(QString::number(matrix[0][i]));
      QFont font = tilesStart[i]->font();
      font.setPointSize(10);
      font.setBold(true);
      tilesStart[i]->setFont(font);
      tilesStart[i]->setStyleSheet("border: 1px solid black");
    }
    for (int i =0; i<3 ;i++ )
    {
        for (int j =0;j<3 ;j++ )
        {
            tilesStart[(i*3)+j]->setGeometry(10+(20*j),30+(20*i),15,15);
        }
    }
}

void mainWindow::showStart(int matrix[N][N])
{
    for (int i = 0; i<9; i++ )
    {
      tilesStart[i]->setText(QString::number(matrix[0][i]));
    }
}

void mainWindow::setupGoal()
{
    startState = new QLabel("目标状态",this);
    startState->setGeometry(90,10,60,20);


    for (int i = 0; i<9; i++ )
    {
      tilesGoal[i] = new QLabel(this);
      tilesGoal[i]->setText(QString::number(matrix[0][i]));
      QFont font = tilesGoal[i]->font();
      font.setPointSize(10);
      font.setBold(true);
      tilesGoal[i]->setFont(font);
      tilesGoal[i]->setStyleSheet("border: 1px solid black");
    }
    for (int i =0; i<3 ;i++ )
    {
        for (int j =0;j<3 ;j++ )
        {
            tilesGoal[(i*3)+j]->setGeometry(90+(20*j),30+(20*i),15,15);
        }
    }
}

void mainWindow::showGoal(int matrix[N][N])
{
    for (int i = 0; i<9; i++ )
    {
      tilesGoal[i]->setText(QString::number(matrix[0][i]));
    }
}

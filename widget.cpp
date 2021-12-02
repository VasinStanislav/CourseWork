#include "widget.h"

/*------------------------Начальная инициализация обработчика матрицы--------------------------------------*/

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
   MatrixHandler *matrixA = new MatrixHandler();
   matrices.append(matrixA);
   layout = new QVBoxLayout(this);

   createMatrix();
}

/*------------------------Задание нового значения для размера матрицы--------------------------------------*/

void Widget::createMatrix()
{
    clearLayout(this->layout);

    QLabel *label = new QLabel("Введите размер треугольной матрицы (одно число)", this);
    QLineEdit *line = new QLineEdit(this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    QPushButton *acceptButton = new QPushButton("Принять", this);

    //label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labels.append(label);
    lines.append(line);
    buttons.append(acceptButton);

    layout->setSpacing(50);
    layout->addWidget(line);
    layout->addWidget(label);
    layout->addWidget(acceptButton);

    if (matrices.at(0)->getColumnsAndRows() > 0)
    {
        buttons.append(cancelButton);
        layout->addWidget(cancelButton);
        connect(cancelButton, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
    }
    else
    {
        delete cancelButton;
    }

    connect(acceptButton, &QPushButton::clicked, this, &Widget::onCreateMatrix);
}

/*------------------------Построчный ввод матрицы--------------------------------------*/

void Widget::fillMatrix()
{
    clearLayout(this->layout);

    int i = matrices.at(0)->getRowInd()+1;
    QString str = QStringLiteral("Введите %1-ую строку\nВводите числа через пробел").arg(i);

    QLineEdit *currentLine = new QLineEdit(this);
    QLabel *label = new QLabel(str, this);
    QPushButton *buttonAccept = new QPushButton("Принять", this);
    QPushButton *buttonCancel = new QPushButton("Отмена", this);

    lines.append(currentLine);
    labels.append(label);
    buttons.append(buttonAccept);
    buttons.append(buttonCancel);

    currentLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(currentLine);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(label);
    buttonAccept->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(buttonAccept);
    buttonCancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(buttonCancel);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onFillMatrix);
    connect(buttonCancel, &QPushButton::clicked, this, &Widget::onCancel);
}

/*------------------------Установление значения ij-ого элемента матрицы--------------------------------------*/

void Widget::setElValue()
{
    clearLayout(this->layout);

    QLabel *label1 = new QLabel("Введите индекс элемента (номера строки и столбца через пробел)", this);
    QLineEdit *inputInd = new QLineEdit(this);
    QLabel *label2 = new QLabel("Введите новое значение для элемента", this);
    QLineEdit *inputValue = new QLineEdit(this);
    QLabel *label3 = new QLabel("", this);
    QPushButton *buttonAccept = new QPushButton("Принять", this);
    QPushButton *buttonEsc = new QPushButton("Отмена", this);

    labels.append(label1);
    labels.append(label2);
    labels.append(label3);
    lines.append(inputInd);
    lines.append(inputValue);
    buttons.append(buttonAccept);
    buttons.append(buttonEsc);

    inputInd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    inputValue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonAccept->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonEsc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(label1);
    layout->addWidget(inputInd);
    layout->addWidget(label2);
    layout->addWidget(inputValue);
    layout->addWidget(label3);
    layout->addWidget(buttonAccept);
    layout->addWidget(buttonEsc);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onSetElValue);
    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

/*------------------------Получение значения ij-ого элемента матрицы--------------------------------------*/

void Widget::getElValue()
{
    clearLayout(this->layout);

    QLabel *label1 = new QLabel("Введите индекс элемента (номера строки и столбца через пробел)", this);
    QLineEdit *currentLine = new QLineEdit(this);
    QLabel *label2 = new QLabel("", this);
    QPushButton *buttonAccept = new QPushButton("Принять", this);
    QPushButton *buttonEsc = new QPushButton("Выйти в меню", this);

    labels.append(label1);
    labels.append(label2);
    lines.append(currentLine);
    buttons.append(buttonAccept);
    buttons.append(buttonEsc);

    currentLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonAccept->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonEsc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(label1);
    layout->addWidget(currentLine);
    layout->addWidget(label2);
    layout->addWidget(buttonAccept);
    layout->addWidget(buttonEsc);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onGetElValue);
    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

/*------------------------Сложение двух матрицы--------------------------------------*/

void Widget::matrixAddition()
{
    clearLayout(this->layout);

    QLabel *label = new QLabel("Для начала выберите способ получения матрицы B");
    QPushButton *buttonCreate = new QPushButton("Создать матрицу");
    QPushButton *buttonRead = new QPushButton("Взять из файла");
    QPushButton *buttonCancel = new QPushButton("Отмена");

    labels.append(label);
    buttons.append(buttonCreate);
    buttons.append(buttonRead);
    buttons.append(buttonCancel);

    buttonCreate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonRead->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonCancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(label);
    layout->addWidget(buttonCreate);
    layout->addWidget(buttonRead);
    layout->addWidget(buttonCancel);

    if (matrices.size() < 3)
    {
        MatrixHandler *matrixB = new MatrixHandler("Matrix_B");
        matrices.append(matrixB);
    }
    matrices.at(1)->createMatrix(matrices.at(0)->getColumnsAndRows());
    matrices.at(1)->setAdding(true);
    matrices.swapItemsAt(0, 1);

    connect(buttonCreate, &QPushButton::clicked, this, &Widget::fillMatrix);
    connect(buttonRead, &QPushButton::clicked, this, &Widget::onReadMatrixB);
    connect(buttonCancel, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::doAddition()
{
    clearLayout(this->layout);

    matrices.at(0)->setAdding(false);
    matrices.swapItemsAt(0, 1);

    if (matrices.size() < 3)
    {
        MatrixHandler *matrixC = new MatrixHandler("Matrix_C");
        matrices.append(matrixC);
    }
    matrices.back()->createMatrix(matrices.at(0)->getColumnsAndRows());
    matrices.back()->doAdding(matrices.at(0)->getElements(), matrices.at(1)->getElements());
    matrices.swapItemsAt(0, 2);

    QLabel *label = new QLabel("\tA + B = ");
    labels.append(label);
    layout->addWidget(label);

    doPrint();
    matrices.swapItemsAt(0, 2);

    QPushButton *buttonEsc = new QPushButton("Выйти в меню");
    buttons.append(buttonEsc);
    layout->addWidget(buttonEsc);
    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

/*------------------------Вывод матрицы--------------------------------------*/

void Widget::doPrint()
{
    int rows = matrices.at(0)->getColumnsAndRows();
    for (int i = 1; i <= rows; i++)
    {
        QString line = matrices.at(0)->getLine(i);
        if (line == "") { continue; }
        QLabel *label = new QLabel(line);
        labels.append(label);
        layout->addWidget(label);
    }
}

/*------------------------Проверка на равенство двух матриц--------------------------------------*/

void Widget::checkMatrices()
{
    clearLayout(this->layout);

    QLabel *label = new QLabel("Выберите матрицу из предложенных вариантов");
    QPushButton *buttonFile = new QPushButton("Из файла");
    QPushButton *buttonCancel = new QPushButton("Отмена");

    buttonFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonCancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labels.append(label);
    buttons.append(buttonFile);

    layout->addWidget(label);
    layout->addWidget(buttonFile);

    if (matrices.size()>1)
    {
        QPushButton *buttonList = new QPushButton("Из списка матриц");
        buttonList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        buttons.append(buttonList);
        layout->addWidget(buttonList);

        connect(buttonList, &QPushButton::clicked, this, &Widget::onCheckMatrices2);
    }

    buttons.append(buttonCancel);
    layout->addWidget(buttonCancel);

    connect(buttonFile, &QPushButton::clicked, this, &Widget::onCheckMatrices1);
    connect(buttonCancel, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

/*------------------------Присвоение матрице A значения матрицы B--------------------------------------*/

void Widget::setA()
{
    clearLayout(this->layout);

    QLabel *label = new QLabel("Выберите матрицу из предложенных вариантов");
    QPushButton *buttonFile = new QPushButton("Из файла");
    QPushButton *buttonCancel = new QPushButton("Отмена");

    buttonFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonCancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labels.append(label);
    buttons.append(buttonFile);

    layout->addWidget(label);
    layout->addWidget(buttonFile);

    if (matrices.size()>1)
    {
        QPushButton *buttonList = new QPushButton("Из списка матриц");
        buttonList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        buttons.append(buttonList);
        layout->addWidget(buttonList);

        connect(buttonList, &QPushButton::clicked, this, &Widget::onSetA1);
    }

    buttons.append(buttonCancel);
    layout->addWidget(buttonCancel);

    connect(buttonFile, &QPushButton::clicked, this, &Widget::onSetA2);
    connect(buttonCancel, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

/*------------------------Создание меню в виде графического интерфейса--------------------------------------*/

void Widget::setMenu()
{
    QLabel *label = new QLabel("Выберите операцию с матрицей", this);
    labels.append(label);
    layout->setSpacing(10);
    layout->addWidget(label);

    QPushButton *button1 = new QPushButton("Создать матрицу заново", this);
    QPushButton *button2 = new QPushButton("Установить значение для ij-ого элемента", this);
    QPushButton *button3 = new QPushButton("Получить значение ij-ого элемента", this);
    QPushButton *button4 = new QPushButton("Построчно ввести матрицу", this);
    QPushButton *button5 = new QPushButton("Построчно вывести матрицу", this);
    QPushButton *button6 = new QPushButton("Сложить две треугольные матрицы", this);
    QPushButton *button7 = new QPushButton("Проверить равенство двух матриц", this);
    QPushButton *button8 = new QPushButton("Записать матрицу в файл", this);
    QPushButton *button9 = new QPushButton("Прочесть матрицу из файла", this);
    QPushButton *button10 = new QPushButton("Присвоить матрице значения матрицы", this);
    QPushButton *button11 = new QPushButton("Выйти", this);

    buttons.append(button1);
    buttons.append(button2);
    buttons.append(button3);
    buttons.append(button4);
    buttons.append(button5);
    buttons.append(button6);
    buttons.append(button7);
    buttons.append(button8);
    buttons.append(button9);
    buttons.append(button10);
    buttons.append(button11);

    QList<QPushButton *>::iterator buttonIt;
    for (buttonIt = buttons.begin(); buttonIt != buttons.end(); buttonIt++)
    {
        buttonIt.operator*()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(*buttonIt);
    }


    connect(button1, &QPushButton::clicked, this, &Widget::createMatrix);
    connect(button2, &QPushButton::clicked, this, &Widget::setElValue);
    connect(button3, &QPushButton::clicked, this, &Widget::getElValue);
    connect(button4, &QPushButton::clicked, this, &Widget::fillMatrix);
    connect(button5, &QPushButton::clicked, this, &Widget::onPrint);
    connect(button6, &QPushButton::clicked, this, &Widget::matrixAddition);
    connect(button7, &QPushButton::clicked, this, &Widget::checkMatrices);
    connect(button8, &QPushButton::clicked, this, &Widget::onWriteInFile);
    connect(button9, &QPushButton::clicked, this, &Widget::onReadFromFile);
    connect(button10, &QPushButton::clicked, this, &Widget::setA);
    connect(button11, &QPushButton::clicked, this, &QApplication::quit);
}

/*------------------------Обработчики событий--------------------------------------*/

void Widget::onSetA1()
{
    clearLayout(this->layout);

    QLabel *label = new QLabel("Успешно");
    QPushButton *buttonAccept = new QPushButton("Принять");
    matrices.at(0)->setElValues(matrices.at(1)->getElements());

    labels.append(label);
    buttons.append(buttonAccept);

    layout->addWidget(label);
    layout->addWidget(buttonAccept);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onEscapeToMenu);

}

void Widget::onSetA2()
{
    clearLayout(this->layout);

    MatrixHandler *matrixB = new MatrixHandler("Matrix_B");
    matrixB->readFromFile();
    matrices.append(matrixB);

    QLabel *label = new QLabel("Успешно");
    QPushButton *buttonAccept = new QPushButton("Принять");

    matrices.at(0)->setElValues(matrices.at(1)->getElements());

    labels.append(label);
    buttons.append(buttonAccept);

    layout->addWidget(label);
    layout->addWidget(buttonAccept);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onCheckMatrices1()
{
    clearLayout(this->layout);

    MatrixHandler *matrixB = new MatrixHandler("Matrix_B");
    matrixB->readFromFile();
    matrices.append(matrixB);

    QLabel *label;
    QPushButton *buttonAccept = new QPushButton("Принять");
    if (matrices.at(0)->compareElements(matrices.at(1)->getElements())) { label = new QLabel("Матрица A равна матрице B"); }
    else { label = new QLabel("Матрица A не равна матрице B"); }

    labels.append(label);
    buttons.append(buttonAccept);

    layout->addWidget(label);
    layout->addWidget(buttonAccept);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onCheckMatrices2()
{
    clearLayout(this->layout);

    QLabel *label;
    QPushButton *buttonAccept = new QPushButton("Принять");
    if (matrices.at(0)->compareElements(matrices.at(1)->getElements())) { label = new QLabel("Матрица A равна матрице B"); }
    else { label = new QLabel("Матрица A не равна матрице B"); }

    labels.append(label);
    buttons.append(buttonAccept);

    layout->addWidget(label);
    layout->addWidget(buttonAccept);

    connect(buttonAccept, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onReadMatrixB()
{
    clearLayout(this->layout);
    matrices.at(0)->readFromFile();

    QLabel *label = new QLabel("Успешно!");
    QPushButton *buttonNext = new QPushButton("Ок");
    labels.append(label);
    buttons.append(buttonNext);
    layout->addWidget(label);
    layout->addWidget(buttonNext);
    buttonNext->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(buttonNext, &QPushButton::clicked, this, &Widget::doAddition);
}

void Widget::onReadFromFile()
{
    clearLayout(this->layout);
    matrices.at(0)->readFromFile();

    QLabel *label = new QLabel("Успешно!");
    QPushButton *buttonEsc = new QPushButton("Ок");
    labels.append(label);
    buttons.append(buttonEsc);
    layout->addWidget(label);
    layout->addWidget(buttonEsc);
    buttonEsc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onWriteInFile()
{
    clearLayout(this->layout);
    matrices.at(0)->writeInFile();

    QLabel *label = new QLabel("Успешно!");
    QPushButton *buttonEsc = new QPushButton("Ок");
    labels.append(label);
    buttons.append(buttonEsc);
    layout->addWidget(label);
    layout->addWidget(buttonEsc);
    buttonEsc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onCreateMatrix()
{
    QString currentLine = lines.back()->text();
    bool isDigit;
    int columnsAndRows = currentLine.toInt(&isDigit, 10);

    if (isDigit)
    {
        if (columnsAndRows <= 50 and columnsAndRows >= 2)
        {
            matrices.at(0)->createMatrix(columnsAndRows);
            disconnect(buttons.back(), &QPushButton::clicked, this, &Widget::onCreateMatrix);
            clearLayout(this->layout);
            setMenu();
        }
        else
        {
            labels.back()->setText("Пожалуйста, введите число в диапазоне [2 ; 50]");
        }
    }
    else
    {
        labels.back()->setText("Ошибка ввода, введите размер треугольной матрицы без лишних знаков");
    }
}

void Widget::onFillMatrix()
{
    QString curLine = lines.back()->text();
    curLine.append(" ");

    int columnsAndRows = matrices.at(0)->getColumnsAndRows();
    int curRow = matrices.at(0)->getRowInd();
    int spaces = 0;

    QString curRowInd;
    curRowInd.setNum(curRow+1);

    bool digits = true;
    for (int i = 0; i < curLine.size(); i++)
    {
        if (curLine[i] == ' ')  { spaces++; }
        else if (curLine[i] == '-')
        {
            if (i > 0)
            {
                if (curLine[i-1] != ' ') { digits = false; }
            }
            if (i < curLine.size() - 1)
            {
                if (!curLine[i+1].isDigit()) { digits = false; }
            }
        }
        else if (!curLine[i].isDigit()) { digits = false; }
    }

    if (!digits or spaces!=columnsAndRows)
    {
        labels.back()->setText("Ошибка ввода!\nВведите " + curRowInd + "-ую строку\nВводите числа через пробел");
    }
    else {
        matrices.at(0)->fillRow(curLine);

        if (matrices.at(0)->getRowInd() == 0)
        {
            disconnect(buttons.at(0), &QPushButton::clicked, this, &Widget::onFillMatrix);
            clearLayout(this->layout);
            if (matrices.at(0)->isAdding()) { doAddition(); }
            else                            { setMenu(); }
        }
        else
        {
            curRow = matrices.at(0)->getRowInd();
            curRowInd.setNum(curRow+1);
            labels.back()->setText("Введите " + curRowInd + "-ую строку\nВводите числа через пробел");
        }
    }
}

void Widget::onCancel()
{
    disconnect(buttons.back(), &QPushButton::clicked, this, &Widget::onCancel);
    matrices.at(0)->reset();
    clearLayout(this->layout);
    setMenu();
}

void Widget::onPrint()
{
    clearLayout(this->layout);
    int rows = matrices.back()->getColumnsAndRows();
    QString rowsStr;
    rowsStr.setNum(rows);
    QLabel *label = new QLabel("Нижняя треугольная матрица чисел размером " + rowsStr + "X" + rowsStr);
    labels.append(label);
    layout->addWidget(label);

    doPrint();

    QPushButton *buttonEsc = new QPushButton("Выйти в меню");
    buttons.append(buttonEsc);
    buttonEsc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(buttonEsc);

    connect(buttonEsc, &QPushButton::clicked, this, &Widget::onEscapeToMenu);
}

void Widget::onSetElValue()
{
    QString index = lines.at(0)->text();

    int spaces = 0;
    for (int i = 0; i < index.size(); i++)
    {
        if (index[i] == ' ') { spaces++; }
    }

    QString rowInd = index.left(index.indexOf(' '));
    QString columnInd = index.right(index.indexOf(' '));
    int rInd = rowInd.toInt();
    int cInd = columnInd.toInt();
    int columnsAndRows = matrices.at(0)->getColumnsAndRows();

    QString value = lines.at(1)->text();
    bool digit;
    int val = value.toInt(&digit);
    if (digit)
    {
        if ((rInd == 0 and rowInd[0]!='0')
            or (cInd == 0 and columnInd[0]!='0'))
        {
            labels.back()->setText("Вводить можно только числа \nПовторите ввод");
        }
        else if ((rInd > columnsAndRows or rInd < 1) or
                 (cInd > columnsAndRows or cInd < 1))
        {
            labels.back()->setText("Введенный индекс выходит за пределы матрицы \nПовторите ввод");
        }
        else if (spaces>1)
        {
            labels.back()->setText("Неправильно введён индекс \nПовторите ввод");
        }
        else
        {
            matrices.at(0)->setEl(rInd, cInd, val);
            disconnect(buttons.back(), &QPushButton::clicked, this, &Widget::onCreateMatrix);
            clearLayout(this->layout);
            setMenu();
        }
    }
    else
    {
        labels.back()->setText("Вводить можно только числа \nПовторите ввод");
    }
}

void Widget::onGetElValue()
{
    QString curLine = lines.back()->text();

    QString rowInd = curLine.left(curLine.indexOf(' '));
    QString columnInd = curLine.right(curLine.indexOf(' '));
    int rInd = rowInd.toInt();
    int cInd = columnInd.toInt();
    int columnsAndRows = matrices.at(0)->getColumnsAndRows();

    if ((rInd == 0 and rowInd[0]!='0')
            or (cInd == 0 and columnInd[0]!='0'))
    {
        labels.back()->setText("Вводить можно только числа \nПовторите ввод");
    }
    else if ((rInd > columnsAndRows or rInd < 1) or
             (cInd > columnsAndRows or cInd < 1))
    {
        labels.back()->setText("Введенный индекс выходит за пределы матрицы \nПовторите ввод");
    }
    else
    {
        int el = matrices.at(0)->getEl(rInd, cInd);
        QString elValue;
        elValue.setNum(el);
        labels.back()->setText(elValue);
    }
}

void Widget::onEscapeToMenu()
{
    disconnect(buttons.back(), &QPushButton::clicked, this, &Widget::onEscapeToMenu);
    clearLayout(this->layout);
    setMenu();
}

/*------------------------Очистка--------------------------------------*/

void Widget::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if ((deleteWidgets) and (widget = item->widget()))
        {
            delete widget;
        }
        if (QLayout* childLayout = item->layout())
        {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }

    buttons.clear();
    lines.clear();
    labels.clear();
}

Widget::~Widget()
{
    for (int i = 0; i < matrices.size(); i++)
    {
        matrices.at(i)->writeInFile();
    }
    matrices.clear();
    clearLayout(layout);
    delete layout;
}


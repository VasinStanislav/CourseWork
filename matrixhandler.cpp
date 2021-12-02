#include "matrixhandler.h"

/*-----------------------------------------------КОНСТРУКТОР-------------------------------------------*/

MatrixHandler::MatrixHandler(QString name)
{
   size = 0, columnsAndRows = 0, iterator = 0, rowsIt = 0;
   this->name = name;
   adding = false;
}

/*-----------------------------------------------СОЗДАНИЕ МАТРИЦЫ-------------------------------------------*/

void MatrixHandler::createMatrix(int columnAndRows)
{
    this->columnsAndRows = columnAndRows;
    this->size = ((pow(columnAndRows, 2) - columnAndRows)/2 + columnAndRows);

    mElements = new int[size]();
}

/*-----------------------------------------------ЗАПОЛНЕНИЕ МАТРИЦЫ-------------------------------------------*/

void MatrixHandler::fillRow(QString row)
{
   int *newArr = new int[columnsAndRows];
   for (int i = 0; i < columnsAndRows; i++)
   {
       QString el = row.left(row.indexOf(' '));
       row.remove(0, el.size()+1);
       newArr[i] = el.toInt();
   }

   for (int i = 0; i < rowsIt+1; i++)
   {
       mElements[iterator] = newArr[i];
       iterator++;
   }

   rowsIt++;
   if (rowsIt>=columnsAndRows)
   {
       rowsIt = 0;
       iterator = 0;
   }
   delete[] newArr;
}

/*-----------------------------------------------УСТАНОВЛЕНИЕ ЗНАЧЕНИЯ ij-ого ЭЛЕМЕНТА-------------------------------------------*/

void MatrixHandler::setEl(int rowInd, int columnInd, int value)
{
    if (columnInd > rowInd) { return; }
    rowsIt = rowInd-1;
    for (int i = 1; i <= rowsIt; i++)
    {
        for (int j = 0; j < i; j++)
        {
            iterator++;
        }
    }
    for (int i = 0; i < columnInd - 1; i++)
    {
        iterator++;
    }
    mElements[iterator] = value;
    rowsIt = 0;
    iterator = 0;
}

/*-----------------------------------------------УЧАСТВУЕТ В СЛОЖЕНИИ?-------------------------------------------*/

void MatrixHandler::setAdding(bool adding)
{
    this->adding = adding;
}

/*-----------------------------------------------СЛОЖЕНИЕ ДВУХ МАТРИЦ И ЗАПИСЬ В НОВУЮ МАТРИЦУ-------------------------------------------*/

void MatrixHandler::doAdding(int *mA, int *mB)
{
    for (int i = 0; i < size; i++)
    {
        mElements[i] = mA[i] + mB[i];
    }
}

/*-----------------------------------------------ЗАПИСЬ МАТРИЦЫ В ФАЙЛ--------------------------------------------*/

void MatrixHandler::readFromFile()
{
    QTextStream out(stdout);

    QString fileName = "D:/qt_projects/matrix/";
    fileName.append(name + ".txt");
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) { qWarning("Cannot open file for reading"); }
    else
    {
        QTextStream in(&file);

        int columnsAndRows = in.readLine().toInt();
        createMatrix(columnsAndRows);

        while (!in.atEnd())
        {
            QString row = in.readLine();
            row.remove(0, 1);
            row.replace('\t', ' ');
            row.append(' ');
            fillRow(row);
        }
    }

    file.close();
}

/*-----------------------------------------------ЗАПИСЬ ИЗ ФАЙЛА--------------------------------------------*/

void MatrixHandler::writeInFile()
{
    QTextStream out(stdout);

    QString fileName = "D:/qt_projects/matrix/";
    fileName.append(name + ".txt");
    QFile file(fileName);

    QList<QString> rows;

    for (int i = 1; i <= columnsAndRows; i++)
    {
        QString line = this->getLine(i);
        if (line == "") { continue; }
        rows.append(line);
    }

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out<<columnsAndRows<<endl;
        for (int i = 1; i <= columnsAndRows; i++) { out<<rows.at(i-1)<<endl; }
    }
    else { qWarning("Could not open file"); }

    file.close();
}

/*-----------------------------------------------ПРИСВОЕНИЕ МАТРИЦЫ--------------------------------------------*/

void MatrixHandler::setElValues(int *elementsB)
{
    for (int i = 0; i < size; i++)
    {
        mElements = elementsB;
    }
}

/*-----------------------------------------------СРАВНЕНИЕ МАТРИЦ--------------------------------------------*/

bool MatrixHandler::compareElements(int *elementsB)
{
    bool eq = true;
    for (int i = 0; i < size; i++)
    {
        if (mElements[i] != elementsB[i])
        {
            eq = false;
            break;
        }
    }
    return eq;
}

/*-----------------------------------------------ГЕТТЕРЫ--------------------------------------------*/

int MatrixHandler::getSize()
{
    return size;
}

int MatrixHandler::getColumnsAndRows()
{
    return columnsAndRows;
}

int MatrixHandler::getIterator()
{
    return iterator;
}

int MatrixHandler::getRowInd()
{
    return rowsIt;
}

int MatrixHandler::getEl(int rowInd, int columnInd)
{
   if (columnInd > rowInd) { return 0; }
   rowsIt = rowInd-1;
   for (int i = 1; i <= rowsIt; i++)
   {
       for (int j = 0; j < i; j++)
       {
           iterator++;
       }
   }
   for (int i = 0; i < columnInd - 1; i++)
   {
       iterator++;
   }
   int el = mElements[iterator];
   rowsIt = 0;
   iterator = 0;
   return el;
}

int * MatrixHandler::getElements()
{
    return mElements;
}

QString MatrixHandler::getLine(int index)
{
    QString line = "";
    if (index > columnsAndRows or index < 1) { return line; }

    int j = 0;
    for (; j < index; j++)
    {
        QString el;
        el.setNum(mElements[iterator]);
        iterator++;

        QString buf = "\t";
        buf.append(el);
        line.append(buf);
    }
    for (; j < columnsAndRows; j++)
    {
        line.append("\t0");
    }

    if (iterator>=size) { iterator = 0; }

    return line;
}

bool MatrixHandler::isAdding()
{
    return adding;
}

/*-----------------------------------------------СБРОС ИТЕРАТОРОВ И ЗНАЧЕНИЙ ЭЛЕМЕНТОВ-------------------------------------------*/

void MatrixHandler::reset()
{
    iterator = 0, rowsIt = 0;
    mElements = new int[size]();
}

/*-----------------------------------------------ОЧИСТКА--------------------------------------------*/

MatrixHandler::~MatrixHandler()
{
   delete[] mElements;
}

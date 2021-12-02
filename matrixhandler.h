#ifndef MATRIXHANDLER_H
#define MATRIXHANDLER_H

#include <QtMath>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QVariant>
#include <QLocale>

class MatrixHandler
{
private:
    int size, columnsAndRows, iterator, rowsIt;
    int *mElements;
    bool adding;
    QString name;
public:
    MatrixHandler(QString name = "Matrix_A");
    ~MatrixHandler();

    void createMatrix(int size);
    void fillRow(QString row);
    void setEl(int rowInd, int columnInd, int value);
    void reset();
    void doAdding(int *mA, int *mB);
    void setAdding(bool adding);
    void readFromFile();
    void writeInFile();
    void setElValues(int *elementsB);
    bool compareElements(int *elementsB);

    int getSize();
    int getColumnsAndRows();
    int getIterator();
    int getRowInd();
    int getEl(int rowInd, int columnInd);
    int *getElements();
    QString getLine(int index);
    bool isAdding();
};

#endif // MATRIXHANDLER_H

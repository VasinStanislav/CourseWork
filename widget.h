#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QApplication>
#include <matrixhandler.h>

class Widget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout;

    QList<MatrixHandler *> matrices;
    QList<QPushButton *> buttons;
    QList<QLineEdit *> lines;
    QList<QLabel *> labels;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void createMatrix();
    void fillMatrix();
    void setMenu();
    void setElValue();
    void getElValue();
    void matrixAddition();
    void doAddition();
    void doPrint();
    void checkMatrices();
    void setA();

    void clearLayout(QLayout* layout, bool deleteWidgets = true);
private slots:
    void onCreateMatrix();
    void onPrint();
    void onFillMatrix();
    void onSetElValue();
    void onGetElValue();
    void onWriteInFile();
    void onReadFromFile();
    void onCheckMatrices1();
    void onCheckMatrices2();
    void onSetA1();
    void onSetA2();
    void onReadMatrixB();
    void onCancel();

    void onEscapeToMenu();
};
#endif // WIDGET_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStudentClicked();
    void removeStudentClicked();
    void changeAttributeClicked();
    void searchStudentClicked();
    void filterStudentsClicked();
    void exitClicked();
    void displayStudents(const QList<Student>& students);   

private:
    void setupUI();

    // Widgets
    QPushButton *addStudentButton;
    QPushButton *removeStudentButton;
    QPushButton *changeAttributeButton;
    QPushButton *searchStudentButton;
    QPushButton *filterByBirthdateButton;
    QPushButton *exitButton;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *idEdit;
    QLineEdit *birthdateEdit;
    QLineEdit *ssnEdit;
    QLineEdit *gpaEdit;
    QLineEdit *addressEdit;
    QLineEdit *majorEdit;
    QTextEdit *resultsTextEdit;
};

#endif // MAINWINDOW_H

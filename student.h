#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QDate>

struct Student {
    QString firstName;
    QString lastName;
    QString ID;
    QDate birthdate;
    QString SSN;
    float GPA;
    QString address;
    QString major;
};

#endif
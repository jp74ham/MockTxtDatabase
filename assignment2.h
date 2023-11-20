#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H
#include "student.h"

void writeStudentToFile(const Student& student);
QList<Student> searchStudentsByAttribute(const QString& attribute, const QString& value);
void removeStudent(const QString& ID);
void changeStudentAttribute(const QString& ID, const QString& attribute, const QString& newValue);
QList<Student> filterStudentsByBirthdate(const QString& filter, const QDate& date);

#endif
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDate>
#include <iostream>
#include <QtWidgets>
#include "student.h"

using namespace std;
// struct Student {
//     QString firstName;
//     QString lastName;
//     QString ID;
//     QDate birthdate;
//     QString SSN;
//     float GPA;
//     QString address;
//     QString major;
// };

void writeStudentToFile(const Student& student) {
    QFile file("studentDB.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << student.firstName << "\t"
            << student.lastName << "\t"
            << student.ID << "\t"
            << student.birthdate.toString("MM/dd/yyyy") << "\t"
            << student.SSN << "\t"
            << student.GPA << "\t"
            << student.address << "\t"
            << student.major << "\n";
        file.close();
    }
}

QList<Student> readStudentsFromFile() {
    QList<Student> students;
    QFile file("studentDB.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList attributes = line.split("\t");
            Student student;
            student.firstName = attributes[0];
            student.lastName = attributes[1];
            student.ID = attributes[2];
            student.birthdate = QDate::fromString(attributes[3], "MM/dd/yyyy");
            student.SSN = attributes[4];
            student.GPA = attributes[5].toFloat();
            student.address = attributes[6];
            student.major = attributes[7];
            students.append(student);
        }
        file.close();
    }
    return students;
}

void addStudent() {
    Student newStudent;
    string temp;

    cout << "Enter First Name: ";
    getline(cin, temp);
    newStudent.firstName = QString::fromStdString(temp);

    cout << "Enter Last Name: ";
    getline(cin, temp);
    newStudent.lastName = QString::fromStdString(temp);

    cout << "Enter ID: ";
    getline(cin, temp);
    newStudent.ID = QString::fromStdString(temp);

    cout << "Enter Birthdate (MM/DD/YYYY): ";
    getline(cin, temp);
    QDate date = QDate::fromString(QString::fromStdString(temp), "MM/dd/yyyy");

    if (!date.isValid()){
        cout<<"Invalid date format. Please use MM/DD/YYYY.\n";
        return;
    }
    newStudent.birthdate=date;

    cout << "Enter SSN: ";
    getline(cin, temp);
    newStudent.SSN = QString::fromStdString(temp);

    cout << "Enter GPA: ";
    getline(cin, temp);
    newStudent.GPA = std::stof(temp);

    cout << "Enter Address: ";
    getline(cin, temp);
    newStudent.address = QString::fromStdString(temp);

    cout << "Enter Major: ";
    getline(cin, temp);
    newStudent.major = QString::fromStdString(temp);

    writeStudentToFile(newStudent);
}


void removeStudent(const QString& ID) {
    QList<Student> students = readStudentsFromFile();
    students.erase(std::remove_if(students.begin(), students.end(),
                     [ID](const Student& student) { return student.ID == ID; }),
                     students.end());

    QFile file("studentDB.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Student& student : students) {
            out << student.firstName << "\t"
                << student.lastName << "\t"
                << student.ID << "\t"
                << student.birthdate.toString("MM/DD/YYYY") << "\t"
                << student.SSN << "\t"
                << student.GPA << "\t"
                << student.address << "\t"
                << student.major << "\n";
        }
        file.close();
    }
}

void changeStudentAttribute(const QString& ID, const QString& attribute, const QString& newValue) {
    QList<Student> students = readStudentsFromFile();
    bool found = false;

    for (Student& student : students) {
        if (student.ID == ID) {
            if (attribute == "1") {
                student.firstName = newValue;
            } else if (attribute == "2") {
                student.lastName = newValue;
            } else if (attribute == "3") {
                student.ID = newValue;
            } else if (attribute == "4") {
                student.birthdate = QDate::fromString(newValue, "MM/dd/yyyy");
            } else if (attribute == "5") {
                student.SSN = newValue;
            } else if (attribute == "6") {
                student.GPA = newValue.toFloat();
            } else if (attribute == "7") {
                student.address = newValue;
            } else if (attribute == "8") {
                student.major = newValue;
            }
            found = true;
            break;
        }
    }

    if (found) {
        QFile file("studentDB.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream out(&file);
            for (const Student& student : students) {
                out << student.firstName << "\t"
                    << student.lastName << "\t"
                    << student.ID << "\t"
                    << student.birthdate.toString("MM/dd/yyyy") << "\t"
                    << student.SSN << "\t"
                    << student.GPA << "\t"
                    << student.address << "\t"
                    << student.major << "\n";
            }
            file.close();
        }
    } else {
        cout << "Student with ID " << ID.toStdString() << " not found.\n";
    }
}

QList<Student> searchStudentsByAttribute(const QString& attribute, const QString& value) {
    QList<Student> students = readStudentsFromFile();
    QList<Student> result;

    for (const Student& student : students) {
        if (attribute == "1" && student.firstName == value) {
            result.append(student);
        } else if (attribute == "2" && student.lastName == value) {
            result.append(student);
        } else if (attribute == "3" && student.ID == value) {
            result.append(student);
        } else if (attribute == "4" && student.birthdate == QDate::fromString(value, "MM/dd/yyyy")) {
            result.append(student);
        } else if (attribute == "5" && student.SSN == value) {
            result.append(student);
        } else if (attribute == "6" && QString::number(student.GPA) == value) {
            result.append(student);
        } else if (attribute == "7" && student.address == value) {
            result.append(student);
        } else if (attribute == "8" && student.major == value) {
            result.append(student);
        }
    }

    return result;
}

QList<Student> filterStudentsByBirthdate(const QString& filter, const QDate& date) {
    QList<Student> students = readStudentsFromFile();
    QList<Student> result;

    if (filter == "before") {
        for (const Student& student : students) {
            if (student.birthdate < date) {
                result.append(student);
            }
        }
    } else if (filter == "after") {
        for (const Student& student : students) {
            if (student.birthdate > date) {
                result.append(student);
            }
        }
    } else if (filter == "on") {
        for (const Student& student : students) {
            if (student.birthdate == date) {
                result.append(student);
            }
        }
    }

    return result;
}

// int main()
// {
//     bool access = true;
//     while (access) {
//         cout << "\nOptions:\n";
//         cout << "1. Add Student\n";
//         cout << "2. Remove Student\n";
//         cout << "3. Change Student Attribute\n";
//         cout << "4. Search Students\n";
//         cout << "5. Filter Students by Birthdate\n";
//         cout << "6. Exit\n";
//         cout << "Enter your choice: ";

//         int choice;
//         cin >> choice;
//         cin.ignore();
        
//         string IDToRemove;
//         string IDToChange, attribute, newValue;
//         string searchAttribute, searchValue;
//         string filterType;
//         string dateString;
//         QList<Student> searchResults;
//         QList<Student> filteredResults;
//         QDate date;    

//         switch (choice) {
//             case 1: // Add Student
//                 addStudent();
//                 break;
//             case 2: // Remove Student
//                 cout << "Enter ID of the student to remove: ";
//                 cin >> IDToRemove;
//                 removeStudent(QString::fromStdString(IDToRemove));
//                 break;
//             case 3: // Change Student Attribute
//                 cout << "Enter ID of the student to change: ";
//                 cin >> IDToChange;
//                 cout << "Enter the attribute to change:\n1.First Name\n2.Last Name\n3.ID\n4.Birthdate\n5.SSN\n6.GPA\n7.Address\n8.Major\n";
//                 cin >> attribute;
//                 cout << "Enter the new value: ";
//                 cin >> newValue;
//                 changeStudentAttribute(QString::fromStdString(IDToChange), QString::fromStdString(attribute), QString::fromStdString(newValue));
//                 break;
//             case 4: // Search Students
//                 cout << "Enter the attribute to search for\n1.First Name\n2.Last Name\n3.ID\n4.Birthdate\n5.SSN\n6.GPA\n7.Address\n8.Major\n";
//                 getline(cin, searchAttribute);
//                 cout << "Enter the value to search for: ";
//                 getline(cin, searchValue);

//                 searchResults = searchStudentsByAttribute(QString::fromStdString(searchAttribute), QString::fromStdString(searchValue));

//                 // Display search results
//                 cout << "Search Results:\n";
//                 for (const Student& student : searchResults) {
//                     cout << "Name: " << student.firstName.toStdString() << " " << student.lastName.toStdString() << "\n";
//                     cout << "ID: " << student.ID.toStdString() << "\n";
//                     cout << "Birthdate: " << student.birthdate.toString("MM/dd/yyyy").toStdString() << "\n";
//                     cout << "SSN: " << student.SSN.toStdString() << "\n";
//                     cout << "GPA: " << student.GPA << "\n";
//                     cout << "Address: " << student.address.toStdString() << "\n";
//                     cout << "Major: " << student.major.toStdString() << "\n\n";
//                 }
//                 break;
//             case 5: // Filter Students by Birthdate
//                 cout << "Enter filter type (before, after, on): ";
//                 getline(cin, filterType);

//                 cout << "Enter date (MM/DD/YYYY): ";
//                 getline(cin, dateString);
//                 date = QDate::fromString(QString::fromStdString(dateString), "MM/dd/yyyy");

//                 filteredResults = filterStudentsByBirthdate(QString::fromStdString(filterType), date);

//                 // Display filtered results
//                 cout << "Filtered Results:\n";
//                 for (const Student& student : filteredResults) {
//                     cout << "Name: " << student.firstName.toStdString() << " " << student.lastName.toStdString() << "\n";
//                     cout << "ID: " << student.ID.toStdString() << "\n";
//                     cout << "Birthdate: " << student.birthdate.toString("MM/dd/yyyy").toStdString() << "\n";
//                     cout << "SSN: " << student.SSN.toStdString() << "\n";
//                     cout << "GPA: " << student.GPA << "\n";
//                     cout << "Address: " << student.address.toStdString() << "\n";
//                     cout << "Major: " << student.major.toStdString() << "\n\n";
//                 }
//                 break;
//             case 6:
//             access=false;
//             break;
//             default:
//                 cout << "Invalid choice. Please try again.\n";
//                 break;
//         }
//     }

//     return 0;
// }


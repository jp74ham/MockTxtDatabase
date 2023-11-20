#include "mainwindow.h"
#include "assignment2.h"
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDate>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    addStudentButton = new QPushButton("Add Student", this);
    addStudentButton->setGeometry(10, 10, 150, 30);
    removeStudentButton = new QPushButton("Remove Student", this);
    removeStudentButton->setGeometry(10, 50, 150, 30);
    changeAttributeButton = new QPushButton("Change Student Attribute", this);
    changeAttributeButton->setGeometry(10, 90, 150, 30);
    searchStudentButton = new QPushButton("Search Student", this);
    searchStudentButton->setGeometry(10, 130, 150, 30);
    filterByBirthdateButton = new QPushButton("Filter Students by Birthdate", this);
    filterByBirthdateButton->setGeometry(10, 170, 150, 30);
    exitButton = new QPushButton("Exit", this);
    exitButton->setGeometry(10, 210, 150, 30);

    // Create input fields
    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    idEdit = new QLineEdit(this);
    birthdateEdit = new QLineEdit(this);
    ssnEdit = new QLineEdit(this);
    gpaEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    majorEdit = new QLineEdit(this);

    QLabel *firstNameLabel = new QLabel("First Name:", this);
    QLabel *lastNameLabel = new QLabel("Last Name:", this);
    QLabel *idLabel = new QLabel("ID:", this);
    QLabel *birthdateLabel = new QLabel("Birthdate (MM/DD/YYYY):", this);
    QLabel *ssnLabel = new QLabel("SSN:", this);
    QLabel *gpaLabel = new QLabel("GPA:", this);
    QLabel *addressLabel = new QLabel("Address:", this);
    QLabel *majorLabel = new QLabel("Major:", this);

    resultsTextEdit = new QTextEdit(this);
    resultsTextEdit->setReadOnly(true);

    // Create layouts
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addStudentButton);
    buttonLayout->addWidget(removeStudentButton);
    buttonLayout->addWidget(changeAttributeButton);
    buttonLayout->addWidget(searchStudentButton);
    buttonLayout->addWidget(filterByBirthdateButton);
    buttonLayout->addWidget(exitButton);

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addWidget(firstNameLabel);
    inputLayout->addWidget(firstNameEdit);
    inputLayout->addWidget(lastNameLabel);
    inputLayout->addWidget(lastNameEdit);
    inputLayout->addWidget(idLabel);
    inputLayout->addWidget(idEdit);
    inputLayout->addWidget(birthdateLabel);
    inputLayout->addWidget(birthdateEdit);
    inputLayout->addWidget(ssnLabel);
    inputLayout->addWidget(ssnEdit);
    inputLayout->addWidget(gpaLabel);
    inputLayout->addWidget(gpaEdit);
    inputLayout->addWidget(addressLabel);
    inputLayout->addWidget(addressEdit);
    inputLayout->addWidget(majorLabel);
    inputLayout->addWidget(majorEdit);

    QVBoxLayout *resultsLayout = new QVBoxLayout;
    resultsLayout->addWidget(resultsTextEdit);
    // Set up the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(resultsLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect buttons to slots
    connect(addStudentButton, SIGNAL(clicked()), this, SLOT(addStudentClicked()));
    connect(removeStudentButton, SIGNAL(clicked()), this, SLOT(removeStudentClicked()));
    connect(changeAttributeButton, SIGNAL(clicked()), this, SLOT(changeAttributeClicked()));
    connect(searchStudentButton, SIGNAL(clicked()), this, SLOT(searchStudentClicked()));
    connect(filterByBirthdateButton, SIGNAL(clicked()), this, SLOT(filterStudentsClicked()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));

    // Hide input fields initially
    firstNameEdit->setVisible(false);
    lastNameEdit->setVisible(false);
    idEdit->setVisible(false);
    birthdateEdit->setVisible(false);
    ssnEdit->setVisible(false);
    gpaEdit->setVisible(false);
    addressEdit->setVisible(false);
    majorEdit->setVisible(false);
}

void MainWindow::exitClicked(){
    close();
}
void MainWindow::filterStudentsClicked(){

    resultsTextEdit->clear();

    QString filterType = QInputDialog::getText(this, "Filter Students", "Enter filter type (before, after, on):");
    QString dateString = QInputDialog::getText(this, "Filter Students", "Enter date (MM/DD/YYYY):");
    QDate date = QDate::fromString(dateString, "MM/dd/yyyy");

    if (!filterType.isEmpty() && !dateString.isEmpty() && date.isValid()) {
        QList<Student> filteredResults = filterStudentsByBirthdate(filterType, date);

        // Display filtered results
        displayStudents(filteredResults);
    }
}
void MainWindow::searchStudentClicked(){
    resultsTextEdit->clear();
    QString searchAttribute = QInputDialog::getText(this, "Search Students", "Enter the attribute to search for:\n1.First Name 2.Last Name 3.ID 4.Birthdate 5.SSN 6.GPA 7.Address 8.Major\n");
    QString searchValue = QInputDialog::getText(this, "Search Students", "Enter the value to search for:");

    if (!searchAttribute.isEmpty() && !searchValue.isEmpty()) {
        QList<Student> searchResults = searchStudentsByAttribute(searchAttribute, searchValue);

        displayStudents(searchResults);
    }
}

void MainWindow::displayStudents(const QList<Student>& students) {
    // Clear any previous results
    resultsTextEdit->clear();

    for (const Student& student : students) {
        resultsTextEdit->append("Name: " + student.firstName + " " + student.lastName);
        resultsTextEdit->append("ID: " + student.ID);
        resultsTextEdit->append("Birthdate: " + student.birthdate.toString("MM/dd/yyyy"));
        resultsTextEdit->append("SSN: " + student.SSN);
        resultsTextEdit->append("GPA: " + QString::number(student.GPA));
        resultsTextEdit->append("Address: " + student.address);
        resultsTextEdit->append("Major: " + student.major);
        resultsTextEdit->append("\n"); 
    }
}

void MainWindow::removeStudentClicked(){
    QString IDToRemove = QInputDialog::getText(this, "Remove Student", "Enter ID of the student to remove:");

    if (!IDToRemove.isEmpty()) {
        removeStudent(IDToRemove);
    }
}
void MainWindow::changeAttributeClicked(){
    QString IDToChange = QInputDialog::getText(this, "Change Student Attribute", "Enter ID of the student to change");
    QString attribute = QInputDialog::getText(this, "Change Student Attribute", "Enter the attribute to change:\n1.First Name 2.Last Name 3.ID 4.Birthdate 5.SSN 6.GPA 7.Address 8.Major\n");
    QString newValue = QInputDialog::getText(this, "Change Student Attribute", "Enter the new value:");

    if (!IDToChange.isEmpty() && !attribute.isEmpty() && !newValue.isEmpty()) {
        changeStudentAttribute(IDToChange, attribute, newValue);
    }
}
void MainWindow::addStudentClicked()
{
    firstNameEdit->show();
    lastNameEdit->show();
    idEdit->show();
    birthdateEdit->show();
    ssnEdit->show();
    gpaEdit->show();
    addressEdit->show();
    majorEdit->show();

    QString firstName = firstNameEdit->text();
    QString lastName = lastNameEdit->text();
    QString ID = idEdit->text();
    QString birthdateStr = birthdateEdit->text();
    QDate birthdate = QDate::fromString(birthdateStr, "MM/dd/yyyy");
    QString SSN = ssnEdit->text();
    float GPA = gpaEdit->text().toFloat();
    QString address = addressEdit->text();
    QString major = majorEdit->text();

    // Input validation
    if (firstName.isEmpty() || lastName.isEmpty() || ID.isEmpty() ||
        !birthdate.isValid() || SSN.isEmpty() || GPA < 0 || GPA > 4.0 ||
        address.isEmpty() || major.isEmpty()) {
        QMessageBox::information(this,"Input validation","Check if boxes are empty, birthdate is MM/DD/YYYY, and 0<=GPA<=4\n\nClick Add Student again to submit.");
        return;
    }

    Student newStudent;
    newStudent.firstName = firstName;
    newStudent.lastName = lastName;
    newStudent.ID = ID;
    newStudent.birthdate = birthdate;
    newStudent.SSN = SSN;
    newStudent.GPA = GPA;
    newStudent.address = address;
    newStudent.major = major;

    // Call the writeStudentToFile function
    writeStudentToFile(newStudent);

    // Optionally, you can clear the input fields after adding a student
    firstNameEdit->clear();
    lastNameEdit->clear();
    idEdit->clear();
    birthdateEdit->clear();
    ssnEdit->clear();
    gpaEdit->clear();
    addressEdit->clear();
    majorEdit->clear();

}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Student
{
    string firstName;
    string lastName;
    double average;
    char letterGrade;
};

char getLetterGrade(double average)
{
    if (average >= 90)
        return 'A';
    if (average >= 80)
        return 'B';
    if (average >= 70)
        return 'C';
    if (average >= 60)
        return 'D';
    return 'F';
}

int main()
{
    string fileName;
    cout << "Enter input file name: ";
    cin >> fileName;

    ifstream infile(fileName.c_str());

    if (!infile)
    {
        cout << "Could not open file.\n";
        return 1;
    }

    int studentCount;
    infile >> studentCount;

    if (!infile || studentCount <= 0)
    {
        cout << "Invalid file format.\n";
        return 1;
    }

    vector<Student> students;
    double classTotal = 0.0;
    double highestAverage = -1.0;
    double lowestAverage = 101.0;
    string highestName = "";
    string lowestName = "";

    for (int i = 0; i < studentCount; i++)
    {
        string firstName, lastName;
        int gradeCount;

        infile >> firstName >> lastName >> gradeCount;

        if (!infile || gradeCount <= 0)
        {
            cout << "Invalid student data in file.\n";
            return 1;
        }

        double total = 0.0;

        for (int j = 0; j < gradeCount; j++)
        {
            double grade;
            infile >> grade;

            if (!infile || grade < 0 || grade > 100)
            {
                cout << "Invalid grade found in file.\n";
                return 1;
            }

            total += grade;
        }

        double average = total / gradeCount;
        char letter = getLetterGrade(average);

        Student s;
        s.firstName = firstName;
        s.lastName = lastName;
        s.average = average;
        s.letterGrade = letter;

        students.push_back(s);
        classTotal += average;

        if (average > highestAverage)
        {
            highestAverage = average;
            highestName = firstName + " " + lastName;
        }

        if (average < lowestAverage)
        {
            lowestAverage = average;
            lowestName = firstName + " " + lastName;
        }
    }

    cout << "\nStudent Results\n";
    cout << left << setw(20) << "Name" << setw(12) << "Average" << setw(12) << "Letter" << endl;
    cout << string(44, '-') << endl;

    for (int i = 0; i < students.size(); i++)
    {
        string fullName = students[i].firstName + " " + students[i].lastName;
        cout << left << setw(20) << fullName
             << setw(12) << fixed << setprecision(2) << students[i].average
             << setw(12) << students[i].letterGrade << endl;
    }

    double classAverage = classTotal / students.size();

    cout << "\nClass Average: " << fixed << setprecision(2) << classAverage << endl;
    cout << "Highest Average: " << highestName << " (" << highestAverage << ")" << endl;
    cout << "Lowest Average: " << lowestName << " (" << lowestAverage << ")" << endl;

    infile.close();
    return 0;
}
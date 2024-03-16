#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
void Order();
void logout();
void stuInfo();
void lessonInfo();
void ave();
void showData();
void saveInfo();
void loadInfo();

class lessonData
{
public:
    char name[50];
    int unit;
    float mark;
};

class stuData
{
public:
    char name[50];
    char Lname[50];
    char ID[15];
    float ave;
    lessonData lessons[21];
} student;

int i = -1;

int main()
{
    cout << "*************** Welcome to the Student's Info Management System ***************" << endl
         << "****************************** By Arman Khalili ******************************" << endl;
    Order();
}

void Order()
{
    int order;
    char nxt[2];

    cout << "Menu:" << endl
          << "1 => Enter student info" << endl
         << "2 => Enter lessons" << endl
         << "3 => Calculate Average" << endl
         << "4 => Show Data" << endl
         << "5 => Save Data" << endl
         << "6 => Load Data" << endl
         << "7 => Exit" << endl;

    cout << endl
         << "Enter your command: ";
    cin >> order;
    cout << endl
         << "**********" << endl;

    switch (order)
    {
    case 1:
        stuInfo();
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;
    case 2:
        lessonInfo();
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;
    case 3:
        ave();
        cout << "Your average grade is: " << student.ave << endl;
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;
    case 4:
        ave();
        showData();
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;
    case 5:
        saveInfo();
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;

    case 6:
        loadInfo();
        cout << endl
             << endl
             << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
        system("cls");
        Order();
        break;
    case 7:
        logout();
        break;

    default:
        cout << endl
             << endl
             << "Invalid order!! try again..." << endl;
        Order();
        break;
    }
}

void logout()
{
    cout << "---Tanks for using our Student's Info Management System---" << endl
         << "     *** Looking forward to seeing you again soon! ***    " << endl;
    exit(0);
}

void stuInfo()
{
    char nxt[2];
    cout << "Enter your ID: ";
    cin >> student.ID;
    cout << "Enter your name: ";
    cin >> student.name;
    cout << "Enter your last name: ";
    cin >> student.Lname;

    cout << "Your data added successfuly";
}

void lessonInfo()
{
    lessonData lesson;
    char nxt[2] = "y";
    while (strcmp(nxt, "y") == 0)
    {
        i++;
        cout << "Enter lesson name: ";
        cin >> lesson.name;
        cout << "Enter lessom units: ";
        cin >> lesson.unit;
        cout << "Enter lesson mark: ";
        cin >> lesson.mark;
        student.lessons[i] = lesson;

        cout << endl
             << "Any other lessons? (y or n)" << endl;
        cin >> nxt;
        cin.ignore();
    }
}

void ave()
{
    int j, Usum = 0, Msum = 0;
    float ave;

    for (j = 0; j <= i; j++)
    {
        Msum += student.lessons[j].mark * student.lessons[j].unit;
        Usum += student.lessons[j].unit;
    }

    ave = (float)Msum / Usum;

    student.ave = ave;
}

void showData()
{
    cout << "--------------------------------------------------------------------" << endl;
    cout << setw(15) << "ID: " << student.ID << setw(25) << "Name: " << student.name << " " << student.Lname << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << setw(25) << "Lesson" << setw(10) << "Units" << setw(10) << "Mark" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (int j = 0; j <= i; j++)
    {
        cout << setw(25) << student.lessons[j].name << setw(10) << student.lessons[j].unit << setw(10) << student.lessons[j].mark << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << "AVERAGE --> " << student.ave << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

void saveInfo()
{
    stuData STU;
    FILE *ip;
    ip = fopen("StudentsInfo.dat", "ab");
    if (!ip)
    {
        cout << "File was not found";
        exit(0);
    }

    STU = student;

    fwrite(&STU, sizeof(STU), 1, ip);
    fclose(ip);

    cout << "Informations Saved successfully.";
}

void loadInfo()
{
    stuData STU;
    char stuId[15];
    bool found = false;
    cout << "Enter your ID: ";
    cin >> stuId;

    ifstream file("StudentsInfo.dat", ios::binary);
    if (!file)
    {
        cout << "File was not found";
        exit(0);
    }

    cout << endl;

    while (file.read(reinterpret_cast<char *>(&STU), sizeof(STU)))
    {
        if (strcmp(stuId, STU.ID) == 0)
        {
            found = true;

            cout << "--------------------------------------------------------------------" << endl;
            cout << setw(15) << "ID: " << STU.ID << setw(25) << "Name: " << STU.name << " " << STU.Lname << endl;
            cout << "--------------------------------------------------------------------" << endl;
            cout << setw(25) << "Lesson" << setw(10) << "Units" << setw(10) << "Mark" << endl;
            cout << "--------------------------------------------------------------------" << endl;

            for (int j = 0; j <= 21; j++)
            {
                if (strlen(STU.lessons[j].name) == 0)
                    break;

                cout << setw(25) << STU.lessons[j].name << setw(10) << STU.lessons[j].unit << setw(10) << STU.lessons[j].mark << endl;
            }

            cout << "--------------------------------------------------------------------" << endl;
            cout << "AVERAGE --> " << STU.ave << endl;
            cout << "--------------------------------------------------------------------" << endl;

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "Data not found!! check the code and Enter again..." << endl;
        loadInfo();
    }
}

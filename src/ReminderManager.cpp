#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include "./include/ReminderManager.h"
using namespace std;

vector<Reminder> reminders;

void ReminderManager::showReminder(Reminder rem)
{
    system("cls");
    cout << "\033[40;36mPrzypomnienie #" << rem.id << endl;
    cout << "\033[40;36mData: " << rem.day << "." << rem.month << "." << rem.year << endl;
    cout << "\033[40;36mGodzina: " << rem.hour << ":" << rem.minute << endl;
    cout << "\033[40;36mTekst: " << rem.text << endl;
}

void ReminderManager::addReminder()
{
    Reminder rem;
    rem.id = reminders.size() + 1;

    cout << "\033[40;36mPodaj datę przypomnienia\033[97m (DD MM RRRR): ";
    cin >> rem.day >> rem.month >> rem.year;

    cout << "\033[40;36mPodaj godzinę przypomnienia\033[97m (GG MM): ";
    cin >> rem.hour >> rem.minute;

    cin.ignore(); // Ignorowanie znaku nowej linii

    cout << "\033[40;36mPodaj treść przypomnienia:\033[97m ";
    getline(cin, rem.text);

    reminders.push_back(rem);
    cout << "\033[40;32mDodano przypomnienie\033[97m #" << rem.id << endl;
}

void ReminderManager::deleteReminder(unsigned int id)
{
    reminders.erase(reminders.begin() + id - 1);
    cout << "\033[40;32mUsunięto przypomnienie\033[97m #" << id << endl;
}

void ReminderManager::editReminder(unsigned int id)
{
    Reminder &rem = reminders[id - 1];

    cout << "\033[40;36mPodaj nową datę przypomnienia\033[97m (DD MM RRRR): ";
    cin >> rem.day >> rem.month >> rem.year;

    cout << "\033[40;36mPodaj nową godzinę przypomnienia\033[97m (GG MM): ";
    cin >> rem.hour >> rem.minute;

    cin.ignore(); // Ignorowanie znaku nowej linii

    cout << "\033[40;35mPodaj nową treść przypomnienia:\033[97m ";
    getline(cin, rem.text);

    cout << "\033[40;32mZaktualizowano przypomnienie\033[97m #" << id << endl;
}

void ReminderManager::saveReminders()
{
    ofstream file("reminders.txt");

    if (file.is_open())
    {
        for (unsigned int i = 0; i < reminders.size(); i++)
        {
            Reminder rem = reminders[i];
            file << rem.id << endl;
            file << rem.day << endl;
            file << rem.month << endl;
            file << rem.year << endl;
            file << rem.hour << endl;
            file << rem.minute << endl;
            file << rem.text << endl;
        }

        file.close();
    }
    else
    {
        cout << "\033[40;31mNie udało się zapisać przypomnień do pliku!\033[97m" << endl;
    }
}

void ReminderManager::loadReminders()
{
    ifstream file("reminders.txt");

    if (file.is_open())
    {
        Reminder rem;
        while (file >> rem.id >> rem.day >> rem.month >> rem.year >> rem.hour >> rem.minute)
        {
            file.ignore(); // pomiń znak nowej linii po godzinie
            getline(file, rem.text);

            reminders.push_back(rem);
        }

        if (file.eof())
        {
            file.close();
        }
        else
        {
            cout << "\033[40;31mBłąd podczas wczytywania przypomnień z pliku!\033[97m" << endl;
        }
    }
    else
    {
        cout << "\033[40;31mNie udało się otworzyć pliku z przypomnieniami!\033[97m" << endl;
    }
}

void ReminderManager::checkReminders()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    for (unsigned int i = 0; i < reminders.size(); i++)
    {
        if (reminders[i].year == 1900 + ltm->tm_year &&
            reminders[i].month == 1 + ltm->tm_mon &&
            reminders[i].day == ltm->tm_mday &&
            reminders[i].hour == ltm->tm_hour &&
            reminders[i].minute == ltm->tm_min)
        {
            showReminder(reminders[i]);
            system("start /B wscript.exe Reminder.vbs");
            system("timeout 15 >nul /NOBREAK");
            system("taskkill /f /im wscript.exe /t");
            cout << "\033[40;36mPomyślnie odtworzono dźwięk przypomnienia.\033[97m" << endl;
            system("pause >nul");
        }
    }
    system("cls");
}

void ReminderManager::displayReminders(const vector<Reminder> &reminders)
{
    for (const Reminder &rem : reminders)
    {
        cout << "\033[40;36mPrzypomnienie #" << rem.id << endl;
        cout << "\033[40;36mData: " << rem.day << "." << rem.month << "." << rem.year << endl;
        cout << "\033[40;36mGodzina: " << rem.hour << ":" << rem.minute << endl;
        cout << "\033[40;36mTekst: " << rem.text << endl;
        cout << endl;
    }
}

void ReminderManager::showMenu()
{
    cout << "\033[40;35m----- PRZYPOMNIENIA -----\033[97m" << endl;
    cout << "\033[40;36m1. Pokaż wszystkie przypomnienia\033[97m" << endl;
    cout << "\033[40;36m2. Dodaj nowe przypomnienie\033[97m" << endl;
    cout << "\033[40;36m3. Edytuj przypomnienie\033[97m" << endl;
    cout << "\033[40;36m4. Usuń przypomnienie\033[97m" << endl;
    cout << "\033[40;36m5. Zapisz przypomnienia\033[97m" << endl;
    cout << "\033[40;36m6. Wyjdź z programu\033[97m" << endl;
    cout << "\033[40;36m7. Odśwież (Wymagane w przypadku wywołania przypomnienia, problemem jest brak znajomości bibliotek threading lub boost/thread.hpp)\033[97m" << std::endl;
    cout << "\033[40;36mWybierz opcję: \033[97m";
}

bool ReminderManager::handleChoice(int choice)
{
    while (true)
    {
        system("cls & @chcp 65001 >nul");
        checkReminders();
        showMenu();

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (reminders.empty())
            {
                cout << "\033[40;36mBrak przypomnień do wyświetlenia.\033[97m" << endl;
                system("pause");
                break;
            }
            for (unsigned int i = 0; i < reminders.size(); i++)
            {
                showReminder(reminders[i]);
                system("pause");
            }
            break;
        case 2:
            addReminder();
            system("pause");
            break;
        case 3:
            if (reminders.empty())
            {
                cout << "\033[40;36mBrak przypomnień do edycji.\033[97m" << endl;
                system("pause");
                break;
            }
            else
            {
                displayReminders(reminders);
            }
            unsigned int idToEdit;
            for (unsigned int i = 0; i < reminders.size(); i++)
            {
                showReminder(reminders[i]);
                system("pause");
            }
            cout << "\033[40;36mPodaj numer przypomnienia do edycji: \033[97m";
            cin >> idToEdit;
            if (idToEdit <= reminders.size())
            {
                editReminder(idToEdit);
            }
            else
            {
                cout << "\033[40;36mNie ma przypomnienia o numerze " << idToEdit << ".\033[97m" << endl;
            }
            system("pause");
            break;
        case 4:
            if (reminders.empty())
            {
                cout << "\033[40;36mBrak przypomnień do usunięcia.\033[97m" << endl;
                system("pause");
                break;
            }
            else
            {
                displayReminders(reminders);
            }
            unsigned int idToDelete;
            for (unsigned int i = 0; i < reminders.size(); i++)
            {
                showReminder(reminders[i]);
                system("pause");
            }
            cout << "\033[40;36mPodaj numer przypomnienia do usunięcia: \033[97m";
            cin >> idToDelete;
            if (idToDelete <= reminders.size())
            {
                deleteReminder(idToDelete);
            }
            else
            {
                cout << "\033[40;36mNie ma przypomnienia o numerze " << idToDelete << ".\033[97m" << endl;
            }
            system("pause");
            break;
        case 5:
            saveReminders();
            system("pause");
            break;
        case 6:
            saveReminders();
            cout << "\033[40;32mZakończono program.\033[97m" << endl;
            return false;
        case 7:
            system("cls");
            continue;
        default:
            cout << "\033[40;36mNieznana opcja.\033[97m" << endl;
            system("pause");
            break;
        }
    }
}
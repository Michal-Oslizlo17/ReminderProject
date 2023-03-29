#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <c++\mingw32\bits\error_constants.h>

using namespace std;

// Struktura przechowująca dane przypomnienia
struct Reminder
{
    string text;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int id;
};

// Wektor zawierający wszystkie przypomnienia
vector<Reminder> reminders;

// Funkcja do dodawania nowego przypomnienia
void addReminder()
{
    // Tworzenie nowego przypomnienia
    Reminder newReminder;

    // Pobieranie danych od użytkownika
    cout << "Podaj tekst przypomnienia: ";
    cin >> newReminder.text;
    cout << "Podaj dzień: ";
    cin >> newReminder.day;
    cout << "Podaj miesiąc: ";
    cin >> newReminder.month;
    cout << "Podaj rok: ";
    cin >> newReminder.year;
    cout << "Podaj godzinę: ";
    cin >> newReminder.hour;
    cout << "Podaj minutę: ";
    cin >> newReminder.minute;

    // Unikalne ID
    newReminder.id = reminders.size() + 1;

    // Dodawanie przypomnienia do wektora
    reminders.push_back(newReminder);
}

// Funkcja do usuwania przypomnienia
void deleteReminder()
{
    // Pobranie ID przypomnienia do usunięcia
    int id;
    cout << "Podaj ID przypomnienia do usunięcia: ";
    cin >> id;

    // Przeszukiwanie wektora w poszukiwaniu wprowadzonego ID
    for (unsigned int i = 0; i < reminders.size(); i++)
    {
        // Sprawdzenie czy ID się zgadza
        if (reminders[i].id == id)
        {
            // Usunięcie przypomnienia
            reminders.erase(reminders.begin() + i);
            cout << "Przypomnienie usunięte!" << endl;
            return;
        }
    }

    // Jeśli nie znaleziono przypomnienia o podanym ID
    cout << "Nie znaleziono przypomnienia o podanym ID!" << endl;
}

// Funkcja do edytowania przypomnienia
void editReminder()
{
    // Pobranie ID przypomnienia do edytowania
    int id;
    cout << "Podaj ID przypomnienia do edytowania: ";
    cin >> id;

    // Przeszukiwanie wektora w poszukiwaniu wprowadzonego ID
    for (unsigned int i = 0; i < reminders.size(); i++)
    {
        // Sprawdzenie czy ID się zgadza
        if (reminders[i].id == id)
        {
            // Wyświetlenie starego tekstu przypomnienia
            cout << "Stary tekst przypomnienia: " << reminders[i].text << endl;

            // Pobranie nowych danych od użytkownika
            cout << "Podaj nowy tekst przypomnienia: ";
            cin >> reminders[i].text;
            cout << "Podaj nowy dzień: ";
            cin >> reminders[i].day;
            cout << "Podaj nowy miesiąc: ";
            cin >> reminders[i].month;
            cout << "Podaj nowy rok: ";
            cin >> reminders[i].year;
            cout << "Podaj nową godzinę: ";
            cin >> reminders[i].hour;
            cout << "Podaj nową minutę: ";
            cin >> reminders[i].minute;

            cout << "Przypomnienie zedytowane!" << endl;
            return;
        }
    }

    // Jeśli nie znaleziono przypomnienia o podanym ID
    cout << "Nie znaleziono przypomnienia o podanym ID!" << endl;
}

// Funkcja do zapisywania danych do pliku
void saveReminders()
{
    // Otwarcie pliku do zapisu
    ofstream file("tasks.txt");

    // Zapisanie wszystkich przypomnień do pliku
    for (unsigned int i = 0; i < reminders.size(); i++)
    {
        file << reminders[i].text << ",";
        file << reminders[i].day << ",";
        file << reminders[i].month << ",";
        file << reminders[i].year << ",";
        file << reminders[i].hour << ",";
        file << reminders[i].minute << ",";
        file << reminders[i].id << endl;
    }

    file.close();
}

// Funkcja do wczytywania danych z pliku
void loadReminders()
{
    // Otwarcie pliku do odczytu
    ifstream file("tasks.txt");

    // Flaga mówiąca o tym czy plik został otwarty
    bool isOpen = file.is_open();

    // Jeśli plik został otwarty
    if (isOpen)
    {
        string line;

        // Odczytanie wszystkich linii pliku
        while (getline(file, line))
        {
            // Tworzenie nowego przypomnienia
            Reminder newReminder;

            // Przetworzenie linii na dane przypomnienia
            int pos = 0;
            string token;
            for (int i = 0; i < 7; i++)
            {
                pos = line.find(",");
                token = line.substr(0, pos);
                line.erase(0, pos + 1);

                switch (i)
                {
                case 0:
                    newReminder.text = token;
                    break;
                case 1:
                    newReminder.day = stoi(token);
                    break;
                case 2:
                    newReminder.month = stoi(token);
                    break;
                case 3:
                    newReminder.year = stoi(token);
                    break;
                case 4:
                    newReminder.hour = stoi(token);
                    break;
                case 5:
                    newReminder.minute = stoi(token);
                    break;
                case 6:
                    newReminder.id = stoi(token);
                    break;
                }
            }

            // Dodawanie przypomnienia do wektora
            reminders.push_back(newReminder);
        }

        file.close();
    }
}

// Funkcja wyświetlająca przypomnienie
void showReminder(Reminder reminder)
{
    // Wyświetlenie przypomnienia na ekranie
    cout << "Przypomnienie o: " << reminder.text << endl;
    cout << reminder.day << "/" << reminder.month << "/" << reminder.year << " ";
    cout << reminder.hour << ":" << reminder.minute << endl;

    cout << "Odtwarzanie dźwięku..." << endl;
    system("start Reminder.vbs");

    // Uspanie programu przez 15 sekund
    int time = 15;
    while (time > 0)
    {
        cout << "Pozostało: " << time << " sekund" << endl;
        time--;
        system("timeout 1 >nul /NOBREAK");
    }

    cout << "Koniec przypomnienia!" << endl;
    system("taskkill /f /im wscript.exe /t");
}

// Główna funkcja programu
int main()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Ustawienie kodowania strony na UTF-8
    system("@chcp 65001 >nul");

    // Wczytanie przypomnień z pliku
    loadReminders();

    // Pętla programu
    while (1)
    {
        // Wyświetlenie aktualnych przypomnień
        showReminder();

        // Wyświetlenie menu
        cout << "Menu:" << endl;
        cout << "1. Dodaj przypomnienie" << endl;
        cout << "2. Usuń przypomnienie" << endl;
        cout << "3. Edytuj przypomnienie" << endl;
        cout << "4. Wyjście" << endl;

        int option;
        cout << "Wybierz opcję: ";
        cin >> option;
        cout << endl;

        if (option < 1 || option > 4)
        {
            cout << "Nie ma takiej opcji!" << endl;
        }
        else
        {
            switch (option)
            {
            case 1:
            {
                // Dodanie przypomnienia
                addReminder();
                break;
            }
            case 2:
            {
                // Usuwanie przypomnienia
                unsigned int id;
                cout << "Podaj ID przypomnienia do usunięcia: ";
                cin >> id;

                if (id > reminders.size() || id < 1)
                {
                    cout << "Nie ma takiego przypomnienia!" << endl;
                }
                else
                {
                    deleteReminder();
                }
                break;
            }
            case 3:
            {
                // Edytowanie przypomnienia
                unsigned int id;
                cout << "Podaj ID przypomnienia do edycji: ";
                cin >> id;

                if (id > reminders.size() || id < 1)
                {
                    cout << "Nie ma takiego przypomnienia!" << endl;
                }
                else
                {
                    editReminder();
                }
                break;
            }
            case 4:
            {
                // Wyjście z programu
                saveReminders();
                cout << "Do zobaczenia!" << endl;
                return 0;
            }
            }
        }

        // Wyczyszczenie konsoli przed kolejnym wyświetleniem menu
        system("cls");
    }
    return 0;
}

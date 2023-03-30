#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

struct Reminder
{
  int id;
  string text;
  int day;
  int month;
  int year;
  int hour;
  int minute;
};

vector<Reminder> reminders;

void showReminder(Reminder rem)
{
  system("cls");
  cout << "Przypomnienie #" << rem.id << endl;
  cout << "Data: " << rem.day << "." << rem.month << "." << rem.year << endl;
  cout << "Godzina: " << rem.hour << ":" << rem.minute << endl;
  cout << "Tekst: " << rem.text << endl;
}

void addReminder()
{
  Reminder rem;
  rem.id = reminders.size() + 1;

  cout << "Podaj datę przypomnienia (DD MM RRRR): ";
  cin >> rem.day >> rem.month >> rem.year;

  cout << "Podaj godzinę przypomnienia (GG MM): ";
  cin >> rem.hour >> rem.minute;

  cin.ignore(); // Ignorowanie znaku nowej linii

  cout << "Podaj treść przypomnienia: ";
  getline(cin, rem.text);

  reminders.push_back(rem);
  cout << "Dodano przypomnienie #" << rem.id << endl;
}

void deleteReminder(unsigned int id)
{
  reminders.erase(reminders.begin() + id - 1);
  cout << "Usunięto przypomnienie #" << id << endl;
}

void editReminder(unsigned int id)
{
  Reminder &rem = reminders[id - 1];

  cout << "Podaj nową datę przypomnienia (DD MM RRRR): ";
  cin >> rem.day >> rem.month >> rem.year;

  cout << "Podaj nową godzinę przypomnienia (GG MM): ";
  cin >> rem.hour >> rem.minute;

  cin.ignore(); // Ignorowanie znaku nowej linii

  cout << "Podaj nową treść przypomnienia: ";
  getline(cin, rem.text);

  cout << "Zaktualizowano przypomnienie #" << id << endl;
}

void saveReminders()
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
    cout << "Nie udało się zapisać przypomnień do pliku!" << endl;
  }
}

void loadReminders()
{
  ifstream file("tasks.txt");

  if (file.is_open())
  {
    Reminder rem;
    while (file >> rem.id >> rem.day >> rem.month >> rem.year >> rem.hour >> rem.minute)
    {
      file.ignore(); // pomiń znak nowej linii po godzinie
      getline(file, rem.text);

      reminders.push_back(rem);
    }

    file.close();
  }
  else
  {
    cout << "Nie udało się wczytać przypomnień z pliku!" << endl;
  }
}


int main()
{
  ifstream file("reminders.txt");

  if (file.is_open())
  {
    Reminder rem;
    while (file >> rem.id >> rem.day >> rem.month >> rem.year >> rem.hour >> rem.minute)
    {
      getline(file, rem.text);
      reminders.push_back(rem);
    }
    file.close();
  }

  while (true)
  {
    system("cls");
    cout << "----- PRZYPOMNIENIA -----" << endl;
    cout << "1. Pokaż wszystkie przypomnienia" << endl;
    cout << "2. Dodaj nowe przypomnienie" << endl;
    cout << "3. Edytuj przypomnienie" << endl;
    cout << "4. Usuń przypomnienie" << endl;
    cout << "5. Zapisz przypomnienia" << endl;
    cout << "6. Wyjdź z programu" << endl;
    cout << "Wybierz opcję: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
      if (reminders.empty())
      {
        cout << "Brak przypomnień do wyświetlenia." << endl;
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
        cout << "Brak przypomnień do edycji." << endl;
        system("pause");
        break;
      }
      unsigned int idToEdit;
      cout << "Podaj numer przypomnienia do edycji: ";
      cin >> idToEdit;
      if (idToEdit <= reminders.size())
      {
        editReminder(idToEdit);
      }
      else
      {
        cout << "Nie ma przypomnienia o numerze " << idToEdit << "." << endl;
      }
      system("pause");
      break;
    case 4:
      if (reminders.empty())
      {
        cout << "Brak przypomnień do usunięcia." << endl;
        system("pause");
        break;
      }
      unsigned int idToDelete;
      cout << "Podaj numer przypomnienia do usunięcia: ";
      cin >> idToDelete;
      if (idToDelete <= reminders.size())
      {
        deleteReminder(idToDelete);
      }
      else
      {
        cout << "Nie ma przypomnienia o numerze " << idToDelete << "." << endl;
      }
      system("pause");
      break;
    case 5:
      saveReminders();
      system("pause");
      break;
    case 6:
      return 0;
    default:
      cout << "Nieprawidłowa opcja. Wybierz ponownie." << endl;
      system("pause");
      break;
    }
  }

  return 0;
}

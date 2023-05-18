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
  cout << "[40;36mPrzypomnienie #" << rem.id << endl;
  cout << "[40;36mData: " << rem.day << "." << rem.month << "." << rem.year << endl;
  cout << "[40;36mGodzina: " << rem.hour << ":" << rem.minute << endl;
  cout << "[40;36mTekst: " << rem.text << endl;
}

void addReminder()
{
  Reminder rem;
  rem.id = reminders.size() + 1;

  cout << "[40;36mPodaj datę przypomnienia[97m (DD MM RRRR): ";
  cin >> rem.day >> rem.month >> rem.year;

  cout << "[40;36mPodaj godzinę przypomnienia[97m (GG MM): ";
  cin >> rem.hour >> rem.minute;

  cin.ignore(); // Ignorowanie znaku nowej linii

  cout << "[40;36mPodaj treść przypomnienia:[97m ";
  getline(cin, rem.text);

  reminders.push_back(rem);
  cout << "[40;32mDodano przypomnienie[97m #" << rem.id << endl;
}

void deleteReminder(unsigned int id)
{
  reminders.erase(reminders.begin() + id - 1);
  cout << "[40;32mUsunięto przypomnienie[97m #" << id << endl;
}

void editReminder(unsigned int id)
{
  Reminder &rem = reminders[id - 1];

  cout << "[40;36mPodaj nową datę przypomnienia[97m (DD MM RRRR): ";
  cin >> rem.day >> rem.month >> rem.year;

  cout << "[40;36mPodaj nową godzinę przypomnienia[97m (GG MM): ";
  cin >> rem.hour >> rem.minute;

  cin.ignore(); // Ignorowanie znaku nowej linii

  cout << "[40;35mPodaj nową treść przypomnienia:[97m ";
  getline(cin, rem.text);

  cout << "[40;32mZaktualizowano przypomnienie[97m #" << id << endl;
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
    cout << "[40;31mNie udało się zapisać przypomnień do pliku![97m" << endl;
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
    cout << "[40;31mNie udało się wczytać przypomnień z pliku![97m" << endl;
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
    system("cls & @chcp 65001 >nul");
    cout << "[40;35m----- PRZYPOMNIENIA -----[97m" << endl;
    cout << "[40;36m1. Pokaż wszystkie przypomnienia[97m" << endl;
    cout << "[40;36m2. Dodaj nowe przypomnienie[97m" << endl;
    cout << "[40;36m3. Edytuj przypomnienie[97m" << endl;
    cout << "[40;36m4. Usuń przypomnienie[97m" << endl;
    cout << "[40;36m5. Zapisz przypomnienia[97m" << endl;
    cout << "[40;36m6. Wyjdź z programu[97m" << endl;
    cout << "[40;36mWybierz opcję: [97m";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
      if (reminders.empty())
      {
        cout << "[40;36mBrak przypomnień do wyświetlenia.[97m" << endl;
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
        cout << "[40;36mBrak przypomnień do edycji.[97m" << endl;
        system("pause");
        break;
      }
      unsigned int idToEdit;
      cout << "[40;36mPodaj numer przypomnienia do edycji: [97m";
      cin >> idToEdit;
      if (idToEdit <= reminders.size())
      {
        editReminder(idToEdit);
      }
      else
      {
        cout << "[40;36mNie ma przypomnienia o numerze " << idToEdit << ".[97m" << endl;
      }
      system("pause");
      break;
    case 4:
      if (reminders.empty())
      {
        cout << "[40;36mBrak przypomnień do usunięcia.[97m" << endl;
        system("pause");
        break;
      }
      unsigned int idToDelete;
      cout << "[40;36mPodaj numer przypomnienia do usunięcia: [97m";
      cin >> idToDelete;
      if (idToDelete <= reminders.size())
      {
        deleteReminder(idToDelete);
      }
      else
      {
        cout << "[40;36mNie ma przypomnienia o numerze #" << idToDelete << ".[97m" << endl;
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
      cout << "[40;36mNieprawidłowa opcja. Wybierz ponownie.[97m" << endl;
      system("pause");
      break;
    }
  }

  // Sprawdzanie przypomnień o ustalonej godzinie i dacie
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
      system("timeout 15 /NOBREAK & taskkill /f /im wscript.exe /t");
      cout << "[40;36mPomyślnie zamknięto proces VBSCRIPT odpowiadający za odtwarzanie dźwięku .mp3[97m" << endl;
      system("pause >nul");
    }
  }

    return 0;
}

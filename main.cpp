#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

struct Reminder
{
  unsigned int id;
  unsigned int day;
  unsigned int month;
  unsigned int year;
  unsigned int hour;
  unsigned int minute;
  string text;
};

vector<Reminder> reminders;

void showReminder(const Reminder &rem)
{
  cout << "[40;36mNumer: " << rem.id << endl;
  cout << "Data: " << rem.day << "/" << rem.month << "/" << rem.year << endl;
  cout << "Godzina: " << rem.hour << ":" << rem.minute << endl;
  cout << "Treść: " << rem.text << "[97m" << endl;
}

void addReminder()
{
  Reminder rem;
  cout << "[40;36mPodaj datę przypomnienia (DD MM RRRR): [97m";
  cin >> rem.day >> rem.month >> rem.year;
  cout << "[40;36mPodaj godzinę przypomnienia (GG MM): [97m";
  cin >> rem.hour >> rem.minute;
  cout << "[40;36mPodaj treść przypomnienia: [97m";
  cin.ignore();
  getline(cin, rem.text);

  rem.id = reminders.size() + 1;
  reminders.push_back(rem);

  cout << "[40;36mPrzypomnienie zostało dodane.[97m" << endl;
}

void editReminder(unsigned int id)
{
  Reminder &rem = reminders[id - 1];
  cout << "[40;36mNumer: " << rem.id << endl;
  cout << "[40;36mStara data: " << rem.day << "/" << rem.month << "/" << rem.year << endl;
  cout << "[40;36mStara godzina: " << rem.hour << ":" << rem.minute << endl;
  cout << "[40;36mStara treść: " << rem.text << endl;

  cout << "[40;36mPodaj nową datę przypomnienia (DD MM RRRR): [97m";
  cin >> rem.day >> rem.month >> rem.year;
  cout << "[40;36mPodaj nową godzinę przypomnienia (GG MM): [97m";
  cin >> rem.hour >> rem.minute;
  cout << "[40;36mPodaj nową treść przypomnienia: [97m";
  cin.ignore();
  getline(cin, rem.text);

  cout << "[40;36mPrzypomnienie zostało zaktualizowane.[97m" << endl;
}

void deleteReminder(unsigned int id)
{
  reminders.erase(reminders.begin() + id - 1);
  cout << "[40;36mPrzypomnienie zostało usunięte.[97m" << endl;
}

void saveReminders()
{
  ofstream file("reminders.txt");
  if (file.is_open())
  {
    for (const Reminder &rem : reminders)
    {
      file << rem.id << " "
           << rem.day << " "
           << rem.month << " "
           << rem.year << " "
           << rem.hour << " "
           << rem.minute << " "
           << rem.text << endl;
    }
    file.close();
    cout << "[40;36mPrzypomnienia zostały zapisane do pliku.[97m" << endl;
  }
  else
  {
    cout << "[40;36mNie udało się otworzyć pliku do zapisu przypomnień.[97m" << endl;
  }
}

void loadReminders()
{
  ifstream file("reminders.txt");
  if (file.is_open())
  {
    reminders.clear();
    Reminder rem;
    while (file >> rem.id >> rem.day >> rem.month >> rem.year >> rem.hour >> rem.minute)
    {
      file.ignore();
      getline(file, rem.text);
      reminders.push_back(rem);
    }
    file.close();
    cout << "[40;36mPrzypomnienia zostały wczytane z pliku.[97m" << endl;
  }
  else
  {
    cout << "[40;36mNie udało się otworzyć pliku z przypomnieniami.[97m" << endl;
  }
}

void checkReminders()
{
  while (true)
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
        system("timeout 15 /NOBREAK & taskkill /f /im wscript.exe /t");
        cout << "[40;36mPomyślnie zamknięto proces VBSCRIPT odpowiadający za odtwarzanie dźwięku .mp3[97m" << endl;
      }
    }
    // Czekaj 1 sekundę przed ponownym sprawdzeniem przypomnień
    this_thread::sleep_for(chrono::seconds(1));
  }
}

int main()
{
  loadReminders();

  thread reminderThread(checkReminders);
  reminderThread.detach();

  bool exitProgram = false;
  while (!exitProgram)
  {
    system("cls");
    cout << "[40;36mMENU GŁÓWNE[97m" << endl;
    cout << "1. Pokaż przypomnienia" << endl;
    cout << "2. Dodaj przypomnienie" << endl;
    cout << "3. Edytuj przypomnienie" << endl;
    cout << "4. Usuń przypomnienie" << endl;
    cout << "5. Zapisz przypomnienia do pliku" << endl;
    cout << "6. Wyjdź z programu" << endl;
    cout << "[40;36mWybierz opcję: [97m";

    int option;
    cin >> option;

    switch (option)
    {
    case 1:
      system("cls");
      cout << "[40;36mPOKAZUJĘ PRZYPOMNIENIA[97m" << endl;
      for (const Reminder &rem : reminders)
      {
        showReminder(rem);
        cout << endl;
      }
      system("pause");
      break;
    case 2:
      system("cls");
      cout << "[40;36mDODAJ PRZYPOMNIENIE[97m" << endl;
      addReminder();
      system("pause");
      break;
    case 3:
      system("cls");
      cout << "[40;36mEDYTUJ PRZYPOMNIENIE[97m" << endl;
      unsigned int editId;
      cout << "[40;36mPodaj numer przypomnienia do edycji: [97m";
      cin >> editId;
      if (editId > 0 && editId <= reminders.size())
      {
        editReminder(editId);
      }
      else
      {
        cout << "[40;36mNieprawidłowy numer przypomnienia.[97m" << endl;
      }
      system("pause");
      break;
    case 4:
      system("cls");
      cout << "[40;36mUSUŃ PRZYPOMNIENIE[97m" << endl;
      unsigned int deleteId;
      cout << "[40;36mPodaj numer przypomnienia do usunięcia: [97m";
      cin >> deleteId;
      if (deleteId > 0 && deleteId <= reminders.size())
      {
        deleteReminder(deleteId);
      }
      else
      {
        cout << "[40;36mNieprawidłowy numer przypomnienia.[97m" << endl;
      }
      system("pause");
      break;
    case 5:
      system("cls");
      cout << "[40;36mZAPISZ PRZYPOMNIENIA DO PLIKU[97m" << endl;
      saveReminders();
      system("pause");
      break;
    case 6:
      exitProgram = true;
      break;
    default:
      cout << "[40;36mNieprawidłowa opcja.[97m" << endl;
      system("pause");
      break;
    }
  }

  return 0;
}

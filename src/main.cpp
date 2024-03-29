#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include "./include/ReminderManager.h"

using namespace std;

int main()
{
  ReminderManager reminderManager;
  reminderManager.loadReminders();

  while (true)
  {
    system("cls & @chcp 65001 >nul");
    reminderManager.checkReminders();
    reminderManager.showMenu();

    int choice;
    cin >> choice;
    if (!reminderManager.handleChoice(choice))
    {
      break; // Przerwanie pętli, jeśli handleChoice zwrócił false
    }
  }

  return 0;
}

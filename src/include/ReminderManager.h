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

class ReminderManager
{
public:
    void saveReminders();
    void loadReminders();
    void checkReminders();
    void showMenu();
    bool handleChoice(int choice);

    vector<Reminder> reminders;

    void showReminder(Reminder rem);
    void addReminder();
    void deleteReminder(unsigned int id);
    void editReminder(unsigned int id);
    void displayReminders(const vector<Reminder> &reminders);
};
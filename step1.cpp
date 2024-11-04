#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream> 

class Event {
public:
    std::string date;  // Дата события
    std::string description;  // Описание события

    Event(const std::string& date, const std::string& description)
        : date(date), description(description) {}
};

class EventCalendar {
private:
    std::vector<Event> events;
    const std::string filename = "events.txt"; // Имя файла для сохранения событий

public:
    EventCalendar() {
        loadFromFile(); // Загружаем события из файла при создании объекта
    }

    void addEvent(const std::string& date, const std::string& description) {
        events.push_back(Event(date, description));
        saveToFile(); // Сохраняем события в файл после добавления
    }

    void viewEvents(const std::string& date) const {
        std::cout << "События на " << date << ":\n";
        for (size_t i = 0; i < events.size(); ++i) {
            if (events[i].date == date) {
                std::cout << i + 1 << ". " << events[i].description << "\n";
            }
        }
    }

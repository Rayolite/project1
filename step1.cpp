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
         std::setlocale(LC_ALL, "ru_RU.UTF-8");
        std::cout << "События на " << date << ":\n";
        for (size_t i = 0; i < events.size(); ++i) {
            if (events[i].date == date) {
                std::cout << i + 1 << ". " << events[i].description << "\n";
            }
        }
    }
  void deleteEvent(size_t index) {
        if (index < 1 || index > events.size()) {
             std::setlocale(LC_ALL, "ru_RU.UTF-8");
            std::cout << "Неверный индекс!\n";
            return;
        }
        events.erase(events.begin() + index - 1);
         std::setlocale(LC_ALL, "ru_RU.UTF-8");
        std::cout << "Событие удалено.\n";
        saveToFile(); // Сохраняем события в файл после удаления
    }

    void saveToFile() const {
        std::ofstream outFile(filename);
        if (!outFile) {
             std::setlocale(LC_ALL, "ru_RU.UTF-8");
            std::cerr << "Ошибка открытия файла для записи.\n";
            return;
        }
        for (const auto& event : events) {
            outFile << event.date << ";" << event.description << "\n";
        }
        outFile.close();
    }

    void loadFromFile() {
        std::ifstream inFile(filename);
        if (!inFile) {
             std::setlocale(LC_ALL, "ru_RU.UTF-8");
            std::cerr << "Файл не найден, создается новый.\n";
            return; // Если файл не найден, просто продолжаем
        }
        std::string line;
        while (std::getline(inFile, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != std::string::npos) {
                std::string date = line.substr(0, delimiterPos);
                std::string description = line.substr(delimiterPos + 1);
                events.push_back(Event(date, description));
            }
        }
        inFile.close();
    }
};

int main() {

   

    EventCalendar calendar;
    int choice;
 std::setlocale(LC_ALL, "ru_RU.UTF-8");
    do {
        std::cout << "1. Добавить событие\n"
                  << "2. Посмотреть события\n"
                  << "3. Удалить событие\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(); // Сбрасываем буфер ввода

        switch (choice) {
            case 1: {
                 std::setlocale(LC_ALL, "ru_RU.UTF-8");
                std::string date, description;
                std::cout << "Введите дату (в формате ГГГГ-ММ-ДД): ";
                std::getline(std::cin, date);
                std::cout << "Введите описание события: ";
                std::getline(std::cin, description);
                calendar.addEvent(date, description);
                break;
            }
            case 2: {
                std::string date;
                 std::setlocale(LC_ALL, "ru_RU.UTF-8");
                std::cout << "Введите дату для просмотра событий: ";
                std::getline(std::cin, date);
                calendar.viewEvents(date);
                break;
            }
            case 3: {
                size_t index;
                 std::setlocale(LC_ALL, "ru_RU.UTF-8");
                std::cout << "Введите индекс события для удаления: ";
                std::cin >> index;
                calendar.deleteEvent(index);
                break;
            }
            case 0:
             std::setlocale(LC_ALL, "ru_RU.UTF-8");
                std::cout << "Выход из программы.\n";
                break;
            default:
             std::setlocale(LC_ALL, "ru_RU.UTF-8");
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}

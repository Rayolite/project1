#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

class Event {
public:
    std::string title;       // Название события
    std::string description; // Описание события

    Event(const std::string& title, const std::string& description)
        : title(title), description(description) {}
};

class EventCalendar {
private:
    std::vector<Event> events;
    const std::string filename = "events.txt"; // Имя файла для сохранения событий

public:
    EventCalendar() {
        loadFromFile(); // Загружаем события из файла при создании объекта
    }

    void addEvent(const std::string& title, const std::string& description) {
        events.push_back(Event(title, description));
        saveToFile(); // Сохраняем события в файл после добавления
    }

    void viewEvents(const std::string& title) const {
        std::cout << "События с названием \"" << title << "\":\n";
        for (size_t i = 0; i < events.size(); ++i) {
            if (events[i].title == title) {
                std::cout << i + 1 << ". " << events[i].description << "\n";
            }
        }
    }

    void deleteEvent(size_t index) {
        if (index < 1 || index > events.size()) {
            std::cout << "Неверный индекс!\n";
            return;
        }
        events.erase(events.begin() + index - 1);
        std::cout << "Событие удалено.\n";
        saveToFile(); // Сохраняем события в файл после удаления
    }

    void saveToFile() const {
        std::ofstream outFile(filename, std::ios::out | std::ios::binary);
        if (!outFile) {
            std::cerr << "Ошибка открытия файла для записи.\n";
            return;
        }
        for (const auto& event : events) {
            outFile << event.title << ";" << event.description << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream inFile(filename, std::ios::in | std::ios::binary);
        if (!inFile) {
            std::cerr << "Файл не найден, создается новый.\n";
            return; // Если файл не найден, просто продолжаем
        }
        std::string line;
        while (std::getline(inFile, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != std::string::npos) {
                std::string title = line.substr(0, delimiterPos);
                std::string description = line.substr(delimiterPos + 1);
                events.push_back(Event(title, description));
            }
        }
    }
};

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    EventCalendar calendar;
    int choice;

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
                std::string title, description;
                std::cout << "Введите название события: ";
                std::getline(std::cin, title);
                std::cout << "Введите описание события: ";
                std::getline(std::cin, description);
                calendar.addEvent(title, description);
                break;
            }
            case 2: {
                std::string title;
                std::cout << "Введите название для просмотра событий: ";
                std::getline(std::cin, title);
                calendar.viewEvents(title);
                break;
            }
            case 3: {
                size_t index;
                std::cout << "Введите индекс события для удаления: ";
                std::cin >> index;
                calendar.deleteEvent(index);
                break;
            }
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
    
}
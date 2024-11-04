#include <string>

class Event {
public:
    std::string date;  // Дата события
    std::string description;  // Описание события

    Event(const std::string& date, const std::string& description)
        : date(date), description(description) {}
};

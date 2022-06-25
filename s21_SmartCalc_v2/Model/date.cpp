#include "date.h"

s21::Date::Date() noexcept {
    initDate();
}

s21::Date::Date(const std::string &date) : dateValue_(date) {
}

void s21::Date::initDate() noexcept {
    auto timeVal = time(0);
    struct tm localTime;
    localtime_r(&timeVal, &localTime);
    std::string day = createPartOfDate(localTime.tm_mday);
    std::string month = createPartOfDate(localTime.tm_mon + 1);
    static const int YEAR_START_NUM = 1900;
    std::string year = std::to_string(YEAR_START_NUM + localTime.tm_year);
    dateValue_ = day + '.' + month + '.' + year;
}

std::string s21::Date::value() const noexcept {
    return dateValue_;
}

int s21::Date::monthDaysCount() const noexcept {
    auto currentMonth = month();
    if (currentMonth == 2)
        return yearDaysCount() == NORMAL_YEAR_DAYS ? FEB_DAYS : FEB_LEAP_YEAR_DAYS;
    else if (currentMonth != 0 && currentMonth <= 7)
        return currentMonth % 2 == 0 ? USUAL_MONTH_DAYS : MAX_DAYS;

    return currentMonth % 2 == 0 ? MAX_DAYS : USUAL_MONTH_DAYS;
}

void s21::Date::increaseDate(int type) noexcept {
    if (type == DAY) {
        auto currentDay = day() + 1;
        if (currentDay > monthDaysCount()) {
            currentDay = 1;
            increaseDate(MONTH);
        }
        auto dayStr = createPartOfDate(currentDay);
        dateValue_.replace(DAY_START_INDEX, COUNT, dayStr);
    } else if (type == MONTH) {
        auto mon = month() + 1;
        if (mon > MONTHMAX) {
            mon = 1;
            increaseDate(YEAR);
        }
        auto monthStr = createPartOfDate(mon);
        dateValue_.replace(MONTH_START_INDEX, COUNT, monthStr);
    } else {
        auto currentYear = std::to_string(year() + 1);
        dateValue_.replace(YEAR_START_INDEX, COUNT + 2, currentYear);
    }
}

int s21::Date::year() const noexcept {
    return std::stoi(dateValue_.substr(YEAR_START_INDEX));
}

int s21::Date::month() const noexcept {
    return std::stoi(dateValue_.substr(MONTH_START_INDEX, COUNT));
}

int s21::Date::day() const noexcept {
    return std::stoi(dateValue_.substr(DAY_START_INDEX, COUNT));
}

int s21::Date::yearDaysCount() const noexcept {
    const int currYear = year();
    return currYear % 4 == 0
        && currYear % 100 == 0
        && currYear % 400 == 0 ? LEAP_YEAR_DAYS : NORMAL_YEAR_DAYS;
}

bool s21::Date::isEqual(const Date &date) const noexcept {
    return dateValue_ == date.dateValue_;
}

bool s21::Date::isDayGreater(const Date &date) const noexcept {
    return year() == date.year() && month() == date.month() && day() > date.day();
}

std::string s21::Date::createPartOfDate(int num) const {
    std::string partStr = std::to_string(num);
    return num < 10 ? '0' + partStr : partStr;
}

bool s21::Date::operator==(const Date &date) const noexcept {
    return isEqual(date);
}


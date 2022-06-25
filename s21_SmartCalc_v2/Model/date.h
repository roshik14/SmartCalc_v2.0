#ifndef SRC_S21_SMARTCALC_V2_MODEL_DATE_H_
#define SRC_S21_SMARTCALC_V2_MODEL_DATE_H_

#include <string>
#include <ctime>

namespace s21 { class Date; }

class s21::Date {
 public:
    static constexpr int MONTHMAX = 12;
    enum {
        DAY = 0,
        MONTH,
        YEAR,
    };

    Date() noexcept;
    explicit Date(const std::string &date);
    std::string value() const noexcept;
    int year() const noexcept;
    int month() const noexcept;
    int day() const noexcept;
    int yearDaysCount() const noexcept;
    int monthDaysCount() const noexcept;
    bool isDayGreater(const Date &date) const noexcept;
    bool isEqual(const Date &date) const noexcept;
    void increaseDate(int type) noexcept;
    bool operator==(const Date &date) const noexcept;

 private:
    enum {
        NORMAL_YEAR_DAYS = 365,
        LEAP_YEAR_DAYS,
    };

    enum {
        FEB_DAYS = 28,
        FEB_LEAP_YEAR_DAYS,
        USUAL_MONTH_DAYS,
        MAX_DAYS
    };

    static constexpr int MONTH_START_INDEX = 3;
    static constexpr int YEAR_START_INDEX = 6;
    static constexpr int DAY_START_INDEX = 0;
    static constexpr int COUNT = 2;

    std::string dateValue_;
    void initDate() noexcept;
    std::string createPartOfDate(int num) const;
};

#endif  // SRC_S21_SMARTCALC_V2_MODEL_DATE_H_

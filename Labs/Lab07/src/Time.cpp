#include "Time.hpp"

#include <iostream>

Time::Time(const int seconds) {
    // int total = seconds;
    // int total = seconds % 86400;
    this->m_hours   = (seconds / 3600) % 24;
    this->m_minutes = (seconds % 3600) / 60;
    this->m_seconds = (seconds % 3600) % 60;

    // std::cout << "hours = " << m_hours << " ";
    // std::cout << "minutes = " << m_minutes << " ";
    // std::cout << "seconds = " << m_seconds << " ";
}

Time::Time(const int hours, const int minutes, const int seconds) {
    const int total = seconds + (minutes * 60) + (hours * 3600);

    // total     = total %= 86400;
    this->m_hours   = (total / 3600) % 24;
    this->m_minutes = (total % 3600) / 60;
    this->m_seconds = (total % 3600) % 60;

    // std::cout << "hours = " << m_hours << " ";
    // std::cout << "minutes = " << m_minutes << " ";
    // std::cout << "seconds = " << m_seconds << " ";
}

Time Time::operator+(const Time& other) const {
    int Total = m_seconds + (m_minutes * 60) + (m_hours * 3600) +
                (other.m_seconds) + (other.m_minutes * 60) +
                (other.m_hours * 3600);

    return Time(Total);
}

Time Time::operator+(const int other) const {
    int Total = other + m_seconds + (m_minutes * 60) + (m_hours * 3600);

    return Time(Total);
}

// Time(2, 10, 0) - Time(1, 50, 0) -> 00:20:00
Time Time::operator-(const Time& other) const {
    int Total =
        (this->m_seconds + (this->m_hours * 3600) + (this->m_minutes * 60)) -
        (other.m_seconds + (other.m_minutes * 60) + (other.m_hours * 3600));

    return Time(Total);
};
// Time(1, 0, 0) - 90 -> 00:58:30
Time Time::operator-(const int other) const {
    int Total =
        (this->m_seconds + (this->m_hours * 3600) + (this->m_minutes * 60)) -
        other;

    return Time(Total);
};

// Time(1, 0, 0) == Time(1, 0, 0) -> true
// Time(1, 0, 0) == Time(0, 59, 59) -> false
bool Time::operator==(const Time& other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);
    int rhs = other.m_seconds + (other.m_minutes * 60) + (other.m_hours * 3600);

    if (lhs == rhs) {
        return true;
    } else {
        return false;
    }
};
// Time(1, 0, 0) == 3600 -> true
// Time(1, 0, 0) == 3599 -> false
bool Time::operator==(const int other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);

    if (lhs == other) {
        return true;
    } else
        return false;
};

// Time(1, 0, 0) != Time(0, 59, 59) -> true
// Time(1, 0, 0) != Time(1, 0, 0) -> false
bool Time::operator!=(const Time& other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);
    int rhs = other.m_seconds + (other.m_minutes * 60) + (other.m_hours * 3600);

    if (lhs != rhs) {
        return true;
    } else {
        return false;
    }
};
// Time(1, 0, 0) != 3599 -> true
// Time(1, 0, 0) != 3600 -> false
bool Time::operator!=(const int other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);

    if (lhs != other) {
        return true;
    } else
        return false;
};

// Time(1, 0, 0) < Time(2, 0, 0) -> true
// Time(1, 0, 0) < Time(0, 59, 59) -> false
bool Time::operator<(const Time& other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);
    int rhs = other.m_seconds + (other.m_minutes * 60) + (other.m_hours * 3600);

    if (lhs < rhs) {
        return true;
    } else {
        return false;
    }
};
// Time(1, 0, 0) < 7200 -> true
// Time(1, 0, 0) < 3599 -> false
bool Time::operator<(const int other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);

    if (lhs < other) {
        return true;
    } else
        return false;
};

// Time(2, 0, 0) > Time(1, 0, 0) -> true
// Time(1, 0, 0) > Time(1, 0, 1) -> false
bool Time::operator>(const Time& other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);
    int rhs = other.m_seconds + (other.m_minutes * 60) + (other.m_hours * 3600);

    if (lhs > rhs) {
        return true;
    } else {
        return false;
    }
};
// Time(2, 0, 0) > 3600 -> true
// Time(1, 0, 0) > 3601 -> false
bool Time::operator>(const int other) const {
    int lhs = this->m_seconds + (this->m_minutes * 60) + (this->m_hours * 3600);

    if (lhs > other) {
        return true;
    } else
        return false;
};

void Time::show() const {
    if (m_hours < 10) {
        std::cout << "0" << m_hours << ":";
    } else {
        std::cout << m_hours << ":";
    }
    if (m_minutes < 10) {
        std::cout << "0" << m_minutes << ":";
    } else {
        std::cout << m_minutes << ":";
    }
    if (m_seconds < 10) {
        std::cout << "0" << m_seconds << std::endl;
    } else {
        std::cout << m_seconds << std::endl;
    }
};

int Time::getHours() const { return this->m_hours; };
int Time::getMinutes() const { return this->m_minutes; };
int Time::getSeconds() const { return this->m_seconds; };
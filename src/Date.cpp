#include"Date.hpp"
#include<iostream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

Date::Date() {
	m_minute = 0;
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_hour = 0;
}
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	setYear(t_year);
	setMonth(t_month);
	setDay(t_day);
	setHour(t_hour);
	setMinute(t_minute);
}
Date::Date(std::string dateString) {
	this->operator=(stringToDate(dateString));
}
int Date::getYear(void) const {
	return m_year;
}
void Date::setYear(const int t_year) {
	m_year = t_year;
}
int Date::getMonth(void) const {
	return m_month;
}
void Date::setMonth(const int t_month) {
	m_month = t_month;
}
int Date::getDay(void) const {
	return m_day;
}
void Date::setDay(const int t_day) {
	m_day = t_day;
}
int Date::getHour(void) const {
	return m_hour;
}
void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}
int Date::getMinute(void) const {
	return m_minute;
}
void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}
bool isRunNian(int year_) {
	if (year_ % 100 == 0) {
		return year_ % 400 == 0;
	} else {
		return year_ % 4 == 0;
	}
}
bool Date::isValid(const Date t_date) {
	if (t_date.m_year < 1000 || t_date.m_year > 9999) return false;
	if (t_date.m_month < 1 || t_date.m_month > 12) return false;
	if (t_date.m_day < 1) return false;
	if (t_date.m_hour < 0 || t_date.m_hour > 23) return false;
	if (t_date.m_minute < 0 || t_date.m_minute > 59) return false;
	if (t_date.m_month == 1 || t_date.m_month == 3 || t_date.m_month == 5 || t_date.m_month == 7 || t_date.m_month == 8 || t_date.m_month == 10 || t_date.m_month == 12) {
		if (t_date.m_day > 31) return false;
	} else {
		if (t_date.m_month == 2) {
			if (isRunNian(t_date.m_year)) {
				if (t_date.m_day > 29) return false;
			} else {
				if (t_date.m_day > 28) return false;
			}
		} else {
			if (t_date.m_day > 30) return false;
		}
	}
	return true;
}
Date Date::stringToDate(const std::string t_dateString) {
	Date output;
	if (t_dateString.length() != 16) return output;
	if (t_dateString[4] != '-' || t_dateString[7] != '-' || t_dateString[10] != '/' || t_dateString[13] != ':') return output;
	string year = "", month =  "", day = "", hour = "", minute = "";
	year = t_dateString.substr(0, 4);
	month = t_dateString.substr(5, 2);
	day = t_dateString.substr(8, 2);
	hour = t_dateString.substr(11, 2);
	minute = t_dateString.substr(14, 2);
	int year_ = atoi(year.c_str());
	int month_ = atoi(month.c_str());
	int day_ = atoi(day.c_str());
	int hour_ = atoi(hour.c_str());
	int minute_ = atoi(minute.c_str());
	Date output_(year_, month_, day_, hour_, minute_);
	if (!isValid(output_)) return output;
	return output_;
}

std::string int2str(int other) {
	stringstream ss;
	string output = "";
	ss << other;
	ss >> output;
	return output;
}
std::string Date::dateToString(Date t_date) {
	stringstream output;
	if (!isValid(t_date)) {
		t_date.setYear(0);
		t_date.setMonth(0);
		t_date.setDay(0);
		t_date.setHour(0);
		t_date.setMinute(0);
		output << "0000-00-00/00:00";
		return output.str();
	}
	output << t_date.getYear() << '-';
	if (t_date.getMonth() < 10) output << '0';
	output << t_date.getMonth() << '-';
	if (t_date.getDay() < 10) output << '0';
	output << t_date.getDay() << '/';
	if (t_date.getHour() < 10) output << '0';
	output << t_date.getHour() << ':';
	if (t_date.getMinute() < 10) output << '0';
	output << t_date.getMinute();
	return output.str();
}
Date & Date::operator=(const Date &t_date) {
	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;
	return *this;
}
bool Date::operator==(const Date &t_date) const {
	return (m_year == t_date.m_year) && (m_month == t_date.m_month) && (m_day == t_date.m_day) && (m_hour == t_date.m_hour) && (m_minute == t_date.m_minute);
}
bool Date::operator>(const Date &t_date) const {
	return dateToString(*this) > dateToString(t_date);
}
bool Date::operator<(const Date &t_date) const {
	return dateToString(*this) < dateToString(t_date);
}
bool Date::operator>=(const Date &t_date) const {
	return dateToString(*this) >= dateToString(t_date);
}
bool Date::operator<=(const Date &t_date) const {
	return dateToString(*this) <= dateToString(t_date);
}

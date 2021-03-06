#pragma once

constexpr int YEAR_ANY = 0;
constexpr int MONTH_ANY = 0;
constexpr int DAY_ANY = 0;

bool isDate(int year = YEAR_ANY, int month = MONTH_ANY, int day = DAY_ANY);
void getDate(int &year, int &month, int &day);

bool isTime(int hour, int minute, int second);
void getTime(int &hour, int &minute, int &second);
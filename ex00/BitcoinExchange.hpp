#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>

void btc(char **av);
bool is_number(std::string num);
bool check_day(std::string date);
bool sup_than_k(std::string num);
float process_data(std::map<std::string, float> data, std::string date);

#endif
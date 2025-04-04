#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <cmath>

bool    is_number(std::string num);
bool    check_day(std::string date);
bool    sup_than_k(std::string num);
int     my_stoi(std::string &s);
float   process_data(std::map<std::string, float> data, std::string date);
void    btc(char **av);

#endif
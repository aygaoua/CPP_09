#include "BitcoinExchange.hpp"

bool is_number(std::string str) {
	if (str[0] == '+')
		str.erase(0, 1);
	if (!std::isdigit(str[0]))
		return false;
	for (unsigned long i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i]) && str[i] != '.')
			return false;
	}
	return true;
}

bool check_day(std::string date) {
	if (!is_number(date.substr(8, 2)) || !is_number(date.substr(5, 2)) || !is_number(date.substr(0, 4)))
		return false;
	std::string day = date.substr(8, 2);
	int dayValue = std::stoi(day);
	int monthValue = std::stoi(date.substr(5, 2));
	int yearValue = std::stoi(date.substr(0, 4));

	if (monthValue > 12 || monthValue < 1){
		return false;
	}

	if (date.length() != 10) {
		return false;
	}

	if (std::count(date.begin(), date.end(), '-') != 2) {
		return false;
	}

	if (monthValue == 2) {
		if (yearValue % 4 == 0 && (yearValue % 100 != 0 || yearValue % 400 == 0)) {
			if (dayValue < 1 || dayValue > 29) {
				return false;
			}
		} else {
			if (dayValue < 1 || dayValue > 28) {
				return false;
			}
		}
	} else if (monthValue == 4 || monthValue == 6 || monthValue == 9 || monthValue == 11) {
		if (dayValue < 1 || dayValue > 30) {
			return false;
		}
	} else {
		if (dayValue < 1 || dayValue > 31) {
			return false;
		}
	}

	return true;
}

bool sup_than_k(std::string num) {
	double number = std::stod(num);
	while (num[0] == '0') {
		num.erase(0, 1);
	}
	if (number > 1000) {
		return true;
	} else {
		return false;
	}
}

float process_data(std::map<std::string, float> data, std::string date) {
	std::map<std::string, float>::iterator it = data.lower_bound(date);
	if (it == data.end() || it->first != date) {
		if (it != data.begin()) {
			--it;
		} else {
			std::cout << "Error: no lower date available in the data file." << std::endl;
			return -1;
		}
	}

	if (it != data.end()) {
		return (it->second);
	} else {
		std::cout << "Error: no data available." << std::endl;
		return -1;
	}
	return (it->second);
}

void btc(char **av) {
	std::string file(av[1]);
	std::map<std::string, float> data;
	std::ifstream file_opened(file);
	std::string db_name("data.csv");
	std::ifstream data_opened(db_name);

	if (file_opened.fail()) {
		std::cout << "Failed to open file: " << file << std::endl;
		if (!data_opened.fail())
			data_opened.close();
		exit(1);
	}
	if (data_opened.fail()) {
		std::cout << "Failed to open file: " << db_name << std::endl;
		file_opened.close();
		exit(1);
	}

	std::string data_line;
	std::getline(data_opened, data_line);
	if (data_line != "date,exchange_rate") {
		std::cout << "Error: the head on data.csv is wrong" << std::endl;
		file_opened.close();
		data_opened.close();
		exit(1);
	}
	while (std::getline(data_opened, data_line)) {
		size_t pos1 = data_line.find(',', 0);
		std::string first = data_line.substr(0, pos1);
		char *endptr;
		float second = strtod(data_line.substr(pos1 + 1, data_line.size() - pos1).c_str(), &endptr);
		std::pair<std::string, float> pair_data;
		pair_data.first = first;
		pair_data.second = second;
		data[pair_data.first] = pair_data.second;
	}

	std::string line;
	std::getline(file_opened, line);
	if (line != "date | value") {
		std::cout << "Error: the head of the input file is wrong" << std::endl;
		file_opened.close();
		data_opened.close();
		exit(1);
	}
	while (std::getline(file_opened, line)) {
		if (line.empty() || std::count(line.begin(), line.end(), ' ') != 2) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		size_t pos1 = line.find('|', 0);
		std::string first = line.substr(0, pos1 - 1);
		if (first.empty()) {
			std::cout << "Error: bad input => date is not found !! `" << line  << "`" << std::endl;
			continue;
		}
		std::string second = line.substr(pos1 + 2, line.size() - pos1 + 2);
		std::pair<std::string, float> pair_file;
		char *endptr;

		if (std::count(line.begin(), line.end(), '|') != 1) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		pair_file.first = first;
		pair_file.second = strtod(second.c_str(), &endptr);
		if (*endptr \
			|| second.empty() \
			|| !is_number(second)) {
			if (pair_file.second < 0)
				std::cout << "Error: not a positive number." << std::endl;
			else
				std::cout << "Error: the input is wrong -> `" << second << "`" << std::endl;
			continue;
		}
		if (sup_than_k(second)) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		if (!check_day(pair_file.first)) {
			std::cout << "Error: bad input => " << pair_file.first << std::endl;
			continue;
		}

		if (process_data(data, pair_file.first) != -1)
			std::cout << pair_file.first << " => " \
						<< pair_file.second << " = " \
						<< pair_file.second * process_data(data, pair_file.first) \
						<< std::endl;
	}

	file_opened.close();
	data_opened.close();
}

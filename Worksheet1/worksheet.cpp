#include <iostream>

void birthday() {
	int day = 0;
	int month = 0;
	while (day < 1 || day > 31) {
		std::cout << "Help! Quickly! What is your day of birth? (Number between 1 and 31) ";
		std::cin >> day;
	}
	while (month < 1 || month > 12) {
		std::cout << "OK! Now the month! Quick! (Number between 1 and 12) ";
		std::cin >> month;
	}
}

int main() {
	birthday();
	return 0;
}

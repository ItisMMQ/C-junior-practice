#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Lib.hpp"

using namespace std;

int main() {
	while (1)
		switch (menu()) {
		case 1: includeBook();  break;
		case 2: checkOutBook(); break;
		case 3: returnBook();   break;
		case 4: status();       break;
		case 5: return 0;
		default: cout << "Wrong option, try again: ";
		}
	system("pause");
	return 0;
}

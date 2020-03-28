#include<iostream>
#include"Polynom.h"
#include<math.h>

using namespace std;

int main() {
	try {
		TPolynom pol1, pol2;
		cout << "Enter 1 polynom" << endl;
		cin >> pol1;
		cout << "Enter 2 polynom" << endl;
		cin >> pol2;
		cout << pol1 << endl;
		cout << pol2 << endl;
		pol1 += pol2;
		cout << pol1 << endl;
		pol2 *= -2;
		cout << pol2 << endl;
	}
	catch (char *s) {
		cout << s;
	}
	system("pause");
	return 0;
}
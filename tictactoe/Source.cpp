#include <iostream>
#include <vector>
using namespace std;

//Глобальные константы
const char EMPTY = ' ';

//Прототипы функций
void instructions();

int main() {
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	
	return 0;
}

void instructions()
{
	cout << "Чтобы совершить ход, введите число от 0 до 8. Число\n";
	cout << "соответствует позиции на игровой доске, как показано на рисунке:\n\n";

	cout << "       0 | 1 | 2\n";
	cout << "       ---------\n";
	cout << "       3 | 4 | 5\n";
	cout << "       ---------\n";
	cout << "       6 | 7 | 8\n\n";

}
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Глобальные константы
const char EMPTY = ' ';

//Прототипы функций
void instructions();
char askYesNo(string question);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);

int main() {
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = 'X';
	displayBoard(board);
	

	system("pause");
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

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

char humanPiece()
{
	char go_first = askYesNo("Вы будете ходить первым?");
	if (go_first == 'y')
	{
		return 'X';
	}
	else
	{
		return 'O';
	}
}

char opponent(char piece)
{
	if (piece == 'X')
	{
		return 'O';
	}
	else
	{
		return 'X';
	}
}

void displayBoard(const vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}
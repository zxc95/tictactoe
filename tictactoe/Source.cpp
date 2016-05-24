#include <iostream>
#include <vector>
#include <string>
using namespace std;

//√лобальные константы
const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char NO_ONE = 'N';
const char TIE = 'T';

//ѕрототипы функций
void instructions();
char askYesNo(string question);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);

int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(board);

	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}

	system("pause");
	return 0;
}
void instructions()
{
	cout << "„тобы совершить ход, введите число от 0 до 8. „исло\n";
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
	char go_first = askYesNo("¬ы будете ходить первым?");
	if (go_first == 'y')
	{
		return X;
	}
	else
	{
		return O;
	}
}
char opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
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
char winner(const vector<char>& board)
{
	//¬се возможные выиграшные р€ды
	const int WINNING_ROWS[8][3] = { { 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 },
	{ 0, 3, 6 },
	{ 1, 4, 7 },
	{ 2, 5, 8 },
	{ 0, 4, 8 },
	{ 2, 4, 6 } };
	const int TOTAL_ROWS = 8;

	// если в одном из выигрышных р€дов уже присутствуют три одинаковых значени€
	// (причем они не равны EMPTY), то победитель определилс€
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	// поскольку победитель не определилс€, провер€ем не наступила ли ничь€ (остались ли пустые клетки)
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	//ѕоскольку победитель не определилс€, и ничь€ не наступила, то игра продолжаетс€
	return NO_ONE;
}
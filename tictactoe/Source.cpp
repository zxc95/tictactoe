#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

//Глобальные константы
const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char NO_ONE = 'N';
const char TIE = 'T';

//Прототипы функций
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(int move, const vector<char>& board);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main() {
	SetConsoleOutputCP(1251);
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
int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}
char humanPiece()
{
	char go_first = askYesNo("Вы будете ходить первым?");
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
	//Все возможные выиграшные ряды
	const int WINNING_ROWS[8][3] = { { 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 },
	{ 0, 3, 6 },
	{ 1, 4, 7 },
	{ 2, 5, 8 },
	{ 0, 4, 8 },
	{ 2, 4, 6 } };
	const int TOTAL_ROWS = 8;

	// если в одном из выигрышных рядов уже присутствуют три одинаковых значения
	// (причем они не равны EMPTY), то победитель определился
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	// поскольку победитель не определился, проверяем не наступила ли ничья (остались ли пустые клетки)
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	//Поскольку победитель не определился, и ничья не наступила, то игра продолжается
	return NO_ONE;
}
inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == EMPTY);
}
int humanMove(const vector<char>& board, char human)
{
	int move = askNumber("Куда сходить?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nЭта позиция уже занята.\n";
		move = askNumber("Куда сходить?", (board.size() - 1));
	}
	cout << "Ход сделан...\n";

	return move;
}
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;

	//Если компьютер может выиграть следующим ходом, то он делает это
	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}

		if (!found)
		{
			++move;
		}
	}

	//Иначе, если человек может победить следущим ходом, то компьютер блокирует этот ход
	if (!found)
	{
		move = 0;
		char human = opponent(computer);

		while (!found && move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found)
			{
				++move;
			}
		}
	}

	//Иначе занять следующим ходом оптимальную свободную клетку
	if (!found)
	{
		move = 0;
		unsigned int i = 0;

		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		//Выбрать оптимальную свободную клетку
		while (!found && i <  board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}

			++i;
		}
	}

	cout << "Мой ход " << move << endl;
	return move;
}
void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << "Победил компьютер.\n";
	}

	else if (winner == human)
	{
		cout << "Вы победили.\n";
	}

	else
	{
		cout << "Ничья.\n";
	}
}

#include <iostream>
#include <vector>
using namespace std;

//���������� ���������
const char EMPTY = ' ';

//��������� �������
void instructions();

int main() {
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	
	return 0;
}

void instructions()
{
	cout << "����� ��������� ���, ������� ����� �� 0 �� 8. �����\n";
	cout << "������������� ������� �� ������� �����, ��� �������� �� �������:\n\n";

	cout << "       0 | 1 | 2\n";
	cout << "       ---------\n";
	cout << "       3 | 4 | 5\n";
	cout << "       ---------\n";
	cout << "       6 | 7 | 8\n\n";

}
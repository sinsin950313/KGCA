#include <iostream>
#include "Source.h"

using namespace std;

int main()
{
	int N, K;
	cout << "��ü ����� �� : ";
	cin >> N;
	cout << endl << "���� : ";
	cin >> K;

	int res = Calculate(N, K);
	cout << "������ : " << res << endl;
}
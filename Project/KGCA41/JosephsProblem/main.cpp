#include <iostream>
#include "Source.h"

using namespace std;

int main()
{
	int N, K;
	cout << "전체 사람의 수 : ";
	cin >> N;
	cout << endl << "간격 : ";
	cin >> K;

	int res = Calculate(N, K);
	cout << "생존자 : " << res << endl;
}
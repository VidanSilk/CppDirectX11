#include <iostream>
#include <string>

using namespace std;

int main(void) {

	string a("myname IS Victory");
	string b = "Mynmae";

	const char* pchar = a.c_str();
	if (a.empty()) {
		cout << "문자열이 없습니다 \n";

	}else{
		cout << "무언어가 있습니다 \n";
	}
	a.clear();



	a = "ABDSADW";
	string c{ "ABD" };
	int findIndex = (int)a.find(c);
	if (findIndex == string::npos)
	{
		cout << "인덱스를 찾았습니다.";
	}
	else {
		cout << "찾지못하였습니다 ";
	}
		return 0;

}
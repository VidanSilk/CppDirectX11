#include <iostream>

using namespace std;

struct sCalculateResults {
	int add_result = 0;
	int mirus_result = 0;
	int mul_result = 0;
	float div_result = 0;
	
	void printCalculate() {
		cout << add_result << endl;
		cout << mirus_result << endl;
		cout << mul_result << endl;
		cout << div_result << endl;
	}
};

using CCR = sCalculateResults;

void calculate(int n1, int n2, CCR& relsult) {
	relsult.add_result = n1 + n2;
	relsult.mirus_result = n1 - n2;
	relsult.mul_result = n1 * n2;
	relsult.div_result = n1 / n2;
}
int main(void) {

	CCR result;
	calculate(10, 2, result);
	result.printCalculate();

	return 0;
}
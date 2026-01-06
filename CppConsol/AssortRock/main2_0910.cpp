//#include <iostream>

/*
typedef 키워드 
자료형에 따 다른 별명, 별칭을 지정해줌

using
typedef와 비슷한 기능이지만, 더 많은 기능이 존재

typedef는 템플릿에서 사용이 불가능하지만
using은 사용이 가능하다 

enum class는 
enum과 다르게 
::스코프 해상도 연산자를 사용해야함
그러면 중복되는 이름도 사용가능
그리고 enum class는 형변환시 강제 캐스팅 된다.

열거형도 using, typedef가 가능

*/
//typedef struct sLocation {
//
//	int x = 0;
//	int y = 0;
//	int z = 0;
//
//}LOCATION, * PTRLOCATION;
//
//using namespace std;
//using UINT = unsigned int;
//using MyLocate = LOCATION;
//using PmyLocate = LOCATION*;
//
//enum class test {
//	t1, t2, t3
//};
//
//enum temp {
//
//	a1,a2,a3
//};
//int main(void) {
//	a1;
//	test::t1;
//
//	int t = a2;
//	t = (int)test::t2;
//	return 0;
//}
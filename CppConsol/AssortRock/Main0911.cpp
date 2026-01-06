/*
	리터럴 문자열
	코드에서 직접 표현되는 문자열  상수, " " 로 구성 
	메모리 구조 중 데이터 영역 그중에서 읽기 전용 메모리 영역에 주소 할당
	같은 문자열이면 하나의 주소를 가지고 가져다 사용.
	맨뒤에 자동으로 \0 NULL문자가 들어감 

	문자열을 조작하는 함수들
	-길이 length
	-복사 copy
	-이어 붙이기
	-문자열 나누기

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

int main(void) {

	char str[] = "hello, World\0";
	char str2[20] = "";
	string strName("Hello,World");

	//길이 length
	//cout << "길이 : " << strlen(str) << endl;
	
#pragma region 복사
	
	/*
	strcpy_s(복사할 목적지(ctrl + v 할 곳), 복사할 곳 크기 ,복사할 곳(ctrl + c하는 곳))
	참고로 사이즈를 지정 안하면 나중에 많은 값을 복사할 때 문제가 발생할 수 있음 
	_s함수는 ms에서 제공하는 곳이라 다른 ide에서는 지원이 안되어서 직접 확인해야함 
	주의 사항 
	1. 복사할 곳이 충분히 크지 않으면, 메모리 침범이 일어날 수 있다.
	2. 널문자 마감 안 했을 때 -> 문제 발생할수있음 
	오류가 났을땐 중단이 아닌 다시하기로 어디서 문제가 발생하는지 확인
	*/
	cout << str << endl;
	cout << str2 << endl;

	strcpy_s(str2, sizeof(str2), str); 
	cout << "strcpy_s 사이즈 지정 str2 : " << str2 << endl;
	strcpy_s(str2, str);
	cout << "strcpy_s 사이즈 없이 str2 : " << str2 << endl;
	strcpy(str2, str); //str
	cout << "strcpy str2 : " << str2 << endl;
#pragma endregion

#pragma region 이어붙이기
	/*
	 문자열 이어 붙이기 
	 strcat_s(연결할 곳, 연갈할 곳의 크기, 연결할 크기)

	 주의사항
	 복사랑 같음
	 1. 연결할 곳충분히 크지 않으면 메모리 침범 발생가능
	 2. 널문자로 끝나야함 
	*/
	strcpy_s(str2, sizeof(str2), "!!");
	cout << "strcpy !! str2 : " << str2 << endl;
	strcat_s(str2, sizeof(str2), str);
	cout << "strcpy_s str2 : " << str2 << endl;
	strcat_s(str2, sizeof(str2), "Jhone");
	cout << "strcat_s str2 : " << str2 << endl;
#pragma endregion

#pragma region 비교
	/*
	비교
	사전순서가 빠른게 더 높다고 생각하면 됨 
	strcmp(비교1, 비교2)
	== → 0 같다 
	< → 1 비교할것1 < 비교할것2	
	> → -1 비교할것1 > 비교할것 2

	"helloworld" == "HelloWorld"; → 리터럴 문자열끼리 이렇게 단순 비교하면 내용을 비교하는게 아닌 
	주소가 같은지를 비교함, 리터열 문자열은 결국 주소 값이기 때문임 
	*/
	cout << endl << endl; 
	"helloworld" == "HelloWorld";
	strcpy(str, "AAC");
	strcpy(str2, "Aac");
	cout << str << endl; 
	cout << str2 << endl; 
	int result = strcmp(str, str2);
	cout << result << endl;
#pragma endregion

#pragma region 검색
/*
	검색 문자열이 문자가 있는지 검색해
	문자열에 해당 문자가 있는지 검사
	strchr(검색할 곳, 검색할 문자)
	반환값이 문자가 있는 곳에 위치의 주소를 반환해주고
	문자가 없으면 nullptr를 반환

*/
	strcpy_s(str,sizeof(str), "ABCDEFGH");
	char* pPosit = strchr(str, 'C' ); // str + C(위치)의 주소 값을 반환 해줌 
	cout << "pPosit : " << pPosit << endl;
 	cout << " &str: " << &str << endl; //str 주소값 출력 
	cout << "*pPosit : "<< *pPosit << endl;
	cout << "(void*) pPosit : " << (void*)pPosit << endl; //pPosit 주소값 출력 

/*
	문자열을 넣어서 검색하는 함수
	strstr(검색할 곳(위치), 검색할 것(값));
	찾으면 해당 위치 주소값 없으면 nullptr반환

	중복된 문자열이 있으면 앞에 주소를 가져온다.
*/
	cout << endl;
	strcpy_s(str, sizeof(str), "ABCDEFGH");
	pPosit = strstr(str, "B");
	cout << "pPosit : " << pPosit << endl;
	cout << " &str: " << &str << endl; //str 주소값 출력 
	cout << "(void*) pPosit : " << (void*)pPosit << endl; //pPosit 주소값 출

#pragma endregion

#pragma region 토큰
	/*
	나누기 토큰
	strtok_s(문자열, 구분자, 컨텍스트);
	문자열에서 구분자 기분으로 나누고 남은 문자열

	문자열에 nullptr 이면 컨텍스트에 있는 내용물로 문자열을 나누니기를 계속 진행 한다 

	*/

	char str3[] = "ABC,D,E,F,G,H,I,K,L,M,M";
	char* context = nullptr;
	char* token = strtok_s(str3, ",", &context);
	cout << "str3 "<< token << endl;
	cout << "context : " << context << endl;
	cout << endl; 

	do{
		cout << "do str3 " << token << endl;
		cout << "do context : " << context << endl;
		token = strtok_s(nullptr, ",", &context);
	}	while (token != nullptr);

	strcpy_s(str3, "A,B;C:D F");
	context = nullptr;
	token = strtok_s(str3, ",;: ", &context);
	cout << "do context : " << context << endl;
#pragma endregion
	return 0;
}
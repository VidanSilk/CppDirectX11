#include "vectorClass.h"


int main(void) {

	vectorClass<int> Vec;
    Vec.Input(); //벡터 입력 
    Vec.VecOutPut(); //벡터 출력
    //벡터 탐색 정방향 역방향 
    Vec.vecSearch();
    Vec.RvecSearch();

    vectorClass<char> Vec2;//이런식으로 하며 체이닝이 일어날까?
    Vec2.vecResize();
    Vec2.VecOutPut();
    Vec2.vecSearch();
    Vec2.RvecSearch();

    //또 뭐가 있을까.
    //뭐가 좋을까? 
    //반복자가 아닌 접근 연산자로 접근해볼까? 

	return 0;
}



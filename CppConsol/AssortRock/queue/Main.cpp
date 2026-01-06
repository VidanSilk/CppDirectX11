/*
큐를 구현해볼까? 
트리를 구현해볼까?
아니면 그래프? 

스택 다음은 큐지?
그럼 큐도 일반 큐를 구현할까?
양방향 큐인 deque을 구현할까?
아니면 순환하는 서클 큐를 구현할까?

셋다 구현을 해보자 

1. 큐란? 
 FIFO 선입 선출을 원리 front는 맨앞 back or 리어 뒤
 출력 동작 은 보통 dequeue라고하고 스택처럼 pop이라고도 할 수 있음
 입력 동작은 Enqueue, or push
 큐는 연결리스트를 통해 구현하는 것이 편함 
 그럼 연결리스트도 일반 큐는 단방향이 편하겠지 ?
 그리고 메모리 파편화대해서도 생각 해볼까? 
 
 2. 데큐,덱 양방향 큐 
 양쪽에서 삽입/인출이 가능 
 fornt이든 rear이든 둘다 삽입 삭제연산이 가능핟. 
 
 3. 순환큐 
 front와 rear바로 옆으로 만나게 만듬 
 그럼 뭘로 구현하는게좋을까?
 메모리는 사람처럼 원형이 아닌 ㅁㅁㅁㅁㅁㅁㅁ연속이니
 ㅁㅁㅁㅁㅁ에서 앞과 뒤를 바로 붙게 만들면되는거아님? 
 f       r를 붙어 
 fr 이런식으로 이중연결리스트(?)로 구현하면 될까? 
 그럼 전부 양방향으로 갈 수 있게 만들어야할까?
*/

#include "queueHeader.h"
int main(void) {

	cQueue<int> myQue;

	myQue.Cenqueue(10);
	std::cout << "순환큐 front1 " << myQue.front() << std::endl;
	std::cout << "순환큐 rear1 " << myQue.rear() << std::endl;
	myQue.Cenqueue(200);
	myQue.Cenqueue(33);
	myQue.Cdequeue();
	myQue.Cenqueue(1670);
	std::cout << "순환큐 front2 " << myQue.front() << std::endl;
	std::cout << "순환큐 front2 " << myQue.rear() << std::endl;
	myQue.Cenqueue(44);
	myQue.Cenqueue(155);
	myQue.Cdequeue();
	myQue.Cenqueue(1023);
	myQue.Cenqueue(1044);
	std::cout << "순환큐 front3 " << myQue.front() << std::endl;
	std::cout << "순환큐 front3 " << myQue.rear() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;


	std::deque<int> deq;
	deq.push_back(10);
	deq.push_front(10);
	deq.pop_back();
	deq.pop_front();
	
	return 0;
}
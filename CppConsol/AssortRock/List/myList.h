#pragma once
/*
반복자를 이용해서 리스트를 구현해보자.
무엇이 필요할까?
삽입 
push_front
push_back 
제거 
pop_fornt
pop_back 

사이즈 관련 
empty 비어있는거 체크 
size
초기화
clear 

그리고 현재 데이터 출력 

반복자 
begin
end
insert
erase
*/

#include <iostream>
#include <list>
//노드
template<typename T>
class CListNode
{
	template<typename T>
	friend class myList;

	template<typename T>
	friend class cIterator;

private:
	T mData;							// 데이터 
	CListNode<T>* mNext = nullptr;	//내 다음 노드 주소
	CListNode<T>* mPrev = nullptr;	// 내 이전 노드 주소 

public:
	CListNode(){}
	~CListNode(){}
};

//반복자
//연산자 모음 
template<typename T>
class cIterator {
	template<typename T>
	friend class myList;

private:
	CListNode<T>* mNode = nullptr;

public:
	cIterator() = default;
	~cIterator() = default;
	// == != ++ -- *역참조

	bool operator==(const cIterator& iter) {
		return mNode == iter.mNode;
	}

	bool operator !=(const cIterator& iter) {
		return mNode != iter.mNode;
	}
	// 자기 자신을 내보낸다 
	const cIterator& operator++() {
		mNode = mNode->mNext;
		return *this;
	}
	// 매개변수에 int를 적어주면 후위연산이 된다
	const cIterator& operator++(int) {
		cIterator<T> iter;//지금 노드 주소를 저장
		iter.mNode = mNode->mNext; //다음으로 옮긴 다음 
		return iter; //이전껄 반환
	}
	const cIterator& operator--() {
		mNode = mNode->mPrev;
		return *this;
	}
	const cIterator& operator--(int) {
		cIterator<T> iter;//지금 노드 주소를 저장
		iter.mNode = mNode->mPrev; //다음으로 옮긴 다음 
		return iter; //이전껄 반환
	}

	T& operator*()	//역참조 구현 
	{
		//mNode가 nulltpr인경우  
		return mNode->mData;
	}
};

template<typename T>
class myList {
private:

	using NODE = CListNode<T>; //CListnode클래스를 NODE라고 지칭 
	NODE* mBegin; // 리스트의 시작지점 
	NODE* mEnd;	// 리스트의 끝지점 
	int mSize = 0;

public:
	using iterator = cIterator<T>;

	//생성자를 통해서 노드 초기화. 
	myList() {
		mBegin = new NODE;
		mBegin->mData = (int)&mBegin;
		mEnd = new NODE;
		mEnd->mData = (int)&mEnd;

		//friend 클래스를 선언했기 때문에 private라도 사용가능하다. 
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	//소멸자 
	~myList() {
		clear();	//동적할당 해제 
		delete mBegin;
		delete mEnd;
	}

	void push_back(const T& _data)
	{
		NODE* node = new NODE;
		if (node == nullptr) return; 
		node->mData = _data;	//데이터 넣어주고 
		//포인터 연결해주기
		NODE* Prev = mEnd->mPrev;
		
		Prev->mNext = node;
		node->mPrev = Prev;
		
		mEnd->mPrev = node;
		node->mNext = mEnd;
		
		mSize++;
	}

	//fornt 앞에서 데이터 삽입
	void push_front(const T& _data) {
		NODE* node = new NODE;
		if (node == nullptr) return;
		//데이터 넣어주고 
		node->mData = _data;
		NODE* Next = mBegin->mNext; //포인터 연결해주고 
		
		Next->mPrev = node;
		node->mNext = Next;

		mBegin->mNext = node;
		node->mPrev = mBegin;
	
		mSize++;
	}

	//삭제 
	void pop_back() {

		if (mSize == 0) return;
		
		NODE* deleteNode = mEnd->mPrev; //삭제할 노드 
		NODE* lastNode = deleteNode->mPrev; // 삭제할 노드 이전의 노드가 마지막노드가 되도록 설정  
		
		lastNode->mNext = mEnd; // 마지막 노드의 다음을 mEnd로 설정
		mEnd->mPrev = lastNode; // mEnd의 이전을 새 마지막 노드로 설정
		
		delete deleteNode; // 메모리 해제
		mSize--; //리스트 크기를 감소해준다 
	}

	//앞에서 삭제 
	void pop_front() {
		if (mSize == 0) return;
		
		NODE* deleteFrontNode = mBegin->mNext; //맨앞에서(?) 삭제할 노드 ->next해줘야하는가? ㅇㅇ 
		NODE* NextFrontNdoe = deleteFrontNode->mNext; //일단 삭제할 노드의 다음이 첫 노드가 됨

		NextFrontNdoe->mPrev = mBegin; // 새 첫 노드의 이전을 begin으로 설정 
		mBegin->mNext = NextFrontNdoe; // 시작 노드의 다음을 새 첫 노드로 설정
		
		delete deleteFrontNode; //넌 이제 필요없으니 ㅃㅃ
		mSize--;
	}
	 
	
	//사이즈 체크
	int size() {
		return mSize;
	}
	
	// 비어있는지 체크
	bool empty() const {
		return mSize == 0;
	}

	//리스트를 출력한다. 
	void printList() {
		NODE* nowNode = mBegin->mNext;
		while (!(nowNode == mEnd)) {
			std::cout << nowNode->mData << " ";
			nowNode = nowNode ->mNext;
		}
		std::cout << std::endl;
	}


	void clear() {
		NODE* node = mBegin->mNext;
		while (node != mEnd) {
			NODE* next = node->mNext;
			delete node;
			node = next;
		}
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0; 
	}

	//반복자들
	iterator begin() {
		iterator iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}
	
	iterator end() {
		iterator iter;
		iter.mNode = mEnd;
		return iter;
	}

	iterator insert(const iterator& iter, const T& dta){
		NODE* node = new NODE;
		node->mData = dta;

		NODE* Prev = iter.mNode->mPrev;
		Prev->mNext = node;
		node->mPrev = Prev;
		node->mNext = iter.mNode;
		iter.mNode->mPrev = node;

		mSize++;
		iterator Riter;
		Riter.mNode = node;
		return Riter;
		
	}

	iterator erase(const iterator& iter) {
		if (mSize <= 0) return end();

		NODE* Prev = iter.mNode->mPrev;
		NODE* Next = iter.mNode->mNext;
		delete iter.mNode;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		--mSize;

		iterator Riter;
		Riter.mNode = Next;
		return Riter;
	}
};




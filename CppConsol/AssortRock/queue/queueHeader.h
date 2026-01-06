#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list> 
#include <queue> //stl에서 제공해주는거라 편하겠지만 가능하면 직접구현하자
//논리적으로 번호표를 바꾸자
#include <deque>
//노드 
template<typename Qu>
struct  sListNode
{
	sListNode* next;//다음 노드 
	Qu data;
	sListNode(const Qu& dt) : data(dt), next(nullptr) {}
};

template<typename Qu>
class cQueue {
private:

	sListNode<Qu>* frontNode = nullptr; // 큐의 맨 앞
	sListNode<Qu>* rearNode = nullptr;  // 큐의 맨 뒤
	int mSize = 0;

public:
	cQueue() {}
	~cQueue() {
		while (!empthy())
		{
			dequeue();
		}
	}

	// 큐의 맨앞 위치를 가르킨다
	Qu front() {
		return frontNode->data;
	}
	// 큐의 맨뒤, Back과 동일함 
	Qu rear() {
		return rearNode->data;
	} 
	
	//rear다음은 fornt, fornt 뒤는 rear
	// 그럼 rearNode->Next = frontNode로 연결하거나 
	// 추가해서 frontNode->BackNext = rearNode로 
	//큐에 push한다(데이터입력) 
	//일반적인 큐 삽입
	void enqueue(const Qu& data) {

		sListNode<Qu>* newNode = new sListNode<Qu>(data);
		if (empthy()) {
			//노드가 비어있으면 리어와 프론트는 같은 곳을 가르킴 
			frontNode = rearNode = newNode;
		}
		else {
			//데이터를 입력하면 뒤쪽은 다음 노드로 이동하고, 
			//그걸 가르킴 
			rearNode->next = newNode;
			rearNode = newNode;

		}
		++mSize;
	}
	//순환큐 삽입
	void Cenqueue(const Qu& data) {

		sListNode<Qu>* newNode = new sListNode<Qu>(data);
		if (empthy()) {
			//노드가 비어있으면 리어와 프론트는 같은 곳을 가르킴 
			frontNode = rearNode = newNode;
			rearNode->next = frontNode; // 순환큐 연결
		}
		else {
			//데이터를 입력하면 뒤쪽은 다음 노드로 이동하고, 
			//그걸 가르킴 
			rearNode->next = newNode;
			rearNode = newNode;
			rearNode->next = frontNode; // 순환 연결 유지

		}
		++mSize;
	}

	// 데이터 삭제 (pop 기능) 
	//일반적인 큐 삭제
	void dequeue() {
		sListNode<Qu>* TempNode = frontNode;
		frontNode = frontNode->next;
		delete TempNode;
		--mSize;
		if (frontNode == nullptr) { 
			rearNode = nullptr; 
		}
	}
	//순환 큐 삭제 
	void Cdequeue() {

		if (frontNode == rearNode) {
			delete frontNode;
			frontNode = rearNode = nullptr;
		}
		else {
			sListNode<Qu>* TempNode = frontNode;
			frontNode = frontNode->next;
			rearNode->next = frontNode; // 순환 연결 유지
			delete TempNode;
		}
		--mSize;
	}

	bool empthy() {
		return mSize == 0;
	}
	
	int size() {
		return mSize;
	}

};
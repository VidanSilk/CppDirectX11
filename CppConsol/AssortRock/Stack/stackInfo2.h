#pragma once
#include <iostream>
#include <stack> //직접구현시 필요 x 
#include <string>
#include <vector>
// 스택 LIFO
// psuh(input) 데이터 입력
// pop 데이터 제거
// top 현재위치 ( 마지막 위치를 가져온다)
#define MYNULL 0

template<typename T>
class myStack {

private: 

	T* arr = nullptr;
	int mSize = 0;
	int mCapacity = 0;

public: 
	myStack() {}
	
	~myStack() {
		if(!(arr == nullptr)) delete[] arr;
	}

	void push(const T& data)
	{
		if (mSize >= mCapacity)	// 메모리 재할당 
		{
			//mCapacity 가 0이면 1, 그외는 2배로 공간을 늘려준다. 
			mCapacity = mCapacity == 0 ? 1 : mCapacity * 2;	//삼항연산자 

			T* newArr = new T[mCapacity];
			for (int i = 0; i < mCapacity; ++i)
			{
				newArr[i] = MYNULL;
			}

			for (int i = 0; i < mSize; ++i)
			{
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
		}
		arr[mSize++] = data;
	}

	T top(){
		return arr[(mSize - 1)];
	}

	void pop() {
		if (mSize > 0) --mSize;
	}

	void clear() {
		for (int i = 0; i < mSize; i++) {
			arr[i] = MYNULL;
		}
		mSize = 0;
	}
	bool empty() {
		return mSize == 0; 
	}
};
 
/*
 vector
	a.push_back; //마지막 요소에 입력  
	a.pop_back;// 마지막 요소만 제거 

	a.size; //크기
	a.resize; //크기 변경 및 재할당  
	a.front //벡터의 첫 요소를 가르킴
	a.back //벡터의 끝요소를 가르킴 
	a.capacity; //벡터의 할당 받는 공간을 확인
	a.clear; //소멸자에서 대체 가능 
	a.emplace; // 테이너에 키가있는 요소가 없는 경우 지정된 인수로 구성된 컨테이너에 새 요소를 삽입한다 //일단 구현해볼까? 이건 고민해보자 
	[] -? opeartor로? 벡터로? 
	iteroator
	insert 
	erase
	++  -- ==
	반복자 만들거면 메모리 양끝 마감체크할 메모리도 추가해줘야한다 
*/
#pragma once
#include<memory>
template <typename T>
class myVector {
	
private:
	template<typename T>
	friend class cIterator;
	
	T* mData;
	int mSize;
	int mCapacity;

	//재할당 함수
	void ReAlloc(int capacity) {
		mCapacity = capacity;
		T* newArray = new T[mCapacity + 2];
		if()
		memcpy();// 메모리 복사 memmory 헤더필요
	}
public:
	using iterator = cIterator<T>;

	myVector() : mData(nullptr), mSize(0), mCapacity(0) {}
	~myVector() {
		if (mData != nullptr) {
			delete[] mData;
		}
	}

	//벡터 마지막 칸 부터 원소 입력
	void push_back(const T& _data) {
		if (mSize > mCapacity) {
			int newCapacity = (mCapacity == 0) ? 1 : mCapacity * 2; //삼항 연산자는 a ? b : c일 때 a가 참이면 b, 거짓일땐 c이다.
			
			T* newData = new T[newCapacity];

			for (int i = 0; i < mSize; i++) {
				newData[i] = mData[i];
			}
			
			mData = newData;
			mCapacity = newCapacity;
		}
		mData[mSize] = _data;
		mSize++;
	}
	//벡터 마지막 칸의 요소 삭제

	void pop_back() {
		if (mSize > 0) {
			mSize--; 
		}
	}

	//크기 확인
	int size() {
		return mSize;
	}
	
	//크기 재할당
	void resize(int rSize) {
		if (rSize < mSize) { //재할당할 사이즈가 현재사이즈보다 작다면 
			mSize = rSize; //크기를 줄인다  
		}
		else if (rSize > mSize) { //재할당한 사이즈가 현재사이즈보다 크다면
			if (rSize > mCapacity) { //그리고 재할당한 사이즈가 용량보다 크다면  
				//rSize = mCapacity * 2; //용량 확보를 해준다. 어떻게 구현할까? 걍 무식하게 곱하기? 아니면 삼항연산? 아니면 리저브호출?
				reserve(rSize);
			}
			for (int i = mSize; i < rSize; ++i) {
				mData[i] = T(); // 기본값으로 초기화
			}
			mSize = rSize;
		}

	}
	//벡터의 용량(=capacity)은 늘리지만, 사이즈(=크기, size)는 변경하지 않는다.
	// 한번 확장된 용량은 줄어들 수 없다.
	//그럼 받아온 값만큼 곱하기로 되지 않을까? 
	int reserve(int rCapacity) {
		return mCapacity *= rCapacity;
	}
	int capacity() {
	//할당된 크기를 확인
		return mCapacity;
	}

	//벡터 비어있는지 확인 
	bool empty() {
		return mSize == 0;
	}

	//벡터 초기화 
	void clear() {
		delete[] mData;
		mData = nullptr;
		mSize = 0;
		mCapacity = 0;
	}
	//////////////////
	//여기서 operator[]와 반복자의 insert와 erase 
	

};

//반복자
//iteroator
//insert
//erase
//++  -- ==
template<typename T>
class cIterator {
private:
	template<typename T>
	friend class myVector;
	
	int mIndex = -1;
	myVector<T>* mData = nullptr; 
public:
	cIterator() = default;
	~cIterator() = default;
	//==
	bool operator==(const cIterator& iter) {
		return mData = iter.mData;
	}
	//++ 전위
	
	bool operator++() {
		++mData; //이게될까? 
		return *this;
	}
	//-- 전위
	bool operator--() {
		--mData;
		return *this;
	}
};
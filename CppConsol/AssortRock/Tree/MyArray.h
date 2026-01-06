#pragma once

#include <memory.h>	//memcpy 사용하기 위해서
#include <utility>	//std::move 사용하기 위해서 

template <typename T>
class CArrayIterator
{
	template<typename T>
	friend class CArray;
public:
	CArrayIterator() = default;
	~CArrayIterator() = default;
private:
	CArray<T>* mCArray = nullptr;
	int mIndex = -1;

public:
	T& operator*()	//역참조 
	{
		return mCArray->mArray[mIndex];
	}

	//++ -- 
	void operator ++()	//전위
	{
		++mIndex;
	}
	void operator ++(int)	//후위 
	{
		mIndex++;
	}

	void operator --()	//전위
	{
		--mIndex;
	}
	void operator --(int)	//후위
	{
		mIndex--;
	}

	// + = += -=
	CArrayIterator<T> operator +(int num) const
	{
		CArrayIterator<T> iter;
		iter.mCArray = mCArray;
		iter.mIndex = mIndex + num;
		return iter;
	}

	CArrayIterator<T> operator -(int num) const
	{
		CArrayIterator<T> iter;
		iter.mCArray = mCArray;
		iter.mIndex = mIndex - num;
		return iter;
	}

	const CArrayIterator<T>& operator +=(int num)
	{
		mIndex += num;
		return *this;
	}

	const CArrayIterator<T>& operator -=(int num)
	{
		mIndex -= num;
		return *this;
	}
	
	// == 비교 연산자 
	bool operator ==(const CArrayIterator<T>& iter) const
	{
		//1. 같은 배열이냐 
		//2. 같은 인덱스인가 
		return (mCArray == iter.mCArray) && (mIndex = iter.mIndex);
	}

	bool operator !=(const CArrayIterator<T>& iter) const
	{
		return !((mCArray == iter.mCArray) && (mIndex == iter.mIndex));
	}
};

template <typename T>
class CArray
{
	template<typename T>
	friend class CArrayIterator;
public:
	using iterator = CArrayIterator<T>;
private:
	T* mArray = nullptr;
	int mSize = 0;
	int mCapacity = 0;

	T* mMemory = nullptr;
	
public:
	CArray() = default;
	~CArray()
	{
		if (mArray != nullptr)
		{
			delete[] mArray;
		}
	}
public:
	void push_back(const T& value)
	{
		if (mSize >= mCapacity)
		{
			if (mCapacity == 0)
			{
				ReAlloc(2);
			}
			else
			{
				int newCapacity = (int)(mCapacity * 2.f);
				ReAlloc(newCapacity);
			}	
		}
		mArray[mSize + 1] = value;	//0번 인덱스는 begin 이니까 인덱스는 +1 해준다. 
		++mSize;
	}
	
	// 이동 시멘틱 
	void push_back(T&& value)
	{
		if (mSize >= mCapacity)
		{
			if (mCapacity == 0)
			{
				ReAlloc(2);
			}
			else
			{
				int newCapacity = (int)(mCapacity * 2.f);
				ReAlloc(newCapacity);
			}
		}
		mArray[mSize + 1] = std::move(value);
		++mSize;
	}

	void pop_back()
	{
		if (mSize > 0)
		{
			--mSize;
		}
	}

	int size() const 
	{
		return mSize;
	}
	int capacity()
	{
		return mCapacity;
	}

	bool empty() const
	{
		return mSize == 0;
	}

	void clear()
	{
		mSize = 0;
	}
	
	//resize
	void resize(int newSize)
	{
		if (newSize > mCapacity)	//한번 확장된 capacity 는 줄어들수 없다. 
		{
			ReAlloc(newSize);
		}
		mSize = newSize;
	}

	//reserve
	void reserve(int newsize)
	{
		if (newsize > mCapacity)
		{
			ReAlloc(newsize);
		}
	}
		
	//연산자 
	T& operator [](int index)
	{
		return mArray[index + 1];	//앞에 begin이 있으니까 +1을 해준것이다. 
	}
///////////////////////////////////////////////////////////
	// 반복자 
	iterator begin()
	{
		iterator iter;
		iter.mCArray = this;
		iter.mIndex = 1;	// mArray[0] 은 begin 시작 메모리이다. 데이터의 시작점은 index 1부터이다. 
		return iter;
	}
	iterator end()
	{
		iterator iter;
		iter.mCArray = this;
		iter.mIndex = mSize + 1;
		return iter;
	}

	//erase
	iterator erase(const iterator& iter)
	{
		if (iter.mIndex <1 || iter.mIndex > mSize)
		{
			return end();
		}

		for (int i = iter.mIndex; i < mSize; ++i)
		{
			mArray[i] = mArray[i + 1];
		}
		--mSize;

		return iter;
	}



private:
	//재할당 함수 미리 만들어두자 
	void ReAlloc(int capacity)
	{
		mCapacity = capacity;

		//begin, end를 표현할 공간을 위해서 
		//2개더 추가해준다. 
		T* newArray = new T[mCapacity + 2];

		if (mArray != nullptr)
		{
			//strcpy(); -> 문자열 복사 	
			memcpy(newArray + 1, mArray + 1 ,sizeof(T) * mSize );	// -> 메모리 복사 memory.h 추가 필요
			delete[] mArray;
		}
		mArray = newArray;
	}

};


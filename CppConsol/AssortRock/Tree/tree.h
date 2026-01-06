#pragma once
#include "MyArray.h" 


template<typename KEY, typename Value>
class cTreeNode {
	//template<typename KEY, typename Value>
	//friend class CTree;

public:
	KEY			mKey;				//키 값
	Value		mValue;				//데이터 값 
	cTreeNode* mParent = nullptr;	//부모노드 
	CArray<CTreeNode*> mChild;		// 자식 노드들
};

template<typename KEY, typename Value>
class cTree {

private:
	template<typename KEY, typename Value>
	friend class cTreeNode;

	cTreeNode<KEY, Value>* mRoot = nullptr;  //루트 노드 
	int mSize = 0; //노드 개수

public:
	cTree() {}
	~cTree() {}
	//오버로딩해서 부모키를 찾아 부모와 연결해주는 자식 노드들 삽입 
	void insert(const KEY& key, const Value& val, const KEY& parentKey) {
		//내 key랑 value를 이용해서 노드를 만든다음
		cTreeNode<KEY, Value>* newNode = new cTreeNode<KEY, Value>;
		newNode->mKey = key;
		newNode->mValue = value;

		//부모키를 이용해서 부모를 찾기
		//애가 만약 루트라면?
		if (mRoot == nullptr)
		{
			//루트노드가 없을 경우 루트로 지정한다. 
			mRoot = newNode;
		}
		else
		{
			//root노드가 있으니까 부모 키값 찾기 부터 해야한다. 
			cTreeNode<KEY, Value>* parentNode = FindNode(parentKey); //찾아와야하는다. 
			if (parentNode != nullptr)
			{
				// 부모의 자식으로 등록한다. 
				parentNode->mChild.push_back(newNode);
				// 자식의 부모를 등록한다. 
				newNode->mParent = parentNode;
			}
			else
			{
				//부모 키값을 찾지못했으므로 동적생성한 노드를 제거한다. 
				delete newNode;
				return;
			}
		}
		mSize++;
	}

	//키값으로 서치 부모 노드와 자식 노드연결할 때 꼭 필요 
	//어떻게 구현할까? dfs? bfs? 아니면 순회로 탐색이 가능하지 않음? 
	//순회는 완성된 걸 하나씩 탐색하는 개념이지 않은가? 
	// 그럼 dfs bfs 여기서는 다 같은 기능임. 
	//전위 순회? 뿌 왼 오  
	
	//찾기용 함수가 필요하다. 
	Value* find(const KEY& key)	//애는 값을 찾아오는용도 
	{
		cTreeNode<Key, Value>* resultNode = FindNode(key);
		if (resultNode != nullptr)
		{
			return &resultNode->mValue;
		}
		return nullptr;
	}

	// 삭제
	//자식부터 지울수도 있고, 중간에 지울수도 있다.
	// 만약에 중간 삭제를 하는 경우 밑에 있는 자식과 위에있는 부모를 재설정해줘야 한다. 만약에 부모부터 지워지는 경우는?
	// 그럼 최상단 노드(루트)를 다시 정해줘야하지않을까? 
	/*void delTree(const KEY& key, const Value& val) {
		.복잡하니 넘어가자! 
		mSize--;
	}*/
	//모두 지우기 
	void clear()
	{
		clear(mRoot);
		mRoot = nullptr;	//댕글링 포인터~ : 쓰래기 포인터 존재하지 않는 녀석을 가리키는 포인터다.
		mSize = 0;
	}

	// 사이즈 가져오기
	int size() {
		return mSize;
	}
	// 비어있는지 
	bool empty() {
		return mRoot == nullptr;
	}

private:
	cTreeNode<KEY, Value>* FindNode(const KEY& key)
	{
		return FindNode(key, mRoot);
	}

	cTreeNode<KEY, Value>* FindNode(const KEY& key, cTreeNode<KEY, Value>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->mKey == key)	//노드찾은거 아니야? 
		{
			return node;
		}

		for (auto iter = node->mChild.begin(); iter != node->mChild.end(); ++iter)
		{
			cTreeNode<KEY, Value>* resultNode = FindNode(key, *iter);
			if (resultNode != nullptr)
			{
				return resultNode;
			}
		}
		return nullptr;
	}

	void clear(cTreeNode<KEY, Value>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		int ChildSize = node->mChild.size();
		for (int i = 0; i < ChildSize; ++i)
		{
			clear(node->mChild[i]);
		}

		delete node;
	}

};
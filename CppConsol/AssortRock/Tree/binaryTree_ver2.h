#pragma once
#include <iostream>

template <typename Key, typename Value>
struct sBinaryTree{

	Key skey; //키 값 
	Value sVal;// 데이터 값 

	sBinaryTree* sParent = nullptr; // base
	sBinaryTree* leftChild = nullptr; // left sub
	sBinaryTree* rightChild = nullptr; //right sub 

};

template <typename Key, typename Value>
class myBinaryTree {
private:
	sBinaryTree<Key, Value>* mRoot; //root

public:
	myBinaryTree() : mRoot(nullptr) {}
	~myBinaryTree() {}

	//메인에서 호출할 함수 즉, 동작(구현은) private에서 한다
	void insert(const Key& _key, const Value& _value) {
		insertNode(mRoot, nullptr, _key, _value);
	}
	
	Value* search(const Key& _key) {
		return  searchNode(mRoot, _key);
	}
	 
	//삭제 
	void delTree(const Key& _key) {
		mRoot = delNode(mRoot, _key);
	}

	//메인에서 호출할 순회 탐색 함수들
	void pre_Treavel() {
		pre_order(mRoot);
	}
	void in_Treavel() {
		in_order(mRoot);
	}
	void post_Treavel() {
		post_order(mRoot);
	}

private :
	void insertNode(sBinaryTree<Key, Value>*& _node, sBinaryTree<Key, Value>* _parent, const Key& _key, const Value& _value) {
		//노드값이 없을 경우 
		if (!_node) {
			//구조체에 설정한 변수와 똑같이 매개변수 설정 key, val, base, left, right sub
			_node = new sBinaryTree<Key, Value>{ _key, _value,_parent, nullptr, nullptr };
			return;
		}
		//키값이 작을 경우
		if (_key < _node->skey) {
			insertNode(_node->leftChild, _node, _key, _value);
	 	} //키값이 클 경우 
		else if (_key > _node->skey) {
			insertNode(_node->rightChild, _node, _key, _value);
		}
		// 키가 같으면 값만 업데이트
		else {
			_node->sVal = _value; 
		}
	}

	//반갈죽해서 탐색 동시에 find 역할도 해줌 
	Value* searchNode(sBinaryTree<Key, Value>* _node, const Key& _key) {
		if (!_node) return nullptr;
		if (_key < _node->skey)
			return searchNode(_node->leftChild, _key);
		else if(_key > _node-> skey)
			return searchNode(_node->rightChild, _key);
		else return &_node->sVal; //같을 경우 해당 값의 주소 반환
	}

	//트리삭제 
	sBinaryTree<Key, Value>* delNode(sBinaryTree<Key, Value>* _node, const Key& _key) {
		if (!_node) return nullptr;

		if (_key < _node->skey) {
			_node->leftChild = delNode(_node->leftChild, _key);
		}
		else if (_key > _node->skey) {
			_node->rightChild = delNode(_node->rightChild, _key);
		}
		else {
			//서브가 없는 경우
			if (!_node->leftChild && !_node->rightChild) {
				delete _node;
				return nullptr;
			}
			//서브가 하나인 경우
			else if (!_node->leftChild) {
				sBinaryTree<Key, Value>* temp = _node->rightChild;
				temp->sParent = _node->sParent;
				delete _node;
				return temp;
			}
			else if (!_node->rightChild) {
				sBinaryTree<Key, Value>* temp = _node->leftChild;
				temp->sParent = _node->sParent;
				delete _node;
				return temp;
			}
			//서브가 둘인 경우 
			else {
				//최소값 노드인 노드를 찾기
				sBinaryTree<Key, Value>* temp2 = _node->rightChild;
				while (temp2 && temp2->leftChild) temp2 = temp2->leftChild;

				_node->skey = temp2->skey;
				_node->sVal = temp2->sVal;
				_node->rightChild = delNode(_node->rightChild, temp2->skey);

			}
		}
		return _node;
	}


	//트리 순회 
	// 전위 뿌 왼 오 
	void pre_order(sBinaryTree<Key, Value>* _node) {
		if (!_node)return;
		//뿌리 출략
		std::cout << "전위 순회 키 : " << _node->skey << "\t 값 : " << _node->sVal << std::endl;
		pre_order(_node->leftChild);
		pre_order(_node->rightChild);
	}
	//중위 왼뿌오
	void in_order(sBinaryTree<Key, Value>* _node) {
		if (!_node) return;
		in_order(_node->leftChild);
		std::cout << "중위 순회 키 : " << _node->skey << "\t 값 : " << _node->sVal << std::endl;
		in_order(_node->rightChild);

	}
	//후위 왼오 뿌
	void post_order(sBinaryTree<Key, Value>* _node) {
		if (!_node) return;
		post_order(_node->leftChild);
		post_order(_node->rightChild);
		std::cout << "후위 순회 키 : " << _node->skey << "\t 값 : " << _node->sVal << std::endl;
	}

};
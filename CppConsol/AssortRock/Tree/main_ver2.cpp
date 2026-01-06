#include "binaryTree.h"

int main(void) {
	
	myBinaryTree<char, float> t;
	//삽입
	t.insert('F', 10.24f);
	t.insert('D', 5.123f);
	t.insert('A', 7.1245f);
	t.insert('C', 12.6880f);
	t.insert('G', 13.1234f);
	t.insert('B', 161.1234f);
	t.insert('Z', 121.1250f);
	t.insert('W', 11.1f);
	t.insert('V', 174.212f);
	std::cout << *t.search('A'); //주소값이 나옴 
	std::cout << std::endl;;
	std::cout << *t.search('Z'); //주소값이 나옴 
	std::cout << std::endl;;


	t.delTree('W');
	t.pre_Treavel(); //전위 순회 
	std::cout << std::endl;
	
	t.delTree('A'); // 키값 A 삭제
	t.in_Treavel(); //중위 순회 (A삭제 됨) 
	std::cout << std::endl;
	
	t.delTree('B'); // B가 키값인 노드 삭제
	t.post_Treavel(); //후위 순회 
	return 0;
}
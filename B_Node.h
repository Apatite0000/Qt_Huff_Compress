#pragma once
#include <string>
class B_Node 
{
public:
	B_Node* lchild;
	B_Node* rchild;
	int data;//数据
	//char data;
	int weight;//权值
	std::string zip_code;

	bool operator<(B_Node right) const { return weight < right.weight; };// less<> 用这个
	bool operator>(B_Node right) const { return weight > right.weight; };// greater<> 用这个

	B_Node() { data = 0; weight = 0; lchild = NULL; rchild = NULL; };
	void set_data(int d, int w, B_Node* lkid=NULL, B_Node* rkid=NULL) { data = d; weight = w; lchild = lkid; rchild = rkid; };
	void weight_plus() { weight++; };
};

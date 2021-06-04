#pragma once
#include "B_Node.h"
#include <queue>
#include <iostream>
class H_Tree 
//   : public B_Tree
{
public:
    H_Tree();//初始化树
    H_Tree(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > p_queue);

    ~H_Tree();//析构函数
    void post_order_and_delete(B_Node* r);

    void create_huff_tree_and_set_code(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > p_queue);

    void create_huff_tree(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > p_queue);
    //建树
    //注意greater的std：：
    //这也是一个模板

    void set_code();//设置哈夫曼编码    
    void set_code(B_Node* &r, std::string code="");

    std::string find_zip_code(int data);//查询data值的哈夫曼编码
    void find_zip_code(int data, B_Node* r,std::string &c);

    bool find_real_code(std::string s, char &data);//解压时返回数值
private:
    B_Node* m_root;
};


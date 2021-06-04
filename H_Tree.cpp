#include "H_Tree.h"

H_Tree::H_Tree()
{
	m_root = NULL;
}

H_Tree::H_Tree(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node>> p_queue)
{
	create_huff_tree(p_queue);
	set_code();
}



H_Tree::~H_Tree()
{
	post_order_and_delete(m_root);
}

void H_Tree::post_order_and_delete(B_Node* r)
{
	if (r != NULL)
	{
		post_order_and_delete(r->lchild);
		post_order_and_delete(r->rchild);
		delete r;
	}

}

void H_Tree::create_huff_tree_and_set_code(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node>> p_queue)
{
	create_huff_tree(p_queue);
	set_code();
}



void H_Tree::create_huff_tree(std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > p_queue)
{
	while (p_queue.size() > 1)
	{
		B_Node *node1 = new B_Node;
		B_Node *node2 = new B_Node;
		B_Node node_insert;
		node1->set_data(p_queue.top().data, p_queue.top().weight, p_queue.top().lchild, p_queue.top().rchild);
		p_queue.pop();
		node2->set_data(p_queue.top().data, p_queue.top().weight, p_queue.top().lchild, p_queue.top().rchild);
		p_queue.pop();
		node_insert.set_data(-10000, node1->weight + node2->weight, node1, node2);
		p_queue.push(node_insert);
	}
	B_Node *node = new B_Node;//注意往树里面写的必须是地址，不然会自己释放掉0xcccccccc
	node->set_data(p_queue.top().data, p_queue.top().weight, p_queue.top().lchild, p_queue.top().rchild);
	m_root = node;
}

void H_Tree::set_code(B_Node* &r, std::string code)
{
	if (r == NULL)	return;
	r->zip_code = code;
	set_code(r->lchild, code + '0');
	set_code(r->rchild, code + '1');
}

void H_Tree::set_code()
{
	B_Node* r = m_root;
	set_code(r);
}

std::string H_Tree::find_zip_code(int data)
{
	std::string answer;
	find_zip_code(data, m_root,answer);
	return answer;
}

void H_Tree::find_zip_code(int d, B_Node* r,std::string &c)
{
	if (r != NULL)
	{
		if (r->data == d)	c = r->zip_code;
		find_zip_code(d, r->lchild, c);
		find_zip_code(d, r->rchild, c);
	}
}

bool H_Tree::find_real_code(std::string s, char &d)
{
	int pos = 0;
	B_Node* r = m_root;
	while (pos < s.size())
	{
		if (r == NULL)	return false;
		s[pos] == '0' ? r = r->lchild : r = r->rchild;
		pos++;
		if (r == NULL)	return false;//22.35
	}
	if (r->data != -10000)
	{
		d = r->data;
		return true;
	}
	else
	{
		return false;
	}

}


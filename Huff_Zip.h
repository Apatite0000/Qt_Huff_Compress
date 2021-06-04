#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <map>
#include "H_Tree.h"
#include "B_Node.h"
#include "md5.h"

class Huff_Zip
{
public:
	//Huff_Zip();//无参构造
	Huff_Zip(std::string file_name,bool mode_code);

	void file_in_compress();
	void file_out_compress();
	void file_decompress();

	char str_to_char(std::string x);//八位二进制转字符
	std::string char_to_str(char x);//字符转八位二进制
	//注意 char范围

	bool is_decompress_same();

	double get_ratio();

    std::string get_md5();
private:
	H_Tree m_huff_tree;
	std::string m_md5;
	std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > 
	m_node_queue;
	std::string m_original_name;
	std::string m_processed_name;
	int m_original_size;
	int m_processed_size;
	bool m_mode;//T为压缩，F为解压
	bool is_same;//m_mode==1时永假
	double m_zip_ratio;
};


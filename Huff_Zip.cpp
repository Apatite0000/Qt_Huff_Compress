#include "Huff_Zip.h"

Huff_Zip::Huff_Zip(std::string file_name, bool mode_code)
{
	m_mode = mode_code;
	m_original_size = -1;
	m_processed_size = -1;
	m_zip_ratio = -1;
	is_same = false;
	//todo 生成容量 ratio
	if (m_mode)
	{
		//压缩模式
		m_original_name = file_name;
		m_processed_name = file_name + ".huffzip";
		file_in_compress();
		file_out_compress();
	}
	else
	{
		//解压模式
		m_processed_name = file_name;
		file_name.erase(file_name.size()-8,8);
		m_original_name = file_name;
		file_decompress();
	}
}

void Huff_Zip::file_in_compress()
{
	std::ifstream in(m_original_name, std::ios::binary);
	std::map<char, int> node_set;
	std::string file_content = "";

	char temp;
	in.get(temp);
	while (in.good())
	{
		int n = temp;
		if (node_set.find(n) == node_set.end())
		{
			node_set[n] = 1;
		}
		else
		{
			node_set[n]++;
		}
		file_content = file_content + temp;
		in.get(temp);
	}

	m_original_size = file_content.size();

	MD5 t_md5(file_content);
	m_md5 = t_md5.toStr();

	for (auto i = node_set.begin(); i != node_set.end(); i++)
	{
		B_Node t_node;
		//set 两个元素为i->first,i->second;
		t_node.set_data(i->first, i->second);
		m_node_queue.push(t_node);
	}
	
	m_huff_tree.create_huff_tree_and_set_code(m_node_queue);
}

void Huff_Zip::file_out_compress()
{
	std::ifstream in(m_original_name, std::ios::binary);
	std::ofstream out(m_processed_name, std::ios::binary);
	std::priority_queue<B_Node, std::vector<B_Node>, std::greater<B_Node> > p_queue = m_node_queue;
	std::string zip_contant="";//记录压缩文件内容
	std::string node_zip_code = "";//输入的每一个字节的对应哈夫曼码
	std::string in_code_8bit = "";//凑齐8位的输出
	char t;

	//正文的转换
	in.get(t);
	int num_of_0 = 0;
	while (in.good())
	{
        //int i = t;
		node_zip_code = m_huff_tree.find_zip_code(t);
		while (node_zip_code.size() > 0)
		{
			char head_char = node_zip_code.at(0);
			node_zip_code.erase(node_zip_code.begin());
			in_code_8bit = in_code_8bit + head_char;
			if (in_code_8bit.size() == 8)
			{
				char t_out = str_to_char(in_code_8bit);
				zip_contant += t_out;//保存输出
				in_code_8bit = "";
			}
		}
		in.get(t);
	}
	if (in_code_8bit.size() > 0)
	{
		
		while (in_code_8bit.size() != 8)
		{
			in_code_8bit = in_code_8bit + '0';
			num_of_0++;
		}
		char last_char;
		last_char = str_to_char(in_code_8bit);
		zip_contant += last_char;//保存最后一位节点
	}
	else
	{
		num_of_0 = 0;
	}

	int file_size = 0;
	//前面辅助数据的输出
	out << zip_contant.size();//正文大小
	int temp_m = zip_contant.size();
	for (; temp_m > 0; temp_m /= 10)	file_size++;
	file_size += zip_contant.size();
	out << ' ';
	out << num_of_0;//末尾补0个数
	out << std::endl;
	out << m_md5;//MD5值
	out << std::endl;
	file_size += 36;//4+32
	out << p_queue.size();//节点个数
	for (temp_m = p_queue.size(); temp_m > 0; temp_m /= 10)	file_size++;
	out << std::endl;
	while (!p_queue.empty())//节点内容
	{
		char t = p_queue.top().data;
		out << t;
		out << ' ';
		out << m_huff_tree.find_zip_code(t);
		out << std::endl;
		p_queue.pop();
		file_size = file_size + 3 + m_huff_tree.find_zip_code(t).size();
	}
	out << zip_contant;//正文的输出

	in.close();
	out.close();
	m_processed_size = file_size;
	m_zip_ratio = m_processed_size * 1.0 / m_original_size;
}

void Huff_Zip::file_decompress()
{
	std::ifstream in(m_processed_name,std::ios::binary);
	std::ofstream out(m_original_name, std::ios::binary);
	int num_of_0, node_num;//, node_weight;
	//num_of_0 文件末尾补充的0的个数
	//node_num 节点个数
	std::string md5_from_text;//待解压文件自身提供的MD5值
	std::string ori_content = "";//原文件内容
	std::string node_zip_code;//单个节点的哈夫曼码
    char node_data, space,t_head_char,data;
	//node_data 待解压文件储存的节点值
	//space	流处理时占位用
	//t_char 待处理字符
	//t_head_char 
	std::map<std::string,char> node_set;
	int file_size;
	in >> file_size;
	m_processed_size = file_size;
	in >> num_of_0;
	in >> md5_from_text;
	in >> node_num;
	for (int temp_m = node_num; temp_m != 0; temp_m /= 10)	m_processed_size++;
	m_processed_size += 33;
	in.get(space);
	std::string file_content(file_size,'\0');
	for (int i = 1; i <= node_num; i++)
	{
		
		in.get(node_data);
		in.get(space);
		in >> node_zip_code;
		in.get(space);
		node_set[node_zip_code] = node_data;
		m_processed_size = m_processed_size + 3 + node_zip_code.size();
	}

	std::string byte_code = "";
	std::string node_code = "";
	char* a = &file_content[0];
	in.read(a, file_size);

	for (int i = 0; i != file_size; i++)
	{
		byte_code = char_to_str(file_content[i]);
		while (!byte_code.empty())
		{
			t_head_char = byte_code[0];
			byte_code.erase(byte_code.begin());
			node_code = node_code + t_head_char;
			if (node_set.count(node_code))
			{
				data = node_set[node_code];
				out << data;
				ori_content += data;
				node_code = "";
			}
		}
	}
	in.close();
	out.close();

	m_original_size = ori_content.size();

	MD5 processed_md5(ori_content);
	string processed_md5_code = processed_md5.toStr();
    if (processed_md5_code == md5_from_text)
    {
        is_same = true;
        m_md5 = md5_from_text;
    }

	m_zip_ratio = m_processed_size * 1.00 / m_original_size;
}


char Huff_Zip::str_to_char(std::string x)//char 在文件中存的是补码
{
	int a = 0;
	if (x[0] == '0')
	{
		//positive
		for (int i = 0; i != x.size(); i++)
		{
			a = a * 2 + x.at(i)- '0';
		}
	}
	else
	{
		bool is_meet_1 = false;
		for (int i = x.size() - 1; i >= 0; i--)
		{
			if (is_meet_1)
			{
				if (x[i] == '0')	x[i] = '1';
				else	x[i] = '0';
			}
			if (x[i] == '1')	is_meet_1 = true;
			//右边开始，直到见1，之后翻转。
		}
		for (int i = 0; i != x.size(); i++)
		{
			a = a * 2 + x.at(i) - '0';
		}
		a = -a;
	}
	return a;
}

std::string Huff_Zip::char_to_str(char x)
{
	int a = abs(x);
	string str_8bit="";
	while (a != 0)
	{
		int t_int = a % 2;
		char t_char = '0' + t_int;
		str_8bit = t_char + str_8bit;
		a /= 2;
	}
	while (str_8bit.size() < 8)	str_8bit = '0' + str_8bit;
	if (x <= 0)
	{
		bool is_meet_1 = false;
		for (int i = str_8bit.size() - 1; i >= 0; i--)
		{
			if (is_meet_1)
			{
				if (str_8bit[i] == '0')	str_8bit[i] = '1';
				else	str_8bit[i] = '0';
			}
			if (str_8bit[i] == '1')	is_meet_1 = true;
			//右边开始，直到见1，之后翻转。
		}
	}
	return str_8bit;
}

bool Huff_Zip::is_decompress_same()
{
	return is_same;
}

double Huff_Zip::get_ratio()
{
	return m_zip_ratio;
}

std::string Huff_Zip::get_md5()
{
    return m_md5;
}

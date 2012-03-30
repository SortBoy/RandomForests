/************************************************************************************/
/*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/31/2011                                                     **/
/***********************************************************************************/
#ifndef NODE_H_
#define NODE_H_
#include"utility.h"

class Node{
private:
	static int node_num_;
	NodeType type_;
	int case_num_;   //added for result file
	int id_;   //added for result file
public:
	Node();
	void set_type_(NodeType);
	NodeType GetNodeType();
	void set_case_num_(int case_num);
	int get_case_num_();
	int get_id_();

};

#endif

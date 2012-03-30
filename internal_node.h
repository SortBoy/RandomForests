/***********************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/20/2012                                                      **/
/***********************************************************************************/
#ifndef INTERNAL_NODE_H_
#define INTERNAL_NODE_H_
#include"utility.h"
#include"node.h"
using namespace std;
class InternalNode:public Node{
private:
	int attribute_;
	double split_value_;
	map<int,Node*> child_node_;
	double info_gain_;  //added for result file
public:
	InternalNode();
	void set_attribute_(int attribute);
	int get_attribute_();
	void set_split_value(double split_value);
	double get_split_value();
	void  set_child_node_(int,Node*);
	map<int,Node*> get_all_child_nodes_();
	Node* get_child_node_(int value);
};


#endif

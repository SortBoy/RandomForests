/***********************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/20/2012                                                      **/
/***********************************************************************************/

#ifndef LEAF_NODE_H_
#define LEAF_NODE_H_

#include"utility.h"
#include"node.h"
using namespace std;

class LeafNode:public Node{
private:
	int class_;
	double purity_;
public:
	LeafNode();
	void set_class_(int class_);
	int get_class_();
	void set_purity_(double purity);
	double get_purity_();
};

#endif 

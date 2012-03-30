/************************************************************************************/
/*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/31/2011                                                     **/
/***********************************************************************************/
#include"node.h"

int Node::node_num_ = 0;

Node::Node(){
	Node::node_num_ ++;
	this->id_ = Node::node_num_;
}

void Node::set_type_(NodeType type){
	this->type_=type;
}

NodeType Node::GetNodeType(){
	return this->type_;
}

void Node::set_case_num_(int case_num){
	this->case_num_ = case_num;
}
int Node::get_case_num_(){
	return this->node_num_;
}
int Node::get_id_(){
	return this->id_;
}

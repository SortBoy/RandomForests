/***********************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/20/2012                                                      **/
/***********************************************************************************/
#include"internal_node.h"

InternalNode::InternalNode(){
	this->set_type_(INTERNALNODE);
}

void InternalNode::set_attribute_(int attribute){
	this->attribute_=attribute;
}
int InternalNode::get_attribute_(){
	return this->attribute_;
}
void InternalNode::set_split_value(double split_value){
	this->split_value_=split_value;
}
double InternalNode::get_split_value(){
	return this->split_value_;
}
void  InternalNode::set_child_node_(int attribute,Node* node){
	this->child_node_.insert(map<int,Node*>::value_type(attribute,node));
}
Node* InternalNode::get_child_node_(int value){
	return this->child_node_[value];
}

map<int,Node*> InternalNode::get_all_child_nodes_(){
	return this->child_node_;
}

//NodeType InternalNode::GetNodeType(){
//	return INTERNALNODE;
//}
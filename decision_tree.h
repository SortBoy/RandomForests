/************************************************************************************/
/*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/31/2011                                                     **/
/***********************************************************************************/
#ifndef DECISION_TREE_H_
#define DECISION_TREE_H_
#include"utility.h"
#include"node.h"
#include"training_set.h"
#include"attribute_selection_method.h"
#include"c4_5_attribute_selection_method.h"
#include"leaf_node.h"
#include"internal_node.h"
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

class DecisionTree{
private:
	Node* root_;
public:
	void set_root_(Node* root);
	Node* get_root_();
	Node* GenerateDecisionTreeByC4_5(TrainingSet* training_set,vector<int> training_set_index,vector<int> attribute_list);
	/***������ȱ�����******/
	void TraverseTree(ofstream& f,TrainingSet* training_set,Node* decision_tree);
	/***����һ����ݣ�Ԥ������*****/
	Node* PredictClass(TrainingSet* training_set,int index,Node* root);
	double GetErrorRate(TrainingSet* training_set,vector<int> training_set_index);
};

#endif

///************************************************************************************/
///*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
///*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
///*      created in 12/29/2011                                                     **/
///***********************************************************************************/
//1.���ĳ���ԣ���training_set_index�õ����training_set_index
//2.��һ��training_set_index�еõ�������ǩ���ֵĸ���
//3.
#ifndef TRAINING_SET_H_
#define TRAINING_SET_H_
#include"utility.h"
#include<map>
#include"attribute_value_mapper.h"
#include"data_file_reader.h"
#include<sstream>
#include<iostream>
using namespace std;

class TrainingSet{
private:
	AttributeValue** value_matrix_;
	AttributeValueMapper attribute_value_mapper_;
	int training_set_num_;
public:
	void set_attribute_value_mapper(AttributeValueMapper);
	int get_training_set_num_();
	//void ProduceTrainingSet(DataFileReader);
	//void test();
	void TestMatrix();
	//Tuple At(int);
	int GetClassifyAttribute();
	AttributeType GetAttributeType(int);
	//int GetTupleClass(int);
	int GetAttributeNum();
	vector<int> GetNormalAttributes();
	int GetAttributeValueNum(int);
	map<int,double> GetClassDistribution(vector<int>);
	int GetTheMostClass(vector<int>);
	bool IsTrainingSetSameClass(vector<int>);
	map<int,vector<int> > SplitByDiscreteAttribute(vector<int>,int);
	/*ͨ��λ�÷���ѵ���������õ��������ֵ�ѵ����,map<0,training_set_index1>Ϊǰһ����
	   map<1,training_set_index2>Ϊ��һ����.pos��ֵ��СΪ1�����Ϊtraining_set_num-1*/
	map<int,vector<int> > SplitByPositon(vector<int>,int);
	void DeleteOneAttribute(vector<int>&,int);
	string GetAttributeName(int attribute);
	string GetAttributeValueName(int attribute,int index);
	vector<int> GetClassesNum(vector<int> training_set_index);
    
	
	void ProduceTrainingSetMatrix(DataFileReader data_file_reader);
	AttributeValue** GetValueMatrixP();

	
};
#endif

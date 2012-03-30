/************************************************************************************/
/*      copyright 2012 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/10/2012                                                    **/
/***********************************************************************************/
/*****C4.5����ѡ����************************/
#ifndef C4_5_ATTRIBUTE_SELECTION_METHOD_H_
#define C4_5_ATTRIBUTE_SELECTION_METHOD_H_
#include<ctime>
#include<cmath>
#include"attribute_selection_method.h"
#include"utility.h"
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstdio>
class C4_5AttributeSelectionMethod:public AttributeSelectionMethod{
private:
    static int seed_num_;
	bool status_;
	const static int training_set_minimum_=2;
	map<int,double> info_gain_;
	map<int,double> split_info_;
	map<int,map<int,vector<int> > >splited_training_set_;
	map<int,double> split_value_;
public:

	C4_5AttributeSelectionMethod(TrainingSet*,vector<int>,vector<int>);
	void set_status_(bool status);
	bool get_status_();
	static int get_training_set_minimum_(){
		return C4_5AttributeSelectionMethod::training_set_minimum_;
	}
	static int get_seed_(){
		return C4_5AttributeSelectionMethod::seed_num_;
	}
	static void inc_seed_(){
		C4_5AttributeSelectionMethod::seed_num_ ++;
	}

	void set_info_gain_(int attribute,double info_gain);
	double get_info_gain_(int attribute);
	void set_split_info_(int attribute,double split_info);
	double get_split_info_(int attribute);
	void set_splited_training_set(int attribute,map<int,vector<int> > splited_training_set_index);
	map<int,vector<int> > get_splited_training_set_(int attribute);
	void set_split_value_(int attribute,double split_value);
	double get_split_value(int attribute);



	double CalculateInfo(vector<int> training_set_index);

	double CalculateContinuousAttributeInfoGain(int attribute);
	bool HandleContinuousAttribute(int attribute);
	double CalculateInfoByClassNum(vector<int>& class_num,int all_num);

	double CalculateDiscreteAttributeInfoGain(int attribute);
	bool HandleDiscreteAttribute(int attribute);

	void ExecuteSelection();

	//void SortTrainingSetByContinuousAttribute(int attribute,vector<int>& training_set_index,int left,int right);
	void SortTrainingSetByContinuousAttribute(vector<IndexValue>& index_value_sort);
	vector<int> GetRandomSubSpace(vector<int> attribute_list);
	void TestGetRandomSubSpace();


};

#endif


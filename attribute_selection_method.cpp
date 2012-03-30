/************************************************************************************/
/*      copyright 2012 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/10/2012                                                    **/
/***********************************************************************************/
#include"attribute_selection_method.h"
AttributeSelectionMethod::AttributeSelectionMethod(TrainingSet* training_set,vector<int> training_set_index, vector<int> attribute_list)
{
	    this->training_set_=training_set;
		this->training_set_index_=training_set_index;
		this->attribute_list_=attribute_list;
		this->case_num_ = training_set_index.size();
}


TrainingSet* AttributeSelectionMethod::get_training_set_(){
	return this->training_set_;
}

vector<int> AttributeSelectionMethod::get_training_set_index_(){
	return this->training_set_index_;
}

vector<int> AttributeSelectionMethod::get_attribute_list_(){
	return this->attribute_list_;
}

void AttributeSelectionMethod::set_attribute_(int attribute){
	this->attribute_=attribute;
}

int AttributeSelectionMethod::get_attribute_(){
	return this->attribute_;
}

void AttributeSelectionMethod::set_split_value_result_(double split_value){
	this->split_value_result_=split_value;
}

double AttributeSelectionMethod::get_split_value_result_(){
	return this->split_value_result_;
}

void AttributeSelectionMethod::set_splited_training_set_result_(map<int,vector<int> > splited_training_set_index){
	this->splited_training_set_result_=splited_training_set_index;
}

map<int,vector<int> > AttributeSelectionMethod::get_splited_training_set_result_(){
	return this->splited_training_set_result_;
}

AttributeSelectionResult AttributeSelectionMethod::GetSelectionResult(){
	AttributeSelectionResult result;
	result.attribute_=this->attribute_;
	if(this->training_set_->GetAttributeType(this->attribute_)==CONTINUOUS)
		result.split_value_=this->split_value_result_;
	result.splited_training_set=this->splited_training_set_result_;
	return result;
}

void AttributeSelectionMethod::set_case_num_(int case_num){
	this->case_num_ = case_num;

}
int AttributeSelectionMethod::get_case_num_(){
	return this->case_num_;
}

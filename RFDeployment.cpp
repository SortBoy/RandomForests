/*
 * RFDeployment.cpp
 *
 *  Created on: 28 Mar, 2012
 *      Author: meng
 */

#include "RFDeployment.h"

RFDeployment::RFDeployment() {

}

RFDeployment::RFDeployment(RandomForests& RF) {
	this->random_forests_ = RF.get_trees();
}

int RFDeployment::PredictClass(TrainingSet* training_set, int tuple) {
	map<int, int> mapper;
	vector<DecisionTree*>::iterator iter;
	for (iter = this->random_forests_.begin();
			iter != this->random_forests_.end(); ++iter) {
		int target_class = ((LeafNode*) ((*iter)->PredictClass(training_set,
				tuple, (*iter)->get_root_())))->get_class_();
		if (mapper.find(target_class) == mapper.end()) {
			mapper.insert(map<int, int>::value_type(target_class, 1));
		} else {
			mapper[target_class]++;
		}

	}
	int max = 0;
	int result;
	map<int, int>::iterator map_iter;
	for (map_iter = mapper.begin(); map_iter != mapper.end(); ++map_iter) {
		if (map_iter->second >= max) {
			result = map_iter->first;
			max = map_iter->second;
		}
	}
	return result;
}

double RFDeployment::GetErrorRate(TrainingSet* training_set,
		vector<int> training_set_index) {
	int error = 0;
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	int target_attribute = training_set->GetClassifyAttribute();
	vector<int>::iterator iter;
	for (iter = training_set_index.begin(); iter != training_set_index.end();
			++iter) {
		if (this->PredictClass(training_set, *iter)
				!= value_matrix[target_attribute][*iter].discrete_value_) {
			error++;
		}
	}
	cout << "the error num is " << error << endl;
	return ((double) error) / ((double) training_set_index.size());
}

void RFDeployment::GetEachTreeErrorRate(TrainingSet* training_set,
		vector<int> training_set_index) {
	double rate = 0;
	int tree_num = 0;
	for (vector<DecisionTree*>::iterator it = this->random_forests_.begin();
			it != this->random_forests_.end(); ++it) {
		double error_rate = (*it)->GetErrorRate(training_set,
				training_set_index);
		rate += error_rate;
		++tree_num;
		cout << "the tree error rate:" << error_rate << endl;
	}
	cout << "the average error rate:" << rate / tree_num << endl;

}

void RFDeployment::GenerateConfusionMatrix(TrainingSet* training_set, vector<int> training_set_index) {

	int class_num = training_set->GetAttributeValueNum(training_set->GetClassifyAttribute());
	int training_set_num = training_set_index.size();
	cout << "the test num = " << training_set_num << endl;
	int i;
	for (i = 0; i < class_num; ++i) {
		confusion_matrix c_matrix;
		c_matrix.false_n_ = 0;
		c_matrix.false_p_ = 0;
		c_matrix.true_n_ = training_set_num;
		c_matrix.true_p_ = 0;
		this->c_matrix_.push_back(c_matrix);
	}
	int error = 0;
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	int target_attribute = training_set->GetClassifyAttribute();
	vector<int>::iterator iter;
	for (iter = training_set_index.begin(); iter != training_set_index.end(); ++iter) {
		int predict_class = this->PredictClass(training_set, *iter);
		int actual_class = value_matrix[target_attribute][*iter].discrete_value_;
		if (predict_class != actual_class) {
			error++;
			this->c_matrix_.at(actual_class).false_n_++;
			this->c_matrix_.at(predict_class).false_p_ ++;
			this->c_matrix_.at(predict_class).true_n_--;
		}
		else{
			this->c_matrix_.at(predict_class).true_p_++;
		}
		this->c_matrix_.at(actual_class).true_n_--;
	}
	vector<confusion_matrix>::iterator it;
	int correct = 0;
	for(it = this->c_matrix_.begin(); it != this->c_matrix_.end(); ++ it){
		correct += it->true_p_;
		cout << it->true_p_ << " " << it->false_n_ << " " << it->false_p_ << " " << it->true_n_ << endl;
	}
	cout << "error num = " << error << endl;
	cout << "correct num = " << correct << endl;
	cout << "the error rate is = "<< (double)error / (double)(error + correct) << endl;
}


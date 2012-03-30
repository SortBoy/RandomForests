/*
 * RFDeployment.h
 *
 *  Created on: 28 Mar, 2012
 *      Author: meng
 */

#ifndef RFDEPLOYMENT_H_
#define RFDEPLOYMENT_H_
#include"utility.h"
#include"random_forests.h"
#include"decision_tree.h"
using namespace std;

struct confusion_matrix {
	int true_p_;
	int false_n_;
	int false_p_;
	int true_n_;
};

class RFDeployment {
private:
	vector<confusion_matrix> c_matrix_;
	vector<DecisionTree*> random_forests_;
public:
	RFDeployment();
	RFDeployment(RandomForests& RF);
	int PredictClass(TrainingSet* training_set,int tuple);
	double GetErrorRate(TrainingSet* training_set,vector<int> training_set_index);
	void GenerateConfusionMatrix(TrainingSet* training_set,vector<int> training_set_index);
	void GetEachTreeErrorRate(TrainingSet* training_set,vector<int> training_set_index);

};

#endif /* RFDEPLOYMENT_H_ */

#ifndef RANDOM_FORESTS_H_
#define RANDOM_FORESTS_H_
#include<vector>
#include"decision_tree.h"
#include"training_set.h"
#include"node.h"
#include"internal_node.h"
#include"leaf_node.h"
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

class RandomForests{
private:
	TrainingSet* training_set_;
	int trees_num_;
	vector<DecisionTree*> random_forests_;
public:
	RandomForests(TrainingSet* training_set,int tree_num);
	vector<DecisionTree*> get_trees();
	void GenerateRF();
	int PredictClass(TrainingSet* training_set,int tuple);
	double GetErrorRate(TrainingSet* training_set,vector<int> training_set_index);
	vector<vector<int> > GetRandomTrainingSet();
	void GetEachTreeErrorRate(TrainingSet* training_set,vector<int> training_set_index);
	void PrintTrees();

	/********��Ԫ���Ժ���**************/
	void TestGetRandomTrainingSet();

};

#endif

/*
 * a.add the exccution time infomation
 */


#include<iostream>
#include<ctime>
#include"utility.h"
#include"data_file_reader.h"
#include"attribute_value_mapper.h"
#include"c4_5_attribute_selection_method.h"
#include"training_set.h"
#include"decision_tree.h"
#include"random_forests.h"
#include"RFDeployment.h"

using namespace std;

int main(int argc,char* argv[]){
	clock_t start = clock();
    if ( argc != 3){
		cout << "you must pass the file stream parameter and tree num parameter !" << endl;
		return 1;
	}

	string stream_name = argv[1];

	string data_file = stream_name + ".data";
	string test_file = stream_name + ".test";
	string name_file = stream_name + ".names";
	string num_str = argv[2];
	int tree_num = atoi(num_str.c_str());


	cout << "Try to read the data file " << endl;

	DataFileReader* df = new DataFileReader();
	df->setFilePath(data_file);
	df->setDelim(',');
    if ( df->read() == FAIL ){
		cout << " Can not read the data file !" << endl;
		return 1;
	}

	cout << "Data file is readed successfully ! " << endl;
	cout << "Try to read the names file ! " << endl;

    AttributeValueMapper * attribute_value_mapper = new AttributeValueMapper(name_file);
	if ( attribute_value_mapper->MapAttributeValue() == FAIL ){
		cout << "Can not read the names file !" << endl;
		return 2;
	}

	attribute_value_mapper->test();

	cout << "Names file is readed successfully ! " << endl;
	cout << "Try to produce the training set ! " << endl;
	TrainingSet*  training_set = new TrainingSet();
	training_set->set_attribute_value_mapper(*attribute_value_mapper);
	training_set->ProduceTrainingSetMatrix(*df);
	cout << "Training set is produced successfully !" << endl;
    delete df;

//
//	vector<int> training_set_index;
//	int training_set_num = training_set->get_training_set_num_();
//	int i;
//	for(i=0;i<training_set_num;i++){
//		training_set_index.push_back(i);
//	}

		

	

    /*cout << "step five !" << endl;

	C4_5AttributeSelectionMethod method(p,training_set_index,p->GetNormalAttributes());
	method.HandleContinuousAttribute(0);*/
//
//    cout << "Try to generate the decision  tree! " << endl;
//	DecisionTree decision_tree;
//	Node* root=decision_tree.GenerateDecisionTreeByC4_5(training_set,training_set_index,training_set->GetNormalAttributes());
//	decision_tree.set_root_(root);
//	decision_tree.TraverseTree(training_set,decision_tree.get_root_(),0);
//
//    cout << "Decision tree is generated successfully !" << endl;
//
//    cout << "Try to evaluate the tree by test data ! " << endl;
//	DataFileReader dt;
//	dt.setFilePath(test_file);
//	dt.setDelim(',');
//	if ( dt.read() == SUCCESS ){
//		TrainingSet* test = new TrainingSet();
//        test->set_attribute_value_mapper(*attribute_value_mapper);
//	    test->ProduceTrainingSetMatrix(dt);
//        vector<int> training_set_index_predict;
//	    int test_num = test->get_training_set_num_();
//	    for(i=0;i<test_num;i++){
//		    training_set_index_predict.push_back(i);
//	    }
//	    cout<<"the error rate is:"<<decision_tree.GetErrorRate(test,training_set_index_predict)<<endl;
//	}else {
//		cout << " Can't find the test data ! " << endl;
//	}


    cout << "Try to produce the random forests which have " << tree_num << " trees !" << endl;
	RandomForests* random_forests = new RandomForests(training_set,tree_num);
	random_forests->GenerateRF();
	//random_forests->PrintTrees();
	cout << "The random forests generates successfully !" << endl;
	cout << "Try to evaluate on the tree !" << endl;
	DataFileReader *dt = new DataFileReader();
	dt->setFilePath(test_file);
	dt->setDelim(',');
	if ( dt->read() == SUCCESS ){
		TrainingSet* test_set = new TrainingSet();
		test_set->set_attribute_value_mapper(*attribute_value_mapper);
		test_set->ProduceTrainingSetMatrix(*dt);
		delete dt;
		delete attribute_value_mapper;
		vector<int> training_set_index_predict;
		int test_num = test_set->get_training_set_num_();
		int i;
		for( i = 0;i < test_num;i ++ ){
			training_set_index_predict.push_back(i);
		}
		cout << "The test data have " << test_num <<  " data sets" << endl;
		cout << "Get each tree error rate in the forests !" << endl;
		RFDeployment RF_deployment(*random_forests);
		//RF_deployment.GetEachTreeErrorRate(test_set,training_set_index_predict);
		RF_deployment.GenerateConfusionMatrix(test_set,training_set_index_predict);
		//cout << "Get the forests error rate !" << endl;
		//cout << "the error rate is:" << RF_deployment.GetErrorRate(test_set,training_set_index_predict) << endl;
	}else {
		cout << " Can't find the test data ! " << endl;
	}

	clock_t finish = clock();
	cout << "the program execution time is " << ((finish - start) / CLOCKS_PER_SEC ) / 60.0 << " minutes";
	return 0;
	

}

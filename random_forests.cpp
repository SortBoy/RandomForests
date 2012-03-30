/*
 * a.the random number generate?
 * b.is the training set repeatalbe?
 * c.the attribute can be repeatable
 */


#include"random_forests.h"
RandomForests::RandomForests(TrainingSet* training_set,int trees_num){
	this->training_set_=training_set;
	this->trees_num_=trees_num;
}

vector<DecisionTree*> RandomForests::get_trees(){
	return this->random_forests_;
}

void RandomForests::GenerateRF(){
	vector<vector<int> > training_sets=this->GetRandomTrainingSet();
	int i = 0;
	vector<vector<int> >::iterator iter;
	for(iter=training_sets.begin();iter!=training_sets.end();++iter){
		DecisionTree* decision_tree=new DecisionTree();
		Node* root=decision_tree->GenerateDecisionTreeByC4_5(this->training_set_,*iter,this->training_set_->GetNormalAttributes());
		decision_tree->set_root_(root);
		this->random_forests_.push_back(decision_tree);
		i ++ ;
		cout << i << " trees have generated !" << endl;
	}

}

void RandomForests::PrintTrees(){
	vector<DecisionTree*>::iterator iter;
	int i = 1;
	for(iter = this->random_forests_.begin(); iter != this->random_forests_.end(); ++ iter){
		string name;
		stringstream ss;
		ss << i;
		ss >> name;
		ofstream f(name.c_str());
		Node* root = (*iter)->get_root_();
		(*iter)->TraverseTree(f,this->training_set_,root);
		i ++;
	}
}

//int RandomForests::PredictClass(TrainingSet* training_set,int tuple){
//
//}

vector<vector<int> > RandomForests::GetRandomTrainingSet(){
	int max= this->training_set_->get_training_set_num_();
	vector<vector<int> > all_vec;
	vector<int> vec;
	int random_num;
	int i;
	int k = 0;
	for(i=0;i<this->trees_num_;++i){
		int j;
		for(j=0;j<max;++j){
			srand(unsigned(time(NULL)+k));
			random_num=rand()%max;
			vec.push_back(random_num);
			k++;
		}
//		sort(vec.begin(),vec.end());
//		vector<int>::iterator it=unique(vec.begin(),vec.end());
//		vec.resize(it-vec.begin());
		all_vec.push_back(vec);
		vec.clear();

	}
	return all_vec;
}

void RandomForests::TestGetRandomTrainingSet(){
	vector<vector<int> > all_vec=this->GetRandomTrainingSet();
	vector<vector<int> >::iterator iter1;
	for(iter1=all_vec.begin();iter1!=all_vec.end();++iter1){
		cout<<"------------------------------------------------------------"<<endl;
		vector<int>::iterator iter2;
		for(iter2=(*iter1).begin();iter2!=(*iter1).end();++iter2){
			cout<<*iter2<<" ";
		}
		cout<<endl;
	}

}

int RandomForests::PredictClass(TrainingSet* training_set,int tuple){
	map<int,int> mapper;
	vector<DecisionTree*>::iterator iter;
	for(iter=this->random_forests_.begin();iter!=this->random_forests_.end();++iter){
		int target_class=((LeafNode*)((*iter)->PredictClass(training_set,tuple,(*iter)->get_root_())))->get_class_();
		if(mapper.find(target_class)==mapper.end()){
			mapper.insert(map<int,int>::value_type(target_class,1));
		}else{
			mapper[target_class]++;
		}

	}
	int max=0;
	int result;
	map<int,int>::iterator map_iter;
	for(map_iter=mapper.begin();map_iter!=mapper.end();++map_iter){
		if(map_iter->second>=max){
			result=map_iter->first;
			max = map_iter->second;
		}
	}
	return result;
}

double RandomForests::GetErrorRate(TrainingSet* training_set,vector<int> training_set_index){
	int error=0;
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	int target_attribute = training_set->GetClassifyAttribute();
	vector<int>::iterator iter;
	for(iter=training_set_index.begin();iter!=training_set_index.end();++iter){
		if(this->PredictClass(training_set,*iter) != value_matrix[target_attribute][*iter].discrete_value_){
			error++;
		}
	}
	cout<<"the error num is "<<error<<endl;
	return ((double)error)/((double)training_set_index.size());
}


void RandomForests::GetEachTreeErrorRate(TrainingSet* training_set,vector<int> training_set_index){
	double rate=0;
	int tree_num=0;
	for(vector<DecisionTree*>::iterator it=this->random_forests_.begin();it!=this->random_forests_.end();++it){
		double error_rate=(*it)->GetErrorRate(training_set,training_set_index);
		rate+=error_rate;
		++tree_num;
		cout<<"the tree error rate:"<<error_rate<<endl;
	}
	cout<<"the average error rate:"<<rate/tree_num<<endl;
	
}

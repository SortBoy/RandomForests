/************************************************************************************/
/*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/31/2011                                                     **/
/***********************************************************************************/

#include"decision_tree.h"
#include"utility.h"


void DecisionTree::set_root_(Node* root){
	this->root_=root;
}

Node* DecisionTree::get_root_(){
	return this->root_;
}

Node* DecisionTree::GenerateDecisionTreeByC4_5(TrainingSet* training_set,vector<int> training_set_index,vector<int> attribute_list){
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	int target_attribute = training_set->GetClassifyAttribute();
	if(training_set_index.size()==0){
		cout<<"error in decision_tree.cpp function GenerateTreeByC4_5:training set is empty"<<endl;
		exit(1);
	}else if(training_set->IsTrainingSetSameClass(training_set_index)){
		LeafNode* leaf_node=new LeafNode();
		//int class_index=training_set->At(training_set_index.at(0)).GetClass(training_set->GetClassifyAttribute());
		//int class_index = value_matrix[training_set_index.at(0)][target_attribute].discrete_value_;
        int class_index = value_matrix[target_attribute][training_set_index.at(0)].discrete_value_;
		leaf_node->set_class_(class_index);
		leaf_node->set_case_num_(training_set_index.size());
		return leaf_node;
	}else if(attribute_list.size()==0){
		int majority_class=training_set->GetTheMostClass(training_set_index);
		LeafNode* leaf_node=new LeafNode();
		leaf_node->set_class_(majority_class);
		leaf_node->set_case_num_(training_set_index.size());
		return leaf_node;
	}else {
		C4_5AttributeSelectionMethod method(training_set,training_set_index,attribute_list);
		method.ExecuteSelection();
		if(!method.get_status_()){
			int majority_class=training_set->GetTheMostClass(training_set_index);
		    LeafNode* leaf_node=new LeafNode();
		    leaf_node->set_class_(majority_class);
		    leaf_node->set_case_num_(training_set_index.size());
			return leaf_node;
		}else{
			AttributeSelectionResult result=method.GetSelectionResult();
			InternalNode* internal_node=new InternalNode();
			int attribute=result.attribute_;
			map<int,vector<int> > mapper_split_result=result.splited_training_set;
			internal_node->set_attribute_(attribute);
			internal_node->set_case_num_(training_set_index.size()); // added for result file
			if(training_set->GetAttributeType(attribute)==DISCRETE){
				training_set->DeleteOneAttribute(attribute_list,attribute);
				map<int,vector<int> >::iterator iter;
				for(iter=mapper_split_result.begin();iter!=mapper_split_result.end();++iter){
					if(iter->second.size()==0){  // maybe this if branch can be deleted
						LeafNode *leaf_node=new LeafNode();
						leaf_node->set_class_(training_set->GetTheMostClass(training_set_index));
						leaf_node->set_case_num_(0);
						internal_node->set_child_node_(iter->first,leaf_node);
				    }else{
						internal_node->set_child_node_(iter->first,GenerateDecisionTreeByC4_5(training_set,iter->second,attribute_list));
				    }
				}
				return internal_node;
			}
			else{
				map<int,vector<int> >::iterator iter;
				for(iter=mapper_split_result.begin();iter!=mapper_split_result.end();++iter){
					internal_node->set_split_value(result.split_value_);
					internal_node->set_case_num_(iter->second.size());
					internal_node->set_child_node_(iter->first,GenerateDecisionTreeByC4_5(training_set,iter->second,attribute_list));
				}
				return internal_node;
			
			}
       }
	}
}

void PrintSpace(int indent){
	int i=0;
	while( i < indent ){
		i++;
		cout << "---";
	}
}

void DecisionTree::TraverseTree(ofstream& f,TrainingSet* training_set,Node* decision_tree){
	if(decision_tree->GetNodeType()==LEAFNODE){
		int target_attribute = training_set->GetClassifyAttribute();
		int class_index = ((LeafNode*)(decision_tree))->get_class_();
		f << "LeafNode {\n\t" << "Class = " << "\"" << training_set->GetAttributeValueName(target_attribute,class_index) <<
		  "\"\n\t" << "ID = \"" << decision_tree->get_id_() << "\"\n\t" << "NumberOfCase = \"" << decision_tree->get_case_num_() << "\"\n}\n";
	}else{
		int attribute=((InternalNode*)(decision_tree))->get_attribute_();
		map<int,Node*> mapper=((InternalNode*)(decision_tree))->get_all_child_nodes_();
		for(map<int,Node*>::iterator iter=mapper.begin();iter!=mapper.end();++iter){
			if(training_set->GetAttributeType(attribute)==CONTINUOUS){
				f << "InternalNode {\n\t" << "name = " << "\"" << training_set->GetAttributeName(attribute) << "\"\n\t" << "Type = \"Continuous\"" <<
				"\n\t" << "ID = \"" << decision_tree->get_id_() << "\"\n\t" << "NumberOfCase = \"" << decision_tree->get_case_num_() << "\"\n}\n";

				if(iter->first == 0){
					f << "Edge {\n\t" << "HeadID = " << "\"" << decision_tree->get_id_() << "\"\n\t" << "TailID =\"" << iter->second->get_id_() <<
					"\"\n\t" << "AttributeValue = \"" << training_set->GetAttributeName(attribute) <<" LE" << ((InternalNode*)decision_tree)->get_split_value()
				    << "\"\n\t"  << "NumberOfCase = \"" << iter->second->get_case_num_() << "\"\n}\n";
				}
				else{
					f << "Edge {\n\t" << "HeadID = " << "\"" << decision_tree->get_id_() << "\"\n\t" << "TailID =\"" << iter->second->get_id_() <<
					"\"\n\t" << "AttributeValue = \"" << training_set->GetAttributeName(attribute) <<" GT" << ((InternalNode*)decision_tree)->get_split_value()
					 << "\"\n\t"  << "NumberOfCase = \"" << iter->second->get_case_num_() << "\"\n}\n";
				}

			}else{
				f << "InternalNode {\n\t" << "name = " << "\"" << training_set->GetAttributeName(attribute) << "\"\n\t" << "Type = \"Discrete\"" <<
				"\n\t" << "ValueNum = \"" <<  training_set->GetAttributeValueNum(attribute) <<"ID = \"" << decision_tree->get_id_() << "\"\n\t" << "NumberOfCase = \"" << decision_tree->get_case_num_() << "\"\n}\n";

				f << "Edge {\n\t" << "HeadID = " << "\"" << decision_tree->get_id_() << "\"\n\t" << "TailID =\"" << iter->second->get_id_() <<
				"\"\n\t" << "AttributeValue = \"" <<  training_set->GetAttributeValueName(attribute,iter->first)
				 << "\"\n\t"  << "NumberOfCase = \"" << iter->second->get_case_num_() << "\"\n}\n";
			}
			TraverseTree(f,training_set,iter->second);
		}
	}
}

Node* DecisionTree::PredictClass(TrainingSet* training_set,int index, Node* node){
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	if(node->GetNodeType()==LEAFNODE){
		return node;
	}
	if(node->GetNodeType()==INTERNALNODE){
		InternalNode* internal_node=(InternalNode*)node;
		int attribute=internal_node->get_attribute_();
		if(training_set->GetAttributeType(attribute)==DISCRETE){                  
			return PredictClass(training_set,index,internal_node->get_child_node_(value_matrix[attribute][index].discrete_value_));
		}else{
			//double value=training_set->At(index).At(attribute).get_continuous_value();
			double value = value_matrix[attribute][index].continuous_value_;
			if(value<=internal_node->get_split_value()){
				return PredictClass(training_set,index,internal_node->get_child_node_(0));
			}else{
				return PredictClass(training_set,index,internal_node->get_child_node_(1));
			}
		}
	}
}

double DecisionTree::GetErrorRate(TrainingSet* training_set,vector<int> training_set_index){
	vector<int>::iterator iter;
	int error=0;
	Node* leaf_node;
	AttributeValue** value_matrix = training_set->GetValueMatrixP();
	int target_attribute = training_set->GetClassifyAttribute();
	for(iter=training_set_index.begin();iter!=training_set_index.end();++iter){
		leaf_node=this->PredictClass(training_set,*iter,this->get_root_());
		if(((LeafNode*)leaf_node)->get_class_() == value_matrix[target_attribute][*iter].discrete_value_){
		}
		else{
			error++;
		}
		
	}
	double error_rate=((double)error)/((double)(training_set_index.size()));
	return error_rate;
}

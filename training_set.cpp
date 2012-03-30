///************************************************************************************/
///*      copyright 2011 HPDM,SIAT,Shenzhen,China                                   **/
///*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
///*      created in 12/30/2011                                                     **/
/************************************************************************************/
#include"training_set.h"


void TrainingSet::set_attribute_value_mapper(AttributeValueMapper attribute_value_mapper){
	this->attribute_value_mapper_=attribute_value_mapper;
}

int TrainingSet::get_training_set_num_(){
	return this->training_set_num_;
}

void TrainingSet::ProduceTrainingSetMatrix(DataFileReader data_file_reader){
	this->training_set_num_=data_file_reader.GetTupleNum();
	vector<vector<string> > data=data_file_reader.GetFileContent();
	int attribute_num=this->attribute_value_mapper_.GetAttributeNum();
	this->value_matrix_ = (AttributeValue**)malloc(sizeof(AttributeValue*)*attribute_num);
	int index;
	for(index = 0;index < attribute_num;++ index){
		this->value_matrix_[index]=(AttributeValue*)malloc(sizeof(AttributeValue)*this->training_set_num_);
	}
	int i = 0;
	int line = 1;
	for(vector<vector<string> >::iterator iter=data.begin();iter!=data.end();++iter){
		vector<string> temp_str_vector;
		temp_str_vector=*iter;
		if( temp_str_vector.size() == attribute_num ){
			int j;
			for(j = 0;j < attribute_num;++ j){
				if(this->attribute_value_mapper_.GetAttributeType(j) == CONTINUOUS){
					double continuous_value;
					stringstream ss;
					ss<<temp_str_vector.at(j);
					ss>>continuous_value;
					this->value_matrix_[j][i].continuous_value_= continuous_value;
				}else{
					map<string,int>::iterator it;
					if( this->attribute_value_mapper_.GetMapperValue(j,temp_str_vector.at(j),it) )
					{
						this->value_matrix_[j][i].discrete_value_ = it->second;
					}else{
						cout << " a error in data file: line " << line << endl;

					}
				}
			}
			i++;
		}else{
			cout << "a error in data file:line " << line << endl;
			cout << "the program exit !" << endl;
			exit(1);
		}
		line ++;

	}
    /*int i;
	for( i = 0 ; i < attribute_num ; i ++ ){
		AttributeValue* one_tuple = (AttributeValue*)malloc(sizeof(AttributeValue)*this->training_set_num_);
        if(this->attribute_value_mapper_.GetAttributeType(i)==DISCRETE){
			int j = 0;
			for(vector<vector<string> >::iterator iter=data.begin();iter!=data.end();++iter){
				vector<string> temp_str_vector;
				temp_str_vector=*iter;
				int discrete_value;
				discrete_value=this->attribute_value_mapper_.GetMapperValue(i,temp_str_vector.at(i));
				one_tuple[j].discrete_value_ = discrete_value;
				j ++ ;
		    }
		}else{
			int j = 0;
			for(vector<vector<string> >::iterator iter=data.begin();iter!=data.end();++iter){
				vector<string> temp_str_vector;
				temp_str_vector=*iter;	
				double continuous_value;
				stringstream ss;
				ss<<temp_str_vector.at(i);
				ss> >continuous_value;
				one_tuple[j].continuous_value_= continuous_value;
				j ++ ;
		    }
		}
		this->value_matrix_[i] = one_tuple;
	}*/

	/*********��ɢ����ֵ����,����ֵ��stringתdouble,****** end ******/
}

//void TrainingSet::ProduceTrainingSet(DataFileReader data_file_reader){
//	this->training_set_num_=data_file_reader.GetTupleNum();
//    /*********��ɢ����ֵ����,����ֵ��stringתdouble,***********begin   */
//	vector<vector<string> > data=data_file_reader.GetFileContent();
//	int attribute_num=this->attribute_value_mapper_.GetAttributeNum();
//	for(vector<vector<string> >::iterator iter=data.begin();iter!=data.end();++iter){
//		vector<string> temp_str_vector;
//		temp_str_vector=*iter;
//		vector<Attribute> temp_attribute_vector;
//		for(int i=0;i<attribute_num;++i){
//			Attribute temp_attribute;
//			if(this->attribute_value_mapper_.GetAttributeType(i)==DISCRETE){
//				int discrete_value;
//				discrete_value=this->attribute_value_mapper_.GetMapperValue(i,temp_str_vector.at(i));
//				temp_attribute.set_discrete_value(discrete_value);
//				temp_attribute_vector.push_back(temp_attribute);
//			}
//			else{
//				double continuous_value;
//				stringstream ss;
//				ss<<temp_str_vector.at(i);
//				ss> >continuous_value;
//				temp_attribute.set_continuous_value(continuous_value);
//				temp_attribute_vector.push_back(temp_attribute);
//			}
//		}
//		Tuple tuple(temp_attribute_vector);
//		this->training_set_.push_back(tuple);
//	}
//	/*********��ɢ����ֵ����,����ֵ��stringתdouble,****** end ******/
//}


//Tuple TrainingSet::At(int pos){
//	return this->training_set_.at(pos);
//}

int TrainingSet::GetClassifyAttribute(){
	return this->attribute_value_mapper_.GetClassifyAttribute();
}

AttributeType TrainingSet::GetAttributeType(int attribute){
	return this->attribute_value_mapper_.GetAttributeType(attribute);
}

//int TrainingSet::GetTupleClass(int tuple){
//	return this->training_set_.at(tuple).GetClass(this->GetClassifyAttribute());
//}

int TrainingSet::GetAttributeNum(){
	return this->attribute_value_mapper_.GetAttributeNum();
}

vector<int> TrainingSet::GetNormalAttributes(){
	vector<int> normal_attributes;
    int i;
	int attribute_num=this->GetAttributeNum();
	int classify_attribute=this->GetClassifyAttribute();
	for(i=0;i<attribute_num;++i){
		if(i==classify_attribute){
			continue;
		}
		else{
			normal_attributes.push_back(i);
		}
	}
	return normal_attributes;
}


//void TrainingSet::test(){
//	int a=this->training_set_num_;
//	int b=this->attribute_value_mapper_.GetAttributeNum();
//	for(int i=0;i<a;++i){
//		Tuple tuple=this->training_set_.at(i);
//		for(int j=0;j<b;++j){
//			if(this->attribute_value_mapper_.GetAttributeType(j)==DISCRETE){
//				cout<<tuple.At(j).get_discrete_value()<<" ";
//			}else{
//				cout<<tuple.At(j).get_continuous_value()<<" ";
//			}
//			
//		}
//		cout<<endl;
//	}
//	cout<<"classify attribute:"<<this->GetClassifyAttribute()<<endl;
//	//cout<<"attribute type:"<<this->GetAttributeType(0)<<endl;
//	//cout<<"tuple class:"<<this->GetTupleClass(1)<<endl;
//	cout<<"attribute num:"<<this->GetAttributeNum()<<endl;
//	cout<<"normal attribute list:"<<this->GetNormalAttributes().size();
//
//}


int TrainingSet::GetAttributeValueNum(int attribute){
	return this->attribute_value_mapper_.GetAttributeValueNum(attribute);
}

//������ѵ�����в����ڷ���
map<int,double> TrainingSet::GetClassDistribution(vector<int> training_set_index){
	int classify_attribute=this->GetClassifyAttribute();
	int training_set_num=training_set_index.size();
	map<int,int> mapper;
	int i;
	int class_index;
	for(i=0;i<training_set_num;i++){
		//class_index=this->training_set_.at(training_set_index.at(i)).GetClass(classify_attribute);
		class_index = this->value_matrix_[classify_attribute][training_set_index.at(i)].discrete_value_;
		if(mapper.find(class_index)==mapper.end())
		{
			mapper.insert(map<int,int>::value_type(class_index,1));
		}
		else
		{
			mapper[class_index]++;
		}
	}
	map<int,double> result;
	for(map<int,int>::iterator iter=mapper.begin();iter!=mapper.end();++iter){
		result.insert(map<int,double>::value_type(iter->first,(double)iter->second/(double)training_set_num));
	}
	return result;
}


int TrainingSet::GetTheMostClass(vector<int> training_set_index){
	int classify_attribute=this->GetClassifyAttribute();
	int training_set_num=training_set_index.size();
	map<int,int> mapper;
	int i;
	int class_index;
	for(i=0;i<training_set_num;i++){
		//class_index=this->training_set_.at(training_set_index.at(i)).GetClass(classify_attribute);
		class_index = this->value_matrix_[classify_attribute][training_set_index.at(i)].discrete_value_;
		if(mapper.find(class_index)==mapper.end())
		{
			mapper.insert(map<int,int>::value_type(class_index,1));
		}
		else
		{
			mapper[class_index]++;
		}
	}
	map<int,int>::iterator iter;
	int temp_num=0;
	int result;
	for(iter=mapper.begin();iter!=mapper.end();++iter){
		if(iter->second>temp_num){
			temp_num=iter->second;
			result=iter->first;
		}
	}
	return result;
}

bool TrainingSet::IsTrainingSetSameClass(vector<int> training_set_index){
	int training_set_num=training_set_index.size();
	if(training_set_num==0){
		cout<<"error in training_set.cpp function: IsTrainingSetSameClass"<<endl;
		exit(1);
	}
	else if( training_set_num==1){
		return true;
	}
	else{
		int target_attribute = this->GetClassifyAttribute();
		int i=0;
		//int class_one=this->training_set_.at(training_set_index.at(i)).GetClass(this->GetClassifyAttribute());
		int class_one = this->value_matrix_[target_attribute][training_set_index.at(i)].discrete_value_;
		i++;
		while(i<training_set_num){
			if(class_one != this->value_matrix_[target_attribute][training_set_index.at(i)].discrete_value_){
				return false;
			}
			i++;
		}
		return true;

	}
}

//
//ItemType TrainingSet::GetItemType(int pos){
//	return this->item_type_.at(pos);
//}

/***������Ե�ĳֵ�ڸ�ѵ������û�г��֣���ӳ��Ϊһ����vector<int>,���������ʱ����õ�*/
map<int,vector<int> > TrainingSet::SplitByDiscreteAttribute(vector<int>training_set_index,int attribute){
	vector<int> temp_vec;
	map<int,vector<int> > result;
	int i;
	for(i=0;i<this->GetAttributeValueNum(attribute);++i){
		result.insert(map<int,vector<int> >::value_type(i,temp_vec));
	}
	int training_set_num=training_set_index.size();
	for(i=0;i<training_set_num;++i){
		int attribute_value=this->value_matrix_[attribute][training_set_index.at(i)].discrete_value_;
        result[attribute_value].push_back(training_set_index.at(i));
	}
	return result;

}


map<int,vector<int> > TrainingSet::SplitByPositon(vector<int>training_set_index,int pos){
	int training_set_num=training_set_index.size();
	map<int ,vector<int> > mapper;
	if(pos<0||pos>=training_set_num){
		cout<<"wrong in training_set.cpp:line 220"<<endl;
		exit(1);
	}
	else{
		vector<int> vec;
		int i;
		for(i=0;i<=pos;++i){
			vec.push_back(training_set_index.at(i));
		}
		mapper.insert(map<int,vector<int> >::value_type(0,vec));
		vec.clear();
		for(i=pos+1;i<training_set_num;++i){
			vec.push_back(training_set_index.at(i));
		}
		mapper.insert(map<int,vector<int> >::value_type(1,vec));
	}
	return mapper;
}

void TrainingSet::DeleteOneAttribute(vector<int>& attribute_list,int attribute){
	vector<int>::iterator iter;
	for(iter=attribute_list.begin();iter!=attribute_list.end();++iter){
		if((*iter)==attribute){
			attribute_list.erase(iter);
			break;
		}
	}
	/******debug*****/
	//cout<<"attribute list:"<<endl;
	//for(iter=attribute_list.begin();iter!=attribute_list.end();++iter){
	//		cout<<*iter<<" ";
	//}
	//cout<<endl;
	/******debug*****/
}

string TrainingSet::GetAttributeName(int attribute){
	return this->attribute_value_mapper_.GetAttributeName(attribute);
}

string TrainingSet::GetAttributeValueName(int attribute,int index){
	return this->attribute_value_mapper_.GetAttributeValueName(attribute,index);
}


vector<int> TrainingSet::GetClassesNum(vector<int> training_set_index){
	int classify_attribute=this->GetClassifyAttribute();
	int training_set_num=training_set_index.size();
	int class_num=this->GetAttributeValueNum(classify_attribute);
//	map<int,int> mapper;
	vector<int>	 mapper;
	int i;
	for(i=0;i<class_num;++i){
		mapper.push_back(0);
	}
	int class_index;
	for(i=0;i<training_set_num;i++){
		//class_index=this->training_set_.at(training_set_index.at(i)).GetClass(classify_attribute);
		class_index = this->value_matrix_[classify_attribute][training_set_index.at(i)].discrete_value_;
		mapper.at(class_index)++;
	}
	return mapper;
}


void TrainingSet::TestMatrix(){
	int attribute_num = this->GetAttributeNum();
	int training_set_num = this->get_training_set_num_();
	int i,j;
	for(i = 0;i < attribute_num;++ i){
		if(this->GetAttributeType(i) == CONTINUOUS){
			for(j = 0;j < training_set_num;++ j){
				cout << this->value_matrix_[i][j].continuous_value_ << " ";
			}
		}else{
			for(j = 0;j < training_set_num;++ j){
				cout << this->value_matrix_[i][j].discrete_value_ << " ";
			}
		}
		cout << endl;
	}
	
}


AttributeValue** TrainingSet::GetValueMatrixP(){
	return this->value_matrix_;
	
}


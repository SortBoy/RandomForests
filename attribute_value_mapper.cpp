/************************************************************************************/
/*      copyright 2012 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/8/2012                                                    **/
/***********************************************************************************/

/*attribute_value_mapper.cpp
  AttributeValueMapper���ʵ��*/

#include"attribute_value_mapper.h"


AttributeValueMapper::AttributeValueMapper(){
}

AttributeValueMapper::AttributeValueMapper(string file_path){
	this->file_path=file_path;
}

void AttributeValueMapper::DeleteSymbol(string& str){
	int i;
    string temp_str="";
	for(i = 0;i < str.length();++ i){
		if(str[i] != ' ' && str [i] != '.' && str[i] != '\'' && str[i] != '\t' && str[i] != '\r'){
           temp_str += str[i];
		}
	}
	str.clear();
	str = temp_str;
}

void AttributeValueMapper::DeleteComment(string& str){
	size_t pos = str.find('|');
	if(string::npos == pos){
		return;
	}else{
		str= str.substr(0,pos);
	}

}

StatusCode AttributeValueMapper::MapAttributeValue(){

    bool is_class_set = false;
	int line = 0;

	int attribute_num=0;
	if(this->file_path.empty()){
        cout << "the names file does't exist" << endl;
		return FAIL;
	}

	ifstream reader;
	reader.open(this->file_path.c_str(),ios_base::in);

	if(!reader.is_open()){
		cout << this->file_path << " does't exist " <<endl;
		return FAIL;
	}

	char temp_str[1000];
	string target_attribute;
	vector<string> temp_str_vec;
	
	while(reader.getline(temp_str,1000)){
		line ++ ;
		string str=temp_str;
		this->DeleteComment(str);
		this->DeleteSymbol(str);
		//cout << str << endl;
		if(str.empty()){
			continue;
		}

		if(!is_class_set){
			target_attribute = str ;
			is_class_set = true;
			continue;

		}
		else{
			this->split(str,':',temp_str_vec);
			if(temp_str_vec.size()!=2){
				cout<<"wrong in line " << line <<endl;
				return FAIL;
			}else{
				if(temp_str_vec.at(0).size() == 0 && temp_str_vec.at(1).size() == 0){
					cout << "wrong in line " << line << endl;
					return FAIL;
				}
			}
	        
	        
			/*if(temp_str_vec.at(0)=="CLASSIFY_ATTRIBUTE"){
				this->classify_attribute_=this->attribute_name_mapper_[temp_str_vec.at(1)];
				temp_str_vec.clear();
				break;*/

			if(temp_str_vec.at(1)=="continuous"){
				this->attribute_name_mapper_.insert(map<string,int>::value_type(temp_str_vec.at(0),attribute_num));
				this->attribute_type_.push_back(CONTINUOUS);
				temp_str_vec.clear();
				attribute_num++;
				continue;
				
			}else {
				this->attribute_name_mapper_.insert(map<string,int>::value_type(temp_str_vec.at(0),attribute_num));
				this->attribute_type_.push_back(DISCRETE);
				vector<string> temp_str_vec2;
				this->split(temp_str_vec.at(1),',',temp_str_vec2);
				int i=0;
				map<string,int> temp_map;
				for(i;i<temp_str_vec2.size();++i){
					temp_map.insert(map<string,int>::value_type(temp_str_vec2.at(i),i));	
				}
				this->attribute_value_mapper_.insert(map<int,map<string,int> >::value_type(attribute_num,temp_map));
				temp_str_vec.clear();
				attribute_num++;
				continue;
				
			}
		}
		

	}

    vector<string> temp_str_vec2;
	this->split(target_attribute,',',temp_str_vec2);
	int i=0;
	map<string,int> temp_map;
	for(i;i<temp_str_vec2.size();++i){
		temp_map.insert(map<string,int>::value_type(temp_str_vec2.at(i),i));	
	}
	this->attribute_value_mapper_.insert(map<int,map<string,int> >::value_type(attribute_num,temp_map));
	this->attribute_type_.push_back(DISCRETE);
	this->attribute_name_mapper_.insert(map<string,int>::value_type("target_attribute",attribute_num));
	this->classify_attribute_=attribute_num;

	this->attribute_num_=attribute_num+1;
	return SUCCESS;

}


StatusCode AttributeValueMapper::split(const string &str,char delim,vector<string> &strVec){
	string tempWord;
	stringstream tempSS(str);
	while(getline(tempSS,tempWord,delim)){
		strVec.push_back(tempWord);
	}
	return SUCCESS;

}


bool AttributeValueMapper::HaveASpace(const string& str){

	for(int i=0;i<str.size();++i){
		if(str.at(i)==' '){
			cout<<"error:the line can't have a space!";
			return true;
	    }
	}

	return false;
}

int AttributeValueMapper::GetAttributeNum(){
	return this->attribute_num_;
}

AttributeType AttributeValueMapper::GetAttributeType(int attribute){
	return this->attribute_type_.at(attribute);
}

//int AttributeValueMapper::GetMapperValue(int attribute,string value){
//	return this->attribute_value_mapper_[attribute][value];
//}
bool AttributeValueMapper::GetMapperValue(int attribute, string value, map<string,int>::iterator &it){
	it = this->attribute_value_mapper_[attribute].find(value);
	if (it == this->attribute_value_mapper_[attribute].end() ){
		return false;
	}else{
		return true;
	}
}

int AttributeValueMapper::GetClassifyAttribute(){
	return this->classify_attribute_;
}

int AttributeValueMapper::GetAttributeValueNum(int attribute){
	return this->attribute_value_mapper_[attribute].size();
}

string AttributeValueMapper::GetAttributeName(int attribute){
	if(attribute>=this->GetAttributeNum()){
		cout<<"error in attribute_value_mapper.cpp in function GetAttributeName()"<<endl;
		std::exit(1);
	}
	map<string,int>::iterator iter=this->attribute_name_mapper_.begin();
	while(iter->second!=attribute){
		iter++;
	}
	return iter->first;
}

string AttributeValueMapper::GetAttributeValueName(int attribute,int index){
	if((attribute>=this->GetAttributeNum())||(index>=this->GetAttributeValueNum(attribute))){
		cout<<"error in attribute_value_mapper.cpp in function GetAttributeValueName()"<<endl;
		exit(1);
	}
	map<string,int> mapper=this->attribute_value_mapper_[attribute];
	map<string,int>::iterator iter=mapper.begin();
	while(iter->second!=index){
		iter++;
	}
	return iter->first;
}


void AttributeValueMapper::test(){
	cout<<"attribute number:"<<this->attribute_num_<<endl;
	cout<<"attribute name mapper:";
	for(map<string,int>::iterator p=this->attribute_name_mapper_.begin();p!=this->attribute_name_mapper_.end();++p){
		cout<<"<"<<p->first<<","<<p->second<<">";
	}
	cout<<endl;
	int i;

    cout << "-----------------------------------------------" << endl;
	for(i=0;i<this->attribute_num_;++i){
		cout<<i<<":";
		for(map<string,int>::iterator p=this->attribute_value_mapper_[i].begin();p!=this->attribute_value_mapper_[i].end();++p){
			cout<<"<"<<p->first<<","<<p->second<<">";
		}
		cout<<endl;		
	}

	cout<<"classify_attribute:"<<this->classify_attribute_<<endl;

	int j=0;
	cout<<"type:";
	for(j;j<this->attribute_num_;++j){
		cout<<this->attribute_type_.at(j)<<" ";
	}
}

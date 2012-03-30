/************************************************************************************/
/*      copyright 2011 by HPDM,SIAT,Shenzhen,China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/27/2011                                                     **/
/***********************************************************************************/

/*data_file_reader.cpp
   DataFileReader���ʵ��*/

#include"data_file_reader.h"


using namespace std;

DataFileReader::DataFileReader(){
}

DataFileReader::DataFileReader(string filePath,char delim){
	this->filePath=filePath;
	this->delim=delim;
}

StatusCode DataFileReader::setDelim(char delim){
	if(!delim){
		return FAIL;
	}
	this->delim=delim;
	return SUCCESS;
}

StatusCode DataFileReader::setFilePath(string filePath){
	if(filePath.empty())
		return FAIL;
	this->filePath=filePath;
	return SUCCESS;
}

StatusCode DataFileReader::read(){
	if(this->filePath.empty()){
		return FAIL; 
	}
	ifstream reader;
	reader.open(this->filePath.c_str(),ios_base::in);
	if(!reader.is_open()){
		return FAIL;
	}
	
	char tempCharArr[100000];
	vector<string> tempStrVec;
	
	while(reader.getline(tempCharArr,100000)){
		string tempStr=tempCharArr;
		split(tempStr,this->delim,tempStrVec);
		this->fileContent.push_back(tempStrVec);
		tempStrVec.clear();         
	}
	reader.close();
	return SUCCESS;    
}

vector<vector<string> > DataFileReader::GetFileContent(){
	return this->fileContent;
}


StatusCode DataFileReader::split(const string &str,char delim,vector<string> &strVec){
	string tempWord;
	stringstream tempSS(str);
	while(getline(tempSS,tempWord,delim)){
		strVec.push_back(tempWord);
	}
	return SUCCESS;

}

int DataFileReader::GetTupleNum(){
	return this->fileContent.size();
}

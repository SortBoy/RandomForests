/************************************************************************************/
/*      copyright 2012 HPDM,SIAT,Shenzhen,China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 2/8/2012                                                    **/
/***********************************************************************************/

/*attribute_value_mapper.h
   AttributeValueMapper��Ҫ��ȡһ���ļ���Ϣ������ļ���Ϣ�������Ե�����
   ���Ե����ͣ������ͣ���ɢ�ͣ�����ɢ�����Եĸ�������ֵ��*/

#ifndef ATTRIBUTE_VALUE_MAPPER_H_
#define ATTRIBUTE_VALUE_MAPPER_H_

#include"utility.h"
#include<cstdio>
#include<cstdlib>
#include<map>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

class AttributeValueMapper{
private:
	string file_path;
	int attribute_num_;
	vector<AttributeType> attribute_type_;//�������Ե�����
	map<string,int> attribute_name_mapper_;//������������֮���ӳ�䣬��0��ʼ
	map<int,map<string,int> > attribute_value_mapper_;//int������ԣ�map<string,int>��������ɢ����������ֵ������֮���ӳ��
	int classify_attribute_;//���������Ŀ������
public:
	AttributeValueMapper();
	AttributeValueMapper(string file_path);
	StatusCode split(const string &str,char delim,vector<string> &strVec);
	bool HaveASpace(const string& str);
	int GetAttributeNum();
	AttributeType GetAttributeType(int attribute);
	//int GetMapperValue(int attribute ,string value);
	bool GetMapperValue(int attribute, string value,map<string,int>::iterator &it);
	//map<string,int> GetAttributeMapper(int attribute);
	int GetClassifyAttribute();
	int GetAttributeValueNum(int attribute);
	string GetAttributeName(int attribute);//������Ե�����
	string GetAttributeValueName(int attribute,int index);//�����ɢ����ֵ������
	/*�������������ô˷���������ɢֵ�ı���*/
	StatusCode MapAttributeValue();
    void DeleteComment(string& str);
	void DeleteSymbol(string& str);
	void test();
};
#endif

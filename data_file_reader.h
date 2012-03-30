/************************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/27/2011                                                     **/
/***********************************************************************************/

/*ѵ����Դ���ݶ�ȡ��
   һ�����ݷ���һ��vector<string>�У��������ݷ���vector<vector<string> >��*/

#ifndef DATA_FILE_READER_H_
#define DATA_FILE_READER_H_

#include<string>
#include<vector>
#include"utility.h"
#include<fstream>
#include<sstream>
using namespace std;

class DataFileReader{
private:
	string filePath;
	/*vector<vector<string> > fileContent
	  the file content is stored in a  two dimension matrix,one vector<string> 
	  object is one line.
    */
	vector<vector<string> > fileContent;
	char delim;//�ָ���
public:
	DataFileReader();
	DataFileReader(string filePath,char delim=' ');
	StatusCode setFilePath(string filePath);
	StatusCode setDelim(char delim);
    StatusCode read(); 
	vector<vector<string> > GetFileContent();
	StatusCode split(const string&,char,vector<string>&);
	int GetTupleNum();

};


#endif

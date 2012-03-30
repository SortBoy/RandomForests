/************************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:simba qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/27/2011                                                     **/
/***********************************************************************************/

/*训练集源数据读取类
   一行数据放在一个vector<string>中，整个数据放在vector<vector<string> >中*/

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
	char delim;//分隔符
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

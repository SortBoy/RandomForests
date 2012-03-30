/************************************************************************************/
/*      copyright 2011 HPDM SIAT Shenzhen China                                   **/
/*      author:alex qinghan meng  email:phoenix.mqh@gmail.com                     **/
/*      created in 12/28/2011                                                     **/
/***********************************************************************************/

/*the declaration in the file is used as the utility of the project                */

#ifndef UTILITY_H_
#define UTILITY_H_
#include<vector>
#include<string>
#include<map>
//#include"training_set.h"

using namespace std;
/* enum StatusCode usually is used as the function return value type*/
enum StatusCode {SUCCESS,FAIL};

/*the union is used as the the item's attribute of the training sets,the arribute is
  a dsicrete value or a continuous value*/

//typedef  TrainingSet xxx;

//typedef vector<string> line;



enum ItemType{DISCRETE,CONTINUOUS};
typedef ItemType AttributeType;

enum NodeType{INTERNALNODE,LEAFNODE,UNKNOWN};


typedef struct item_struct{
	union item_value{
		 short discrete_value_;  
         double continuous_value_;
	} value_; 
	ItemType type_;
}Item;

typedef vector<vector<string> > StringMatrix;

typedef union attribute_value {
		int discrete_value_;
		double continuous_value_;
}AttributeValue;

typedef struct attribute_selection_result{
	//AttributeType attribute_type_; // modified in 2/15/2012,TrainingSet�����п��Եõ�����
	int attribute_;
	double split_value_;
	map<int,vector<int> > splited_training_set;
} AttributeSelectionResult;

typedef struct index_value {
		int index_;
		double value_;
} IndexValue;

typedef struct index_class {
	int index_;
	int class_;
} IndexClass;



//typedef union attribute_value {
//	int d_value_;
//	double c_value_;
//} AttributeValue;







#endif

#include<iostream>
#include"GradeBook.h"
using namespace std;

int main(){
	
	GradeBook gradeBook1("CS101 Introduction to C++ Programming");
	GradeBook gradeBook2("CS102 Date Structures in C++");
	
	cout<<"GradeBook1 created for course: "<<gradeBook1.getCourseName()
		<<"\nGradeBook2 created for course: "<<gradeBook2.getCourseName()
		<<endl;
	
return 0;                   
} 	

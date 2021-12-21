// student grading system.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<algorithm>
#include<vector>
#include<iomanip>
#include<iostream>
#include<string>
#include<numeric>
#include<cstddef>
#include<memory>
#include<iterator>
#include<fstream>
using namespace std;

template<class T>
class Vec{
public:
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;

	//constructors
	Vec(){create();}
	explicit Vec(size_type s, const T& val){create(s, val);}

	~Vec(){uncreate();}//destructor
	//overloaded operator [] for indexing of objects of class vec
	T& operator[](size_type i){return data[i];}                //for both read and write access
	const T& operator[](size_type i) const { return data[i];}  // for only read access

	//overloaded assignment operator = 
	Vec& operator=(const Vec& rhs);

	//functions returning iterators begin and end of vector
	iterator begin(){return data;}
	const_iterator begin() const {return data;}

	iterator last_entry(){return avail;}
	const_iterator last_entry() const {return avail;}

	iterator end(){return limit;}
	const_iterator end() const {return limit;} 

	//function returning size of vector
	size_type size(){ return limit - data;}

	//push_back function
	void push_back(const T& val){
		if(avail == limit)
			grow();
		unchecked_append(val);
	}
	//erase funcion ; removes one element
	void erase(iterator pos){
		iterator temp = data;
		size_type s = limit -data;
		iterator new_data= alloc.allocate(s);
		iterator new_temp = temp;
		iterator new_avail;
		while(temp!=avail){
			if(temp == pos){
				new_temp = uninitialized_copy(data, temp , new_data);	
				new_avail = uninitialized_copy(temp+1, avail , new_temp);
				data = new_data;
				avail = new_avail;
				limit = new_data + s -1;
				return;
			}
			temp++;
		}
		cout<<"\nInputted iterator does not exist\n";
	};
	//erase function functionality 2.0 when range is specified instead of single iterator
	void erase(iterator b, iterator e){
		size_type s = limit - data;
		iterator new_data = alloc.allocate(s);
		iterator it = data;
		iterator temp;
		iterator new_avail;
		while(it!=avail){ 
			if(it == b && e <= avail){
				temp = uninitialized_copy(data, it , new_data);
				new_avail = uninitialized_copy(e+1 , avail , temp);
				data = new_data;
				avail = new_avail;
				limit = new_data + (s - (e-b)-1);
				return;
			}
			it++;
		}
	
	}
	//clear function that erases all values 
	void clear(){
		iterator it = data;
		while(it!= limit){
			*it = 0;
			it++;
		}
	}

	
private:
	iterator data ;
	iterator avail;
	iterator limit;

	allocator<T> alloc;

	void create();
	void create(size_type n, const T& val);
	void create(iterator i, iterator j);

	void uncreate();

	void grow();
	void unchecked_append(const T&);


};
template<class T>
void Vec<T>::create(){
	data = limit = avail = 0;
}

template<class T>
void Vec<T>::create(size_type s, const T& val){
	data = alloc.allocate(s);
	avail = data +s;
	limit = avail;
	uninitialized_fill(data, limit, val);
}

template<class T>
void Vec<T>::create(iterator i , iterator j){
	data = alloc.allocate(j-i);
	avail = limit = uninitialized_copy(i, j , data);
}

template<class T>
void Vec<T>::uncreate(){
	if(data){
		iterator it = avail;
		while(it != data){
			alloc.destroy(--it);
		}
	
	alloc.deallocate(data, limit -data);
	}
	data = avail = limit =0;
}

template<class T>
void Vec<T>::grow(){
	size_type new_size = 2* (limit -data);
	
	iterator new_data = alloc<T>.alloc(new_size);
	iterator new_limit = new_data + new_size;
	iterator new_avail = uninitialized_copy(data, limit, new_data);
	uncreate();

	data = new_data;
	limit = new_limit;
	avail = new_avail;
}

template<class T>
void Vec<T>::unchecked_append(const T& val){
	if(avail < limit){
		*avail++ = val; 
	}
}
 
template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs){
	if(this!=&rhs){
		uncreate();

		create(rhs.begin(), rhs.end());
	}
	return *this;
}

class Str {
public:
	typedef Vec<char>::size_type size_type;
	//initialization constructor
	Str();

	//
	Str(size_type s , const char ch):data(s, ch);

	Str(const char* ch){
		copy(ch, ch + strlen(ch), back_inserter(data));
	}

	template<class In> Str(In b , In e){
		copy(b,e,back_inserter(data));
	}


private:
	Vec<char> data;
};


double grade(double mid, double final, vector<double> homework);



class Student_infor{
public:
	istream& read(istream&);
	double grade() const { return ::grade(midterm, final, homework);};
	bool valid() const{ return !homework.empty();};
	const string name() const { return n;};
    Student_infor(): midterm(0), final(0){}
private:
	string n;
	double midterm , final;
	vector<double> homework;
};




bool compare(Student_infor& x, Student_infor& y){
	return x.name() < y.name();
}





struct Student_info{
	string name;
	double midterm, finals;
	vector<double> homework;
	double grade;
};
void grade(vector<Student_info>& student);
bool fgrade(struct Student_info x);
void enterStudentData(vector<Student_info>& student);
void printStudentDataAll(const vector<Student_info>& student);
void studentGrade();
void sortArrSpecial();
bool compare(struct Student_info& x, struct Student_info& y);
vector<Student_info> extract_failsIndex(vector<Student_info>& student);
vector<Student_info> extract_failsIterator(vector<Student_info>& student);
vector<Student_info> extract_failsPartition(vector<Student_info>& student);
bool didAllHW(const vector<Student_info>& s);
double average(const vector<double>& v);
//*************************************************************************************************************************
int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> u(10,100);

	Vec<int> ob(10,21);
	ob[5] = 16;
	ob[6] = 13;
	int *p = &ob[6];
	//ob.erase(p);
	//ob.clear();
	ob[8] = 69;
	int * x = &ob[8]; 
	ob.erase(p,x);
	Vec<int>::iterator it = ob.begin();
	while(it!= ob.end()){
		cout<<*it<<" ";
		it++;
	}

	ifstream file("student_grading system.cpp");
	cout<<file;
	//for(int i =0; i< 10; i++){
		//cout<<ob[i]<<" ";
	//}
	int *begin = ob.begin();
	cout<<"\n**"<<*begin;

/*
	
	double x;
	vector<double> test;
	while(cin>>x){
		test.push_back(x);
	}
	cout<<endl;
	double avg = average(test);
	cout<<avg;
	//vector<Student_info> student;
	//sortArrSpecial();
	//enterStudentData(student);
	//printStudentDataAll(student);
	*/
	return 0;
}

double average(const vector<double>& v){
	return (accumulate(v.begin(), v.end(),0.0)/v.size());
}
bool didAllHW(const Student_info& s){
	return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}
vector<Student_info> extract_failsIndex(vector<Student_info>& student){
	typedef vector<Student_info>::size_type vec_sz;
	vec_sz i =0;
	vector<Student_info> fail;
	while(i!=student.size()){
		if(fgrade(student[i])){
			fail.push_back(student[i]);
			student.erase(student.begin()+i);
		}
		else{
			i++;
		}
	}
	return fail;
}
vector<Student_info> extract_failsIterator(vector<Student_info>& student){
	vector<Student_info>::iterator iter=student.begin();
	vector<Student_info> fails;
	while(iter!=student.end()){
		if(fgrade(*iter)){
			fails.push_back(*iter);
			iter = student.erase(iter);
			
		}
		else{
			iter++;
		}
	}
	return fails;
}
/*
vector<Student_info> extract_failsPartition(vector<Student_info>& student){
	vector<Student_info>::iterator iter = stable_partition(student.begin(), student.end(), !fgrade);
	vector<Student_info> fails(iter, student.end());
	student.erase(iter, student.end());
	return fails;

}
*/
bool fgrade(struct Student_info x){
	return x.grade < 60;
}


bool compare(struct Student_info& x, struct Student_info& y){
	return x.name > y.name;
	
}

void grade(vector<Student_info>& student){
	typedef vector<Student_info>::size_type vec_sz;
	const vec_sz size = student.size();
	for(vec_sz i =0; i<size; i++){
		double sum =0;
		for(int j =0; j<5 ; j++){
			sum +=student[i].homework[j];
		}
		student[i].grade = 0.2*student[i].midterm + 0.4* student[i].finals + 0.4 * sum / 5;
	}

}

void printStudentDataAll(const vector<Student_info>& student){
	typedef vector<Student_info>::size_type vec_sz;
	const vec_sz size = student.size();
	
	for(vec_sz i =0; i<size ; i++){
		cout<<student[i].name<<endl;
		cout<<student[i].midterm<<endl;
		cout<<student[i].finals<<endl;
		const vec_sz size1 = student[i].homework.size();
		for(vec_sz j =0; j<size1;j++){
			cout<<student[i].homework[j]<<endl;
		}
	}

}

void enterStudentData(vector<Student_info>& student){
	struct Student_info newStudent;
	cout<<"enter student name\n";
	getline(cin,newStudent.name);
	cout<<"enter midterm and finals grade in order:\n";
	cin>>newStudent.midterm>>newStudent.finals;

	cout<<"enter homework grades";
	for(int i =0; i< 5; i++){
		double x;
		cin>>x;
		newStudent.homework.push_back(x);
	}

	student.push_back(newStudent);
}

void sortArrSpecial(){
	int arr[] = {0,0,2,1,0,2,1,0,2,1,1,2,0};
	int length = sizeof(arr)/sizeof(arr[0]);
	int *zero = arr;
	int *first = arr;
	int *second = &arr[length-1];
	for(int i = 0; i< length; i++){
		if(arr[i]== 0){
			swap(*zero, arr[i]);
			zero++;
			first = zero;
		}	
		else if(arr[i]==2){
			swap(*second, arr[i]);
			second--;
		}
		else{
			swap(*(first+1), arr[i]);
			first++;
		}
		
	}
	for(int i =0; i< length; i++){
		cout<<" "<<arr[i];
	}
}



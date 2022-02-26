#ifndef STRING_H_
#define STRING_H_
#include <iostream>		
#include <algorithm>


class String;
//non-member methodes


//std::ostream& operator<<(std::ostream& os,String& str);



class String
{
public:		//Constructors
	String();
	String(char*);
	String(const String&);
	String& operator=(const String&);
	String(String&&)noexcept;
	String& operator=(String&&)noexcept;
	~String();

public:		//operators
	friend std::ostream & operator<<(std::ostream & os,const String& str);
	String operator+(String str);
	String& operator+=(String str);
	char& operator[](int pos);
	const char& operator[](int pos)const;
public:		//methods
	bool starts_with();  //C++ 20
	bool ends_with();  //C++ 20
	bool conteins();  //C++ 23
	const char* data()const;
	int size()const;
	int length()const;
	void clear();
	String& replace(int pos,int count,char ch);
	String& replace(int pos,char* );
	String substr(int pos,int count);
	int copy(char* ptr,int pos,int count);
	void resize(int count,char ch);
	void resize_and_overwrite();  //C++ 23
	String& erase(int index,int count);//out_of_range if index > size
	void push_back(char);
	void pop_back();
	String& append(const String& str);
	void insert(int,char);
	char& at(int);
	int find(char ch);
	void swap(String&)noexcept;

private:	//Helper functions
	void alloc();
	void set_null();

private:	//private DATA
	int _len{};
	int _cap;
	char* _buffer;
};

#endif 	

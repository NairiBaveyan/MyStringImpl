#include <cstring>
#include "string.h"

String::String()
	:_len{0},_cap{1}
{
	_buffer = new char[_cap];
	_buffer[0] = '\0';
}

String::String(char* str)
{
	
	_len = strlen(str);
	_cap = _len + 1;
	_buffer = new char[_cap];
	for(int i{};i < _len;++i)
	{
		_buffer[i] = str[i];
	}
	_buffer[_len] = '\0';
}


String::String(const String& str)
{
	_len = str._len;
	_cap = str._cap;
	_buffer = new char[_cap];
	for(int i{};i < _len;++i)
	{
		_buffer[i] = str._buffer[i];
	}
	_buffer[_len] = '\0';
}



String& String::operator=(const String& str)
{
	if(this == &str)
		return *this;
	while(str._cap > _cap)
		alloc();
	_len = str._len;
	for(int i{};i < str._len;++i)
		_buffer[i] = str._buffer[i];
	set_null();
	return *this;
}



String::String(String&& str)noexcept
{
	_buffer = str._buffer;
	_len = str._len;
	_cap = str._cap;
	str._len = 0;
	str._cap = 0;
	str._buffer = nullptr;
}

String& String::operator=(String&& str)noexcept
{
	if(this == &str)
		return *this;
	delete [] _buffer;
	
	_cap = str._cap;
	_len = str._len;
	_buffer = str._buffer;
	str._buffer = nullptr;
	str._len = 0;
	str._cap = 0;
 
	return *this;
}

String::~String()
{
	delete [] _buffer;
}

void String::swap(String & str)noexcept //copy & swap idiom
{
        std::swap(_buffer, str._buffer);
	std::swap(_len,str._len);
	std::swap(_cap,str._cap);
}

void String::insert(int pos,char ch)
{
	try{
		if(pos > _len){
			throw std::invalid_argument("Invalid argument!");
		}	
	}
	catch(const char* err){
		std::cout<<err<<std::endl;
	}

	if(pos == _len)		//deleted else
	{
		if(_len == _cap)
		{
			this->alloc();
			_buffer[_len] = ch;
			this->set_null();
		}
		else{
			_buffer[_len] = ch;
			this->set_null();
		}
	}
	else{
		if(_len == _cap)
		{
			this->alloc();
			for(int i{_len};i > pos;--i)
			{
				_buffer[i] = _buffer[i-1];
			}
			_buffer[pos] = ch;
			this->set_null();
		}
		else{
			for(int i{_len};i > pos;--i)
			{
				_buffer[i] = _buffer[i-1];
			}
			_buffer[pos] = ch;
			this->set_null();
		}
	}
}

void String::push_back(char ch)
{
	this->insert(_len,ch);
}

void String::pop_back()
{
	if(_len)
	{
		--_len;
		_buffer[_len] = '\0';
	}
	else{
		try{
			throw std::logic_error("Logic ERROR!");
		}
		catch(const char * err){
			std::cout<<err;
		}
	}
}

void String::set_null()
{
	++_len;
	_buffer[_len] = '\0';
}

void String::alloc()
{
	_cap*=2;
	char* ptr = new char[_cap];
	for(int i{};i <= _len;++i)
	{
		ptr[i] = _buffer[i];
	}
	delete[] _buffer;
	_buffer = ptr;
}

void String::resize(int count,char ch)
{
	try{
		if(count < 0)
			throw std::invalid_argument("Invalid Argument!");
	}
	catch(const char* err){
		std::cout<<err<<std::endl;
	}

	if(count == 0)
		return;
	while(count > _cap)
		this->alloc();
	for(int i{_len};i < _len+count;++i)
	{
		_buffer[i] = ch;
	}
	_len+=(count-1);
	this->set_null();
}

String String::substr( int pos, int count)
{
	try{
		if(pos + count >= _len)
			throw std::out_of_range("Out of Range!");
	}
	catch(const char* err){
		std::cout<<err<<std::endl;
	}

	char* ptr = new char[count];
	for(int i{pos};i < (pos+count);++i)
	{
		ptr[i - pos] = _buffer[i];
	}
	String subs(ptr);
	delete[] ptr;
	return subs;
}

String& String::erase(int index,int count)
{
	try{
		if(index >= _len){
			throw std::out_of_range("Out of Range!");
		}
	}
	catch(const char* err){
		std::cout<<err<<std::endl;
	}
	if(_len <= (index +count)){
		_len = index-1;
		this->set_null();
	}
	else{
		for(int i{index};i+count < _len;++i)
		{
			_buffer[i] = _buffer[i+count];
		}
		_len -= count;
		_buffer[_len] = '\0';
	}
	return *this;
}


std::ostream & operator<<(std::ostream& os,const String& str)
{	
	for(int i{};i < str._len;++i)
		os<<str._buffer[i];
	return os;
}



const char& String::operator[](int pos)const
{
	return _buffer[pos];
}


char& String::operator[](int pos)
{
	return const_cast<char&>(
			static_cast<const String&>(*this)[pos]
			);
		
}

char& String::at(int pos)
{
	try{
		if(pos >=_len || pos < 0){
			throw std::out_of_range("Out of Range!");
		}
	}
	catch(const char* err){
		std::cout<<err<<std::endl;
	}
	return _buffer[pos];
}

int String::find(char ch)
{
	for(int i{};i < _len;++i)
	{
		if(_buffer[i]==ch)
			return i;
	}
	return -1;
}


void String::clear()
{
	_len = 0;
	_buffer[_len] = '\0';
}


const char* String::data()const
{
	return _buffer;
}

int String::size()const
{
	return _len;
}


int String::length()const
{
	return _len;
}

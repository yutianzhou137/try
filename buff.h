#ifndef _BUFF_H_
#define _BUFF_H_

#include "formulas.h"
#include "stack.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

static const int MAX=100;

class Buff { //用户输入接口，并对输入进行处理, 给出参数为formulas的栈的引用
	private:
		char buff[1024];
		//输入函数
		void get_buff(); //输入buff
		//预处理函数
		void delete_while_charater();  //清除输入中的空格
		bool is_end(); // 检查输入是否为 end
		bool is_error(); // 检查输入是否有错误
		//字符转数字
		void get_num(Stack<Formulas>& p);
		bool is_figure(const char* const character); //判断是否为数字；
		double seperate_num(int& i); //从给定的参数开始，将之后buff中的数字分离出来直到遇到数学字符或为空为止
	public:
		States function(Stack<Formulas>& formulas); //参数为一个formulas的栈的引用，负责调用类内的函数，并返回一个状态码
};

void Buff::get_buff() {
	std::cout << ">>" ;
	std::cin >> buff;
}

void Buff::delete_while_charater() {
	for (int i=0; buff[i]!='\0'; i++) {
		if (buff[i]!=' ');
		else {
			for (int j=i;; j++) {
				buff[j+1]=buff[j];
				if(buff[j+1]=='\0')
					break;
			}
		}
	}
}

bool Buff::is_end() {
	const char* point=buff;
	for (int i=0; point[i+2]!='\0'; i++) {
		if (point[i]=='e'&&point[i+1]=='n'&&point[i+2]=='d')
			return true;
	}
	return false;
}

bool Buff::is_error() {
	const char* point=buff;
	for(int i=0; point[i+1]!='\0'; i++) {
		if(point[i]=='/'&&point[i+1]=='0')
			return true;
	}
	return false;
}

void Buff::get_num(Stack<Formulas>& formulas) {
	for (int i=0; buff[i]!='\0';) {
		Formulas p;
		if (is_figure(&buff[i])==false) {
			p.sign=char_to_sym(buff[i]);
			formulas.push(p);
			i+=1;
		} else {
			p.data=seperate_num(i);
			formulas.push(p);
		}
	}
	formulas.upside_stack();
}

bool Buff::is_figure(const char* const character) {
	const char c=*character;
	if (c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9') {
		return true;
	}
	return false;
}

double Buff::seperate_num(int& fre) {
	char tem[MAX];
	memset(tem,'\0',MAX);
	for (int i=0; buff[fre]!='\0'&&(is_figure(&buff[fre])==true||buff[fre]=='.'); i++) {
		tem[i]=buff[fre];
		fre+=1;
	}
	return atof(tem);
}

States Buff::function(Stack<Formulas>& formulas) {
	memset(buff,'\0',sizeof(buff));
	this->get_buff();
	this->delete_while_charater();
	if(is_end()==true) {
		return States::END;
	}
	if(is_error()==true) {
		return States::ERROR;
	}
	this->get_num(formulas);
	return States::OK;
}

#endif
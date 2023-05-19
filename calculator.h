#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "formulas.h"
#include "stack.h"
#include<iostream>

class calcultor { //计算 ,给出参数为formulas的类型的栈的引用，并输出一个double类型的值
	private:
		Stack<Formulas> last_stack;
		//将中缀表达式转为后缀表达式
		void  get_last_stack(Stack<Formulas>& buff);  //将中缀转为后缀
		bool figure_part(Stack<Symbols>& symbols_stack,Symbols sign); //负责加减乘除的情况
		bool high_important(const Symbols& out,const Symbols& top); //判断优先程度；
		void get_bracket(Stack<Symbols>& symbols_stack); //从右括号开始，将符号栈的元素出栈，直到左括号为止
		//将后缀表达式计算出来
		double get_result();

	public:
		double function(Stack<Formulas>& formulas); //用户接口，负责调用各种类内函数，并返回计算结果
};

void calcultor::get_last_stack(Stack<Formulas>& buff) {
	Formulas tem;
	Stack<Symbols> symbols_stack;
	while(buff.is_empty()==false) {
		buff.pop(&tem);
		switch(tem.sign) {
			case Symbols::blank:
				last_stack.push(tem);
				break;
			case Symbols::left_bracket:
				symbols_stack.push(tem.sign);
				break;
			case Symbols::right_bracket:
				get_bracket(symbols_stack);
				break;
			default :
				figure_part(symbols_stack,tem.sign);
				break;
		}
	}
	while(symbols_stack.is_empty()==false) {
		Formulas tem2;
		Symbols sign_tem;
		symbols_stack.pop(&sign_tem);
		tem2.sign=sign_tem;
		last_stack.push(tem2);
	}
	last_stack.upside_stack();
}

bool calcultor::figure_part(Stack<Symbols>& symbols_stack,Symbols sign) {
	if (symbols_stack.is_empty()==true) {
		symbols_stack.push(sign);
		return true;
	}
	Symbols top;
	symbols_stack.get_top(&top);
	if (top==Symbols::left_bracket||high_important(sign,top)==true) {
		symbols_stack.push(sign);
		return true;
	}
	Symbols tem;
	do {
		if(symbols_stack.is_empty()==true)
			break;
		symbols_stack.pop(&tem);
		Formulas tem2;
		tem2.sign=tem;
		last_stack.push(tem2);
	} while(true);
	symbols_stack.push(sign);
	return false;
}

bool calcultor::high_important(const Symbols& out,const Symbols& top) { //a为取出元素，b为栈顶元素
	if ((out==Symbols::multiply||out==Symbols::except)&&(top==Symbols::plus||top==Symbols::minus)) {
		return true;
	}
	return false;
}

void calcultor::get_bracket(Stack<Symbols>& symbols_stack) {
	Formulas tem_one;
	Symbols tem;
	while(true) {
		symbols_stack.pop(&tem);
		if(tem==Symbols::left_bracket)
			break;
		tem_one.sign=tem;
		last_stack.push(tem_one);
	}
}

double calcultor::get_result() {
	double result;
	Stack<double> num_stack;
	Formulas tem;
	//cout << "开始计算后缀表达式" << endl;
	do {
		//	cout << "栈未到底" << endl;
		last_stack.pop(&tem);
		if (tem.sign==Symbols::blank) {
			num_stack.push(tem.data);
			continue;
		}
		double num1,num2;
		num_stack.pop(&num2);
		num_stack.pop(&num1);
		switch (tem.sign) {
			case Symbols::plus:
				num1+=num2;
				break;
			case Symbols::minus:
				num1-=num2;
				break;
			case Symbols::multiply:
				num1*=num2;
				break;
			case Symbols::except:
				num1/=num2;
				break;
			default :
				break;
		}
		num_stack.push(num1);
	} while(last_stack.is_empty()==false);

	num_stack.pop(&result);

	return result;
}


double calcultor::function(Stack<Formulas>& formulas) {
	last_stack.clear_stack();
	this->get_last_stack(formulas);
/*	std::cout << "formulas last_stack:";
	this->print(last_stack);*/
	double result=this->get_result();
	return result;
}

/*	bool print(Stack<Formulas>& formulas) {
			using namespace std;
			int len=formulas.stack_length();
			if(len==0)
				return false;
			Formulas tem;
			for (int i=0; i<len; i++) {
				formulas.get_elem(i+1,&tem);
				if(tem.sign==Symbols::blank)
					cout << tem.data;
				else
					cout << (char)tem.sign;
			}
			cout << endl;
			return true;
		}*/

#endif
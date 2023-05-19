#ifndef _FORMULAS_H_
#define _FORMULAS_H_

enum class Symbols:char { //数学符号枚举类定义
	blank='\0',
	plus='+',
	minus='-',
	multiply='*',
	except='/',
	left_bracket='(',
	right_bracket=')'
};

enum class States:int { //定义状态码
	OK,END,ERROR
};

Symbols char_to_sym (char ch) { //char 类型转 symbols类型
	switch(ch) {
		case '+':
			return Symbols::plus;
			break;
		case '-':
			return Symbols::minus;
			break;
		case '*':
			return Symbols::multiply;
			break;
		case '/':
			return Symbols::except;
			break;
		case '(':
			return Symbols::left_bracket;
			break;
		case ')':
			return Symbols::right_bracket;
			break;
		default:
			return Symbols::blank;
			break;
	}
	return Symbols::blank;
}

class Formulas { //用于储存计算式的类
	public:
		double data;
		Symbols sign;
		Formulas() {
			data=0;
			sign=Symbols::blank;//只需要判断sign是否为‘\0'
		}
};

#endif
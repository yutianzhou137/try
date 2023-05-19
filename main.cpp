#include "calculator.h"
#include "buff.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
bool print(Stack<Formulas>& formulas){
	using namespace std;
     int len=formulas.stack_length();
     if(len==0)
     return false;
     Formulas tem;
     for (int i=0;i<len;i++){
         formulas.get_elem(i+1,&tem);
         if(tem.sign==Symbols::blank)
         cout << tem.data;
         else
         cout << (char)tem.sign;
	 }
	 cout << endl;
	 return true;
}
*/
int main(int argc, char** argv) {
	system("chcp 65001");
	using namespace std;

	Stack<Formulas> formulas; //给出的栈
	Buff buff_a; // 缓冲区a
	calcultor Calcultor; //计算器
	States states; //给定的状态码变量
	double outcome; //结果变量

	cout << "This is a simple calculator" << endl
	     << "Put \"end\" to break" << endl;

	do { //程序主体
	    formulas.clear_stack();
		states=buff_a.function(formulas);
		switch(states) {
			case States::OK:
				outcome=Calcultor.function(formulas);
				cout << "result:" << outcome << endl;
				break;
			case States::ERROR:
				cout << "ERROR!!!" << endl;
				continue;
			case States::END:
				cout << "Thanks for using!!!" << endl;
				break;
		}
	} while(states!=States::END);


	return 0;
}
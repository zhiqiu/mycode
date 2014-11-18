#include <iostream>
#include <deque>
using namespace std;

deque<int> chanG2H1;
deque<int> chanH12F;
deque<int> chanF2G;     //output
deque<int> chanG2H0;
deque<int> chanH02F;

int counter;
int flag0;
int flag1;
int flagF;
int flagG;
int flagH0;
int flagH1;

void f(){
	if (flagF) {  //flagF = 1  read h1
		if (chanH12F.empty())   ;
		else{
			int n = chanH12F.front();
			chanH12F.pop_front();
			chanF2G.push_back(n);
			cout << "counter " << counter++ << ": " << n << endl;
			flagF = !flagF;
			return;
		}
	}
	else{
		if (chanH02F.empty());
		else{
			int n = chanH02F.front();
			chanH02F.pop_front();
			chanF2G.push_back(n);
			cout << "counter " << counter++ << ": " << n << endl;
			flagF = !flagF;
			return;
		}
	}
}
void g(){
	if (chanF2G.empty())  ;
	else {
		if (flagG) {  //flagF = 1  write h1	
			int n = chanF2G.front();
			chanF2G.pop_front();
			chanG2H1.push_back(n);
			//cout <<"counter "<< counter++ <<": "<< n <<  endl;					
		}
		else{
			int n = chanF2G.front();
			chanF2G.pop_front();
			chanG2H0.push_back(n);
			//cout <<"counter "<< counter++ <<": "<< n <<  endl;
		}
		flagG = !flagG;
	}
}
void h1(){
	if (flag1)  {
		chanH12F.push_back(1);
		//flagH1 = !flagH1;
		flag1 = 0;
	}
	else{
		if (chanG2H1.empty());
		else{
			int n = chanG2H1.front();
			chanG2H1.pop_front();
			chanH12F.push_back(n);
		}
	}

}
void h0(){
	if (flag0)  {
		chanH02F.push_back(0);
		//flagH1 = !flagH1;
		flag0 = 0;
	}
	else{
		if (chanG2H0.empty());
		else{
			int n = chanG2H0.front();
			chanG2H0.pop_front();
			chanH02F.push_back(n);
		}
	}

}
int main(){
	counter = 0;
	cout << "Order 1:   h1, h0, f, g" << endl;
	flag1 = 1;
	flag0 = 1;
	flagF = 1;
	flagG = 1;
	flagH0 = 1;
	flagH1 = 1;
	for (int i = 0; i < 100; i++){
		h1();
		h0();
		f();
		g();
	}
	cout << endl << endl;
	chanG2H1.clear();
	chanG2H0.clear();
	chanF2G.clear();
	chanH12F.clear();
	chanH02F.clear();
	flag1 = 1;
	flag0 = 1;
	flagF = 1;
	flagG = 1;
	flagH0 = 1;
	flagH1 = 1;
	counter = 0;
	cout << "Order 2:   h1, h1, h1, g, f, h0, h0" << endl;
	for (int i = 0; i < 100; i++){
		h1();
		h1();
		h1();
		g();
		f();
		h0();
		h0();
	}
	cout << endl << endl;
	cout << "Order 3:   f, f, g, h1, h0, h1, h0, h0, g" << endl;
	chanG2H1.clear();
	chanG2H0.clear();
	chanF2G.clear();
	chanH12F.clear();
	chanH02F.clear();
	flagF = 1;
	flagG = 1;
	flagH0 = 1;
	flagH1 = 1;
	flag1 = 1;
	flag0 = 1;
	counter = 0;
	for (int i = 0; i < 100; i++){
		f();
		f();
		g();
		h1();
		h0();
		h1();
		h0();
		h0();
		g();
	}
	return 0;
}


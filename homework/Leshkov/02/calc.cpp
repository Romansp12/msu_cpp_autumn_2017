#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;


/*
	Grammar:
 S -> D{+D} | D{-D}
 D -> T{*T} | T{/T}
 T -> -N | N
 N -> [0-9] {[0-9]}
*/
int S(const char* s, int &i);
int D(const char* s, int &i);
int T(const char* s, int &i);
int N(const char* s, int &i);



int main(int argc, char* argv[]){


	if (argc!=2){
		cout<<"Incorrect amount of args\n";
		return 1;
	}
	//Сhecking amount of Аrgs
	int i=0;
	int j=0;
	char* str=(char*)malloc(strlen(argv[1])+1);
	for(i=0; i<strlen(argv[1]); i++){
		if(argv[1][i]!=' ')
			str[j++]=argv[1][i];
	}
	str[j] = '\0';
	//Making input string without spaces


	int iter=0;
	try{
		cout<<S(str,iter)<<endl;	
	}
	catch(char c){
		cout<<"Error on "<<c<<endl;
		free(str);
		return 1;
	}

	free(str);
	return 0;
}




//*********************-------------------************************
//Далее реализация грамматики с соответствующими проверками на 
//допустимые цепочки грамматики и деление на 0


int N(const char* s, int &i){
	if ((s[i]<'0')||(s[i]>'9')){
		cout<< "Invalid Syntax N\n";
		throw s[i];
		//Исключает тройные минусы
	}

	int num=0;
	while((s[i]>='0')&&(s[i]<='9')){
		num=num*10+s[i]-'0';
		i++;
	}
	return num;
}

int T(const char* s, int &i){

	if (s[i]=='-'){
		i++;
		return -N(s,i);
	}

	return N(s,i);
}

int D(const char* s, int &i){
	int tmp=T(s,i);
	int d;

	//Высчитываем * и /
	while((s[i]=='*')||(s[i]=='/')){

		if (s[i]=='/'){
			i++;
			d=T(s,i);
			if(d!=0)
				tmp/=d;
			else{
				cout<<"Error: zero division\n";
				throw '0';
				//Проверка деления на 0
			}
		}
		if (s[i]=='*'){
			i++;
			tmp*=T(s,i);
		}

	}
	return tmp;
}

int S(const char* s, int &i){
	int res=D(s,i);

	//Суммируем + и -
	while(s[i]!='\0'){
		
		if(s[i]=='+'){
			i++;
			res+=D(s,i);
		}
		if(s[i]=='-'){
			i++;
			res-=D(s,i);
		}
		if((s[i]!='\0')&&(s[i]!='-')&&
			(s[i]!='+')){
			cout<<"S: unexpectible Lexem: "<<s[i]<<endl;
			throw s[i];
			//Проверка на символы, не являющиеся терминалными
		}

	}
	return res;
}


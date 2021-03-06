#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>

using namespace std;

enum class Token
{
  Invalid,
  Minus,
  Plus,
  Mul,
  Div,
  Number,
  End
};



// считывает токен, меняет позицию прочитанного текста и записывает число в глобальную переменную
Token getToken(const char*& text)
{
  while (const auto c = *text++)
  {
    switch (c)
    {
      case ' ': continue;
      case '-': return Token::Minus;
      case '+': return Token::Plus;
      case '*': return Token::Mul;
      case '/': return Token::Div;
    }
    if (c >= '0' && c < '9')
    {
      return Token::Number;
    }
    return Token::Invalid;
  }
  return Token::End;
}
//        логика вычислений:
// <выражение> = <слагаемое> {+ <слагаемое>}  ||
// <слагаемое> = <множитель> {+ <множитель>}  ||
// <множитель> = <число> {+ <выражение>}      ||


int term (Token& token, const char*& text);
int primary (Token& token, const char*& text);

int expression (Token& token, const char*& text) { // выражение
  int left = term(token, text);
  while (token != Token::End) {
    switch(token)
    {
      case Token::Plus:{
        left += term(token, text);
        break;
      }
      case Token::Minus:{
        left -= term(token, text);
        break;
      }
      case Token::End:{
        return left;
      }
      default:
        return left;
    }
  }
  return left;
}

int term (Token& token, const char*& text) { // слагаемое
  int left_term = primary(token, text);
  while (token != Token::End){
    switch(token){
      case Token::Mul:{
        left_term *= primary(token, text);
        break;
      }
      case Token::Div:{
        int denominator = primary(token, text);
	if (denominator == 0) {  // Обработка случая деления на ноль
	  throw "Error! Can't devide by zero";
	  break;
	}
	else {
          left_term /= denominator;
          break;
	}
      }
        case Token::Plus:{
	  return left_term;
        }
	case Token::Minus:{
	  return left_term;
	}
	case Token::End:{
	  return left_term;
	}
	default:
	  throw "Invalid symbol";
	  return left_term;
    }
  }
  return left_term;
}

int primary (Token& token, const char*& text) { // множитель
  token = getToken(text);
  switch(token){
    case Token::Number: {
      --text;
      auto f = *text;
      int num = 0;
      while (f >= '0' && f <= '9') // преобразование многозначного чила в целый тип
      {
        num = num * 10 + f - '0';
	++text;
	f = *text;
      }
      token = getToken(text);
      return num;
    }
      case Token::Minus:{ // унарный минус
      return -primary(token, text);
    }
    default:
      throw "Invalid symbol";
      return 1;
  }
}


// переменнная text - идентификатор позиции
// token - показывает что находится на этой позиции
// number - сюда записывается число

int main(int argc, char* argv[])
{
  try
  {
    //const char* text = "1 * 6 + 3 / 2 - 2 * 2";
    const char* text = argv[1];
    //cout << text << endl;
    Token token; // преобразовали текст в токены
    int result = expression(token, text); // вычислелние выражения
    cout << result << endl;
      return 0;
  }
  catch (const char* str){
    cout << str << endl;
    return 1;
  }
}

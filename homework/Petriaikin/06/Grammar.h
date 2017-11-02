#pragma once

#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

//=========================================================================================

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <exception>

#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

#include <math.h>

#define CALC_ASSERT(x) if (!(x)) {throw std::logic_error(#x);}
#define ERROR_CODE 1

//=========================================================================================

//Sum = Mul +<or>- Mul
//Mul = Atomic *<or>/ Atomic
//Atomic = Number <or> '(' Sum ')'
//Number = (-)[0...9].[0...9] <or> Pi <or> e

const std::unordered_map<std::string, std::string> constants_c =
{
	{ "Pi", "3.14" },
	{ "e", "2.7" }
};


//GrammarElement ������ ������ �������. ������ �����, ������ ��� ��������� �������� ����������� ������ ������, � ��������� ����� �������
template <typename T>
class GrammarElement
{
	protected:
		const char* string_; //������ ��� ������� (��� ��������)
		int shift_; //������� ��������

		std::vector<GrammarElement*> subelements_; //����������� ��������

	protected:
		virtual void Parse_() = 0; //�������� �����������

	public:
		GrammarElement(const char* str, int shift);
		virtual T GetValue() const = 0; //���������� �������� � ����

		int GetShift() const { return shift_; }

		virtual ~GrammarElement();
};

//=========================================================================================

//����� ����� � �������� T - ��� �����, �������������� �������������

template <typename T>
using BinaryOperationFunction = std::function<T(T, T)>;

template <typename T>
using BinaryOperation = std::pair<char, BinaryOperationFunction<T> >;

template <typename T>
using BinaryOperations = std::vector<BinaryOperation<T> >;

//��� operations ������ ��������� ����������� ���������� operations ���� BinaryOperations, ����������� ��������� �������� ��� ������� ����������
//NextElementType - ������� ����� �������� ����������
template<typename T, typename NextElementType, const BinaryOperations<T>* operations>
class BinaryGrammarElement : public GrammarElement<T>
{
	protected:
		std::vector<BinaryOperationFunction<T>> opetations_between_arguments_; //���������� �������� ����� ����������� - �� operations

	protected:
		virtual void Parse_();

		static const BinaryOperation<T>* GetOperationFromSymbol_(char symbol_p);

	public:
		BinaryGrammarElement(const char* str, int shift);

		virtual T GetValue() const;
};

//=========================================================================================

template<typename T>
class NumberParser
{
	public:
		static T GetNumber(const char* str, int& shift);
};

//AtomicExpression - ����� ������� �������. ��� ��������� ��� ����� ������������ � �����-��������� ������� ������� ����������.
template <typename T, typename lowest_rule_decorator>
class AtomicExpression : public GrammarElement<T>
{
	protected:
		T value_;

	protected:
		virtual void Parse_();

	public:
		AtomicExpression(const char* str, int shift);

		virtual T GetValue() const;
};

//=========================================================================================

//������ ������: ������������ �������� ����������������� ���� � �������� ������� ����������, ������� ��������� (�������� �������� ������ ����������)
//�������������� ������: ������������ lowest_rule ��� AtomicExpression
template <typename T>
class Calculator;

//��� ���������� �������� �������� (���������, ��� T): ��������� ��������� (����� ���� ����������� �������),
//������� �������� BinaryOperations ��� �������� � BinaryGrammarElement
//name_operation - ��� ������ ������������� �������� ��������
//next_operation - ��� ������ ��������� �� ���������� ��������
#define DEFINE_BINARY_OPERATION(name_operation, next_operation, ...)\
										struct name_operation##_struct_operations\
										{\
											static const BinaryOperations<T> operations;\
										};\
										template<typename T>\
										const BinaryOperations<T> name_operation##_struct_operations<T>::operations = __VA_ARGS__;\
										template <typename T>\
										using name_operation = BinaryGrammarElement<T, next_operation,\
																				    &name_operation##_struct_operations<T>::operations>

//������������ �������� ����������
template<typename T>
using AtomicExpressionSpecified = AtomicExpression<T, Calculator<T>>;

template<typename T>
DEFINE_BINARY_OPERATION(Pow, AtomicExpressionSpecified<T>, {\
															   {'^', [](T a, T b)\
																     {\
																	     if (b == 0.0) { return (T) 1.0; }\
																	     return (T) pow(a, b);\
															         }\
														       }\
											               });

template<typename T>
DEFINE_BINARY_OPERATION(MultiplicationDivision, Pow<T>, {\
														     {'*', [](T a, T b) { return a * b; }},\
														     {'/', [](T a, T b)\
																   {\
																        if (b == 0) { throw std::invalid_argument("Dividing by zero!"); }\
																        return a / b;\
															       }\
														     }\
													    });

template<typename T>
DEFINE_BINARY_OPERATION(SumDifference, MultiplicationDivision<T>, {\
																	  {'+', [](T a, T b) { return a + b; }},\
																	  {'-', [](T a, T b) { return a - b; }}\
															      });

// ������������� ������ ������������������ �������
template <typename T>
class Calculator
{
	public:
		typedef T calc_type;
		typedef SumDifference<T> lowest_rule;

	public:
		//���������� ��� ������
		static int GetValue(std::string& str);
};

//=========================================================================================

#endif
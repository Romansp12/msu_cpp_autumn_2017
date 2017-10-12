#pragma once

#ifndef _GRAMMAR_ELEMENT_H_
#define _GRAMMAR_ELEMENT_H_

//=========================================================================================

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <exception>

#define CALC_ASSERT(x) if (!(x)) {throw std::logic_error(#x);}

//=========================================================================================

//Sum = Mul +<or>- Mul
//Mul = Atomic *<or>/ Atomic
//Atomic = Number <or> '(' Sum ')'
//Number = (-)[0...9].[0...9] <or> Pi <or> e

//GrammarElement ������ ������ �������. ������ �����, ������ ��� ��������� �������� ����������� ������ ������, � ��������� ����� �������
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
		virtual double GetValue() const = 0; //���������� �������� � ����

		int GetShift() const { return shift_; }

		virtual ~GrammarElement();
};

//=========================================================================================

using BinaryOperationFunction = std::function<double(double, double)>;
using BinaryOperation  = std::pair<char, BinaryOperationFunction>;
using BinaryOperations = std::vector<BinaryOperation>;

//��� operations ������ ��������� ����������� ���������� operations ���� BinaryOperations, ����������� ��������� �������� ��� ������� ����������
//NextElementType - ������� ����� �������� ����������
template<typename NextElementType, typename operations>
class BinaryGrammarElement : public GrammarElement
{
	protected:
		std::vector<BinaryOperationFunction> opetations_between_arguments_; //���������� �������� ����� ����������� - �� operations

	protected:
		virtual void Parse_();

		static const BinaryOperation* GetOperationFromSymbol_(char symbol_p);

	public:
		BinaryGrammarElement(const char* str, int shift);

		virtual double GetValue() const;
};

//=========================================================================================

//lower_rule - ������� ����������, ������� ����� ������ � ������� - �� ����������, ��������� ����������� ������
class AtomicExpression : public GrammarElement
{
	protected:
		double value_;

	protected:
		virtual void Parse_();

	public:
		AtomicExpression(const char* str, int shift);

		virtual double GetValue() const;
};

//=========================================================================================

//��� ���������� �������� ��������: ��������� ���������, ������� �������� BinaryOperation ��� �������� � BinaryGrammarElement
//����� ������������ BinaryGrammarElement ��������� (��� ���������� ��������� ���������, ��������, � ������ ������� - ������ ������� ����������)

//name_operation - ��� ������ ������������� �������� ��������
//next_operation - ��� ������ ��������� �� ���������� ��������
//name_struct - ��������������� ��� ���������
//����� ���������� ����� ���������������� name_operation::operations � cpp �����

#define DEFINE_BINARY_OPERATION(name_operation, next_operation, name_struct)\
										struct name_struct {static const BinaryOperations operations;};\
										using name_operation = BinaryGrammarElement<next_operation, name_struct>

DEFINE_BINARY_OPERATION(Pow, AtomicExpression, PowOperations); //�� ���������� ��������� ��������� AtomicExpression - ����������� ������!
DEFINE_BINARY_OPERATION(MultiplicationDivision, Pow, MulDivOperations);
DEFINE_BINARY_OPERATION(SumDifference, MultiplicationDivision, SumDiffOperation);

//=========================================================================================

#endif
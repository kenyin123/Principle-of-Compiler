#pragma warning(disable:4996)
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
#include"��ͷ.h"


//��ʼ״̬�������˵�һ���ַ�
//����״̬���������һ���ַ���ֻ��һ���ַ���
//�����ȡ���޷�����������1��û��ȡ������0
int Grammar_unsigned_int() {
	if (symbol == INTCON) {
		fprintf(fp_out, "<�޷�������>\n");
		return 1;
	}
	else return 0;
}
//��ʼ״̬��������һ���ַ�
//����״̬���������һ���ַ� 
//����������1��û������return 0 ��û�ж���
int Grammar_int() {
	if (symbol == PLUS) {
		getsym();
		if (Grammar_unsigned_int()) {
			fprintf(fp_out, "<����>\n");
			printf("<����>\n");
			return 1;
		}
		else error(0);
	}
	else if (symbol == MINU) {
		getsym();
		if (Grammar_unsigned_int()) {
			fprintf(fp_out, "<����>\n");
			return 1;
		}
		else error(0);
	}
	else if (Grammar_unsigned_int()) {
		fprintf(fp_out, "<����>\n");
		return 1;
	}
	else return 0;
}

//��ʼ״̬����ȡ����һ���ַ�
//����״̬������";"
//�г�������Ļ�����1.û�з���0
int Const_Definition() {
	if (symbol == INTTK) {
		getsym();
		if (symbol != IDENFR)error(0);
		getsym();
		if (symbol != ASSIGN)error(0);
		getsym();
		if(!Grammar_int())error(0);
		getsym();
		while (symbol == COMMA) {
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol != ASSIGN)error(0);
			getsym();
			if (!Grammar_int())error(0);
			getsym();
		}
		if (symbol != SEMICN)error(0);
		fprintf(fp_out, "<��������>\n");
		return 1;
	}
	else if (symbol == CHARTK) {
		getsym();
		if (symbol != IDENFR)error(0);
		getsym();
		if (symbol != ASSIGN)error(0);
		getsym();
		if (symbol != CHARCON)error(0);
		getsym();
		while (symbol == COMMA) {
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol != ASSIGN)error(0);
			getsym();
			if (symbol != CHARCON)error(0);
			getsym();
		}
		if (symbol != SEMICN)error(0);
		printf("<��������>\n");
		return 1;
	}
	else return 0;
}



//��ʼ״̬���Ѿ�ʶ��const����
//����״̬����ȡ��������һ���ַ�
//����0 ��ʾ������ֻ��һ�ַ���ֵ��
int Const_Declaration() {
	getsym();
	if(!Const_Definition())error(0);
	if (symbol != SEMICN)error(0);
	getsym();
	if (symbol == CONSTTK) {
		Const_Declaration();
	}
	fprintf(fp_out, "<����˵��>\n");
	return 0;
}

/*
��ʼ״̬����ȡ�˵�һ���ַ���δʶ��
����״̬��
return 0:û�б�������
return 1������";"��һλ
return 2:����char a( 
return 3:����void
*/
int Var_Definition() {
	if (symbol == VOIDTK)return 3;
	if (symbol == CHARTK) {
		getsym();
		if (symbol != IDENFR)error(0);
		getsym();

		//char a;
		//char a[2];
		//char a,b[2];
		//char a()
		if (symbol == LPARENT)return 2;//�з��غ�������
		if (symbol == LBRACK) {
			getsym();
			if (!Grammar_unsigned_int())error(0);//������Ҫ����0
			if (int_get <= 0)error(0);
			getsym();
			if (symbol != RBRACK)error(0);
			getsym();
		}
		while (symbol == COMMA) {
			getsym();
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol == LBRACK) {
				getsym();
				if (!Grammar_unsigned_int())error(0);//������Ҫ����0
				if (int_get <= 0)error(0);
				getsym();
				if (symbol != RBRACK)error(0);
				getsym();
			}
		}
		if (symbol != SEMICN)error(0);
		fprintf(fp_out, "<��������>\n");
	}
	else if (symbol == INTTK) {
		getsym();
		if (symbol != IDENFR)error(0);
		getsym();

		//char a;
		//char a[2];
		//char a()
		//char a,b[2];
		if (symbol == LPARENT)return 2;//�з��غ�������
		if (symbol == LBRACK) {
			getsym();
			if (!Grammar_unsigned_int())error(0);//������Ҫ����0
			if (int_get <= 0)error(0);
			getsym();
			if (symbol != RBRACK)error(0);
			getsym();
		}
		while (symbol == COMMA) {
			getsym();
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol == LBRACK) {
				getsym();
				if (!Grammar_unsigned_int())error(0);//������Ҫ����0
				if (int_get <= 0)error(0);
				getsym();
				if (symbol != RBRACK)error(0);
				getsym();
			}
		}
		if (symbol != SEMICN)error(0);
		fprintf(fp_out, "<��������>\n");
	}
	else return 0;
	getsym();
	return 1;
}
/*
pre_flag��ǰ���Ѿ��б������壬���Ա����������˵��
����״̬��
return2������
return3��void
*/
int Var_Declaration(){
	int flag; 
	int temp = Var_Definition();
	if (temp == 1)flag = 1;
	while (temp == 1) {
		temp = Var_Definition();
	}
	if (flag == 1) {
		fprintf(fp_out, "<����˵��>\n");
	}
	if (temp == 0)return 0;
	if (temp == 2)return 2;
	if (temp == 3)return 3;
}
//todo Ӧ���ܺϲ������Լ����棬�ϲ���һ������������ĺ���
/*
��ʼ״̬����ȡ�˵�һ���ַ���
�ж����������ӵĻ�����Ӧ�������ӣ������б�Ŀ���
return 0:ûʶ��
return 1:����
return 2:���ʽ
return 3:�ַ�
return 4:��ʶ��
return 5:��ʶ��[]
return 6:�з���ֵ�����������
����״̬��ʶ����ϲ���ȡ�˽�������һ���ַ�
���return 6���Ѿ��ж�ȡ����ע�⣿
ע��˳������
���鷳���ǣ�������ԣ���ô�᲻��������������
*/
int Factor() {
	if (Grammar_int() == 1) {
		getsym();
		fprintf(fp_out, "<����>\n");
		return 1;
	}
	else if (symbol == LPARENT) {
		getsym();
		if (Expression() == 0)error(0);//��ȡ��Expression()�ĵ�һ���ַ�,����ʱ���ȡ����һ���ַ�
		if (symbol != RPARENT)error(0);
		getsym();
		fprintf(fp_out, "<����>\n");
		return 2;
	}
	else if (symbol == CHARCON) {
		getsym();
		fprintf(fp_out, "<����>\n");
		return 3;
	}
	else if (symbol == IDENFR) {
		getsym();
		if ((symbol != LBRACK)&&(symbol != LPARENT)) {
			fprintf(fp_out, "<����>\n");
			return 4;
		}
		else if(symbol == LBRACK) {
			getsym();
			if (Expression() == 0)error(0);
			if (symbol != RBRACK)error(0);
			getsym();
			fprintf(fp_out, "<����>\n");
			return 5;
		}
		else if (symbol == LPARENT) {
			value_param_list();
			if (symbol == RPARENT) {
				getsym();
				fprintf(fp_out, "<����>\n");
				return 6;
			}
			else error(0);
		}
	}
	else return 0;
}
int Term() {
	if (Factor() == 0)return 0;
	while ((symbol == MULT) || (symbol == DIV)) {
		getsym();
		Factor();
	}
	fprintf(fp_out, "<��>\n");
	return 1;
}
//Ԥ����һλ
int Expression() {
	if ((symbol == PLUS) || (symbol == MINU)) {
		getsym();
		if (Term()) {
			while ((symbol == PLUS) || (symbol == MINU)) {
				getsym();
				if (Term() == 0)error(0);
			}
			fprintf(fp_out, "<���ʽ>\n");
			return 1;
		}
		else error(0);
	}
	else if (Term()) {
		while ((symbol == PLUS) || (symbol == MINU)) {
			getsym();
			if (Term() == 0)error(0);
		}
		fprintf(fp_out, "<���ʽ>\n");
		return 1;
	}
	else return 0;
}

/*
�βα� symbol = LPARENT
*/
void paramHandler() {
	getsym();
	while (symbol != RPARENT) {
		if (symbol == INTTK) {
			getsym();
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol == COMMA)getsym();
			else if (symbol != RPARENT)error(0);
		}
		else if (symbol == CHARTK) {
			getsym();
			if (symbol != IDENFR)error(0);
			getsym();
			if (symbol == COMMA)getsym();
			else if (symbol != RPARENT)error(0);
		}
		else error(0);
	}
	fprintf(fp_out, "<������>\n");
	getsym();
}
/*
���
��ʼ״̬��Ԥ���˵�һ���ַ�
����״̬��Ԥ����һ���ַ�
�ر�ע��;
*/
void statementHandler() {
	if (symbol == LBRACE) {
		getsym();
		statement_list();
		getsym();
	}
	else if (symbol == IFTK) if_Handler();
	else if (symbol == WHILETK)while_Handler();
	else if (symbol == DOTK)do_while_Handler();
	else if (symbol == FORTK)for_Handler();
	else if (symbol == SCANFTK) {
		scanf_Handler();
		if (symbol != SEMICN)error(0);
		getsym();
	}
	else if (symbol == PRINTFTK) {
		printf_Handler();
		if (symbol != SEMICN)error(0);
		getsym();
	}
	else if (symbol == RETURNTK) {
		return_Handler();
		if (symbol != SEMICN)error(0);
		getsym();
	}
	else if (symbol == SEMICN) {
		getsym();
	}
	else if (symbol == IDENFR) {
		getsym();
		if (symbol == LPARENT) {
			call_fun_Handler();
			if (symbol == SEMICN) getsym();
			else error(0);
		} 
		else {
			assign_Handler();
			if (symbol == SEMICN) getsym();
			else error(0);
		}
	}
	else error(0);
	fprintf(fp_out, "<���>\n");
}
void statement_list() {
	while (symbol != RBRACE) {
		statementHandler();
	}
	fprintf(fp_out, "<�����>\n");
}
/*
�������
��ʼ����״̬Ĭ�ϣ�����{}
*/
void complex_statement() {
	getsym();
	if (symbol == CONSTTK) {
		Const_Declaration();
	}
	if (symbol == INTTK || symbol == CHARTK) {
		if (Var_Declaration() != 0)error(0);
	}
	statement_list();
	fprintf(fp_out, "<�������>\n");
}
/*
����
��ʼ״̬��Ԥ����һλ
����״̬��Ԥ����һλ
*/
void condition() {
	if (Expression() == 0)error(0);
	if (isRelation(symbol)) {
		getsym();
		if (Expression() == 0)error(0);
	}
	fprintf(fp_out, "<����>\n");
}
void if_Handler() {
	getsym();
	if (symbol != LPARENT) error(0);
	getsym();
	condition();
	if (symbol != RPARENT)error(0);
	statementHandler();
	if (symbol != ELSETK) {
		fprintf(fp_out, "<�������>\n");
	}
	else {
		getsym();
		statementHandler();
		fprintf(fp_out, "<�������>\n");
	}
}

/*
ѭ�����
��ʼ״̬��
����״̬��Ԥ����һλ
*/
void while_Handler() {
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	condition();
	if (symbol != RPARENT)error(0);
	getsym();
	statementHandler();
	fprintf(fp_out, "<ѭ�����>\n");
}
void do_while_Handler() {
	getsym();
	statementHandler();
	if (symbol != WHILETK)error(0);
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	condition();
	if (symbol != RPARENT)error(0);
	getsym();
	fprintf(fp_out, "<ѭ�����>\n");
}
int step_length() {
	if (symbol == INTCON) {
		fprintf(fp_out, "<����>\n");
		return 1;
	}
	else return 0;
}
void for_Handler() {
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	if (symbol != IDENFR)error(0);
	getsym();
	if (symbol != ASSIGN)error(0);
	getsym();
	if (Expression() == 0)error(0);
	if (symbol != SEMICN)error(0);
	getsym();
	condition();
	if (symbol != SEMICN)error(0);
	getsym();
	if (symbol != IDENFR)error(0);
	getsym();
	if (symbol != ASSIGN)error(0);
	getsym();
	if (symbol != IDENFR)error(0);
	getsym();
	if ((symbol != PLUS) && (symbol != MINU))error(0);
	getsym();
	if (!step_length())error(0);
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	statementHandler();
	fprintf(fp_out, "<ѭ�����>\n");
}

/*
ֵ������
��ʼ״̬��Ԥ����һλ
����״̬��Ԥ����һλ
*/
void value_param_list() {
	if (Expression()) {
		while (symbol == SEMICN) {
			getsym();
			Expression();
		}
		fprintf(fp_out, "<ֵ������>\n");
	}
	else if (symbol == RPARENT) {
		getsym();
		fprintf(fp_out, "<ֵ������>\n");
	}
	else error(0);
}

/*
��������
��ʼ״̬��(
*/
void call_fun_Handler() {
	getsym();
	value_param_list();
	if (symbol != RPARENT)error(0);
	fprintf(fp_out, "<�����������>\n");
	getsym();
}
void assign_Handler() {
	if (symbol == ASSIGN) {
		getsym();
		if (Expression() == 0)error(0);
		fprintf(fp_out, "<��ֵ���>\n");
	}
	else if (symbol == LBRACK) {
		if (Expression() == 0)error(0);
		if (symbol != RBRACK)error(0);
		getsym();
		if (symbol != ASSIGN)error(0);
		getsym();
		if (Expression() == 0)error(0);
		fprintf(fp_out, "<��ֵ���>\n");
	}
	else error(0);
}
void scanf_Handler() {
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	if (symbol != IDENFR)error(0);
	getsym();
	while (symbol == COMMA) {
		getsym();
		if (symbol != IDENFR)error(0);
		getsym();
	}
	if (symbol != RPARENT)error(0);
	getsym();
	fprintf(fp_out, "<�����>\n");
}
void printf_Handler() {
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	if (symbol == STRCON) {
		fprintf(fp_out, "<�ַ���>\n");
		getsym();
		if (symbol == COMMA) {
			getsym();
			Expression();
		}
		if (symbol != RPARENT)error(0);
		getsym();
		fprintf(fp_out, "<д���>\n");
	}
	else if (Expression()) {
		if (symbol != RPARENT)error(0);
		getsym();
		fprintf(fp_out, "<д���>\n");
	}
	else error(0);
}
void return_Handler() {
	getsym();
	if (symbol == SEMICN) {
		fprintf(fp_out, "<�������>\n");
		return;
	}
	else if (symbol == LPARENT) {
		getsym();
		if (Expression() == 0)error(0);
		if (symbol != RPARENT)error(0);
		getsym();
		fprintf(fp_out, "<д���>\n");
	}
	else error(0);
}
void returned_func_definition() {
	getsym();
	if (symbol != IDENFR)error(0);
	fprintf(fp_out, "<����ͷ��>\n");
	getsym();
	if (symbol != LPARENT)error(0);
	paramHandler();
	if (symbol != LBRACE)error(0);
	getsym();
	complex_statement();
	if (symbol != RBRACE)error(0);
	fprintf(fp_out, "<�з���ֵ��������>\n");
	getsym();
}
int unreturn_func_definition() {
	getsym();
	if (symbol == MAINTK)return 1;
	if (symbol != IDENFR)error(0);
	getsym();
	if (symbol != LPARENT)error(0);
	paramHandler();
	if (symbol != LBRACE)error(0);
	getsym();
	complex_statement();
	if (symbol != RBRACE)error(0);
	fprintf(fp_out, "<�޷���ֵ��������>\n");
	getsym();
	return 0;
}
void mainfunc() {
	getsym();
	if (symbol != LPARENT)error(0);
	getsym();
	if (symbol != RPARENT)error(0);
	getsym();
	if (symbol != LBRACE)error(0);
	getsym();
	complex_statement();
	if (symbol != RBRACE)error(0);
	fprintf(fp_out, "<������>\n");
}
void program() {
	getsym();
	if (symbol == CONSTTK) {
		Const_Declaration();
	}
	if (symbol == INTTK || symbol == CHARTK) {
		int temp = Var_Declaration();
		if (temp == 2) {
			fprintf(fp_out, "<����ͷ��>\n");
			paramHandler();
			if (symbol != LBRACE)error(0);
			getsym();
			complex_statement();
			if (symbol != RBRACE)error(0);
			fprintf(fp_out, "<�з���ֵ��������>\n");
			getsym();
		}
	}
	while (symbol == VOIDTK || symbol == INTTK || symbol == CHARTK) {
		if (symbol == VOIDTK) {
			if (unreturn_func_definition() == 1) {
				break;
			}
		}
		else if (symbol == INTTK || symbol == CHARTK) {
			returned_func_definition();
		}
		else error(0);
	}
	mainfunc();
	fprintf(fp_out, "<����>\n");
	getsym();
	if (symbol != UNKNOWN)error(0);
}
int main() {
	fp_in = fopen("testfile.txt", "r");
	fp_out = fopen("output.txt", "w");
	program();
	fclose(fp_in);
	fclose(fp_out);
	return 0;
}
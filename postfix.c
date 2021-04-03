/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == "\0")
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
/*입력된 수식을 읽으면서 피연산자는 postFixExp에 저장하고 ( 는 스택에 넣고
)만나면 이전까지의 연산자를 pop하고 ( 는  문자열에 저장하지 않고 pop한다
나머지는 우선순위에 맞게 스택에 넣고 마지막에는 스택에 모든 연산자를pop한다
이경우 우선순위가 낮은 연산자가 오는 경우 스택에 모든 연산자를 pop하고 해당 연산자를 
push한다
*/
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		int i = 0;
		if (getPriority(exp[i]) == 1) {
			x = exp[i];
			charCat(&x);
		}
		else if (getPriority(exp[i]) == 0) {
			x = exp[i];
			postfixPush(x);
		}
		else if (getPriority(exp[i]) == 9) {
			while (postfixStack[postfixStackTop] != '(') {
				x = postfixPop();
				charCat(&x);
			}
			postfixStack[postfixStackTop] = '\0';
			postfixPop();
		}
		else if (getPriority(exp[i]) == 4|| getPriority(exp[i])==5) {
			x = exp[i];
			if (postfixStackTop == -1)
				postfixPush(x);
			else if (postfixStack[postfixStackTop] == '-' || postfixStack[postfixStackTop] == '+') {
				char y;
				y = postfixPop();
				charCat(&y);
				postfixPush(x);
			}
			else if (postfixStack[postfixStackTop] == '(')
				postfixPush(x);
			else {
				for(int i=0;i<2;i++) {
					char z;
					z = postfixPop();
					charCat(&z);
				}
				postfixPush(x);
			}

		}
		else {
			x = exp[i];
			if (postfixStackTop == -1)
				postfixPush(x);
			else if (postfixStack[postfixStackTop] == '*' || postfixStack[postfixStackTop] == '/') {
				char y;
				y = postfixPop();
				charCat(&y);
				postfixPush(x);
			}
			else if (postfixStack[postfixStackTop] == '(')
				postfixPush(x);
			else 
				postfixPush(x);
			}
		exp++;
		}
	while (postfixStackTop != -1) {
		x = postfixStack[postfixStackTop];
		charCat(&x);
		postfixPop();
		}
	}

	


void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
/*후위 표기가 완료된 수식을 받아서 스택에 피연산자는 넣고
연산자를 만나면 차례로 연산후 연산결과를 다시 스택에 저장하는
방식으로 차례로 연산후 결과값출력*/
void evaluation()
{
	char *exp=postfixExp;
	while (*exp != '\0') {
		int i = 0;
		if (getPriority(exp[i]) == 1) {
			evalPush(exp[i]);
		}
		else if (getPriority(exp[i]) == 4) {
			evalResult = (evalStack[evalStackTop - 1] - '0') - (evalStack[evalStackTop] - '0');
			--evalStackTop;
			evalStack[evalStackTop] = evalResult+'0';
		}
		else if (getPriority(exp[i]) == 5) {
			evalResult = (evalStack[evalStackTop - 1] - '0') + (evalStack[evalStackTop] - '0');
			--evalStackTop;
			evalStack[evalStackTop] = evalResult+'0';
		}
		else if (getPriority(exp[i]) == 6) {
			evalResult = (evalStack[evalStackTop - 1] - '0') / (evalStack[evalStackTop] - '0');
			--evalStackTop;
			evalStack[evalStackTop] = evalResult+'0';
		}
		else {
			evalResult = (evalStack[evalStackTop - 1] - '0') * (evalStack[evalStackTop] - '0');
			--evalStackTop;
			evalStack[evalStackTop] = evalResult+'0';
		}
		exp++;
	}
}


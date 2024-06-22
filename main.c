#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAXOP 100
int calculateExpression(const char *expr, int *index);
int calculateSimpleExpr(const char *expr, int *index);

int main() {
    char expr[MAXOP];
    printf("Enter expression: ");
    fgets(expr, MAXOP, stdin);
    int index = 0;
    int result = calculateExpression(expr, &index);
    printf("Result: %d\n", result);
    return 0;
}

// 递归函数处理整个表达式，包括括号
int calculateExpression(const char *expr, int *index) {
    int result = 0, num;
    char op = '+';

    while(isspace(expr[*index])) (*index)++;
    if(expr[*index] == '(') {
        (*index)++;
        result = calculateExpression(expr, index);
        if(expr[*index] != ')') {
            printf("Error: Missing closing parenthesis.\n");
            return -1;
        }
        (*index)++;
    } else {
        result = calculateSimpleExpr(expr, index);
    }

    while(isspace(expr[*index])) (*index)++;
    while(expr[*index] == '+' || expr[*index] == '-') {
        op = expr[*index];
        (*index)++;
        num = calculateSimpleExpr(expr, index);
        if(op == '+') result += num;
        else result -= num;
    }

    return result;
}

// 处理简单表达式（无括号，仅含+-）
int calculateSimpleExpr(const char *expr, int *index) {
    int result = 0, num;
    char op = '+';

    if(isdigit(expr[*index])) {
        result = expr[*index++] - '0';
        while(isdigit(expr[*index])) {
            result = result * 10 + (expr[*index++] - '0');
        }
    } else {
        printf("Error: Expected digit.\n");
        return -1;
    }

    while(isspace(expr[*index])) (*index)++;
    if(expr[*index] == '*' || expr[*index] == '/') {
        op = expr[*index];
        (*index)++;
        num = calculateSimpleExpr(expr, index);
        if(op == '*') result *= num;
        else if(num != 0) result /= num;
        else {
            printf("错误：除以零。\n");
            return -1;
        }
    }

    return result;
}

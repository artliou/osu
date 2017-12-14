/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/22/17
 ** Description: Project 9.b

 Prompt: Write a function named postfixEval that uses a stack<double> (from the Standard Template Library) to evaluate postfix expressions.
 It should take a C-style string parameter that represents a postfix expression.  The only symbols in the string will be +, -, *, /, digits and spaces.
 The return type should be double.
 Help: You may find the isdigit() function useful in parsing the expression.  You may also use strtok() and atof().

*********************************************************************/

#include <iostream>
#include <stack>
#include <cstring>
#include <cstdlib>

using namespace std;

double postfixEval(char stringIn[])
{
    stack<double> expression;
    double op1, op2;
    double total = 0;
    char *token = strtok(stringIn, " ");

    while (token != NULL)
    {
        if (isdigit(*token))
            expression.push(atof(token));
        else
        {
            op1 = expression.top();
            expression.pop();
            op2 = expression.top();
            expression.pop();
            switch (*token)
            {
            case '+':
                total = op2 + op1;
                expression.push(total);
                break;
            case '-':
                total = op2 - op1;
                expression.push(total);
                break;
            case '*':
                total = op2 * op1;
                expression.push(total);
                break;
            case '/':
                total = op2 / op1;
                expression.push(total);
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    return total;
}

// int main() {
//     char postFixExpression[] = "25 12 7 - 2 * /";
//     double answer1 = postfixEval(postFixExpression);
//     cout << "The answer for expression1 is: " << answer1 << endl;
//     char postFixExpression2[] = "2 3 4 + * 5 *"; //70
//     double answer2 = postfixEval(postFixExpression2);
//     cout << "The answer for expression2 is: " << answer2 << endl;
//     return 0;
// }

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

// Function to calculate based on the operator
int calculate_Sum(int number1, int number2, char operatorChar) {
    switch (operatorChar) {
        case '+': return number1 + number2;
        case '-': return number1 - number2;
        case '*': return number1 * number2;
        case '/':
            if (number2 == 0) {
                printf("Invalid expression\n");
                exit(0);
            }
            return number1 / number2;
        default:
            printf("Invalid expression\n");
            exit(0);
    }
}

// Function to extract numbers from the expression
int check_Numbers(const char *expression, int numbersArray[]) {
    int index = 0, numberIndex = 0;
    while (expression[index] != '\0') {
        if (isspace(expression[index])) {
            index++;
            continue;
        }
        if (isdigit(expression[index])) {
            int value = 0;
            while (isdigit(expression[index])) {
                value = value * 10 + (expression[index] - '0');
                index++;
            }
            numbersArray[numberIndex++] = value;
        } else {
            index++;
        }
    }
    return numberIndex;
}

// Function to extract operators from the expression
int check_Operators(const char *expression, char operatorsArray[]) {
    int index = 0, operatorIndex = 0;
    while (expression[index] != '\0') {
        if (strchr("+-*/", expression[index])) {
            operatorsArray[operatorIndex++] = expression[index];
        }
        index++;
    }
    return operatorIndex;
}

// Function to process multiplication and division
int process_Multiplication_Division(int numbersArray[], int numbersCount, char operatorsArray[], int operatorsCount) {
    int newOperatorsCount = operatorsCount;
    for (int i = 0; i < newOperatorsCount; i++) {
        if (operatorsArray[i] == '*' || operatorsArray[i] == '/') {
            numbersArray[i] = calculate_Sum(numbersArray[i], numbersArray[i + 1], operatorsArray[i]);
            for (int j = i + 1; j < numbersCount - 1; j++) {
                numbersArray[j] = numbersArray[j + 1];
            }
            for (int j = i; j < newOperatorsCount - 1; j++) {
                operatorsArray[j] = operatorsArray[j + 1];
            }
            numbersCount--;
            newOperatorsCount--;
            i--;
        }
    }
    return numbersCount;
}

// Function to process addition and subtraction
int process_Addition_Subtraction(int numbersArray[], int numbersCount, char operatorsArray[], int operatorsCount) {
    for (int i = 0; i < operatorsCount; i++) {
        numbersArray[i + 1] = calculate_Sum(numbersArray[i], numbersArray[i + 1], operatorsArray[i]);
    }
    return numbersArray[operatorsCount];
}

// Function to evaluate the expression
int evaluate_Expression(const char *expression) {
     for (int i = 0; expression[i] != '\0'; i++) {
        if (isalpha(expression[i])) {
            printf("Invalid expression\n");
            exit(0);
        }
    }
    int numbersArray[100];
    char operatorsArray[100];
    int numbersCount = check_Numbers(expression, numbersArray);
    int operatorsCount = check_Operators(expression, operatorsArray);
    numbersCount = process_Multiplication_Division(numbersArray, numbersCount, operatorsArray, operatorsCount);
    return process_Addition_Subtraction(numbersArray, numbersCount, operatorsArray, operatorsCount - (operatorsCount - numbersCount + 1));
}

int main() {
    char userInput[100];
    printf("Enter the Expression below:\n");
    fgets(userInput, sizeof(userInput), stdin);

    int result = evaluate_Expression(userInput);
    printf("The result is %d\n", result);
    return 0;
}

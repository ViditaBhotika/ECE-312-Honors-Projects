#include <iostream>
#include <map>
#include <string>
#include <stack>
#include "Parse.h"
#include <cstring>

using namespace std;

stack<int> operands;

map <string, int> variables;

int add(int one, int two) {
    return one + two;
}

int subtract(int one, int two) {
    return one - two;
}

int multiply(int one, int two) {
    return one * two;
}

int divide(int one, int two) {
    return one/two;
}

int mod(int one, int two) {
    return one%two;
}

int andd(int one, int two) {
    return (one && two);
}

int orr(int one, int two) {
    return (one || two);
}

int lesss(int one, int two) {
    return (one < two);
}

int greaterr(int one, int two) {
    return (one > two);
}

int equals(int one, int two) {
    return (one == two);
}

int notEquals(int one, int two) {
    return (one != two);
}

int lessEquals(int one, int two) {
    return (one <= two);
}

int greaterEquals(int one, int two) {
    return (one >= two);
}

map <string, int(*)(int, int)> operators = {
    {"+", add},
    {"-", subtract},
    {"*", multiply},
    {"/", divide},
    {"%", mod},
    {"&&", andd},
    {"||", orr},
    {"<", lesss},
    {">", greaterr},
    {"==", equals},
    {"!=", notEquals},
    {"<=", lessEquals},
    {">=", greaterEquals}
};

void processExpression() {
    int op1;
    int op2;

    read_next_token();
    char nextToken[128];
    strcpy(nextToken, next_token());
    int nextTokenType = next_token_type;
    int nextTokenValue = 0;
    if (nextTokenType == NUMBER) {
        nextTokenValue = token_number_value;
    }
    peek_next_token();
    char nextNextToken[128];
    strcpy(nextNextToken, next_token());
    if (strcmp(nextNextToken, "text") && strcmp(nextNextToken, "set") && strcmp(nextNextToken, "var") && strcmp(nextNextToken, "output") && strcmp(nextNextToken, "//") && next_token_type != END) {
        processExpression();
    }

    if (nextTokenType == NUMBER) {
        operands.push(nextTokenValue);
    } else if (nextTokenType == NAME) {
        operands.push(variables[nextToken]);
    } else {
        if (strcmp(nextToken, "~") == 0) {
            int result = operands.top() * (-1);
            operands.pop();
            operands.push(result);
        } else if (strcmp(nextToken, "!") == 0) {
            int result = !operands.top();
            operands.pop();
            operands.push(result);
        } else {
            op1 = operands.top();
            operands.pop();
            op2 = operands.top();
            operands.pop();

            operands.push(operators[nextToken](op1, op2));
        }
    }
}

void addVar() {
    read_next_token();
    string varName = next_token();
    if (variables.find(varName) != variables.end()) {
        cout << "variable " << varName << " incorrectly re-initialized" << endl;
    } else {
        variables.insert({varName, 0});
    }
    peek_next_token();
    if (next_token_type == NUMBER) {
        read_next_token();
        variables[varName] = token_number_value;
    } else {
        processExpression();
        variables[varName] = operands.top();
        operands.pop();
    }
    
}

void setVar() {
    read_next_token();
    string varName = next_token();
    if (variables.find(varName) == variables.end()) {
        cout << "variable " << varName << " not declared" << endl;
        variables.insert({varName, 0});
    }

    peek_next_token();
    if (next_token_type == NUMBER) {
        read_next_token();
        variables[varName] = token_number_value;
    } else {
        processExpression();
        variables[varName] = operands.top();
        operands.pop();
    }
}

int run() {
    read_next_token();
    while (next_token_type != END) {
        if ((string)next_token() == "set") {
            setVar();
        }
        else if ((string)next_token() == "var") {
            addVar();
        }else if ((string)next_token() == "text") {
            read_next_token();
            cout << next_token();
        } else if ((string)next_token() == "output") {
            peek_next_token();
            if (next_token_type == NUMBER) {
                read_next_token();
                cout << token_number_value;
            } else {
                processExpression();
                cout << operands.top();
                operands.pop();
            }
        }
        read_next_token();
    };

    return 1;
}

int main() {
    set_input("test_grader.blip");
    run();
    

    return 0;
}


/*template<typename t, typename s> struct element {
    bool isOperation;
    t value;
    int need;
    element<s>* previous;
    element* nextLeft = NULL;
    element* nextRight = NULL;
};

int processInputs() {
    int addedFirstElement = 0; // don't forget to toggle
    int returnVal = 0;
    peek_next_token();
    element<string>* previousPt = NULL;

    if (next_token_type == NUMBER) {
        read_next_token();
        return token_number_value;
    } 
    
    while (next_token_type == SYMBOL || next_token_type == NUMBER) {
        read_next_token();
        if (next_token() == "//") {
            skip_line();
            return returnVal; // make it one of the tree parsing functions
        } 
        
        while (previousPt != NULL) {
            if (previousPt->need == 0) {
                previousPt = previousPt->previous;
            }
        }
        if (previousPt == NULL && addedFirstElement) {
            //go to a tree parsing function
        }
        
        if (next_token_type == SYMBOL) {
            if (next_token() == "!" || next_token() == "~") {
                element<string>* curr = new element<string>{true, next_token(), 1, previousPt, NULL, NULL};
                if (!addedFirstElement) {
                    addedFirstElement = 1;
                }
                previousPt = curr;
            } else {
                element<string>* curr = new element<string>{true, next_token(), 2, previousPt, NULL, NULL};
            }
        } else if (next_token_type == NAME) {
            element<int>* curr = new element<int>{false, variables[next_token()], 0, previousPt, NULL, NULL};
        }

        peek_next_token();
    };
}*/
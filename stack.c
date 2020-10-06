#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct stackNode {
  int data;
  struct stackNode* next;
};

struct stackNode* createNode(int data){
    struct stackNode* newNode = (struct stackNode*)malloc(sizeof(struct stackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void push(struct stackNode** top, int value){
  struct stackNode* newNode = createNode(value);
  newNode->next = *top;
  *top = newNode;
  // printf("%d pushed to stack\n", newNode->data);
}


int isEmpty(struct stackNode* top){
  return top == NULL;
}

void peek(struct stackNode* top){
  if(isEmpty(top)){
    printf("Stack is empty\n");
    return;
  }
  printf("The top value = %d\n", top->data);
}


struct stackNode* pop(struct stackNode** top){
  struct stackNode* temp = *top;
  *top = (*top)->next;
  return temp;
}


struct operators {
  char oper;
  struct operators* next;
};

struct operators* createOpNode(char oper){
    struct operators* newNode = (struct operators*)malloc(sizeof(struct operators));
    newNode->oper = oper;
    newNode->next = NULL;
    return newNode;
}

void pushOp(struct operators** topOp, char oper){
  struct operators* newNode = createOpNode(oper);
  newNode->next = *topOp;
  *topOp = newNode;
}

struct operators* popOp(struct operators** topOp){
    struct operators* temp = *topOp;
    *topOp = (*topOp)->next;
    return temp;
}

char peekOp(struct operators* topOp){
    return topOp->oper;
}

void main(){
  struct stackNode* top = NULL;
  struct stackNode* popNode = NULL;

  struct operators* topOp = NULL;
  struct operators* popOpNode = NULL;

  char infix[100], postfix[100][100], num1[10], oper2;
  int k = 0, j = 0, number, operand1, operand2;

  printf("Enter 1 for stack operation or 2 for infix to postfix: ");
  int oper, oper1, value;
  scanf("%d", &oper);
  while(oper == 1){
    printf("Enter 1, 2, 3 for push, peek or pop: ");
    scanf("%d", &oper1);
    if(oper1 == 1){
      printf("Enter value to be pushed on stack: ");
      scanf("%d", &value);
      push(&top, value);
    }
    else if(oper1 == 2){
      peek(top);
    }
    else if(oper1 == 3){
      if(top != NULL){
        popNode = pop(&top);
        printf("%d was deleted from stack\n", popNode->data);
        free(popNode);
      }
      else{
        printf("Stack is empty\n");
      }
    }
    else{
      printf("Invalid stack operation\n");
    }
    printf("Enter 1 to continue stack operations or 2 for infix to postfix:\n");
    scanf("%d", &oper);
  }
  while(top != NULL){
    pop(&top);
  }// clearing stack

  if(oper == 2){
    printf("Enter equation: ");
    scanf("%s", infix);
    for(int i = 0; i<strlen(infix); i++){
      if(infix[i] == '*' || infix[i] == '/' || infix[i] == '^' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(' || infix[i] == ')'){
        number = atoi(num1);
        k = 0;
        if(number != 0){
          strcpy(postfix[j], num1);
          j++;
          memset(num1,0,strlen(num1));
          push(&top, number);
        }
        if(topOp == NULL){
          pushOp(&topOp, infix[i]);
        }
        else if(infix[i] == '*' || infix[i] == '/'){
          oper2 = peekOp(topOp);
          if(oper2 == '^'){
            popOpNode = popOp(&topOp);
            pushOp(&topOp, infix[i]);
            popNode = pop(&top);
            operand2 = popNode->data;
            popNode = pop(&top);
            operand1 = popNode->data;
            operand1 = pow(operand1, operand2);
            push(&top, operand1);
            postfix[j][0] = oper2;
            j++;
          }
          else{
            pushOp(&topOp, infix[i]);
          }
        }
        else if(infix[i] == '^'){
          pushOp(&topOp, infix[i]);
        }
        else if(infix[i] == '+' || infix[i] == '-'){
          oper2 = peekOp(topOp);
          if(oper2 == '^' || oper2 == '*' || oper2 == '/'){
            popOpNode = popOp(&topOp);
            pushOp(&topOp, infix[i]);
            postfix[j][0] = oper2;
            j++;
            popNode = pop(&top);
            operand2 = popNode->data;
            popNode = pop(&top);
            operand1 = popNode->data;
            if(oper2 == '^'){
              operand1 = pow(operand1, operand2);
              push(&top, operand1);
            }
            else if(oper2=='*'){
              operand1 = operand1 * operand2;
              push(&top, operand1);
            }
            else{
              operand1 = operand1/operand2;
              push(&top, operand1);
            }
          }
          else{
            pushOp(&topOp, infix[i]);
          }
        }
        else if(infix[i] == '('){
          pushOp(&topOp, infix[i]);
        }
        else if(infix[i] == ')'){
          do{
            popOpNode = popOp(&topOp);
            if(popOpNode->oper != '('){
            postfix[j][0] = popOpNode->oper;
            popNode = pop(&top);
            operand2 = popNode->data;
            popNode = pop(&top);
            operand1 = popNode->data;
            if(popOpNode->oper == '+'){
              operand1 = operand1+operand2;
              push(&top, operand1);
            }
            else if(popOpNode->oper == '-'){
              operand1 = operand1-operand2;
              push(&top, operand1);
            }
            else if(popOpNode->oper == '*'){
              operand1 = operand1*operand2;
              push(&top, operand1);
            }
            else if(popOpNode->oper == '/'){
              operand1 = operand1/operand2;
              push(&top, operand1);
            }
            else{
              operand1 = pow(operand1, operand2);
              push(&top, operand1);
            }
            j++;
          }
          }while(popOpNode->oper!='(');
        }
      }
      else if(infix[i] >= '0' && infix[i] <= '9'){
        num1[k] = infix[i];
        k++;
      }
      else{
        printf("Invalid character in equation\n");
      }
    }
    number = atoi(num1);
    if(number!=0){
      strcpy(postfix[j], num1);
      j++;
        push(&top, number);
  }
    while(topOp!=NULL){
      popOpNode = popOp(&topOp);
      popNode = pop(&top);
      operand2 = popNode->data;
      popNode = pop(&top);
      operand1 = popNode->data;
      if(popOpNode->oper == '+'){
        operand1 = operand1+operand2;
        push(&top, operand1);
      }
      else if(popOpNode->oper == '-'){
        operand1 = operand1-operand2;
        push(&top, operand1);
      }
      else if(popOpNode->oper == '*'){
        operand1 = operand1*operand2;
        push(&top, operand1);
      }
      else if(popOpNode->oper == '/'){
        operand1 = operand1/operand2;
        push(&top, operand1);
      }
      else if(popOpNode->oper == '^'){
        operand1 = pow(operand1, operand2);
        push(&top, operand1);
      }
      else if(popOpNode->oper == '(' || popOpNode->oper == ')'){
        continue;
      }
      postfix[j][0] = popOpNode->oper;
      j++;
    }
    printf("The equation is : ");
    for(int i = 0; postfix[i][0] != '\0'; i++){
      printf("%s ", postfix[i]);
    }
    printf("\n");
    while(top != NULL){
      popNode = pop(&top);
      printf("Result = %d\n", popNode->data);
    }
    free(popNode);
  }

}

#include <stdio.h>
#include<stdlib.h>

struct student{
    char name[50];
    int marks;
    int roll_num;
    char division;
    struct student* next;
};

struct student* create_ll(struct student* head, int n){
    struct student* curNode = NULL;
    curNode = (struct student*)malloc(sizeof(struct student));
    head->next = curNode;
    for(int i = 0; i<n; i++){
        printf("Enter name: ");
        fflush(stdout);
        scanf("%s", curNode->name);
        printf("Enter roll number: ");
        fflush(stdout);
        scanf("%d", &curNode->roll_num);
        printf("Enter marks: ");
        fflush(stdout);
        scanf("%d", &curNode->marks);
        printf("Enter division: ");
        fflush(stdout);
        scanf(" %c", &curNode->division);
        if(i == n-1){
            curNode->next = NULL;
            break;
        }
        curNode->next = (struct student*)malloc(sizeof(struct student));
        curNode = curNode->next;
    }
    return head;
}

void display(struct student* head){
    struct student* curNode;
    curNode = (struct student*)malloc(sizeof(struct student));
    curNode = head->next;
    while(curNode != NULL){
        printf("%s\n", curNode->name);
        curNode = curNode->next;
    }
}

// All deleting functions
// Deleting first node
void delBegin(struct student* head, struct student* curNode){
  head->next = curNode->next;
  printf("%s has been deleted\n", curNode->name);
  curNode->next = NULL;
  free(curNode);
}

// Deleting last node
void delEnd(struct student* curNode){
  while(curNode->next->next != NULL){
      curNode = curNode->next;
  }
  printf("%s has been deleted\n", curNode->next->name);
  free(curNode->next->next);
  curNode->next = NULL;
}

// Deleting node with a specific roll number
int delSpecific(struct student* head, struct student* curNode){
  struct student* delNode = NULL;
  delNode = (struct student*)malloc(sizeof(struct student));
  delNode = curNode->next;
  printf("Enter roll number: ");
  fflush(stdout);
  int delroll;
  scanf("%d", &delroll);
  if(curNode->roll_num == delroll){// If roll number is at beginning
    delBegin(head, curNode);
    return 0;
  }
  while(delNode != NULL){
    if(delNode->roll_num == delroll){
      curNode->next = delNode->next;
      delNode->next = NULL;
      printf("%s with roll number %d has been deleted\n", delNode->name, delNode->roll_num);
      free(delNode);
      return 0;
    }
    printf("Okay\n");
    curNode = curNode->next;
    delNode = delNode->next;
  }
  printf("No student with roll number %d exists\n", delroll);
  return 0;
}
// Delete funstions' menu
void delete(struct student* head){
    struct  student* curNode = NULL;
    curNode = (struct student*)malloc(sizeof(struct student));
    curNode = head->next;
    printf("Enter 1, 2 or 3 for  deleting head node, end node or the record of a student with a specific roll number: ");
    fflush(stdout);
    int deloper;
    scanf("%d", &deloper);
    if(deloper == 1){
        delBegin(head, curNode);
    }
    else if(deloper == 2){
        delEnd(curNode);
    }
    else if(deloper == 3){
      delSpecific(head, curNode);
    }
    else{
      printf("Invalid deleting operation\n");
    }
}

// All inserting functions
// Insert at head
void insertHead(struct student* head, struct student* newNode){
  newNode->next = head->next;
  head->next = newNode;
}

// Insert at end
void insertEnd(struct student* curNode, struct student* newNode){
  while(curNode->next != NULL){
    curNode=curNode->next;
  }
  curNode->next = newNode;
  newNode->next = NULL;
}

// Insert after the specified roll number
void insertAfter(struct student* curNode, struct student* newNode){
  int rollAfter;
  printf("Enter roll number after which new student node is to be added: ");
  fflush(stdout);
  scanf("%d", &rollAfter);
  while(curNode->next != NULL){
    if(curNode->roll_num == rollAfter){
      newNode->next = curNode->next;
      curNode->next = newNode;
      return;
    }
    curNode = curNode->next;
  }
  if(curNode->roll_num == rollAfter){
    curNode->next = newNode;
    newNode->next = NULL;
    return;
  }
  else{
    printf("Roll number entered does not exist\n");
  }
}
// Insert functions' menu
void insert(struct student* head){
  struct  student* curNode = NULL;
  curNode = (struct student*)malloc(sizeof(struct student));
  curNode = head->next;
  struct student* newNode;
  newNode = (struct student*)malloc(sizeof(struct student));
  printf("Enter name of new student: ");
  fflush(stdout);
  scanf("%s", newNode->name);
  printf("Enter roll number: ");
  fflush(stdout);
  scanf("%d", &newNode->roll_num);
  printf("Enter marks: ");
  fflush(stdout);
  scanf("%d", &newNode->marks);
  printf("Enter division: ");
  fflush(stdout);
  scanf(" %c", &newNode->division);
  printf("Enter 1, 2, 3 to insert a node at head, end or a position in between: ");
  fflush(stdout);
  int oper;
  scanf("%d", &oper);
  if(oper == 1){
    insertHead(head, newNode);
  }
  else if(oper == 2){
    insertEnd(curNode, newNode);
  }
  else if(oper == 3){
    insertAfter(curNode, newNode);
  }
  else{
    printf("Invalid insert operation\n");
  }
}
// Main functions
int main(){
    struct student* head = NULL;
    head = (struct student*)malloc(sizeof(struct student));
    int n;
    printf("Enter number of nodes: ");
    fflush(stdout);
    scanf("%d", &n);
    head = create_ll(head, n);
    printf("List before operating on it \n");
    fflush(stdout);
    display(head);
    printf("Press I or D to insert or delete :");
    fflush(stdout);
    char operation;
    scanf(" %c", &operation);
    if(operation == 'D'){
        delete(head);
    }
    else if(operation == 'I'){
       insert(head);
    }
    else{
        printf("Invalid operation\n");
    }
    printf("List after operating on it \n");
    fflush(stdout);
    display(head);
    return 0;
}

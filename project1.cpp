#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Node{
    char name[25];
    char pass[25];
    Node *prev, *next;
}*head=NULL,*tail=NULL;


Node *createNode(const char* name,const char* pass){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name,name);
    strcpy(newNode->pass,pass);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void pushHead(const char *name,const char *pass){
    Node *temp = createNode(name, pass);

    if(!head){
        head = tail = temp;
    }
    else{
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail(const char *name, const char *pass){
    Node *temp = createNode(name,pass);

    if(!head){
        head = tail = temp;
    }
    else{
        tail->next=temp;
        temp->prev = tail;
        tail = temp;
    }
}


/*void popHead(){
    if(!head){
        return;
    }
    else if(head== tail){ 
        free(head); 
        head=NULL; 
    }
    else{
        Node *candidateHead = head->next;
        head->next = candidateHead->prev = NULL;
        free(head);
        head = candidateHead;
    }
}*/

/*void popTail(){
    if(!head){
        return;
    }
    else if(head== tail){ 
        free(head); 
        head=NULL; 
    }
    else{
        Node *candidateTail= tail->prev;
        candidateTail->next =tail->prev = NULL;
        free(tail);
        tail = candidateTail; 
    }
}*/


void pushMid(const char* name, const char* pass){
    if(!head){ 
        Node *temp = createNode(name, pass);
        head = tail = temp;
    }
    else if(strcmp(name, head->name) < 0){
        pushHead(name, pass);
    }
    else if(strcmp(name,tail->name)>0){ 
        pushTail(name,pass);
    }
    else{
        Node *curr = head;
        Node *temp = createNode(name,pass);

        while(curr->name < name){
            curr - curr->next; 
        }
        temp->prev = curr->prev;
        temp->next=curr;
        curr->prev=temp;
    }
}

// void popMid(int)
//     if(!head){ 
//     return;
//     }
//     else if(value == head->value){ 
//         popHead();
//     }
//     else if(value ==  tail->value){ 
//         popTail();
//     }       
//  Node *curr = head
//         
//         while(curr && curr->val){
//          
//         //9(head) -><- 10 -><- 13(curr(tail)->
//         curr->prev->next = curr->next
//         curr->next->prev-curr->prev; /
//         curr->prev = curr->next= NULL;// 9(head) -><- 10 -><- 15(tail)->
//         free(curr);
//         curr = NULL;
//  
// }
void mainMenu();
void addFriend(){

}

void userpage(const char *name){
    time_t t;
    time(&t);
    printf("Oo=====================================oO\n");
    printf("Welcome, %s\n", name);
    printf("Oo=====================================oO\n");
    printf("Logged in: %s", ctime(&t));
    printf("\n-----------------------------\n\n");
    printf("[All Friends of %s]\n\n",name);
    printf("-----------------------------\n");
    printf("\t\t>>Menu<<\n");
    printf("-----------------------------\n");
    printf("[1] Add Friend\n[2] Remove Friend\n[3] View Inbox\n[4] View Sent Requestn\n[5] Add, Edit, Announce, Delete Note\n[6] Log out\n");
    printf("-----------------------------\n");
    printf(">> ");
    int menu;
    scanf("%d",&menu);
        switch(menu){
        case 1:{
            addFriend();
            break;
        }
        case 2:{
//            removeFriend();
            break;
        }
        case 3:{
//            viewInbox();
            break;
        }
        case 4:{
//            sentReq();
            break;
        }
        case 5:{
            
            break;
        }
        case 6:{

           break;
        }
    }
}

void registerMenu(){
    printf("Please type in your password[lowecase || 1..24]: ");
    char name[25];
    do{ 
        scanf("%s",&name);
        getchar();       
    }while(strlen(name)<1 || strlen(name)>24);
    printf("Please type in your password[lowecase || 1..24]: ");
    char pass[25];
    do{
       scanf("%s",&pass); 
       getchar();
    }while(strlen(pass)<1 || strlen(pass)>24);
    Node *curr=tail;
    while(curr){
        if(strcmp(name, curr->name) == 0){
            printf("\n--- The username has been used! ---");
            printf("\nPress enter to continue!\n");
            getchar();
            system("cls");
            mainMenu();
        }
        curr=curr->prev; 
    }
    pushMid(name, pass);
    printf("\n");
    printf("--- Registration Successfull ---\n");
    printf("Press enter to continue!");
    getchar();
    system("cls");
    mainMenu();
}

void loginMenu(){
    printf("Username: ");
    char name[25];
    do{ 
        scanf("%s",&name);
        getchar();       
    }while(strlen(name)<1 || strlen(name)>24);
    printf("Password: ");
    char pass[25];
    do{
       scanf("%s",&pass); 
       getchar();
    }while(strlen(pass)<1 || strlen(pass)>24);
    Node *curr=tail;
    while(curr){
        if(strcmp(name, curr->name) == 0 && strcmp(pass, curr->pass) == 0){
            printf("\n--- Login Successfull :) ---");
            printf("\nPress enter to continue!\n");
            getchar();
            userpage(name);
            system("cls");
        }
        curr=curr->prev; 
    }
    printf("Login unsuccessful\n");
    printf("Press enter to continue!");
    getchar();
    mainMenu();
}

void mainMenu(){
    
    time_t t;
    t=clock();

    printf("Oo=====================================oO\n");
    printf("\t\tSTUDY NETWORK\n");
    printf("Oo=====================================oO\n");
    printf("\n");
    printf("[All User]\n");
    printf("No.\tUsername\n");
    Node *curr=head;
    int i=1;
	while(curr){
		printf("%d\t%s\n",i,curr->name);
		i++;
		curr=curr->next;
	} 
    printf("-----------------------------------------\n");
    printf("[1] Register\n");
    printf("[2] Login\n");
    printf("[3] Exit\n");
    printf("-----------------------------------------\n");
    printf("Press 0 and enter to abort an operation\n");
    printf("-----------------------------------------\n");
    printf(">> ");
    int menu;
    scanf("%d",&menu);
    switch(menu){
        case 0:{
            return;
            break;
        }
        case 1:{
            registerMenu();
            break;
        }
       case 2:{
           loginMenu();
           break;
       }
       case 3:{   
           t = clock()-t;
           double time_taken = ((double)t)/CLOCKS_PER_SEC;
           printf("\nTime spent %.2lf seconds\n",time_taken);
           return;
           break;
       }
    }
}

int main(){
    mainMenu();
    return 0;
}
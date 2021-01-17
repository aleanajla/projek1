#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Node{
    char name[25];
    char pass[25];
    Node *prev, *next;
    Node *fsentprev,*fsentnext,*fsenttail;
}*head,*tail;

Node *now,*pantat;

Node *createNode(const char* name,const char* pass){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name,name);
    strcpy(newNode->pass,pass);
    newNode->prev = newNode->next = NULL;
    newNode->fsentnext = newNode->fsentprev =NULL;
    return newNode;
}

void pushSent(const char *name,const char *flag){
	Node *temp= createNode(name,flag);
	pantat->fsentnext=temp;
    temp->fsentprev = pantat;
    pantat = temp;

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

void popHead(){
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
}

void popTail(){
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
}


//void popMid(int){
//	if(!head){
//    	return;
//    }
//    else if(value == head->value){
//        popHead();
//    }
//    else if(value ==  tail->value){
//        popTail();
//    }
//  	Node *curr = head
//    while(curr && curr->val){
//		curr->prev->next = curr->next
//        curr->next->prev-curr->prev; /
//        curr->prev = curr->next= NULL;
//        free(curr);
//        curr = NULL;
//	}
//}

void registerMenu();
void loginMenu();
void userpage();
void addFriend();
void removeFriend();
void viewInbox();
void viewsentReq();
void addNote();

char username[25];

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
    Node *curr=head;
    while(curr){
        if(strcmp(name, curr->name) == 0){
            printf("\n--- The username has been used! ---");
            printf("\nPress enter to continue!\n");
            getchar();
            system("cls");
            mainMenu();
        }
        curr=curr->next;
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
            //initiliaze
            now=curr;
            strcpy(username,name);
            now->fsenttail=now;

            getchar();
            system("cls");

            userpage();
        }
        curr=curr->prev;
    }
    printf("Login unsuccessful\n");
    printf("Press enter to continue!");
    getchar();
    system("cls");
    mainMenu();
}

void userpage(){
    time_t t;
    time(&t);
    printf("Oo=====================================oO\n");
    printf("Welcome, %s\n", username);
    printf("Oo=====================================oO\n");
    printf("Logged in: %s", ctime(&t));
    printf("\n-----------------------------\n\n");
    printf("[All Friends of %s]\n\n",username);
    printf("No.\tUsername\n");
    printf("-----------------------------\n");
    printf("\t>>Menu<<\n");
    printf("-----------------------------\n");
    printf("[1] Add Friend\n[2] Remove Friend\n[3] View Inbox\n[4] View Sent Request\n[5] Add, Edit, Announce, Delete Note\n[6] Log out\n");
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
            removeFriend();
            break;
        }
        case 3:{
            viewInbox();
            break;
        }
        case 4:{
            viewsentReq();
            userpage();
            break;
        }
        case 5:{
            addNote();
            break;
        }
        case 6:{
			system("cls");
			mainMenu();
        	break;
        }
    }
}

void addFriend(){
    printf("-----------------------------\n\n");
    printf("[All User]\n");
    printf("No.\tUsername\n");
	Node *curr=head;
    int i=1;
	while(curr){
		if(strcmp(curr->name,username)!=0){
			printf("%d\t%s\n",i,curr->name);
			i++;
		}
		curr=curr->next;
	}

	printf("\n\n");
	printf("Which user do you want to add?\n");
	printf(">> ");
	char fname[25];
	scanf("%s",fname);
	getchar();
	Node *curr1=head;
	while(curr1){
        if(strcmp(fname, curr1->name) == 0){
            printf("\n-- Your request has been sent to %s --",fname);
            printf("\nPress enter to continue!\n");

            pantat=now->fsenttail;
			pushSent(fname,"0");
			now->fsenttail=pantat;

            getchar();
            system("cls");
            userpage();
        }
        curr1=curr1->next;
    }


    printf("-- there is no data in database --\n");
	printf("Press enter continue!");
	getchar();
	system("cls");
    userpage();

}

void removeFriend(){
    printf("-----------------------------\n\n");
    printf("[All Friends of %s]\n",username);
    printf("No.\tUsername\n");
	Node *curr=head;
    int i=1;
	while(curr){
		if(strcmp(curr->name,username)!=0){
			printf("%d\t%s\n",i,curr->name);
			i++;
		}
		curr=curr->next;
	}

	printf("\n\n");
	printf("Which user do you want to remove?\n");
	printf(">> ");
	char fname[25];
	scanf("%s",fname);
	getchar();
	Node *curr1=head;
	while(curr1){
        if(strcmp(fname, curr1->name) == 0){
            printf("\n-- You are no longer friends with %s --",fname);
            printf("\nPress enter to continue!\n");

            pantat=now->fsenttail;
			pushSent(fname,"0");
			now->fsenttail=pantat;

            getchar();
            system("cls");
            userpage();
        }
        curr1=curr1->next;
    }


    printf("-- there is no data in database --\n");
	printf("Press enter continue!");
	getchar();
	system("cls");
    userpage();
}

void viewInbox(){
    printf("-----------------------------\n\n");
    printf("[All Friend Requests of %s]\n",username);
    printf("No.\tUsername\n");
	Node *curr=head;
    int i=1;
	while(curr){
		if(strcmp(curr->name,username)!=0){
			printf("%d\t%s\n",i,curr->name);
			i++;
		}
		curr=curr->next;
	}

	printf("\n\n");
	printf("Which user do you want to be accepted?\n");
	printf(">> ");
	char fname[25];
	scanf("%s",fname);
	getchar();
	Node *curr1=head;
	while(curr1){
        if(strcmp(fname, curr1->name) == 0){
            printf("\n-- You accepted the request from %s --",fname);
            printf("\nPress enter to continue!\n");

            pantat=now->fsenttail;
			pushSent(fname,"0");
			now->fsenttail=pantat;

            getchar();
            system("cls");
            userpage();
        }
        curr1=curr1->next;
    }


    printf("-- there is no data in database --\n");
	printf("Press enter continue!");
	getchar();
	system("cls");
    userpage();
}

void viewsentReq(){
	printf("-----------------------------\n\n");
	printf("[Sent Request]\n");
	printf("No.\tUsername\n");
	Node *curr=now;
	curr=curr->fsentnext;
	int i=1;
	while(curr){
		printf("%d\t%s\n",i,curr->name);
        i++;
		curr=curr->fsentnext;
	}
	printf("press enter to continue!");
    getchar();
    system("cls");

}

void addNote(){

}


int main(){
    mainMenu();
    return 0;
}

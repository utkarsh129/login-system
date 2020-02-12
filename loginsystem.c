/*
*
*     Government portal using linked list implementation of simple queue
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

//structure to store user data
struct node
{
	char firstname[30];
	char fathername[30];
	char lastname[30];
	int age;
	float income;
	struct node *link;
}*front=NULL,*rear=NULL;

//Functions related to user
void user();
void userlogin(char key[],char key2[]);
void usersignup();
void userstatus();
//Functions related to queue
void adduser();
void verify();
int isEmpty();
void showdatabase();
void firstuser();
//database functions
void importdatabase();
void exportdatabase();
//Functions related to admin profile
void adminpage();
void adminlogin(char key[],char key2[]);
void adminmodify();
void admin();

int i;
char str[20];

//Operations on queue
void adduser()           //Enqueue
{
	struct node *n, *ptr;
	n =(struct node*)malloc(sizeof(struct node));

	printf("\n----------------------------------------------------------------------------\n");
	printf("\n-----------------------------REGISTRATION-----------------------------------\n");
	printf("\n----------------------------------------------------------------------------\n");

	printf("\t\tEnter your first name\n");
	scanf("%s",n->firstname);
	printf("\t\tEnter your father's name\n");
	scanf("%s",n->fathername);
	printf("\t\tEnter your last name\n");
	scanf("%s",n->lastname);
	printf("\t\tEnter your age\n");
	scanf("%d",&(n->age));
	printf("\t\tEnter your annual income\n");
	scanf("%f",&(n->income));

	n->link = NULL;
	if(isEmpty() == 1 )
	{
		FILE *fp = fopen("Database.txt","w");
		front = n;
		rear = n;
		fprintf(fp,"%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",n->firstname,n->fathername,n->lastname,n->age,n->income);
		fclose(fp);
	}
	else
	{
		FILE *fp = fopen("Database.txt","a");
		ptr = rear;
		ptr->link = n;
		rear = n;
		fprintf(fp,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",n->firstname,n->fathername,n->lastname,n->age,n->income);
		fclose(fp);
	}
}

void verify()            //Dequeue
{
	int ch;
	struct node *ptr;

	if(isEmpty()==1)
	{
		system("CLS");
		printf("Database is empty\n\n");
		return ;
	}

	do
	{
	system("CLS");
	firstuser();
	printf("\n\n\t\t Verify the data and choose from the following \n");
	printf("\t\t1. Approve the application\n\n");
	printf("\t\t2. Reject the application\n\n");
	printf("\t\t3. Exit\n\n");
	scanf("%d",&ch);

	switch(ch)
	{
	case 1://approve
		;    //an empty statement since declaration is not allowed here

	//sending the approved application to Approved.txt
	FILE *fp = fopen("Approved.txt","a");
	if(front == rear)
	{
		ptr = front;
		fprintf(fp,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		front = NULL;
		rear = NULL;
	}
	else
	{
		ptr = front;
		fprintf(fp,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		front = ptr->link;
	}
	//Rearranging the database
	FILE *fp2 = fopen("Database.txt","w");
	ptr = front;
	while(ptr!=NULL)
	{
		fprintf(fp2,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		ptr=ptr->link;
	}
	break;

	case 2://reject
	//deleting the application
	if(front == rear)
	{
		front = NULL;
		rear = NULL;
	}
	else
	{
		ptr = front;
		front = ptr->link;
	}
	//Rearranging the database
	FILE *fp3 = fopen("Database.txt","w");
	ptr = front;
	while(ptr!=NULL)
	{
		fprintf(fp3,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		ptr=ptr->link;
	}
	break;

	default:
		printf("Enter a valid choice\n\n");
	}
	}while(ch<3);

}

void showdatabase()		 //Traversal
{
	struct node *ptr;
	ptr = front;
	if(isEmpty() == 1)
	{
		printf("Empty Database\n");
	}
	else
	{
	printf("--------------------------------------------------------------------------");
	printf("\n\t\t\t\tREGISTERED USERS\t\t\t\n");
	printf("--------------------------------------------------------------------------");
	printf("\n|FIRST NAME\t|FATHER's NAME\t|LAST NAME\t|AGE\t\t|INCOME      \n");

	while(ptr!=NULL)
	{
		printf("|%s\t\t|%s\t\t|%s\t\t|%d\t\t|%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		ptr= ptr->link;
	}
	}
}

void firstuser()     //peek
{
	struct node *ptr;
	ptr = front;
	printf("--------------------------------------------------------------------------\n");
	printf("\n|FIRST NAME\t|FATHER's NAME\t|LAST NAME\t|AGE\t\t|INCOME      \n");
	printf("--------------------------------------------------------------------------\n");
    printf("|%s\t\t|%s\t\t|%s\t\t|%d\t\t|%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
	printf("--------------------------------------------------------------------------\n");

}

int isEmpty()
{
	if(front == NULL)
		return 1;
	else
		return 0;
}

//Database functions
void exportdatabase()
{
	struct node *ptr;
	FILE *fp=fopen("Backup.txt","w");
	ptr = front;
	if(ptr == NULL)
	{
		printf("\t\tNo data is available to export\n");
		return;
	}
	while(ptr!=NULL)
	{
		fprintf(fp,"\n%s\t\t%s\t\t%s\t\t%d\t\t%.2f\n",ptr->firstname,ptr->fathername,ptr->lastname,ptr->age,ptr->income);
		ptr= ptr->link;
	}
	fclose(fp);
	printf("\t\tDone! Backup Taken.\n\n");
}

void importdatabase()
{
	struct node *n, *ptr;
	n =(struct node*)malloc(sizeof(struct node));
	FILE *fp = fopen("Backup.txt","r");

	n->link = NULL;
	while(!feof(fp))
	{
	if(front == NULL)
	{
		front = n;
		rear = n;
		fscanf(fp,"\n%s%s%s%d%f\n",n->firstname,n->fathername,n->lastname,&(n->age),&(n->income));
	}
	else
	{
		ptr = (struct node*)malloc(sizeof(struct node));
		n -> link = ptr;
		fscanf(fp,"%s%s%s%d%f\n",ptr->firstname,ptr->fathername,ptr->lastname,&(ptr->age),&(ptr->income));

		rear = ptr ;
		n = ptr;

	}
	}
	printf("\t\tDone! Successfully imported data.\n");
	fclose(fp);
}

//Admin functions
/*
void admin()
{
	int choice;
	char key[20],key2[20];
	printf("\n----------------------------------------------------------------------------\n");
	printf("                          	 Welcome       "                        	 			);
	printf("\n----------------------------------------------------------------------------\n");

		printf("--------------------------------------------------------------------------");
		printf("\n\t\t\t\t1.Login\n\n\t\t\t\t0.Exit\n\n");
		printf("--------------------------------------------------------------------------");
		printf("\nEnter your choice\n\n");
		scanf("%d",&choice);

		if(choice==1)
		{
		system("CLS");
		printf("\n----------------------------------------------------------------------------\n");
	    printf("\n-------------------------ADMIN  LOGIN--------------------------------------\n");
		printf("\n----------------------------------------------------------------------------\n");
				printf("Enter your user id\n\n");
				scanf("%s",key);
				printf("Enter password\n\n");
				i = 0;
				while (i<=9)
                    {
                    str[i]=_getch();
                    if(str[i]==13)
						break;
                    else if(str[i]== '\b')
                    	printf("\b \b");

                    else
						printf("*");
                    i++;
                    }
                    str[i]='\0';

				strcpy(key2,str);
				adminlogin(key,key2);
		}
		else if(choice==0)
			return;
}*/

void adminlogin(char key[],char key2[])
{
	FILE *fp = fopen("Admin.txt","r");
	char adminname2[20];
	char adminpass2[20];
	int flag,flag2;

	fscanf(fp,"%s%s",adminname2,adminpass2);

	flag = strcmp(adminname2,key);
	if(flag == 0)
	{
		flag2=strcmp(adminpass2,key2);
		if(flag2 == 0)
		{
			printf("\t\tLog in successful\n");
			adminpage();
		}
		else
		{
			printf("\t\tWrong Login Details\n");
		}

	}
	else
		{
			printf("\t\tWrong Login Details\n");
		}
		fclose(fp);

}
void adminpage()
{
	system("CLS");
	int choice;
	//int state;
	   printf("\n----------------------------------------------------------------------------\n");
       printf("\n-----------------------------------ADMIN------------------------------------\n");
       printf("\n----------------------------------------------------------------------------\n");
	do
	{
		printf("\n\t\t\t\t1.Registered Users\n\n\t\t\t\t2.Approve applications\n\n\t\t\t\t"
				"3.Change username & password\n\n\t\t\t\t4.Export Database\n\n\t\t\t\t"
				"5.Import Database\n\n\t\t\t\t6.Main Menu\n\n");
		printf("\nEnter your choice\n\n");
		scanf("%d",&choice);

			switch(choice)
			{
			case 1:
				system("CLS");
			    showdatabase();
				break;
			case 2:
				system("CLS");
				verify();
				break;
			case 3:
				system("CLS");
				adminmodify();
				break;
			case 4:
				system("CLS");
				exportdatabase();
				break;
			case 5:
				system("CLS");
				importdatabase();
				break;
			case 6:
				system("CLS");
				return;
			default:
				system("CLS");
				printf("Enter a valid choice\n");
			}
	}while(choice<7);
}

void adminmodify()
{
	FILE *fp = fopen("Admin.txt","w");    //previous data will be deleted.
	char adminname[20];
	char adminpass[20];

	printf("\n----------------------------------------------------------------------------\n");
	printf("\n-----------------------------MODIFY LOGIN DETAILs---------------------------\n");
	printf("\n----------------------------------------------------------------------------\n");
	printf("\t\t Enter your new admin name\n\n");
	scanf("%s",adminname);
	printf("\t\t Enter new password\n\n");
	i = 0;
				while (i<=9)
                    {
                    str[i]=_getch();
                    if(str[i]==13)
						break;
                    else if(str[i]== '\b')
                    	printf("\b \b");

                    else
						printf("*");
                    i++;
                    }
                    str[i]='\0';
                    strcpy(adminpass,str);

	fprintf(fp,"%s\t\t%s",adminname,adminpass);
	printf("\n\n Your new login details has been modified successfully\n");
	fclose(fp);
}
//User functions
void user()
{
	int choice;
	char key[20],key2[20];

	printf("\n----------------------------------------------------------------------------\n");
	printf("                          	 Welcome       "                        	 		 );
	printf("\n----------------------------------------------------------------------------\n");

	do
	{
		printf("--------------------------------------------------------------------------");
		printf("\n\t\t\t\t1.New Applicant Registration\n\n\t\t\t\t2.Applicant Login\n\n\t\t\t\t0.Main Menu\n\n");
		printf("--------------------------------------------------------------------------");
		printf("\nEnter your choice\n\n");
		scanf("%d",&choice);

			switch(choice)
			{
				case 1:
				system("CLS");
				usersignup();
				system("CLS");
				adduser();
				system("CLS");
				printf("Registration has been done successfully\n");
				break;

				case 2:
				system("CLS");
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n---------------------------APPLICANT LOG IN---------------------------------\n");
				printf("\n----------------------------------------------------------------------------\n");
				printf("\t\tEnter your username\n\n");
				scanf("%s",key);
				printf("\t\tEnter password\n\n");
				i = 0;
				while (i<=9)
                    {
                    str[i]=_getch();
                    if(str[i]==13)
						break;
                    else if(str[i]== '\b')
                    	printf("\b \b");

                    else
						printf("*");
                    i++;
                    }
                    str[i]='\0';

				strcpy(key2,str);
				userlogin(key,key2);
				break;

				case 0:
					system("CLS");
					break;

				default:
				system("CLS");
				printf("Enter a valid choice\n");
			}
		}while(choice!=0);
}

void usersignup()
{
	FILE *fp = fopen("User.txt","a+");
	char userid[20];
	int flag;

	    printf("\n----------------------------------------------------------------------------\n");
	    printf("\n-------------------------NEW APPLICANT REGISTRATION-------------------------\n");
		printf("\n----------------------------------------------------------------------------\n");

		here:
		fseek(fp, 0 , SEEK_SET);       //fp is passed to starting position of file.
		printf("\n\n\t\t Choose a user name\n\n");
		scanf("%s",userid);
		char username2[20];
		char userpass2[20];

		//check if the entered username is already taken or not
		while(fscanf(fp,"%s%s\n",username2,userpass2)!=EOF)
		{
			flag = strcmp(username2,userid);
			if(flag == 0)
			{
				printf("This username is not available! Choose a different username\n");
				goto here;
			}
		}

		printf("\n\n Create a password\n\n");

		//to mask password
		i = 0;
				while (i<=9)
                    {
                    str[i]=_getch();
                    if(str[i]==13)
						break;
                    else if(str[i]== '\b')
                    	printf("\b \b");

                    else
						printf("*");
                    i++;
                    }
                    str[i]='\0';
		strcpy(userpass2,str);

		fprintf(fp,"\n%s\t\t%s\n",userid,userpass2);
		printf("\n\n Your account has been created\n");
		fclose(fp);
}

void userlogin(char key[],char key2[])
{
	FILE *fp = fopen("User.txt","r");
	char username2[20];
	char userpass2[20];
	int flag,flag2;

		while(fscanf(fp,"%s%s\n",username2,userpass2)!=EOF)
		{
			flag = strcmp(username2,key);
			if(flag == 0)
			{
				flag2=strcmp(userpass2,key2);
				if(flag2 == 0)
				{
					printf("\t\tLogged in successfully\n");
					userstatus();
					break;
				}
				else
				{
					system("CLS");
					printf("\t\tYou have entered a wrong Password\n");

					break;
				}
			}
		}
		if(flag!=0)
		{
			printf("\t\tThis username does not exist\n");
			return;
		}
		fclose(fp);
}

void userstatus()     //to check whether the application was approved or rejected
{
	system("CLS");
	int flag,flag2,status;
	char fname2[30],lname2[30],fname[30],lname[30],mname[30];

	int age;
	float income;
	printf("\n----------------------------------------------------------------------------\n");
	printf("\n-----------------------------APPLICATION STATUS-----------------------------\n");
	printf("\n----------------------------------------------------------------------------\n");
	//case sensitive
	printf("\n\t\t Enter your first name\n");
	scanf("%s",fname2);
	printf("\n\t\t Enter your last name\n");
	scanf("%s",lname2);

	//Searching the entered data in Database
	FILE *fp = fopen("Database.txt","r");
	while(fscanf(fp,"\n%s%s%s%d%f\n",fname,mname,lname,&age,&income)!=EOF)
		{
			flag = strcmp(fname,fname2);
			if(flag == 0)
			{
				flag2=strcmp(lname,lname2);
				if(flag2 == 0)
				{
					printf("\n\t\tYour application for income certificate is in process.\n\n");
		            return;
				}
			}
		}
	//If the data is not in database then search it in approved.txt
	FILE *fpt = fopen("Approved.txt","r");
	while(fscanf(fpt,"\n%s%s%s%d%f\n",fname,mname,lname,&age,&income)!=EOF)
		{
			flag = strcmp(fname,fname2);
			if(flag == 0)
			{
				flag2=strcmp(lname,lname2);
				if(flag2 == 0)
				{
					printf("\n\t\tYour application has been approved.\n\n");
					printf("\n\t\tYou can collect your income certificate.\n\n");

					status = 1;
					break;
				}
			}
		}
	if(status !=1 )    //i.e. the data is neither in database.txt nor in approved.txt
	{
		printf("\n\t\tYour application for income certificate is rejected.\n\t\tYou can re-apply.\n\n");
		printf("\t\t\t\tOR\n\n");
		printf("\t\tPlease check your input details\n ");
	}
}
//************************************************
int main()
{
	system("color f0");
	int choice;
	char key[20];
	char key2[20];
	do
	{
		printf("**************************************************************************\n");
		printf("--------------------------------------------------------------------------\n");
		printf("---------------------   GOVERNMENT OF MAHARASHTRA    ---------------------\n");
		printf("--------------------------------------------------------------------------\n");
		printf("**************************************************************************\n");
		printf("\t Log in as:\n\n");
		printf("\n\t\t\t\t1.User\n\n\t\t\t\t2.Admin\n\n\t\t\t\t0.Exit\n\n");
		printf("--------------------------------------------------------------------------");
		printf("\nEnter your choice\n\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				system("CLS");
				user();
				break;

			case 2:
				system("CLS");
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n------------------------------LOG IN----------------------------------------\n");
				printf("\n----------------------------------------------------------------------------\n");

				printf("\t\tEnter your username\n\n");
				scanf("%s",key);
				printf("\t\tEnter password\n\n");
				i = 0;
				while (i<=9)
				{
                    str[i]=_getch();
                    if(str[i]==13)
						break;
                    else if(str[i]== '\b')
                    	printf("\b \b");

                    else
						printf("*");
                    i++;
				}
				str[i]='\0';

				strcpy(key2,str);
				adminlogin(key,key2);
				break;

			case 0:
				printf("\n");
				break;
			default:
				system("CLS");
				printf("Enter a valid choice");
		}
	}while(choice!=0);
    return 0;
}


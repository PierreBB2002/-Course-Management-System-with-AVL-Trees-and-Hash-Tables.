/*
Pierre Backleh
1201296
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 800
typedef struct AVLnode *AVLNode;
#define TABLE_SIZE 20
FILE *out;
FILE *out1;
//AVL Tree
struct AVLnode
{
    char course_name[100];
    int c_hours;
    char c_code[10];
    char department[100];
    char sub[1000];
    AVLNode Left;
    AVLNode Right;
    int Height;
};
// Course structure
typedef struct Course
{
    char course_name[100];
    int c_hours;
    char c_code[10];
    char department[100];
    char sub[1000];
} Course;
Course *hash_table_1[TABLE_SIZE];
Course *hash_table_2[TABLE_SIZE];
//to find the greater value between two values
int Max( int Lhs, int Rhs)
{
    if (Lhs>Rhs)
        return Lhs;
    else
        return Rhs;
}
//to find the smaller value between two values
AVLNode FindMin(AVLNode T)
{
    AVLNode current= T;
    while (current->Left != NULL)
        current = current->Left;

    return current;
}
//To make the AVL tree empty
AVLNode MakeEmpty(AVLNode T)
{
    if(T!=NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}
//To calculate the hight of the tree
int height(AVLNode N)
{
    if (N == NULL)
        return 0;
    return N->Height;
}

AVLNode SingleRotateLeft(AVLNode K2)
{
    AVLNode K1;

    K1=K2->Left;
    K2->Left=K1->Right;
    K1->Right= K2;

    K2->Height= Max(height(K2->Left), height(K2->Right))+1;
    K1->Height= Max(height(K1->Left), K2->Height)+1;

    return K1;
}
AVLNode SingleRotateRight(AVLNode K1)
{
    AVLNode K2;

    K2=K1->Right;
    K1->Right=K2->Left;
    K2->Left= K1;

    K1->Height= Max(height(K1->Left), height(K1->Right))+1;
    K2->Height= Max(height(K2->Right), K1->Height)+1;

    return K2;
}
AVLNode DoubleRotateLeft(AVLNode K3)
{
    K3->Left =SingleRotateRight(K3->Left);
    return SingleRotateLeft(K3);
}

AVLNode DoubleRotateRight(AVLNode K1)
{
    K1->Right =SingleRotateLeft(K1->Right);
    return SingleRotateRight(K1);
}
//To insert a new node to the AVL Tree
AVLNode Insert(char N[100],int G,char AD[50],char BD[50],char ILL[100],AVLNode T)
{
    if(T==NULL)
    {
        T= malloc(sizeof (struct AVLnode));
        if(T==NULL)
            printf("Out of space!\n");
        else
        {
            strcpy(T->course_name, N);
            T->c_hours=G;
            strcpy(T->c_code, AD);
            strcpy(T->department, BD);
            strcpy(T->sub, ILL);
            T->Height=0;
            T->Left =T->Right= NULL;
        }
    }
    else if(strcmp(N, T->c_code)<0)
    {
        T->Left= Insert(N, G, AD, BD, ILL, T->Left);
        if (height(T->Left)- height(T->Right)==2)
            if(strcmp(N,T->Left->c_code)<0)
                T= SingleRotateLeft(T);
            else
                T=DoubleRotateLeft(T);
    }
    else if (strcmp(N, T->c_code)>0)
    {
        T->Right= Insert(N, G, AD, BD, ILL, T->Right);
        if(height(T->Right)- height(T->Left)==2)
            if (strcmp(N, T->Right->c_code)>0)
                T= SingleRotateRight(T);
            else
                T= DoubleRotateRight(T);
    }
    T->Height= Max(height(T->Left), height(T->Right))+1;
    return T;
}
AVLNode InsertDep(char N[100],int G,char AD[50],char BD[50],char ILL[100],AVLNode T)
{
    if(T==NULL)
    {
        T= malloc(sizeof (struct AVLnode));
        if(T==NULL)
            printf("Out of space!\n");
        else
        {
            strcpy(T->course_name, N);
            T->c_hours=G;
            strcpy(T->c_code, AD);
            strcpy(T->department, BD);
            strcpy(T->sub, ILL);
            T->Height=0;
            T->Left =T->Right= NULL;
        }
    }
    else if(strcmp(N, T->department)<0)
    {
        T->Left= Insert(N, G, AD, BD, ILL, T->Left);
        if (height(T->Left)- height(T->Right)==2)
            if(strcmp(N,T->Left->department)<0)
                T= SingleRotateLeft(T);
            else
                T=DoubleRotateLeft(T);
    }
    else if (strcmp(N, T->department)>0)
    {
        T->Right= Insert(N, G, AD, BD, ILL, T->Right);
        if(height(T->Right)- height(T->Left)==2)
            if (strcmp(N, T->Right->department)>0)
                T= SingleRotateRight(T);
            else
                T= DoubleRotateRight(T);
    }
    T->Height= Max(height(T->Left), height(T->Right))+1;
    return T;
}
//Left - Root - Right
void PrintInOrder(AVLNode t, int p)
{
    if(t!=NULL)
    {
        if(p==0)
        {
            PrintInOrder(t->Left, 0);
            printf("%-30s   %-10d   %-30s   %-25s \n", t->course_name, t->c_hours, t->c_code,t->department);
            printf("Subjects: %s\n\n",t->sub);
            PrintInOrder(t->Right, 0);
        }
        else
        {
            PrintInOrder(t->Left, 1);
            fprintf(out,"%-30s   %-10d   %-30s   %-25s \n", t->course_name, t->c_hours, t->c_code,t->department);
            fprintf(out,"Subjects: %s\n\n",t->sub);
            PrintInOrder(t->Right, 1);
        }
    }
}
//To find a specific node in the tree
AVLNode Find (char *X, AVLNode T)
{
    if (T!=NULL)
    {
        if (strcmp(X,T->c_code)<0)
            return Find(X, T->Left);

        else if(strcmp(X,T->c_code)>0)
            return Find(X, T->Right);

        else
        {
            if (strcmp(X,T->c_code)==0)
            {
                printf("Course Name: %s\n", T->course_name);
                printf("Credit Hours: %d\n", T->c_hours);
                printf("Course Code: %s\n", T->c_code);
                printf("Department: %s\n", T->department);
                printf("Subjects: %s\n", T->sub);
                return T;
            }
        }
    }
    return T;

}
//to calculate the balance in the AVL Tree
int getBalance(AVLNode T)
{
    if (T == NULL)
        return 0;
    return height(T->Left) - height(T->Right);
}
AVLNode RightRotation(AVLNode y)
{
    AVLNode x = y->Left;
    AVLNode T2 = x->Right;

    x->Right = y;
    y->Left = T2;

    y->Height = Max(height(y->Left), height(y->Right)) + 1;
    x->Height = Max(height(x->Left), height(x->Right)) + 1;

    return x;
}

AVLNode LeftRotation(AVLNode x)
{
    AVLNode y = x->Right;
    AVLNode T2 = y->Left;

    y->Left = x;
    x->Right = T2;

    x->Height = Max(height(x->Left), height(x->Right)) + 1;
    y->Height = Max(height(y->Left), height(y->Right)) + 1;

    return y;
}
//To delete a node from the tree
AVLNode Delete(char key[100], AVLNode T)
{
    if (T == NULL)
        return T;

    if ( strcmp(key, T->c_code )<0)
        T->Left = Delete(key, T->Left);

    else if( strcmp(key, T->c_code)>0)
        T->Right = Delete(key, T->Right);

    else
    {
        if( (T->Left == NULL) || (T->Right == NULL) )
        {
            AVLNode temp = T->Left ? T->Left : T->Right;

            if (temp == NULL)
            {
                temp = T;
                T = NULL;
            }
            else
                *T = *temp;
            free(temp);
        }
        else
        {
            AVLNode temp = FindMin(T->Right);

            strcpy(T->c_code, temp->c_code ) ;

            T->Right = Delete(temp->c_code, T->Right );
        }
    }

    if (T == NULL)
        return T;

    T->Height = 1 + Max(height(T->Left),height(T->Right));

    int balance = getBalance(T);

    if (balance > 1 && getBalance(T->Left) >= 0)
        return RightRotation(T);

    if (balance > 1 && getBalance(T->Left) < 0)
    {
        T->Left =  LeftRotation(T->Left);
        return RightRotation(T);
    }

    if (balance < -1 && getBalance(T->Right) <= 0)
        return LeftRotation(T);

    if (balance < -1 && getBalance(T->Right) > 0)
    {
        T->Right = RightRotation(T->Right);
        return LeftRotation(T);
    }
    return T;
}
//To delete a specific node in the tree according to the department of the course
AVLNode DeleteChar(char key[100], AVLNode T)
{
    if (T == NULL)
        return T;

    if ( strcmp(key, T->department )<0)
        T->Left = Delete(key, T->Left);

    else if( strcmp(key, T->department)>0)
        T->Right = Delete(key, T->Right);

    else
    {
        if( (T->Left == NULL) || (T->Right == NULL) )
        {
            AVLNode temp = T->Left ? T->Left : T->Right;

            if (temp == NULL)
            {
                temp = T;
                T = NULL;
            }
            else
                *T = *temp;
            free(temp);
        }
        else
        {
            AVLNode temp = FindMin(T->Right);

            strcpy(T->department, temp->department ) ;

            T->Right = Delete(temp->department, T->Right );
        }
    }

    if (T == NULL)
        return T;

    T->Height = 1 + Max(height(T->Left),height(T->Right));

    int balance = getBalance(T);

    if (balance > 1 && getBalance(T->Left) >= 0)
        return RightRotation(T);

    if (balance > 1 && getBalance(T->Left) < 0)
    {
        T->Left =  LeftRotation(T->Left);
        return RightRotation(T);
    }

    if (balance < -1 && getBalance(T->Right) <= 0)
        return LeftRotation(T);

    if (balance < -1 && getBalance(T->Right) > 0)
    {
        T->Right = RightRotation(T->Right);
        return LeftRotation(T);
    }
    return T;
}
AVLNode FindCourse(char *c, AVLNode T,int ch)
{
    if(T!=NULL)
    {
        if (strcmp(c,T->c_code)<0)
            return FindCourse(c, T->Left,ch);

        else if(strcmp(c,T->c_code)>0)
            return FindCourse(c, T->Right,ch);

        else
        {
            if (strcmp(c,T->c_code)==0)
            {
                printf("Subjects: %s\n", T->sub);
                return T;
            }
        }
    }
    else
    {
        printf("Course is not found!!\n");
        ch=1000;
    }
    return T;
}
//To find a node that contains a specific course that belong to a specific department
AVLNode FindDep(char *c, AVLNode T)
{
    if(T!=NULL)
    {
        if (strcmp(c,T->department)<0)
            return FindDep(c, T->Left);

        else if(strcmp(c,T->department)>0)
            return FindDep(c, T->Right);

        else
        {
            if (strcmp(c,T->department)==0)
            {
                PrintInOrder(T,0);
                return T;
            }
        }
    }
    else
        printf("Department is not found!!\n");
    return T;
}
//To find the first character from the string
char getFirstChar(char word[])
{
    return word[0];
}
//this function is to delete an index from array
void deleteFromArray(Course P[], int pos, int size)
{
    int i;
    for(i=pos ; i<size-1 ; i++)
    {
        //to swap all the elements after the specific index
        P[i]=P[i+1];
    }
}
//To check if the course founded or not
int isFound(Course c, char x)
{
    if(getFirstChar(c.c_code) == x)
    {
        return 1;
    }
    return 0;
}
int isFoundDep(Course c, char x[])
{
    if(strcmp(c.department,x)==0)
    {
        return 1;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
int hash_1(char *course_name)
{
    int wordLength = strnlen(course_name,100);
    int hash_value = 0;
    for(int i=0; i<wordLength; i++)
    {
        hash_value+=course_name[i];
    }
    hash_value = hash_value%TABLE_SIZE;
    return hash_value;
}
int hash_2(char *course_name)
{
    int wordLength = strlen(course_name);
    int hash_value = 0;
    for(int i=0; i<wordLength; i++)
    {
        hash_value+=course_name[i];
    }
    hash_value = 1 + hash_value%(TABLE_SIZE-1);
    return hash_value;
}
void make_empty_table()
{
    for (int i=0; i<TABLE_SIZE; i++)
    {
        hash_table_1[i] = NULL;
        hash_table_2[i] = NULL;
    }
}
void print_table_1()
{
    printf("no.       course information:     \n");
    for(int i=0; i<9; i++)
    {
        if (hash_table_1[i] == NULL)
        {
            printf("%i.  EMPTY ROW\n\n",i);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.%-30s%-20d%-20s%-30s %-20s\n\n",i, hash_table_1[i]->course_name,hash_table_1[i]->c_hours,hash_table_1[i]->c_code,hash_table_1[i]->department,hash_table_1[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
    for(int i=10; i<TABLE_SIZE; i++)
    {
        if (hash_table_1[i] == NULL)
        {
            printf("%i. EMPTY ROW\n\n",i);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.%-30s%-20d%-20s%-30s %-20s\n\n",i, hash_table_1[i]->course_name,hash_table_1[i]->c_hours,hash_table_1[i]->c_code,hash_table_1[i]->department,hash_table_1[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
}
void print_table_2()
{
    printf("no.       course information:     \n");
    for(int i=0; i<9; i++)
    {
        if (hash_table_2[i] == NULL)
        {
            printf("%i.  EMPTY ROW\n\n",i);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.%-30s%-20d%-20s%-30s %-20s\n\n",i, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
    for(int i=10; i<TABLE_SIZE; i++)
    {
        if (hash_table_2[i] == NULL)
        {
            printf("%i. EMPTY ROW\n\n",i);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.%-30s%-20d%-20s%-30s %-20s\n\n",i, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
}
void insert_to_hash_table_open_addressing(Course *courses)
{
    char word[100];
    strcpy(word,courses->course_name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(word) + i)%TABLE_SIZE;
        if(hash_table_1[index] == NULL)
        {
            hash_table_1[index] = courses;
            return ;
        }
    }
}
void insert_to_hash_table_double_hashing(Course *courses)
{
    char word[100];
    strcpy(word,courses->course_name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(word) + i*hash_2(word))%TABLE_SIZE;
        if(hash_table_2[index] == NULL)
        {
            hash_table_2[index] = courses;
            return;
        }
    }
}
Course *findCourseFromHashTable(char *name)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i)%TABLE_SIZE;
        if(hash_table_1[index] != NULL && strcmp(hash_table_1[index]->course_name,name)==0)
        {
            printf("%i.%-30s%-20d%-20s%-20s %-20s\n\n",i, hash_table_1[index]->course_name,hash_table_1[index]->c_hours,hash_table_1[index]->c_code,hash_table_1[index]->department,hash_table_1[index]->sub);
            return hash_table_1[index];
        }
    }
    return NULL;
}
Course *findCourseFromHashTable_2(char *name)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i*hash_2(name))%TABLE_SIZE;
        if(hash_table_2[index] != NULL && strcmp(hash_table_2[index]->course_name,name)==0)
        {
            printf("%i.%-30s%-20d%-20s%-20s %-20s\n\n",i, hash_table_2[index]->course_name,hash_table_2[index]->c_hours,hash_table_2[index]->c_code,hash_table_2[index]->department,hash_table_2[index]->sub);
            return hash_table_2[index];
        }
    }
    return NULL;
}
void deleteFromHash(char *name)
{
    int check=0;
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i)%TABLE_SIZE;
        if(hash_table_1[index] != NULL && strcmp(hash_table_1[index]->course_name,name)==0)
        {
            hash_table_1[index] = NULL;
            \
            check = 1;
        }
        int index2 = (hash_1(name) + i*hash_2(name))%TABLE_SIZE;
        if(hash_table_2[index2] != NULL && strcmp(hash_table_2[index2]->course_name,name)==0)
        {
            hash_table_2[index2] = NULL;
            check = 2;
        }
    }
    if(check == 0)
    {
        printf("Course is not found!\n");
    }
}
int main()
{
    FILE *in;
    in = fopen("courses.txt","r");
    out = fopen("offered_courses.txt","w");
    printf("           =================         \n");
    printf("           =  Taking Data  =         \n");
    printf("           =================         \n");
    //To check if the file exists in the computer
    in==NULL ? printf("courses text file does not exist\n") : printf("taking data from courses file .... \n");
    printf("=====================================\n");
    int option;
    char line[MAX_SIZE];
    int i=0,j=0,size;
    Course courses[MAX_SIZE];
    char arrOfSub[100][MAX_SIZE];
    int sizeOfSub=0;
    AVLNode tree,tree2;
    tree= MakeEmpty(NULL);
    tree2= MakeEmpty(NULL);
    char name[100],code[100],dep[100],sub[1000];
    int hour;
    int menu;
    printf("Which menu do you want to display?\n");
    printf("1. AVL Tree menu\n");
    printf("2. Hash Table menu\n");
    scanf("%d",&menu);
    if(menu == 1)
    {
        while (option != 11)
        {
            //MAIN MINU
            printf("           =================         \n");
            printf("           =   MAIN MENU   =         \n");
            printf("           =================         \n");
            printf("Press (1) to Read the file courses.txt file and create the tree.\n");
            printf("Press (2) to Insert a new course from the user with all its associated data.\n");
            printf("Press (3) to Find a course and support updating of its information. \n");
            printf("Press (4) to List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n");
            printf("Press (5) to List all topics associated with a given course.\n");
            printf("Press (6) to List all courses in lexicographic order that belong to the same department.\n");
            printf("Press (7) to Delete a course.\n");
            printf("Press (8) to Delete all courses that start with a specific letter.\n");
            printf("Press (9) to Delete all courses belong to a given department.\n");
            printf("Press (10)to Save all words in file offered_courses.txt\n");
            printf("Press (11) to exit the program.\n");
            printf("=====================================\n");
            printf("Enter your choice: ");
            //to scan which option do the user want
            scanf("%d",&option);
            printf("\n");
            //this option is to read the file and create the tree
            if(option == 1)
            {
                while(fgets(line,MAX_SIZE,in)!=NULL)
                {
                    //to skip the blank lines
                    if(line[0]=='\n')
                    {
                        continue;
                    }
                    char *word = strtok(line,":");
                    strcpy(courses[i].course_name,word);
                    word = strtok(NULL,"#");
                    courses[i].c_hours=atoi(word);
                    word = strtok(NULL,"#");
                    strcpy(courses[i].c_code,word);
                    word = strtok(NULL,"/");
                    strcpy(courses[i].department,word);
                    word = strtok(NULL,"\n");
                    strcpy(courses[i].sub,word);
                    printf("%s",courses[i].course_name);
                    //To insert all the read information from the file to the AVL tree
                    tree = Insert(courses[i].course_name,courses[i].c_hours,courses[i].c_code,courses[i].department,courses[i].sub,tree);
                    i++;
                }
                size=i;
                printf("Data read successfully \n");
                fclose(in);
            }
            //this option is to insert a new record
            if(option == 2)
            {
                printf("Please fill out the course information bellow:\n");
                printf("Course Name: ");
                //to read the whole line
                scanf("%*c%[^\n]",courses[size].course_name);
                printf("Credit Hours: ");
                scanf("%d",&courses[size].c_hours);
                printf("Course Code: ");
                scanf("%*c%[^\n]", courses[size].c_code);
                printf("Department: ");
                scanf("%*c%[^\n]", courses[size].department);
                printf("Course Subjects (use (, ) between the subjects: ");
                scanf("%*c%[^\n]", courses[size].sub);
                size++;
                tree=MakeEmpty(tree);
                for(int i=0; i<size; i++)
                {
                    tree=Insert(courses[i].course_name,courses[i].c_hours,courses[i].c_code,courses[i].department,courses[i].sub,tree);
                }
            }
            //this option is to find the course and update its information
            if(option == 3)
            {
                int choice;
                AVLNode T;
                int f=0;
                char find_course_name[100];
                printf("Enter the course code you want to find: ");
                scanf("%*c%[^\n]", find_course_name);
                T=Find(find_course_name,tree);
                if(T==NULL)
                {
                    for(int i=0; i<size; i++)
                    {
                        if(strcmp(courses[i].c_code,find_course_name)==0)
                        {
                            //to print the founded course on the screen
                            printf("%-30s   %-10d   %-30s   %-25s \n", courses[i].course_name,courses[i].c_hours,courses[i].c_code,courses[i].department);
                            printf("%s\n\n",courses[i].sub);
                            f++;
                        }
                    }
                }
                if(tree->c_code==NULL)
                {
                    break;
                }
                //to check if the user wants to edit the course information
                printf("Do you want to edit this course's information? (Yes=1, No=0)");
                scanf("%d",&choice);
                if(choice==1)
                {
                    tree = Delete(find_course_name,tree);
                    printf("To update the course's information please fill out the course information bellow:\n");
                    printf("Course Name: ");
                    scanf("%*c%[^\n]",name);
                    printf("Credit Hours: ");
                    scanf("%d",&hour);
                    printf("Course Code: %s\n",find_course_name);
                    printf("Department: ");
                    scanf("%*c%[^\n]", dep);
                    printf("Course Subjects (use (, ) between the subjects: ");
                    scanf("%*c%[^\n]", sub);
                    //to find the index of the needed course
                    for(int i=0; i<size; i++)
                    {
                        if(strcmp(find_course_name,courses[i].c_code)==0)
                        {
                            strcpy(courses[i].course_name,name);
                            courses[i].c_hours=hour;
                            strcpy(courses[i].c_code,find_course_name);
                            strcpy(courses[i].department,dep);
                            strcpy(courses[i].sub,sub);
                        }
                    }
                    //insert the course with its new information to the tree
                    tree = Insert(name,hour,code,dep,sub,tree);
                }
            }
            //this option is to print the AVL Tree sorted on the screen
            if(option == 4)
            {
                tree = MakeEmpty(tree);
                for(int i=0; i<size; i++)
                {
                    tree=Insert(courses[i].course_name, courses[i].c_hours, courses[i].c_code,courses[i].department,courses[i].sub,tree);
                }
                printf("Course Name:                     Hours:       Code:                            Department: \n");
                //the second parameter in the function is used to determine if we want to print the data on the screen or on a new file
                PrintInOrder(tree,0);
            }
            //this option is to print all the subjects belong to a specific course
            if(option == 5)
            {
                char course_name_to_print_sub[100];
                int check=0;
                printf("Enter the course you want to print all its subjects: ");
                scanf("%*c%[^\n]", course_name_to_print_sub);
                //FindCourse(course_name_to_print_sub,tree,check);
                for(int i=0; i<size; i++)
                {
                    if(strcmp(course_name_to_print_sub,courses[i].c_code)==0)
                    {
                        printf("subjects for %s : %s\n",courses[i].c_code,courses[i].sub);
                    }
                }
            }
            //this option is to print all the courses belong to a specific department
            if(option == 6)
            {
                //to insert all the courses belong to the entered department to the new tree
                tree2=MakeEmpty(NULL);
                char course_name_to_print_dep[100];
                printf("Enter the subject's department to list all courses in lexicographic order that belong to the same department: ");
                scanf("%*c%[^\n]", course_name_to_print_dep);
                for(int i=0; i<size; i++)
                {
                    if(strcmp(courses[i].department,course_name_to_print_dep)==0)
                    {
                        tree2=Insert(courses[i].course_name,courses[i].c_hours,courses[i].c_code,courses[i].department,courses[i].sub,tree2);
                    }
                }
                PrintInOrder(tree2,0);
                printf("======================================================\n");
                AVLNode neww = MakeEmpty(NULL);
                for (int i=0; i<size; i++)
                {
                    neww = InsertDep(courses[i].course_name,courses[i].c_hours,courses[i].c_code,courses[i].department,courses[i].sub,neww);
                }
                PrintInOrder(neww,0);

            }
            //this option is to delete a specific course
            if(option == 7)
            {
                char del_course[100];
                printf("Enter the course you want to delete: ");
                scanf("%*c%[^\n]", del_course);
                tree = Delete(del_course, tree);
                for(int i=0; i<size; i++)
                {
                    if(strcmp(courses[i].c_code,del_course)==0)
                    {
                        deleteFromArray(courses, i, size);
                        size--;
                    }
                }
            }
            //this option is to to delete all courses that starts with a specific letter
            if(option == 8)
            {
                char letter;
                printf("Enter a letter to delete all courses that start with a specific letter: ");
                scanf(" %c",&letter);
                int check=0;
                int counter=0;
                for(int i=0; i<size; i++)
                {
                    //to get the first character from the course code
                    if(getFirstChar(courses[i].c_code)==letter)
                    {
                        deleteFromArray(courses,i,size);
                        size--;
                        check++;
                        counter++;
                    }
                }
                int i=0;
                //to delete all nodes from the tree that has the same character
                while(i<counter)
                {
                    if(getFirstChar(courses[i].c_code)==letter)
                    {
                        tree=Delete(courses[i].c_code,tree);
                        deleteFromArray(courses,i,size);
                        size--;
                    }
                    i++;
                }
                //to check if there is a word starts with the letter or not
                if(check==0)
                {
                    printf("There is no course starts with a letter %c.\n",letter);
                }
            }
            //this option is used to delete all the courses that belong to the department
            if(option == 9)
            {
                char dep_to_delete[30];
                printf("Enter the department to delete all courses that belong to it: ");
                scanf("%*c%[^\n]", dep_to_delete);
                int ch=0;
                int count=0;
                for(int i=0; i<size; i++)
                {
                    if(strcmp(courses[i].department,dep_to_delete)==0)
                    {
                        deleteFromArray(courses,i,size);
                        size--;
                        ch++;
                        count++;
                    }
                }
                int pp=0;
                while(pp<count)
                {
                    if(strcmp(courses[pp].department,dep_to_delete)==0)
                    {
                        tree=Delete(courses[pp].c_code,tree);
                        deleteFromArray(courses,pp,size);
                        size--;
                    }
                    pp++;
                }
                if(ch==0)
                {
                    printf("There is no course belong to %s.\n",dep_to_delete);
                }
            }
            //To print the information in the file
            if(option == 10)
            {
                if(out != NULL)
                {
                    tree = MakeEmpty(tree);
                    for(int i=0; i<size; i++)
                    {
                        tree=Insert(courses[i].course_name, courses[i].c_hours, courses[i].c_code,courses[i].department,courses[i].sub,tree);
                    }
                    printf("The data written successfully in file\n");
                    PrintInOrder(tree,1);
                    fclose(out);
                }
            }
        }
    }
    if(menu == 2)
    {
        while(fgets(line,MAX_SIZE,in)!=NULL)
        {
            if(line[0]=='\n')
            {
                continue;
            }
            char *word = strtok(line,":");
            strcpy(courses[i].course_name,word);
            word = strtok(NULL,"#");
            courses[i].c_hours=atoi(word);
            word = strtok(NULL,"#");
            strcpy(courses[i].c_code,word);
            word = strtok(NULL,"/");
            strcpy(courses[i].department,word);
            word = strtok(NULL,"\n");
            strcpy(courses[i].sub,word);
            insert_to_hash_table_open_addressing(courses[i]);
            insert_to_hash_table_double_hashing(courses[i]);
            i++;
        }
        size=i;
        fclose(in);
        while (option != 9)
        {
            printf("           =================         \n");
            printf("           =   MAIN MENU   =         \n");
            printf("           =================         \n");
            printf("Press (1) to Print hashed tables (including empty spots).\n");
            printf("Press (2) to Print out table size and the load factor.\n");
            printf("Press (3) to Print out the used hash functions. \n");
            printf("Press (4) to Insert a new record to hash table (insertion will be done on both hash tables). \n");
            printf("Press (5) to Search for a specific word (specify which table to search in).\n");
            printf("Press (6) to Delete a specific record (from both tables).\n");
            printf("Press (7) to Compare between the two methods in terms of number of collisions occurred.\n");
            printf("Press (8) to Save hash table back to a file named saved_courses.txt (of the double hashing).\n");
            printf("Press (9) to exit the program.\n");
            printf("=====================================\n");
            printf("Enter your choice: ");
            scanf("%d",&option);
            printf("\n");
            if(option == 1)
            {
                printf("           =================         \n");
                printf("           =   TABLE -1-   =         \n");
                printf("           =================         \n");
                print_table_1();
                printf("           =================         \n");
                printf("           =   TABLE -2-   =         \n");
                printf("           =================         \n");
                print_table_2();
            }
            if(option == 2)
            {
                printf("Table size: %d\n",TABLE_SIZE);
                float load = (float)size / TABLE_SIZE;
                printf("Load Factor: %.2f\n",load);
            }
            if(option == 3)
            {
                printf("function 1: hash_value = hash_value % TABLE_SIZE \n");
                printf("function 2:  hash_value = 1 + hash_value%(MAX_SIZE-1) \n");
            }
            if(option == 4)
            {
                printf("Please fill out the course information bellow:\n");
                printf("Course Name: ");
                //to read the whole line
                scanf("%*c%[^\n]",courses[size].course_name);
                printf("Credit Hours: ");
                scanf("%d",&courses[size].c_hours);
                printf("Course Code: ");
                scanf("%*c%[^\n]", courses[size].c_code);
                printf("Department: ");
                scanf("%*c%[^\n]", courses[size].department);
                printf("Course Subjects (use (, ) between the subjects: ");
                scanf("%*c%[^\n]", courses[size].sub);
                insert_to_hash_table_open_addressing(courses[size]);
                insert_to_hash_table_double_hashing(courses[size]);
                size++;
            }
            if(option == 5)
            {
                char name_to_find[100];
                Course *founded;
                int numOfTable;
                printf("Enter the name of the course which you want to find: ");
                scanf("%*c%[^\n]", name_to_find);
                printf("Which table do you want to search in ?:\n");
                printf("1. Table (1)\n");
                printf("2. Table (2)\n");
                scanf("%d",&numOfTable);
                if(numOfTable == 1)
                {
                    founded = findCourseFromHashTable(name_to_find);
                }
                if(numOfTable == 2)
                {
                    founded = findCourseFromHashTable_2(name_to_find);
                }
            }
            if(option == 6)
            {
                char name_to_delete[100];
                printf("Enter the name of the course which you want to delete: ");
                scanf("%*c%[^\n]", name_to_delete);
                deleteFromHash(name_to_delete);
            }
            if(option == 7)
            {
                int counter = 0;
                int counter1 = 0;
                for (int i=0; i<size; i++)
                {
                    if(hash_table_1[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE]->course_name != courses[i].course_name && hash_table_1[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE] != NULL)
                    {
                        counter++;
                    }
                }
                printf("The number of collisions in table 1 : %d\n",counter);
                for (int i=0; i<size; i++)
                {
                    if(hash_table_2[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE]->course_name != courses[i].course_name && hash_table_2[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE] != NULL)
                    {
                        counter1++;
                    }
                }
                printf("The number of collisions in table 2 : %d\n",counter1);
            }
            if(option == 8)
            {
                out1 = fopen("saved_courses.txt","w");
                fprintf(out1,"no.       course information:     \n");
                for(int i=0; i<9; i++)
                {
                    if (hash_table_2[i] == NULL)
                    {
                        fprintf(out1,"%i.  EMPTY ROW\n\n",i);
                        fprintf(out1,"===================================================================================================================================================================\n");
                    }
                    else
                    {
                        fprintf(out1,"%i.%-30s%-20d%-20s%-20s %-20s\n\n",i, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
                        fprintf(out1,"===================================================================================================================================================================\n");
                    }
                }
                for(int i=10; i<TABLE_SIZE; i++)
                {
                    if (hash_table_2[i] == NULL)
                    {
                        fprintf(out1,"%i. EMPTY ROW\n\n",i);
                        fprintf(out1,"===================================================================================================================================================================\n");
                    }
                    else
                    {
                        fprintf(out1,"%i.%-30s%-20d%-20s%-20s %-20s\n\n",i, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
                        fprintf(out1,"===================================================================================================================================================================\n");
                    }
                }
            }
        }
    }
}

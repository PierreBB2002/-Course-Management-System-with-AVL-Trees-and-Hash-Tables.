/*
Pierre Backleh
1201296
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *out1;
#define TABLE_SIZE 50
#define MAX_SIZE 1000
// Course structure
typedef struct Course
{
    char course_name[100];
    int c_hours;
    char c_code[10];
    char department[100];
    char sub[1000];
} Course;
// defining two hash tables to insert the data and the pointer is to detect the null rows in the table
Course *hash_table_1[TABLE_SIZE];
Course *hash_table_2[TABLE_SIZE];
//this function is to convert the string to int according to each ASCI code letter
int string_to_int(char *a){
    //to find the length of the string
    int wordLength = strlen(a);
    int hash_value = 0;
    //to calculate the index of the hash value
    for(int i=0; i<wordLength; i++)
    {
        hash_value+=a[i];
    }
    return hash_value;
}
//this function is to find the index to add the course to this index in table one using open addressing method
int hash_1(char *course_name)
{
    int wordLength = strlen(course_name);
    int hash_value = string_to_int(course_name);
    hash_value = hash_value%TABLE_SIZE;
    return hash_value;
}
//this function is to find the index to add the course into a specified index in table two using double hashing method
int hash_2(char *course_name)
{
    int wordLength = strlen(course_name);
    int hash_value = string_to_int(course_name);
    hash_value = 1 + hash_value%(TABLE_SIZE-1);
    return hash_value;
}
//to define all rows as NULL
void make_empty_table()
{
    for (int i=0; i<TABLE_SIZE; i++)
    {
        hash_table_1[i] = NULL;
        hash_table_2[i] = NULL;
    }
}
//to print the table one
void print_table_1()
{
    printf("no.       course information:     \n");
    for(int i=0; i<9; i++)
    {
        if (hash_table_1[i] == NULL)
        {
            printf("%i.  EMPTY ROW\n\n",i+1);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.  %-30s%-20d%-20s%-30s %-20s\n\n",i+1, hash_table_1[i]->course_name,hash_table_1[i]->c_hours,hash_table_1[i]->c_code,hash_table_1[i]->department,hash_table_1[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
    for(int i=10; i<TABLE_SIZE; i++)
    {
        if (hash_table_1[i] == NULL)
        {
            printf("%i. EMPTY ROW\n\n",i+1);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i. %-30s%-20d%-20s%-30s %-20s\n\n",i+1, hash_table_1[i]->course_name,hash_table_1[i]->c_hours,hash_table_1[i]->c_code,hash_table_1[i]->department,hash_table_1[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
}
//to print the table two
void print_table_2()
{
    printf("no.       course information:     \n");
    for(int i=0; i<9; i++)
    {
        if (hash_table_2[i] == NULL)
        {
            printf("%i.  EMPTY ROW\n\n",i+1);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i.  %-30s%-20d%-20s%-30s %-20s\n\n",i+1, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
    for(int i=10; i<TABLE_SIZE; i++)
    {
        if (hash_table_2[i] == NULL)
        {
            printf("%i. EMPTY ROW\n\n",i+1);
            printf("===================================================================================================================================================================\n");
        }
        else
        {
            printf("%i. %-30s%-20d%-20s%-30s %-20s\n\n",i+1, hash_table_2[i]->course_name,hash_table_2[i]->c_hours,hash_table_2[i]->c_code,hash_table_2[i]->department,hash_table_2[i]->sub);
            printf("===================================================================================================================================================================\n");
        }
    }
}
//to insert the course to a specific index in table one
void insert_to_hash_table_open_addressing(Course *courses)
{
    char word[100];
    //to get the course name (key)
    strcpy(word,courses->course_name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(word) + i)%TABLE_SIZE;
        //to check if this index is empty
        if(hash_table_1[index] == NULL)
        {
            hash_table_1[index] = courses;
            //to exit from the function
            return ;
        }
    }
}
//to insert the course to a specific index in table two
void insert_to_hash_table_double_hashing(Course *courses)
{
    char word[100];
    //to get the course name (key)
    strcpy(word,courses->course_name);
    for (int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(word) + i*hash_2(word))%TABLE_SIZE;
        //to check if this index is empty
        if(hash_table_2[index] == NULL)
        {
            hash_table_2[index] = courses;
            //to exit from the function
            return;
        }
    }
}
//to find a specific course according to the entered name from table one
Course *findCourseFromHashTable(char *name)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i)%TABLE_SIZE;
        if(hash_table_1[index] != NULL && strcmp(hash_table_1[index]->course_name,name)==0)
        {
            //to print this course
            printf("%i.%-30s%-20d%-20s%-20s %-20s\n\n",i+1, hash_table_1[index]->course_name,hash_table_1[index]->c_hours,hash_table_1[index]->c_code,hash_table_1[index]->department,hash_table_1[index]->sub);
            return hash_table_1[index];
        }
    }
    //else the function should return nothing
    return NULL;
}
Course *findCourseFromHashTable_2(char *name)
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i*hash_2(name))%TABLE_SIZE;
        if(hash_table_2[index] != NULL && strcmp(hash_table_2[index]->course_name,name)==0)
        {
            printf("%i.%-30s%-20d%-20s%-20s %-20s\n\n",i+1, hash_table_2[index]->course_name,hash_table_2[index]->c_hours,hash_table_2[index]->c_code,hash_table_2[index]->department,hash_table_2[index]->sub);
            return hash_table_2[index];
        }
    }
    return NULL;
}
//to delete a specific course from the hash function
void deleteFromHash(char *name)
{
    //to check if the entered course has found or not
    int check=0;
    for(int i=0; i<TABLE_SIZE; i++)
    {
        int index = (hash_1(name) + i)%TABLE_SIZE;
        if(hash_table_1[index] != NULL && strcmp(hash_table_1[index]->course_name,name)==0)
        {
            hash_table_1[index] = NULL;
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
int main() {
    FILE *in;
    in = fopen("courses.txt","r");
    fopen("offered_courses.txt", "w");
    printf("           =================         \n");
    printf("           =  Taking Data  =         \n");
    printf("           =================         \n");
    //To check if the file exists in the computer
    in==NULL ? printf("courses text file does not exist\n") : printf("taking data from courses file .... \n");
    printf("=====================================\n");
    int option;
    char line[MAX_SIZE];
    int i=0, size;
    Course courses[MAX_SIZE];
    //to read from the file line by line
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
        insert_to_hash_table_open_addressing(&courses[i]);
        insert_to_hash_table_double_hashing(&courses[i]);
        i++;
    }
    //to find out the final size of the array
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
        // this option is to Print hashed tables (including empty spots)
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
        //this option is to Print out table size and the load factor which is the used size divided by the table size
        if(option == 2)
        {
            int count_hash_1=0;
            int count_hash_2=0;
            printf("Table size: %d\n",TABLE_SIZE);
            for (int i=0;i<TABLE_SIZE;i++){
                if (hash_table_1[i] != NULL)
                    count_hash_1++;
                if (hash_table_2[i] != NULL)
                    count_hash_2++;
            }
            float load = (float)count_hash_1 / TABLE_SIZE;
            printf("Load Factor: %.2f\n",load);
            printf("Used size in Table 1: %d\n",count_hash_1);
            printf("Used size in Table 2: %d\n",count_hash_2);
        }
        //this option is used to print out the used functions
        if(option == 3)
        {
            printf("function 1: index = (name in ASSCI) %c table size \n",37);
            printf("function 2:  index = 1 + (name in ASSCI) %c (table size - 1) \n",37);
            printf("Hp function : index = (function 1(name) + i*function 2(name))%c table size;\n",37);
        }
        //this option is used to insert a new record from the user
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
            //to insert the entered information to the hash tables ( 1 and 2 )
            insert_to_hash_table_open_addressing(&courses[size]);
            insert_to_hash_table_double_hashing(&courses[size]);
            size++;
        }
        //this option is used to find a specific course information
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
            //to determine which table you want to find from
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
        //this option is used to delete a specific course
        if(option == 6)
        {
            char name_to_delete[100];
            printf("Enter the name of the course which you want to delete: ");
            scanf("%*c%[^\n]", name_to_delete);
            deleteFromHash(name_to_delete);
            printf("deleting.....\n");
        }
        //this option for calculating the number of collisions in each table
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
                //to check if the index is not null and not equal the course name
                if(hash_table_2[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE]->course_name != courses[i].course_name && hash_table_2[(hash_1(courses[i].course_name) + 0)%TABLE_SIZE] != NULL)
                {
                    counter1++;
                }
            }
            printf("The number of collisions in table 2 : %d\n",counter1);
        }
        //to print the results in text file called saved_courses.txt
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

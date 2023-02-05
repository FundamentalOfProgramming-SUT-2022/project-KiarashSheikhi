//401106169

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>


//***************************************
bool hazfeDoubleQot(char* string)
{
    int i;
    if (string[strlen(string) - 1] != '"')
    {
        return false;
    }
    for (i = 0; ; i++)
    {
        string[i] = string[i + 1];
        if (string[i] == '\0')
        {
            string[i - 1] = '\0';
            break;
        }
    }
    return true;
}

//***************************************
bool inputFile(char str[])
{
    scanf(" %c",&str[0]);
    if(str[0]=='"')
    {
        if(hazfeDoubleQot(str)==-1)
        {
            return false;
        }
    }
    else
    {
        scanf("%s",&str[1]);
    }
    if(str[0]=='/')
        strcpy(str,&str[1]);
    if(str[strlen(str)-1]=='/')
        str[strlen(str)-1]='\0';
    return true;
}

//****************************************
bool addressIsRight(char str[])
{
    int i;
    char path[100];
    for(i=0;str[i]!='\0';i++)
    {
        path[i]=str[i];
    }
    path[i]='a';
    FILE* f;
    if((f=fopen(path,"w"))==NULL)
    {
        fclose(f);
        remove(path);
        return false;
    }
    fclose(f);
    remove(path);
    return true;
}


//****************************************

/*************MAIN**********************/
int main()
{
    puts("Welcome!");
    puts("This project is developed by Kiarash Sheihki.");
    puts("Whenever you want to leave, enter 'exit'\n");
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
    mkdir("root");
    char command[10000];
    while (1)
    {
         scanf("%s", command);
////////////////////////////////////////////////////////////
        if(!strcmp(command,"createfile"))
        {
            createFile();
        }
////////////////////////////////////////////////////////////
        else if(!strcmp(command,"cat"))
        {
            cat();
        }
////////////////////////////////////////////////////////////

//        else if(!strcmp(command,"insertstr"))
//        {
//            ;
//        }

//////////////////////////////////////////////////////////

//        else if(!strcmp(command,"removestr"))
//        {
//            ;
//        }
//////////////////////////////////////////////////////////
//        else if(!strcmp(command,"copystr"))
//        {
//            ;
//        }
//////////////////////////////////////////////////////////
//        else if(!strcmp(command,"cutstr"))
//        {
//            ;
//        }
///////////////////////////////////////////////////////////
//        else if(!strcmp(command,"pastestr"))
//        {
//            ;
//        }

///////////////////////////////////////////////////////////
//        else if(!strcmp(command,"find"))
//        {
//            ;
//        }
///////////////////////////////////////////////////////////
//        else if(!strcmp(command,"replace"))
//        {
//            ;
//        }
///////////////////////////////////////////////////////////
//        else if(!strcmp(command,"grep"))
//        {
//            ;
//        }

//////////////////////////////////////////////////////////
//        else if(!strcmp(command,"auto_indent"))
//        {
//            ;
//        }

//////////////////////////////////////////////////////////
//        else if(!strcmp(command,"compare"))
//        {
//            ;
//        }
/////////////////////////////////////////////////////////
//        else if(!strcmp(command,"tree"))
//        {
//            ;
//        }
/////////////////////////////////////////////////////////
        else if(!strcmp(command,"exit"))
        {
            return 0;
        }
        else
        {
            puts("Invalid input");
            continue;
        }
    }

}

/********************CREATEFILE******************/

void createFolderAndFile(const char path[])
{
    int i = 0;
    int k = 0;
    while (1)
    {
        if(path[i] == '/')
        {
            k = i;
        }
        char pathCopy[1000] = {0};
        if(k != 0)
        {
            for(int j = 0; j < k; j++)
            {
                pathCopy[j] = path[j];
            }
            pathCopy[strlen(pathCopy)] = '\0';
            DIR *check = opendir(pathCopy);
            if(check)
            {
                closedir(check);
            }
            else
            {
                mkdir(pathCopy);
            }
        }
        i++;
        if(i == strlen(path))
            break;
        k = 0;
    }

    FILE *fptr = fopen(path , "r");
    if(fptr) {
        puts("The File already exists!");
        fclose(fptr);
    }
    else
    {
        fptr = fopen(path , "w");
        puts("Done!");
        fclose(fptr);
    }
}

//************************************************
int createFile()
{
    char komaki[100];
    int j,i=0;
    int flagIsValid = checkFlag(1);
    if(flagIsValid == -1)
    {
        puts("Invalid input");
        puts("If you want to create a file, enter createfile --file <file name and address>");
        return -1;
    }

    char fileaddress[100];
    fgets(fileaddress, 100,stdin);

    if (fileaddress[strlen(fileaddress) - 1] == '\n')
        fileaddress[strlen(fileaddress) - 1] = 0;

    if (fileaddress[1] == '\"')
    {
        if (fileaddress[strlen(fileaddress) - 1] != '\"')
        {
            puts("Invalid input(\")");
            return -1;
        }

        for (i = 0; i < strlen(fileaddress)-1; i++)
        {
            fileaddress[i] = fileaddress[i+1];
        }
        fileaddress[strlen(fileaddress) - 1] = 0;

        for(i = 0; i < strlen(fileaddress) - 2; i++)
        {
            komaki[i] = fileaddress[i + 1];
        }
        komaki[strlen(komaki)-2]=0;
        createFolderAndFile(komaki+1);
    }


    else
    {
        for (i = 0; i < strlen(fileaddress)-1; i++)
        {
            fileaddress[i ] = fileaddress[i+1];
        }
        fileaddress[strlen(fileaddress) - 1] = 0;
            createFolderAndFile(fileaddress+1);
    }

}

//***********************************************
int checkFlag(int n)
{
    char flag[50];

    scanf("%s", flag);

    if(n==1)
    {
        if(strcmp(flag,"--file"))
        {
            return -1;
        }
        else return 1;
    }

}

////*********************************************
/******************CAT*****************/
////////////////////////////////////////

void cat()
{
    int numberOfLines=1,numberOfChars=0;
    char c;
    char path[100];
    char flag[50];
    scanf("%s",flag);
    if(strcmp(flag,"--file"))
    {
        puts("Invalid input");
        return -1;
    }
    if(!inputFile(path))
    {
        puts("Invalid input");
        return;
    }
    if(!addressIsRight(path))
    {
        puts("Invalid input");
        return;
    }
    FILE* f;
    if(f=fopen(path,"r")==NULL)
    {
        fclose(f);
        puts("Couldn't find the file!");
        return -1;
    }
    fclose(f);

    FILE* fptr=fopen(path,"r");

    while(1)
    {
        c =fgetc(fptr);
        if(c == EOF)
        {
            break;
        }
        if(c == '\n')
        {
            numberOfLines++;
        }
        numberOfChars++;
        printf("%c",c);
    }
    printf("\nnumber of lines: %d\n",numberOfLines);
    printf("number of characters: %d\n",numberOfChars);

    fclose(fptr);
    return 1;
}

//****************************************



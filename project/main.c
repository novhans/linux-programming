#include <stdio.h>
#include <unistd.h>
#include "dir.h"
#include "ls.h"

#define LIST    1
#define INODE   2
#define RECUR   4
#define ALL     8

int main(int argc, char **argv)
{
    int ch;
    int c_flag = 0;
    int flag = 0;
    while((ch = getopt(argc, argv, "liRa"))!= -1)
    {
        switch(ch)
        {
            case 'l': flag |= LIST; break;
            case 'i': flag |= INODE; break;
            case 'R': flag |= RECUR; break;
            case 'a': flag |= ALL; break;
            
        }
    }
    if(flag == 0) printf("%s\n", argv[1]);
    
    else
    {
        if(flag & LIST && argc >= 3) 
        {
            int i;
            for(i=3;i<=argc;i++)
            {
                if( strcmp(argv[i-1], "-i") && strcmp(argv[i-1], "-l") && strcmp(argv[i-1], "-R") && strcmp(argv[i-1], "-a"))
                {
                    if(strcmp(argv[i-1], "-i") == 0)
                        Fileprint(argv[i-1], 1);
                    else
                        Fileprint(argv[i-1], 0);
                    c_flag = 1;
                }
                
            }
            if(!c_flag) my_ls(".", flag);
        }
        else my_ls(".", flag);
    }
   
    /*
    if(flag & LIST) printf("l\n");
    if(flag & INODE) printf("i\n");
    if(flag & RECUR) printf("R\n");
    if(flag & ALL) printf("a\n");
    */
    return 0;
}
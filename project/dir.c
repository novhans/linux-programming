#include "ls.h"
#include "dir.h"

#define LIST 1
#define INODE 2
#define RECUR 4
#define ALL 8

void my_ls(char *dname, int flag)
{
    DIR *dp;
    struct dirent *p;
    struct stat buf;
    chdir(dname);
    dp = opendir(".");
    if (flag & RECUR) printf("%s:\n", dname);
    while(p = readdir(dp))
    {
        if (flag & ALL == 0 && !(strcmp(p->d_name, ".") && strcmp(p->d_name, "..")))
            continue;
        if(flag & LIST)
            if(flag & INODE)
                Fileprint(p->d_name, 1);
            else 
                Fileprint(p->d_name, 0);
        else
        {
            printf("%s ", p->d_name);
        }
    }
        
    printf("\n");
   
    if(flag & RECUR )
    {
        printf("\n");
        rewinddir(dp);
        while (p = readdir(dp))
        {
            lstat(p->d_name, &buf);
            if (S_ISDIR(buf.st_mode))
            {
                if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
                    my_ls(p->d_name, flag);
            }
        }
        closedir(dp);
        chdir("..");
    }
    
}

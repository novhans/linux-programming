#include "ls.h"

int Fileprint(char *name, int flag)
{
    struct stat buf;
    struct passwd *pwd;
    struct group *grp;
    struct tm *tmp;
    char perm[11] = "----------";
    char rwx[] = "rwx";
    char sst[] = "sst";
    int i;
    char *ptr;

    lstat(name, &buf);
    if (S_ISDIR(buf.st_mode))       perm[0] = 'd';
    else if (S_ISCHR(buf.st_mode))  perm[0] = 'c';
    else if (S_ISBLK(buf.st_mode))  perm[0] = 'b';
    else if (S_ISFIFO(buf.st_mode)) perm[0] = 'p';
    else if (S_ISLNK(buf.st_mode))  perm[0] = 'l';
    else if (S_ISSOCK(buf.st_mode)) perm[0] = 's';

    for (i = 0; i < 9; i++)
    {
        if (buf.st_mode >> (8 - i) & 0x1)
            perm[1 + i] = rwx[i % 3];
    }
    for (i = 0; i < 3; i++)
    {
        if (buf.st_mode >> (11 - i) & 0x1)
        {
            if (perm[(i + 1) * 3] == '-')
                perm[(i + 1) * 3] = sst[i] - ('a' - 'A');
            else
                perm[(i + 1) * 3] = sst[i];
        }
    }
    if(flag) printf("%lu ", buf.st_ino);
    printf("%s ", perm);
    printf("%ld ", buf.st_nlink);

    pwd = getpwuid(buf.st_uid);
    printf("%s ", pwd->pw_name);

    grp = getgrgid(buf.st_gid);
    printf("%s ", grp->gr_name);
    if(perm[0] == 'c' || perm[0] == 'b')
        printf("%lu, %lu ", (buf.st_rdev >> 8) & 0xff, buf.st_rdev & 0xff );
    else
        printf("%lu ", buf.st_size);
    tmp = localtime(&buf.st_mtime);
    printf("%2d월 %2d %02d:%02d ", tmp->tm_mon, tmp->tm_mday, tmp->tm_hour, tmp->tm_min);
    if(perm[0] == 'l')
    {
        char buf[256];
        int ret;
        ret = readlink(name, buf, sizeof buf);
        printf("%s -> %s\n", name, buf);
    }
        
    else
        printf(" %s\n", name);
    return 0;
}
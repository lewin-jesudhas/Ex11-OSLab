#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

struct file {  
    char *filename;  
    int start, length;  
};  

int *memory;  
int isFree(int s, int l) {  
    for (int i = 0; i < l; i++) {  
        if (memory[s + i] == 1) {  
            return 0;  
        }  
    }  
    return 1;  
}  

void printStructure(struct file *directory, int n) {  
    printf("\nFilename\tStart\tLength");  
    for (int i = 0; i < n; i++) {  
        printf("\n%s\t\t%d\t%d", directory[i].filename, directory[i].start, directory[i].length);  
    }  
}
void main()  
{  
    int capacity, n;  
    printf("\nEnter block size: ");  
    scanf("%d", &capacity);  
    memory = (int *)malloc(capacity * sizeof(int));  
    for (int i = 0; i < capacity; i++)  
    {  
        memory[i] = 0;  
    }  

    int s, l;  
    char filename[20];  

    printf("\nEnter number of files: ");  
    scanf("%d", &n);  
    struct file *directory = (struct file *)malloc(n * sizeof(struct file));  

    for (int i = 0; i < n; i++)  
    {  
        printf("\nEnter filename: ");  
        scanf("%s", filename);  
        printf("Enter starting block and number of blocks required by file %d: ", i + 1);  
        scanf("%d%d", &s, &l);  
        if (isFree(s, l) == 1)  
        {  
            if (s > capacity)  
            {  
                printf("\nMemory not found - Cannot Allocate File");  
            }  
            else  
            {  
                if (s + l > capacity)  
                {  
                    printf("\nMemory exceeded - Cannot Allocate File");  
                }  
                else  
                {  
                    for (int k = 0; k < l; k++)  
                    {  
                        memory[s + k] = 1;  
                    }  
                    directory[i].filename = filename;  
                    directory[i].start = s;
                    directory[i].length = l;
                    printf("\nFile successfully allocated");
                      }
            }
        }
      else
        {
              printf("\nCannot allocate file to that block");
                }
                }
      printStructure(directory,n);
}

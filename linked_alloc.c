#include <stdio.h>  
#include <stdlib.h>  
void recursiveParts(int pagesAllocation[]){  
    int s, length, k, c, j;  
    printf("Enter the beginning block's index as well as length: ");  
    scanf("%d%d", &s, &length);  
    k = length;  
    if (pagesAllocation[s] == 0){  
        for (j = s; j < (s + k); j++){  
            if (pagesAllocation[j] == 0){  
                pagesAllocation[j] = 1;  
                printf("%d------>%d\n", j, pagesAllocation[j]);  
            }  
            else {  
                printf("The block %d has already been allocated \n", j);  
                k++;  
            }  
        }  
    }  
    else  
        printf("The block %d has already been allocated \n", s);  
    printf("Do you want to add more files? \n");  
    printf("Enter 1 for continue, Enter 0 for No: ");  
    scanf("%d", &c);  
    if (c==1)  
        recursiveParts(pagesAllocation);  
    else  
        exit(0);  
    return;  
}  
  
int main(){  
    int pagesAllocation[50], p1, a1;  
    for (int i = 0; i < 50; i++)  
        pagesAllocation[i] = 0;  
    printf("Enter the quantity of provided blocks: ");  
    scanf("%d", &p1);  
    printf("Enter the number of alloted blocks ");  
    for (int i = 0; i < p1; i++){  
        scanf("%d", &a1);  
        pagesAllocation[a1] = 1;  
    }  
  
    recursiveParts(pagesAllocation);  
  
    return 0;  
}  

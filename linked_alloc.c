#include <stdio.h>
#include <stdlib.h>

void recursiveParts(int pagesAllocation[]) {
    int s, length, c;
    
    printf("Enter the beginning block's index as well as length: ");
    scanf("%d%d", &s, &length);

    int allocated = 0;
    
    if (pagesAllocation[s] == 0) {
        for (int j = s; j < s + length; j++) {
            if (pagesAllocation[j] == 0) {
                pagesAllocation[j] = 1;
                printf("%d------>%d\n", j, pagesAllocation[j]);
                allocated++;
            } else {
                printf("The block %d has already been allocated\n", j);
            }
        }

        // If we couldn't allocate the exact number of blocks needed, inform the user
        if (allocated < length) {
            printf("Could only allocate %d blocks out of the requested %d.\n", allocated, length);
        }
    } else {
        printf("The starting block %d has already been allocated\n", s);
    }
    
    printf("Do you want to add more files? \n");
    printf("Enter 1 to continue, Enter 0 to stop: ");
    scanf("%d", &c);
    if (c == 1)
        recursiveParts(pagesAllocation);
    else
        exit(0);
}

int main() {
    int pagesAllocation[50], p1, a1;
    for (int i = 0; i < 50; i++)
        pagesAllocation[i] = 0;

    printf("Enter the quantity of provided blocks: ");
    scanf("%d", &p1);
    printf("Enter the indices of the initially allocated blocks: ");
    for (int i = 0; i < p1; i++) {
        scanf("%d", &a1);
        if (a1 >= 0 && a1 < 50) {
            pagesAllocation[a1] = 1;
        } else {
            printf("Invalid block index %d. Please enter indices between 0 and 49.\n", a1);
            i--;  // decrement to re-prompt the correct index
        }
    }

    recursiveParts(pagesAllocation);

    return 0;
}

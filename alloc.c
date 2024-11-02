#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file {
    char name[50];
    int size;
    int start_block;
};

struct disk {
    int total_blocks;
    int *used_blocks;
    int *free_blocks;
};

void init_disk(struct disk *d, int total_blocks) {
    d->total_blocks = total_blocks;
    d->used_blocks = (int *)calloc(total_blocks, sizeof(int));
    d->free_blocks = (int *)calloc(total_blocks, sizeof(int));
    for (int i = 0; i < total_blocks; i++) {
        d->free_blocks[i] = 1;
    }
}

struct file *allocate_file(struct disk *d, char *name, int size) {
    int start_block = -1;
    int contiguous_blocks = 0;

    for (int i = 0; i < d->total_blocks; i++) {
        if (d->free_blocks[i] == 1) {
            if (start_block == -1) {
                start_block = i;
            }
            contiguous_blocks++;

            if (contiguous_blocks == size) {
                break;
            }
        } else {
            start_block = -1;
            contiguous_blocks = 0;
        }
    }

    if (contiguous_blocks != size) {
        return NULL;
    }

    for (int i = start_block; i < start_block + size; i++) {
        d->used_blocks[i] = 1;
        d->free_blocks[i] = 0;
    }

    struct file *f = (struct file *)malloc(sizeof(struct file));
    strcpy(f->name, name);
    f->size = size;
    f->start_block = start_block;

    return f;
}

void free_file(struct disk *d, struct file *f) {
    // Mark all the blocks as free
    for (int i = f->start_block; i < f->start_block + f->size; i++) {
        d->used_blocks[i] = 0;
        d->free_blocks[i] = 1;
    }
    free(f);
}

void print_disk_status(struct disk *d) {
    printf("\nDisk Status:\n");
    printf("Block\tStatus\n");
    for (int i = 0; i < d->total_blocks; i++) {
        printf("%d\t%s\n", i, d->used_blocks[i] ? "Used" : "Free");
    }
}

int main() {
    // Initialize the disk with more blocks
    struct disk d;
    init_disk(&d, 15);  // Increase from 10 to 15 blocks

    // Allocate space for the first file
    struct file *f1 = allocate_file(&d, "file1", 3);
    if (f1 == NULL) {
        printf("Could not allocate space for file1\n");
        exit(1);
    }
    print_disk_status(&d); // Show status after allocation

    // Allocate space for the second file
    struct file *f2 = allocate_file(&d, "file2", 5);
    if (f2 == NULL) {
        printf("Could not allocate space for file2\n");
        exit(1);
    }
    print_disk_status(&d); // Show status after allocation

    // Free the first file
    free_file(&d, f1);
    print_disk_status(&d); // Show status after deallocation

    // Allocate space for the third file
    struct file *f3 = allocate_file(&d, "file3", 4);
    if (f3 == NULL) {
        printf("Could not allocate space for file3\n");
        exit(1);
    }
    print_disk_status(&d); // Show status after allocation

    // Free the second file
    free_file(&d, f2);
    print_disk_status(&d); // Show status after deallocation

    // Free the third file
    free_file(&d, f3);
    print_disk_status(&d); // Show final status

    // Clean up
    free(d.used_blocks);
    free(d.free_blocks);

    return 0;
}

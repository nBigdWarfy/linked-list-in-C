#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define data_size 128
#define buffer_size 128

// Define a structure for a linked list node containing a double value and a pointer to the next node.
struct node {
    char data[data_size];
    struct node *next;
};
typedef struct node *Node; // Define a pointer to the node structure as 'Node'.
Node head = NULL; // Initialize a global variable 'head' as NULL, representing the head of the linked list.

// Define a structure to hold file names.
struct fileArray {
    char name[data_size];
};
typedef struct fileArray FileArray; // Typedef the structure as 'FileArray'.
FileArray filenamesArray[data_size]; // Initialize an array to hold file names.
int filesNum = 0; // Initialize a variable to hold the number of files.

// Function to create a new node with the given value and return a pointer to it.
Node createNode(char value[data_size]) {
    Node newNode = (Node)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation error.\n");
        return NULL;
    }
    strcpy(newNode->data, value);
    newNode->next = NULL;
    return newNode;
}

// Function to add a new node with the given value to the end of the linked list.
void addNode(Node head, char value[data_size]) {
    Node newNode, ptr;
    ptr = head;
    newNode = createNode(value);
    if (ptr == NULL) {
        head = newNode;
        return;
    }
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = newNode;
}

// Function to print the elements of the linked list to a file.
void printList(Node head, FILE *file) {
    if (head == NULL) {
        printf("The list is empty.");
        return;
    }
    Node current = head;
    while (current) {
        fprintf(file, "%s\n", current->data);
        current = current->next;
    }
}

// Function to free the memory allocated for the linked list nodes.
void freeMemory(Node head) {
    Node current = head;
    while (current) {
        Node next = current->next;
        free(current);
        current = next;
    }
}

// Function to save the elements of the linked list to a file.
void saveFile(Node head, const char *filename) {
    char filenameWithExt[data_size];
    snprintf(filenameWithExt, sizeof(filenameWithExt), "%s.txt", filename);
    FILE *file = fopen(filenameWithExt, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }
    printList(head, file);
    fclose(file);
    printf("List successfully saved in the file %s.\n", filenameWithExt);
}

// Function to load elements from a file into the linked list.
void loadFile(Node *head, const char *filename) {
    char filenameWithExt[data_size];
    snprintf(filenameWithExt, sizeof(filenameWithExt), "%s.txt", filename);
    FILE *file = fopen(filenameWithExt, "r");
    if (file == NULL) {
        printf("Opening file error.\n");
        return;
    }
    char value[data_size];
    while (fscanf(file, "%s", value) == 1) {
        if (*head == NULL) {
            *head = createNode(value);
        } else {
            addNode(*head, value);
        }
        printf("%s\n", value);
    }
    fclose(file);
    printf("List loaded successfully from the file.\n");
}

// Function to delete all elements of the linked list.
void deleteList(Node *head) {
    char answer[2];
    printf("Do you want to delete all the list data? (Y/N)\n");
    scanf(" %1s", answer);
    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
        freeMemory(*head);
        *head = NULL;
        printf("The list was successfully cleaned.\n");
    } else if (strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0) {
        printf("The list was not cleaned.\n");
    } else {
        printf("Invalid input. Please enter Y or N.\n");
    }
}

// Function to clear the input buffer.
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Function to display a message and wait for user confirmation before clearing the screen.
void screen() {
    printf("\nPress enter to continue...");
    fflush(stdin);
    getchar();
    system("cls");
}

// Function to save the linked list to a file with a given filename.
void saveList(Node head, const char *filename) {
    char bufferFile[buffer_size];
    snprintf(bufferFile, sizeof(bufferFile), "%s", filename);
    FILE *file = fopen(bufferFile, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }
    printList(head, file);
    fclose(file);
    if ((size_t)filesNum < sizeof(filenamesArray) / sizeof(filenamesArray[0])) {
        strcpy(filenamesArray[filesNum].name, filename);
        filesNum++;
    } else {
        printf("Maximum number of files reached.\n");
    }
}

// Function to load a linked list from a file with a given filename.
void loadList(Node *head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char value[data_size];
    while (fscanf(file, "%s", value) == 1) {
        if (*head == NULL) {
            *head = createNode(value);
        } else {
            addNode(*head, value);
        }
        printf("%s\n", value);
    }
    fclose(file);
    printf("List loaded successfully from the file.\n");
}

// Function to handle the creation or loading of a new list.
void newList(Node *head) {
    int option;
    printf("Do you want to save or load a list?\n1. Save\n2. Load\n3. Back\n");
    scanf("%d", &option);
    switch (option) {
        case 1:
            system("cls");
            char filenameSave[100];
            printf("Enter the file's name: ");
            clearInputBuffer();
            fgets(filenameSave, sizeof(filenameSave), stdin);
            filenameSave[strcspn(filenameSave, "\n")] = '\0';
            saveList(*head, filenameSave);

            screen();
            break;

        case 2:
            system("cls");
            char listnameLoad[100];
            printf("Enter the file's name: ");
            clearInputBuffer();
            fgets(listnameLoad, sizeof(listnameLoad), stdin);
            listnameLoad[strcspn(listnameLoad, "\n")] = '\0';
            loadList(head, listnameLoad);
            screen();
            break;

        default:
            system("cls");
            printf("Getting back to the previous menu.\n");
            screen();
            break;
    }
}

// Main function controlling the menu-driven program.
int main() {
    int option;
    char data[data_size];

    while (true) {
        printf("\nMenu:\n");
        printf("1. Add a new data in the list\n");
        printf("2. Print the list\n");
        printf("3. Save the list in a file\n");
        printf("4. Load a list file\n");
        printf("5. Delete the current list\n");
        printf("6. Save or load a list\n");
        printf("9. End the program\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nEnter the data: ");
                scanf("%s", data);
                if (head == NULL) {
                    head = createNode(data);
                } else {
                    addNode(head, data);
                }
                printf("\nSuccessfully added data.");
                screen();
                break;

            case 2:
                if (head == NULL) {
                    printf("\nThe list is empty.");
                } else {
                    system("cls");
                    printf("List:\n");
                    printList(head, stdout);
                }
                screen();
                break;

            case 3:
                system("cls");
                if (head == NULL) {
                    printf("The list is empty, there is no data to save.\n");
                } else {
                    char filenameSave[data_size];
                    printf("Enter the file name to save the list:\n");
                    clearInputBuffer();
                    fgets(filenameSave, sizeof(filenameSave), stdin);
                    filenameSave[strcspn(filenameSave, "\n")] = '\0';
                    saveFile(head, filenameSave);
                }
                screen();
                break;

            case 4:
                system("cls");
                char filenameLoad[data_size];
                printf("Enter the file name to load the list:\n");
                clearInputBuffer();
                fgets(filenameLoad, sizeof(filenameLoad), stdin);
                filenameLoad[strcspn(filenameLoad, "\n")] = '\0';
                loadFile(&head, filenameLoad);
                screen();
                break;

            case 5:
                system("cls");
                if (head == NULL) {
                    printf("The list is empty, there is no data to delete.\n");
                } else {
                    deleteList(&head);
                }
                screen();
                break;

            case 6:
                system("cls");
                newList(&head);
                break;

            case 9:
                printf("\nEnding the program.");
                for (int i = 0; i < filesNum; i++) {
                    remove(filenamesArray[i].name);
                }
                freeMemory(head);
                screen();
                return 0;

            default:
                printf("\nInvalid input! Try again.");
                screen();
                break;
        }
    }
}
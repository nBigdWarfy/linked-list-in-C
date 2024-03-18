#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a linked list node containing a double value and a pointer to the next node.
struct node { 
    double data;
    struct node *next;
};
typedef struct node *node; // Define a pointer to the node structure as 'node'.
node head = NULL; // Initialize a global variable 'head' as NULL, representing the head of the linked list.

// Define a structure to hold file names.
struct fileArray {
    char name[110];
};
typedef struct fileArray fileArray; // Typedef the structure as 'fileArray'.
fileArray filenamesArray[256]; // Initialize an array to hold file names.
int filesNum; // Initialize a variable to hold the number of files.

// Function to create a new node with the given value and return a pointer to it.
node createNode(double value) {
    node newNode = (node)malloc(sizeof(struct node));  
    if (newNode == NULL) {
        printf("Memory allocation error.\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode; 
}

// Function to add a new node with the given value to the end of the linked list.
void addNode(node head, double value) { 
    node newNode, ptr;
    ptr = head;
    newNode = createNode(value);
    while (ptr->next) { 
        ptr = ptr->next; 
    }
    ptr->next = newNode; 
}

// Function to print the elements of the linked list to a file.
void printList(node *head, FILE *file) {
    if (head == NULL) {
        printf("The list is empty.");
        return;
    }
    node current = *head;
    while (current) {
        fprintf(file, "%.1lf\n", current->data); 
        current = current->next;
    }
}

// Function to free the memory allocated for the linked list nodes.
void freeMemory(node *head) {
    node current = *head;
    while(current) {
        node next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Function to save the elements of the linked list to a file.
void saveFile(node *head, const char *filename) { 
    char filenameWithExt[110];
    snprintf(filenameWithExt, sizeof(filenameWithExt), "%s.txt", filename); 
    FILE *file = fopen(filenameWithExt, "w"); 
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }
    printList(head, file); 
    fclose(file);
    printf("List succesfully saved in the file %s.\n", filenameWithExt);
}

// Function to load elements from a file into the linked list.
void loadFile(node *head, const char *filename) { 
    char filenameWithExt[110];
    snprintf(filenameWithExt, sizeof(filenameWithExt), "%s.txt", filename);
    FILE *file = fopen(filenameWithExt, "r"); 
    if (file == NULL) {
        printf("Opening file error.\n");
        return;
    }
    double value;
    while (fscanf(file, "%lf", &value) == 1) { 
        if (*head == NULL) {
            *head = createNode(value); 
        } else {
            addNode(*head, value); 
        }
        printf("%.1lf\n", value);
    }
    fclose(file);
    printf("List loaded successfully from the file.\n");
}

// Function to delete all elements of the linked list.
void deleteList(node *head) {
    char answer[5];
    printf("Do you want to delete all the list data? (Y/N)\n");
    scanf(" %4s", answer);
    system("cls");
    if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) {
        freeMemory(head);
        printf("The list was succesfully cleaned.\n");
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
void saveList(node *head, const char *filename) {
    char bufferFile[110];
    snprintf(bufferFile, sizeof(bufferFile), "%s", filename);
    FILE *file = fopen(bufferFile, "w");
    if (file == NULL) {
        printf("Error creating file.");
        return;
    }
    printList(head, file);
    fclose(file);
    if (filesNum < sizeof(filenamesArray) / sizeof(filenamesArray[0])) {
        strcpy(filenamesArray[filesNum].name, filename);
        filesNum++;
    } else {
        printf("Maximum number of files reached.\n");
    }
}

// Function to load a linked list from a file with a given filename.
void loadList(node *head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    double value = 0;
    while (fscanf(file, "%lf", &value) == 1) {
        if (*head == NULL) {
            *head = createNode(value);
        } else {
            addNode(*head, value);
        }
        printf("%lf\n", value);
    }
    fclose(file);
    printf("List loaded succesfully from the file.\n");
}

// Function to handle the creation or loading of a new list.
void newList(node *head) {
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
            saveList(head, filenameSave);
            
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
    double value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a new value in the list\n");
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
                printf("\nEnter the value: ");
                scanf("%lf", &value);
                if (head == NULL) {
                    head = createNode(value); 
                } else {
                    addNode(head, value); 
                }
                printf("\nSuccessfully added value.");
                screen();
                break;

            case 2:
                if (head == NULL) {
                    printf("\nThe list is empty.");
                } else {
                    system("cls");
                    printf("List:\n");
                    printList(&head, stdout); 
                }
                screen();
                break;

            case 3:
                system("cls");
                if (head == NULL) {
                    printf("The list is empty, there is no data to save.\n");
                } else {
                    char filenameSave[100];
                    printf("Enter the file name to save the list:\n");
                    clearInputBuffer();
                    fgets(filenameSave, sizeof(filenameSave), stdin);
                    filenameSave[strcspn(filenameSave, "\n")] = '\0';
                    saveFile(&head, filenameSave);
                }
                screen();
                break;

            case 4:
                system("cls");
                char filenameLoad[100];
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
                freeMemory(&head);
                screen();
                return 0;

            default:
                printf("\nInvalid input! Try again.");
                screen();
                break;
        }
    }
}
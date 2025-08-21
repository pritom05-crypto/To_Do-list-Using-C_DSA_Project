#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TASKS 100

struct Task {
    char name[50];
    char description[100];
    char date[20];
    int completed;
};


void addTask(struct Task tasks[], int *taskCount, char name[], char description[], char date[]) {
    if (*taskCount < MAX_TASKS) {
        struct Task newTask;
        strcpy(newTask.name, name);
        strcpy(newTask.description, description);
        strcpy(newTask.date, date);
        newTask.completed = 0;
        tasks[*taskCount] = newTask;
        (*taskCount)++;
        printf("Task '%s' with name '%s' added to the to-do list with the date '%s'.\n", description, name, date);
    } else {
        printf("The to-do list is full. Cannot add more tasks.\n");
    }
}

void markTaskAsComplete(struct Task tasks[], int taskCount, char name[]) {
    int taskIndex = searchTaskByName(tasks, taskCount, name);
    if (taskIndex != -1) {
        tasks[taskIndex].completed = 1;
        printf("Task '%s' has been marked as complete.\n", name);
    } else {
        printf("Task '%s' not found in the to-do list.\n", name);
    }
}


int searchTaskByName(struct Task tasks[], int taskCount, char name[]) {
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}


int searchTaskByDate(struct Task tasks[], int taskCount, char date[]) {
    int left = 0;
    int right = taskCount - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(tasks[mid].date, date);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}


void displayTasks(struct Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("Your to-do list is empty.\n");
    } else {
        printf("Your to-do list:\n");
        for (int i = 0; i < taskCount; i++) {
            printf("%d. Task Name: %s, Description: %s (Date: %s, %s)\n", i + 1, tasks[i].name, tasks[i].description, tasks[i].date, tasks[i].completed ? "Complete" : "Incomplete");
        }
    }
}



int main() {
    struct Task tasks[MAX_TASKS];
    int taskCount = 0;
    char name[50];
    char description[100];
    char date[20];

    while (1) {
        int choice;
        printf("\nWelcome To This Application\n\nTo-Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. Remove Task\n");
        printf("3. Display Tasks\n");
        printf("4. Mark Task as Complete\n");
        printf("5. Search for Task by Task Name\n");
        printf("6. Search for Task by Date\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task name: ");
                scanf(" %[^\n]", name);
                printf("Enter task description: ");
                scanf(" %[^\n]", description);
                printf("Enter task date (YYYY-MM-DD): ");
                scanf(" %[^\n]", date);
                addTask(tasks, &taskCount, name, description, date);
                break;
            case 2:
                printf("Enter task description to remove: ");
                scanf(" %[^\n]", description);
                int taskIndex = searchTaskByName(tasks, taskCount, description);
                if (taskIndex != -1) {
                    for (int j = taskIndex; j < taskCount - 1; j++) {
                        tasks[j] = tasks[j + 1];
                    }
                    taskCount--;
                    printf("Task '%s' removed from the to-do list.\n", description);
                } else {
                    printf("Task '%s' not found in the to-do list.\n", description);
                }
                break;
            case 3:
                displayTasks(tasks, taskCount);
                break;
            case 4:
                printf("Enter task name to mark as complete: ");
                scanf(" %[^\n]", name);
                markTaskAsComplete(tasks, taskCount, name);
                break;
            case 5:
                printf("Enter task name to search for: ");
                scanf(" %[^\n]", name);
                int searchResult = searchTaskByName(tasks, taskCount, name);
                if (searchResult != -1) {
                    printf("Task with name '%s' found at position %d. (%s)\n", name, searchResult + 1, tasks[searchResult].completed ? "Complete" : "Incomplete");
                } else {
                    printf("Task with name '%s' not found in the to-do list.\n", name);
                }
                break;
            case 6:
                printf("Enter task date to search for (YYYY-MM-DD): ");
                scanf(" %[^\n]", date);
                int searchResultByDate = searchTaskByDate(tasks, taskCount, date);
                if (searchResultByDate != -1) {
                    printf("Task with date '%s' found at position %d. (%s)\n", date, searchResultByDate + 1, tasks[searchResultByDate].completed ? "Complete" : "Incomplete");
                } else {
                    printf("No task with date '%s' found in the to-do list.\n", date);
                }
                break;
            case 7:
                printf("Exiting the to-do list application.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

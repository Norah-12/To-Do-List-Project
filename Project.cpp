#include <iostream>
#include <string>
using namespace std;

// defining a structure for each task in the to do list
struct Task {
    string data;      // Task description
    bool isDone;      // Flag to check if task is completed
    Task* next;       // Pointer to the next task in the list
};

// Head points to the first task, tail to the last one
Task* head = NULL;
Task* tail = NULL;

// Function to add a new task to the end of the list
void addTask() {
    Task* newTask = new Task; // Create a new task
    cout << "Enter Task Description:\n";
    cin.ignore();             // Clear input buffer
    getline(cin, newTask->data); // Get task description from user

    if (newTask->data.empty()) {
        cout << "Task description can't be empty.\n";
        delete newTask;
        return;
    }

    newTask->isDone = false;  // set the task as not completed
    newTask->next = NULL;     // No task after it yet

    // If the list is empty, this is the first task
    if (head == NULL) {
        head = tail = newTask;
    } else {
        tail->next = newTask; // Add to the end
        tail = newTask;       // Update the last task
    }

    cout << "Task added successfully!\n";
}

// Function to view all tasks in the list
void viewAllTasks() {
    if (head == NULL) {
        cout << "Task list is empty.\n";
        return;
    }

    cout << "\nAll Tasks:\n";
    Task* current = head;
    int index = 1;

    // Traverse and print each task
    while (current != NULL) {
        cout << index << ". " << current->data;
        if (current->isDone)
            cout << " [Completed]";
        cout << endl;
        current = current->next;
        index++;
    }
}

// Function to update an existing task's description
void updateTask() {
    viewAllTasks(); // Show current tasks

    cout << "\nEnter task number to update: ";
    int taskNumber;
    cin >> taskNumber;
    cin.ignore();

    Task* current = head;
    int index = 1;

    // go to the selected task
    while (current != NULL && index < taskNumber) {
        current = current->next;
        index++;
    }

    if (current == NULL) {
        cout << "Invalid task number.\n";
    } else {
        cout << "Current Description: " << current->data << endl;
        cout << "Enter new description: ";
        string newDesc;
        getline(cin, newDesc);

        if (newDesc.empty()) {
            cout << "Task description can't be empty.\n";
            return;
        }

        current->data = newDesc; // Update task
        cout << "Task updated successfully.\n";
    }
}

// Function to delete a task from the list
void deleteTask() {
    viewAllTasks(); // Show current tasks

    cout << "\nEnter task number to delete: ";
    int taskNumber;
    cin >> taskNumber;

    if (head == NULL) {
        cout << "Task list is empty.\n";
        return;
    }

    Task* current = head;
    Task* previous = NULL;
    int index = 1;

    // Find the task to delete
    while (current != NULL && index < taskNumber) {
        previous = current;
        current = current->next;
        index++;
    }

    if (current == NULL) {
        cout << "Invalid task number.\n";
    } else {
        if (previous == NULL) {
            head = current->next; // Remove first task
        } else {
            previous->next = current->next; // Remove in between or end
        }

        if (current == tail) {
            tail = previous; // Update tail if last was deleted
        }

        delete current; // Free memory
        cout << "Task deleted.\n";
    }
}

// Function to mark a task as completed
void markTaskAsCompleted() {
    viewAllTasks(); // Show tasks

    cout << "\nEnter task number to mark as completed: ";
    int taskNumber;
    cin >> taskNumber;

    Task* current = head;
    int index = 1;

    // Find the selected task
    while (current != NULL && index < taskNumber) {
        current = current->next;
        index++;
    }

    if (current == NULL) {
        cout << "Invalid task number.\n";
    } else {
        current->isDone = true;
        cout << "Task marked as completed.\n";
    }
}

// Function to search for tasks containing a keyword
void searchTask() {
    cin.ignore();
    cout << "Enter keyword to search for: ";
    string keyword;
    getline(cin, keyword);

    Task* current = head;
    int index = 1;
    bool found = false;

    cout << "\nSearch Results:\n";
    while (current != NULL) {
        if (current->data.find(keyword) != string::npos) {
            cout << index << ". " << current->data;
            if (current->isDone)
                cout << " [Completed]";
            cout << endl;
            found = true;
        }
        current = current->next;
        index++;
    }

    if (!found) {
        cout << "No tasks found.\n";
    }
}

// Show only completed tasks
void showCompletedTasks() {
    Task* current = head;
    int index = 1;
    bool found = false;

    cout << "\nCompleted Tasks:\n";
    while (current != NULL) {
        if (current->isDone) {
            cout << index << ". " << current->data << " [Completed]\n";
            found = true;
        }
        current = current->next;
        index++;
    }

    if (!found) {
        cout << "No completed tasks.\n";
    }
}

// Show only pending (not completed) tasks
void showPendingTasks() {
    Task* current = head;
    int index = 1;
    bool found = false;

    cout << "\nPending Tasks:\n";
    while (current != NULL) {
        if (!current->isDone) {
            cout << index << ". " << current->data << "\n";
            found = true;
        }
        current = current->next;
        index++;
    }

    if (!found) {
        cout << "No pending tasks.\n";
    }
}

// Free all memory used by the task list
void freeAllTasks() {
    Task* current = head;
    while (current != NULL) {
        Task* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = NULL;
}

// Display the main menu
void displayMenu() {
    cout << "\n=============================\n";
    cout << "         TO-DO LIST\n";
    cout << "————————————————————\n";
    cout << "1. Add Task\n";
    cout << "2. View All Tasks\n";
    cout << "3. Update Task\n";
    cout << "4. Delete Task\n";
    cout << "5. Mark Task as Completed\n";
    cout << "6. Search Task\n";
    cout << "7. Show Completed Tasks\n";
    cout << "8. Show Pending Tasks\n";
    cout << "9. Exit\n";
    cout << "—————————————————-\n";
}

// Main function to run the program
int main() {
    int choice;

    do {
        displayMenu();            // Show options
        cout << "Enter your choice: ";
        cin >> choice;            // Get user choice

        // Call the appropriate function
        switch (choice) {
            case 1: addTask(); break;
            case 2: viewAllTasks(); break;
            case 3: updateTask(); break;
            case 4: deleteTask(); break;
            case 5: markTaskAsCompleted(); break;
            case 6: searchTask(); break;
            case 7: showCompletedTasks(); break;
            case 8: showPendingTasks(); break;
            case 9: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    freeAllTasks(); // Clean up memory before exiting
    return 0;
}
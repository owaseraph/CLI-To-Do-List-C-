#include "list.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main() {
    // Main CLI entry point for the To-Do List application
    string s;
    string name = "default"; // Default export file name
    bool exported = false;   // Tracks if the list has been exported
    List list;               // To-Do list object

    while (true) {
        // Display menu options
        cout << "Welcome to your today's to do list!\n";
        cout << "\nSelect one of the actions below: \n";
        cout << "1. Read tasks from file\n2. Add task\n3. View tasks\n4. Mark as complete a task\n5. Delete completed tasks\n"
             << "6. Export list to Text File\n7. Update exported list\n8. Exit\n\n";

        int c;
        cin >> c;
        cin.ignore(); // Ignore leftover newline character

        switch (c) {
            case 1: {
                // Load tasks from a file
                cout << "Enter the filename: ";
                string filename;
                getline(cin, filename);
                list.LoadfromFile(filename);
                break;
            }
            case 2:
                // Add a new task
                cout << "Enter the name of the task: ";
                getline(cin, s);
                list.AddTask(s);
                break;
            case 3:
                // View all tasks
                list.ViewTasks();
                break;
            case 4: {
                // Mark multiple tasks as complete
                cout << "Which tasks do you want to mark as complete? \nFormat the input as such: no. of task(space)no. of another task, etc.\n";
                list.ViewTasks();
                string input;
                getline(cin, input);
                istringstream iss(input);
                vector<int> taskNumbers;
                int taskNumber;

                // Parse task numbers from user input
                while (iss >> taskNumber) {
                    taskNumbers.push_back(taskNumber);
                }

                if (taskNumbers.empty()) {
                    cout << "No valid task numbers entered.\n";
                } else {
                    list.CompleteTask(taskNumbers);
                    cout << "List updating...\n";
                    list.ViewTasks();
                }
                break;
            }
            case 5:
                // Delete all completed tasks
                cout << "Deleting...\n";
                list.DeleteCompletedTasks();
                cout << "List updating...\n";
                list.ViewTasks();
                break;
            case 6: {
                // Export tasks to a file
                if (exported) {
                    cerr << "You already exported this list!\n";
                    break;
                }
                cout << "Enter the name of the file you want to save as: ";
                getline(cin, name);
                name += ".txt";
                cout << "Exporting...\n";
                list.SaveToFile(name);
                exported = true;
                break;
            }
            case 7: {
                // Update the previously exported file
                if (name == "default") {
                    cerr << "You did not export the to-do list!\n";
                    break;
                }
                ofstream f;
                f.open(name);
                if (!f.is_open()) {
                    cerr << "Could not export safely!\n";
                    break;
                }
                f << list;
                f.close();
                cout << "List updated...\n";
                break;
            }
            case 8:
                // Exit the application
                exit(1);
                break;
            default:
                break;
        }
    }
}
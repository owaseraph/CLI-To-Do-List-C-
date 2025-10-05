#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class List {
    struct Task {
        string title;      // Task title
        bool completed;    // Task completion status

        // Constructor for Task
        Task(string t, bool c) : title(t), completed(c) {}

        // Overload stream operator for Task
        friend ostream& operator<<(ostream& stream, Task task) {
            stream << (task.completed ? "[x] " : "[] ") << task.title;
            return stream;
        }
    };

    vector<Task> tasks; // List of tasks

public:
    // Constructor for List
    List() {}

    // Add a new task to the list
    void AddTask(string title) {
        Task newTask{title, false};
        tasks.push_back(newTask);
    }

    // Get all tasks
    const vector<Task>& GetTasks() {
        return tasks;
    }

    // Get the number of tasks
    int GetNumberofTasks() {
        return tasks.size();
    }

    // Display all tasks
    void ViewTasks() {
        if (tasks.empty()) {
            cerr << "No tasks yet!\n";
            return;
        }
        cout << "Your tasks: \n";
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[x] " : "[] ") << tasks[i].title << "\n";
        }
    }

    // Mark multiple tasks as complete
    void CompleteTask(vector<int> nr) {
        if (tasks.empty()) {
            cerr << "No tasks yet!\n";
            return;
        }
        for (int taskIndex : nr) {
            if (taskIndex < 1 || taskIndex > tasks.size()) {
                cerr << "Invalid task number: " << taskIndex << "\n";
            } else {
                tasks[taskIndex - 1].completed = true;
            }
        }
    }

    // Mark a single task as complete
    void CompleteTask(int choice) {
        if (tasks.empty()) {
            cerr << "No tasks yet!\n";
            return;
        }
        tasks[choice].completed = true;
    }

    // Delete all completed tasks
    void DeleteCompletedTasks() {
        if (tasks.empty()) {
            cerr << "No tasks yet!\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); i++) {
            if (tasks[i].completed == true) {
                tasks.erase(tasks.begin() + i);
                i--; // Adjust index after deletion
            }
        }
    }

    // Load tasks from a file
    void LoadfromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No saved tasks found. Starting fresh...\n";
            return;
        }
        tasks.clear(); // Clear current list

        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            stringstream ss(line);

            string statusStr, title;

            if (!(getline(ss, statusStr, ';')))
                continue;
            if (!(getline(ss, title)))
                continue;

            bool completed = (statusStr == "1");
            tasks.push_back(Task{title, completed});
        }
        file.close();
        cout << "Loaded " << tasks.size() << " tasks from file...\n";
    }

    // Save tasks to a file
    void SaveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not export safely!\n";
            return;
        }

        for (const auto& t : tasks) {
            file << (t.completed ? "[x] " : "[] ") << t.title << "\n";
        }
        file.close();
        cout << "Tasks exported successfully!\n";
    }

    // Overload stream operator for saving tasks
    friend ofstream& operator<<(ofstream& stream, List list) {
        for (const auto& t : list.tasks) {
            stream << (t.completed ? "[x] " : "[] ") << t.title << "\n";
        }
        return stream;
    }
};
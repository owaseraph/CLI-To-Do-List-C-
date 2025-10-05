# To-Do List Application

A feature-rich **To-Do List Application** built with **C++**, offering both **Command-Line Interface (CLI)** and **Graphical User Interface (GUI)** versions. This project is designed to help users manage their daily tasks efficiently, with options to add, view, complete, delete, and export tasks.

---

## Features

### CLI Version
- **Add Tasks**: Add new tasks to your to-do list.
- **View Tasks**: Display all tasks with their completion status.
- **Mark Tasks as Complete**: Mark one or multiple tasks as completed in a single operation.
- **Delete Completed Tasks**: Remove all completed tasks from the list.
- **Export Tasks**: Save your tasks to a text file for future reference.
- **Update Exported List**: Modify and update an already exported list.

### GUI Version
- **Interactive Interface**: Built using **GLFW**, **GLAD**, and **Dear ImGui** for a modern and responsive GUI.
- **Task Management**: Add, view, complete, and delete tasks with intuitive buttons and checkboxes.
- **Export Functionality**: Save your tasks to a file directly from the GUI.
- **Real-Time Updates**: See changes to your task list immediately as you interact with the application.

---

## Project Structure
```bash
├── To-Do-List
│   ├── CMakeLists.txt # Build Configuration #
│   ├── include # Header files #
│   ├── lib # Precompiled libraries #
│   ├── src # Source files #
│   ├── third_party # Third-party libraries (Dear ImGui) #
│   ├── build # Build output directory #
│   ├── .vscode/ # VS Code configuration files #
│   └── README.md # Project documentation
```

## Installation and Setup

### Prerequisites
- **CMake** (3.10 or higher)
- **C++ Compiler** (C++17 support)
- GLFW, GLAD, and Dear ImGui (included in the repository)

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ToDoList.git
   cd ToDoList
2. Create a build directory and configure the project:
    ```bash
    mkdir build
    cd build
    cmake ..
3. Build the project:
    ```bash
    cmake --build .
4. Run the executables:
- CLI Version:
    ```bash
    ./ToDoListCLI
- GUI Version
    ```bash
    ./ToDoListGUI


## Usage

### CLI Version
- Launch the CLI executable and follow the menu to manage tasks.
- Example operations: Add tasks, mark tasks as complete, export tasks to a file.

### GUI Version
- Launch the GUI executable and use the interactive interface to manage tasks.
- Example operations: Add tasks, mark tasks as complete, delete tasks, export tasks.


## Example Task File 
### Sample  ```list.txt``` file format:
    1;Wash Dishes
    0;Clean Bedroom
    0;Feed Cats
    1;Take out Trash
- ```0;``` indicates an **incomplete** task
- ```1;``` indicates a **completed** task

## Technologies Used
- **C++17**: Core programming language.
- **CMake**: Build system generator.
- **GLFW**: Window and input handling for the GUI.
- **GLAD**: OpenGL function loader.
- **Dear ImGui**: GUI framework for the graphical version.

## Contributions
- Contributions are welcome! Open an issue or submit a pull request for new features or improvements.

## License
- This project is licensed under the MIT License.

## Contact
- **Github**: owaseraph
- **Email**: tcaciuc.rares.stefan@gmail.com

#include "list.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int main(){
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "ZMMR", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    string s;
    string name="default";
    bool exported=false;
    List list;
    while(true){
        cout<<"Welcome to your today's to do list!\n";
        cout<<"\nSelect one of the actions below: \n";
        cout<<"1. Read tasks from file\n2. Add task\n3. View tasks\n4. Mark as complete a task\n5. Delete completed tasks\n"<<
        "6. Export list to Text File\n7. Update exported list\n8. Exit\n\n";
        int c;
        cin>>c;
        cin.ignore();
        switch(c){
            case 1:{
                cout<<"Enter the filename: ";
                string filename;
                getline(cin,filename);
                list.LoadfromFile(filename);
                break;
            }
            case 2:
                cout<<"Enter the name of the task: ";
                getline(cin,s);
                list.AddTask(s);
                break;
            case 3:
                list.ViewTasks();
                break;
            case 4:
                cout<<"Which task do you want to mark as complete? ";
                list.ViewTasks();
                int choice;
                cin>>choice;
                list.CompleteTask(choice);
                cout<<"List updating...\n";
                list.ViewTasks();
                break;
            case 5:
                cout<<"Deleting...\n";
                list.DeleteCompletedTasks();
                cout<<"List updating...\n";
                list.ViewTasks();
                break;
            case 6:{
                if(exported){
                    cerr<<"You already exported this list!\n";
                    break;
                }
                cout<<"Enter the name of the file you want to save as: ";
                getline(cin,name);
                name+=".txt";
                cout<<"Exporting...\n";
                list.SaveToFile(name);
                exported=true;
                break;
            }
            case 7:{
                if(name=="default"){
                    cerr<<"You did not export the to-do list!\n";
                    break;
                }
                ofstream f;
                f.open(name);
                if(!f.is_open()){
                    cerr<<"Could not export safely!\n";
                    break;
                }
                f<<list;
                f.close();
                cout<<"List updated...\n";
                break;
            }
            case 8:
                exit(1);
                break;
            default: 
                break;
        }
    }
}
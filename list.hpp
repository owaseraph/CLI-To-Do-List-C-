#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class List{
    struct Task{
        string title;
        bool completed;
        Task(string t, bool c):title(t),completed(c){};
        friend ostream& operator<<(ostream& stream, Task task){
            stream<<(task.completed ? "[x] ":"[] ")<<task.title;
            return stream;
        }
    };
    vector<Task>tasks;
    public:
        List(){};
        void AddTask(string title){
            Task newTask{title, false};
            tasks.push_back(newTask);
        }
        void ViewTasks(void){
           if(tasks.empty()){
                cerr<<"No tasks yet!\n";
                return;
           }
           cout<<"Your tasks: \n";
           for(size_t i=0;i<tasks.size();i++){
            cout<<i+1<<". "<<(tasks[i].completed?"[x] ":"[] ")<<tasks[i].title<<"\n";
           }
        }
        void CompleteTask(int choice){
            if(tasks.empty()){
                cerr<<"No tasks yet!\n";
                return;
            }
            tasks[choice-1].completed=true;
        }
        void DeleteCompletedTasks(void){
            if(tasks.empty()){
                cerr<<"No tasks yet!\n";
                return;
            }
            for(size_t i=0;i<tasks.size();i++){
                if(tasks[i].completed==true){
                    tasks.erase(tasks.begin()+i);
                    i--;
                }
            }
        }
        void UpdateTasks(void){
             if(tasks.empty()){
                cerr<<"No tasks yet!\n";
                return;
            }
            
        }
        friend ofstream& operator<<(ofstream &stream, List list);
};

ofstream& operator<<(ofstream &stream, List list){
    for(size_t i=0;i<list.tasks.size();i++){
        stream<<list.tasks[i]<<"\n";
    }
    return stream;
}
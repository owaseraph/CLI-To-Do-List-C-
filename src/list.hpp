#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
        void LoadfromFile(const string& filename){
            ifstream file(filename);
            if(!file.is_open()){
                cerr<<"No saved tasks found. Starting fresh...\n";
                return;
            }
            tasks.clear(); //clearing the current list

            string line;
            while(getline(file,line)){
                if(line.empty())
                    continue;
                stringstream ss(line);

                string statusStr, title;

                if(!(getline(ss,statusStr,';')))
                    continue;
                if(!(getline(ss,title)))
                    continue;
                
                bool completed = (statusStr=="1");
                tasks.push_back(Task{title,completed});
            }
            file.close();
            cout<<"Loaded "<<tasks.size()<<" tasks from file...\n";

        }
        void SaveToFile(const string& filename){
            ofstream file(filename);
            if(!file.is_open()){
                cerr<<"Could not export safely!\n";
                return;
            }

            for(const auto& t: tasks){
                file<<(t.completed?"[x] ":"[] ")<<t.title<<"\n";
            }
            file.close();
            cout<<"Tasks exported successfully!\n";
        }
        friend ofstream& operator<<(ofstream &stream, List list);
};

ofstream& operator<<(ofstream &stream, List list){
    for(size_t i=0;i<list.tasks.size();i++){
        stream<<list.tasks[i]<<"\n";
    }
    return stream;
}
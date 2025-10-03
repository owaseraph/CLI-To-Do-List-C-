#include "list.hpp"

int main(){
    string s;
    string name="default";
    bool exported=false;
    List list;
    while(true){
        cout<<"Welcome to your today's to do list!\n";
        cout<<"\nSelect one of the actions below: \n";
        cout<<"1. Add task\n2. View tasks\n3. Mark as complete a task\n4. Delete completed tasks\n"<<
        "5. Export list to Text File\n6. Update exported list\n7. Exit\n\n";
        int c;
        cin>>c;
        cin.ignore();
        switch(c){
            case 1:
                cout<<"Enter the name of the task: ";
                getline(cin,s);
                list.AddTask(s);
                break;
            case 2:
                list.ViewTasks();
                break;
            case 3:
                cout<<"Which task do you want to mark as complete? ";
                list.ViewTasks();
                int choice;
                cin>>choice;
                list.CompleteTask(choice);
                cout<<"List updating...\n";
                list.ViewTasks();
                break;
            case 4:
                cout<<"Deleting...\n";
                list.DeleteCompletedTasks();
                cout<<"List updating...\n";
                list.ViewTasks();
                break;
            case 5:{
                if(exported){
                    cerr<<"You already exported this list!\n";
                    break;
                }
                cout<<"Enter the name of the file you want to save as: ";
                getline(cin,name);
                cout<<"Exporting...\n";
                ofstream f;
                f.open(name);
                if(!f.is_open()){
                    cerr<<"Could not export safely!\n";
                    break;
                }
                f<<list;
                exported=true;
                f.close();
                break;
            }
            case 6:{
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
            case 7:
                exit(1);
                break;
            default: 
                break;
        }
    }
}
#include "list.hpp"

int main(){
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
#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;
int listsize=0,idcount=0;
struct student{
    int id;
    int no;
    string name;
};
struct node{
    student data;
    node *next;
};
string mask(){
    string password="";
    char ch;
    cout<<"Enter your password: "<<flush;
    while(1){
        ch=_getch();
        if(ch==13||ch==10){
            cout<<endl;
            break;
        }
        else if(ch==8||ch==127){
            if(password.length()>0){
                password.pop_back();
                cout<<"\b \b"<<flush;
            }
        }
        else{
            password+=ch;
            cout<<'*'<<flush;
        }
    }
    return password;
}
bool verify() {
    string password=mask();
    if(password=="lhm") {
        return true;
    } else {
        cout << "Wrong password!" << endl;
        return false;
    }
}
int menu() {
    system("cls");
    cout << "========== Students Manager ==========\n";
    cout << "1. Add\n";
    cout << "2. Delete\n";
    cout << "3. Search\n";
    cout << "4. Display\n";
    cout << "5. Modify\n";
    cout<<"6. Count\n";
    cout<<"7. Sort\n";
    cout << "8. Save\n";
    cout << "9. Load\n";
    cout << "0. Exit\n";
    cout << "=================================="<<endl;
    cout << "Enter your choice: "<<flush;
    int choice=_getch()-'0';
    cout<<endl;
    return choice;
}
node *initialize(){
    node *head=new node;
    head->data.id=0;
    head->data.no=-1;
    head->data.name="head";
    head->next=NULL;
    return head;
}
void add(node *cur){
    node *temp=new node;
    temp->next=NULL;
    cout<<"Enter number: ";
    cin>>temp->data.no;
    cout<<"Enter name: ";
    cin>>temp->data.name;
    temp->data.id=++idcount;
    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next=temp;
    ++listsize;
    cout<<"ID: "<<idcount<<" added successfully"<<endl;
}
void del(node *cur){
    cout<<"ID to be deleted: ";
    int id;
    cin>>id;
    if(id<=0||id>idcount){
        cout<<"ID: "<<id<<" not found"<<endl;
        return;
    }
    while(cur->next!=NULL){
        if(cur->next->data.id==id){
            node *temp=cur->next;
            cur->next=cur->next->next;
            delete temp;
            --listsize;
            cout<<"Deleted successfully"<<endl;
            return;
        }
        else{
            cur=cur->next;
        }
    }
    cout<<"ID: "<<id<<" not found"<<endl;
}
void search(node *cur){
    cout<<"ID to be searched: ";
    int id;
    cin>>id;
    while(cur->next!=NULL){
        if(cur->next->data.id==id){
            cout<<"ID Number Name"<<endl;
            cout<<cur->next->data.id<<" "<<cur->next->data.no<<" "<<cur->next->data.name<<endl;
            return;
        }
        else{
            cur=cur->next;
        }
    }
    cout<<"ID: "<<id<<" not found"<<endl;
}
void display(node *cur){
    cout<<"ID Number Name"<<endl;
    cur=cur->next;
    while(cur!=NULL){
        cout<<cur->data.id<<" "<<cur->data.no<<" "<<cur->data.name<<endl;
        cur=cur->next;
    }
}
void modify(node *cur){
    cout<<"ID to be modified: ";
    int id;
    cin>>id;
    if(id<=0||id>idcount){
        cout<<"ID: "<<id<<" not found"<<endl;
        return;
    }
    while(cur->next!=NULL){
        if(cur->next->data.id==id){
            cout<<"Enter new number: ";
            cin>>cur->next->data.no;
            cout<<"Enter new name: ";
            cin>>cur->next->data.name;
            cout<<"ID: "<<id<<" modified successfully"<<endl;
            return;
        }
        else{
            cur=cur->next;
        }
    }
    cout<<"ID: "<<id<<" not found"<<endl;
}
node *sort(node *old){
    node *head=initialize(),*minp=old,*newcur=head,*oldcur=old;
    if(listsize>0){
        for(int i=0;i<listsize;++i){
            int minno=old->next->data.no;
            oldcur=old;
            minp=old;
            while(oldcur->next!=NULL){
                if(oldcur->next->data.no<minno){
                    minp=oldcur;
                    minno=minp->next->data.no;
                }
                oldcur=oldcur->next;
            }
            while(newcur->next!=NULL){
                newcur=newcur->next;
            }
            newcur->next=minp->next;
            minp->next=minp->next->next;
            newcur->next->next=NULL;
        }
        delete old;
        cout<<"Sorted successfully"<<endl;
        return head;
    }
    else{
        cout<<"No data to sort"<<endl;
        return old;
    }
}
void save(node *cur){
    ofstream outfile("students.txt");
    outfile << listsize << "," << idcount << endl;
    cur=cur->next;
    while(cur!=NULL){
        outfile << cur->data.id << ","<< cur->data.no << ","<< cur->data.name << endl;
        cur=cur->next;
    }
    cout << "Saved successfully! Total students: " << listsize << ", Last ID: " << idcount << endl;
}
void deleteList(node *head) {
    node *current = head;
    while (current != NULL) {
        node *next = current->next;
        delete current;
        current = next;
    }
}
node *load(){
    ifstream infile("students.txt");
    if(!infile){
        cout<<"Cannot open file for reading"<<endl;
        cout<<"No saved data found. Creating new list."<<endl;
        return initialize();
    }
    string firstLine;
    getline(infile, firstLine);
    size_t commaPos = firstLine.find(",");
    if(commaPos == string::npos){
        cout << "Error: Invalid file format!" << endl;
        infile.close();
        return initialize();
    }
    listsize = stoi(firstLine.substr(0, commaPos));
    int savedIdCount = stoi(firstLine.substr(commaPos + 1));
    node *head = initialize();
    node *current = head;
    string line;
    int studentsLoaded = 0;
    int actualMaxId = 0;
    while(getline(infile, line)){
        if(line.empty()){
            continue;
        }
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        if(pos1 != string::npos && pos2 != string::npos){
            node *newNode = new node;
            newNode->next = NULL;
            newNode->data.id = stoi(line.substr(0, pos1));
            newNode->data.no = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            newNode->data.name = line.substr(pos2 + 1);
            if(newNode->data.id > actualMaxId){
                actualMaxId = newNode->data.id;
            }
            current->next = newNode;
            current = newNode;
            ++studentsLoaded;
        }
    }
    infile.close();
    idcount = actualMaxId;
    if(studentsLoaded != listsize){
        cout << "Warning: Expected " << listsize << " students, but loaded " << studentsLoaded << endl;
        listsize = studentsLoaded;
    }
    if(savedIdCount != actualMaxId){
        cout << "Note: File's idcount was " << savedIdCount << ", but actual max ID is " << actualMaxId << endl;
    }
    cout << "Loaded successfully! Total students: " << listsize << ", Last ID: " << idcount << endl;
    return head;
}
int main(){
    ios::sync_with_stdio(false);
    if(!verify()){
        system("pause");
        return 0;
    }
    node *head=initialize();
    while(1){
        int choice=menu();
        if(choice==0){
            deleteList(head);
            return 0;
        }
        else if(choice==1){
            add(head);
        }
        else if(choice==2){
            del(head);
        }
        else if(choice==3){
            search(head);
        }
        else if(choice==4){
            display(head);
        }
        else if(choice==5){
            modify(head);
        }
        else if(choice==6){
            cout<<"Total number of students: "<<listsize<<endl;
        }
        else if(choice==7){
            head=sort(head);
        }
        else if(choice==8){
            save(head);
        }
        else if(choice==9){
            deleteList(head);
            head=load();
        }
        else{
            cout<<"Invalid choice"<<endl;
        }
        system("pause");
    }
}
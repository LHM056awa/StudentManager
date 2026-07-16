#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
#include<windows.h>
#include<wincrypt.h>
#include<sstream>
#include<iomanip>
#include<limits>
#pragma comment(lib,"advapi32.lib")
struct Student{
    int id,no;
    std::string name;
};
struct Node{
    Student data;
    Node *next;
};
int listsize,idcount;
Node *tail = nullptr;
std::string mask(){
    std::string password;
    char ch;
    std::cout<<"Enter your password: "<<std::flush;
    while(true){
        ch=_getch();
        if(ch==13||ch==10){
            std::cout<<std::endl;
            break;
        }else if(ch==8||ch==127){
            if(password.length()>0){
                password.pop_back();
                std::cout<<"\b \b"<<std::flush;
            }
        }else{
            password+=ch;
            std::cout<<'*'<<std::flush;
        }
    }
    return password;
}
std::string sha256(const std::string& input) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE hash[32]; // SHA256 输出 32 字节
    DWORD hashLen = 32;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        return "";
    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        return "";
    }
    if (!CryptHashData(hHash, (BYTE*)input.c_str(), input.length(), 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return "";
    }
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return "";
    }
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    std::stringstream ss;
    for (DWORD i = 0; i < hashLen; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}
bool verify() {
    std::string password = mask();
    const std::string correctHash = "9e74e921e470e635ef7256f7fde6479070849277f0a0c7e71681e057fa41f25c";
    if (sha256(password) == correctHash) {
        return true;
    } else {
        std::cout << "Wrong password!" << std::endl;
        return false;
    }
}
int menu() {
    system("cls");
    std::cout << "========== Student Manager ==========\n";
    std::cout << "1. Add\n";
    std::cout << "2. Delete\n";
    std::cout << "3. Search\n";
    std::cout << "4. Display\n";
    std::cout << "5. Modify\n";
    std::cout << "6. Count\n";
    std::cout << "7. Sort\n";
    std::cout << "8. Save\n";
    std::cout << "9. Load\n";
    std::cout << "0. Exit\n";
    std::cout << "==================================\n";
    std::cout << "Enter your choice: "<<std::flush;
    char ch = _getch();
    std::cout << ch << std::endl;
    return ch - '0';
}
Node *initialize(){
    Node *head=new Node;
    head->data.id=0;
    head->data.no=-1;
    head->data.name="head";
    head->next=nullptr;
    tail = head;
    return head;
}
void add(Node *cur){
    int no;
    std::cout<<"Enter number: ";
    if(!(std::cin>>no)){
        std::cout<<"Invalid number input."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name;
    std::cout<<"Enter name: ";
    std::getline(std::cin, name);
    Node *temp=new Node;
    temp->next=nullptr;
    temp->data.no=no;
    temp->data.name=name;
    temp->data.id=++idcount;
    if(tail!=nullptr){
        tail->next=temp;
    } else {
        cur->next=temp;
    }
    tail=temp;
    ++listsize;
    std::cout<<"ID: "<<idcount<<" added successfully"<<std::endl;
}
void del(Node *cur){
    std::cout<<"ID to be deleted: ";
    int id;
    if(!(std::cin>>id)){
        std::cout<<"Invalid ID input."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(cur->next!=nullptr){
        if(cur->next->data.id==id){
            Node *temp=cur->next;
            if(temp==tail){
                tail=cur;
            }
            cur->next=temp->next;
            delete temp;
            --listsize;
            std::cout<<"Deleted successfully"<<std::endl;
            return;
        }else{
            cur=cur->next;
        }
    }
    std::cout<<"ID: "<<id<<" not found"<<std::endl;
}
void search(Node *cur){
    std::cout<<"ID to be searched: ";
    int id;
    if(!(std::cin>>id)){
        std::cout<<"Invalid ID input."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(cur->next!=nullptr){
        if(cur->next->data.id==id){
            std::cout<<"ID Number Name"<<std::endl;
            std::cout<<cur->next->data.id<<" "<<cur->next->data.no<<" "<<cur->next->data.name<<std::endl;
            return;
        }else{
            cur=cur->next;
        }
    }
    std::cout<<"ID: "<<id<<" not found"<<std::endl;
}
void display(Node *cur){
    std::cout<<"ID Number Name"<<std::endl;
    cur=cur->next;
    while(cur!=nullptr){
        std::cout<<cur->data.id<<" "<<cur->data.no<<" "<<cur->data.name<<std::endl;
        cur=cur->next;
    }
}
void modify(Node *cur){
    std::cout<<"ID to be modified: ";
    int id;
    if(!(std::cin>>id)){
        std::cout<<"Invalid ID input."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(cur->next!=nullptr){
        if(cur->next->data.id==id){
            std::cout<<"Enter new number: ";
            if(!(std::cin>>cur->next->data.no)){
                std::cout<<"Invalid number input."<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Enter new name: ";
            std::getline(std::cin, cur->next->data.name);
            std::cout<<"ID: "<<id<<" modified successfully"<<std::endl;
            return;
        }else{
            cur=cur->next;
        }
    }
    std::cout<<"ID: "<<id<<" not found"<<std::endl;
}
Node *sortlist(Node *old){
    if(listsize>0){
        Node *head=initialize(),*minp=old,*newcur=head,*oldcur=old;
        for(int i=0;i<listsize;++i){
            int minno=old->next->data.no;
            oldcur=old;
            minp=old;
            while(oldcur->next!=nullptr){
                if(oldcur->next->data.no<minno){
                    minp=oldcur;
                    minno=minp->next->data.no;
                }
                oldcur=oldcur->next;
            }
            while(newcur->next!=nullptr){
                newcur=newcur->next;
            }
            newcur->next=minp->next;
            minp->next=minp->next->next;
            newcur->next->next=nullptr;
            tail = newcur->next;
        }
        delete old;
        std::cout<<"Sorted successfully"<<std::endl;
        return head;
    }else{
        std::cout<<"No data to sort"<<std::endl;
        return old;
    }
}
void save(Node *cur){
    std::ofstream outfile("students.csv");
    outfile << listsize << "," << idcount << std::endl;
    cur=cur->next;
    while(cur!=nullptr){
        outfile << cur->data.id << ","<< cur->data.no << ","<< cur->data.name << std::endl;
        cur=cur->next;
    }
    std::cout << "Saved successfully to students.csv! Total students: " << listsize << ", Last ID: " << idcount << std::endl;
}
void reset(Node *head) {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    idcount=0;
    listsize=0;
    tail = nullptr;
}
Node *load(){
    std::ifstream infile("students.csv");
    if(!infile){
        std::cout<<"Cannot open file for reading"<<std::endl;
        std::cout<<"No saved data found. Creating new list."<<std::endl;
        return initialize();
    }
    std::string firstLine;
    if(!std::getline(infile, firstLine) || firstLine.empty()){
        std::cout << "Error: Invalid file format!" << std::endl;
        infile.close();
        return initialize();
    }
    size_t commaPos = firstLine.find(",");
    if(commaPos == std::string::npos){
        std::cout << "Error: Invalid file format!" << std::endl;
        infile.close();
        return initialize();
    }
    int savedListSize;
    int savedIdCount;
    try{
        savedListSize = std::stoi(firstLine.substr(0, commaPos));
        savedIdCount = std::stoi(firstLine.substr(commaPos + 1));
    }catch(...){
        std::cout << "Error: Invalid file header!" << std::endl;
        infile.close();
        return initialize();
    }
    if(savedListSize < 0 || savedIdCount < 0){
        std::cout << "Error: Invalid file header values!" << std::endl;
        infile.close();
        return initialize();
    }
    Node *head = initialize();
    Node *current = head;
    std::string line;
    int studentsLoaded = 0;
    int actualMaxId = 0;
    bool badFormat = false;
    while(std::getline(infile, line)){
        if(line.empty()){
            continue;
        }
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        if(pos1 == std::string::npos || pos2 == std::string::npos){
            badFormat = true;
            break;
        }
        Node *newNode = new Node;
        newNode->next = nullptr;
        try{
            newNode->data.id = std::stoi(line.substr(0, pos1));
            newNode->data.no = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        }catch(...){
            delete newNode;
            badFormat = true;
            break;
        }
        newNode->data.name = line.substr(pos2 + 1);
        if(newNode->data.id <= 0){
            delete newNode;
            badFormat = true;
            break;
        }
        current->next = newNode;
        current = newNode;
        tail = newNode;
        ++studentsLoaded;
        if(newNode->data.id > actualMaxId){
            actualMaxId = newNode->data.id;
        }
    }
    infile.close();
    if(badFormat){
        std::cout << "Error: Invalid file format! Loading aborted." << std::endl;
        reset(head);
        return initialize();
    }
    if(studentsLoaded == 0){
        tail = head;
    }
    listsize = studentsLoaded;
    idcount = std::max(savedIdCount, actualMaxId);
    if(savedListSize != studentsLoaded){
        std::cout << "Warning: Expected " << savedListSize << " students, but loaded " << studentsLoaded << std::endl;
    }
    if(savedIdCount != idcount){
        std::cout << "Note: File's idcount was " << savedIdCount << ", effective max ID is " << idcount << std::endl;
    }
    std::cout << "Loaded successfully! Total students: " << listsize << ", Last ID: " << idcount << std::endl;
    return head;
}
int main(){
    std::ios::sync_with_stdio(false);
    if(!verify()){
        system("pause");
        return 0;
    }
    Node *head=initialize();
    while(true){
        int choice=menu();
        switch(choice){
            case 0:reset(head);return 0;
            case 1:add(head);break;
            case 2:del(head);break;
            case 3:search(head);break;
            case 4:display(head);break;
            case 5:modify(head);break;
            case 6:std::cout<<"Total number of students: "<<listsize<<std::endl;break;
            case 7:head=sortlist(head);break;
            case 8:save(head);break;
            case 9:reset(head);head=load();break;
            default:std::cout<<"Invalid choice"<<std::endl;
        }
        system("pause");
    }
}
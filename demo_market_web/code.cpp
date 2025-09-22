#include <bits/stdc++.h>
using namespace std;

// Forward declaration
class farmer;

// Global storage
vector<farmer> farm;   // all farmers
vector<class company> comp;  // all companies
set<string> u_farmer;  // unique farmer emails
set<string> u_company; // unique company emails

// Farmer class
class farmer {
public:
    string fname; // name
    string eid;   // email/id
    long number;
    int age;
    string location;
    string pass;

    vector<pair<int, pair<string,double>>> tcrop; // crops {index, {name, qty}}
    vector<string> orders; // orders received

    farmer(string id1, string password) {
        eid = id1;
        pass = password;
    }

    void add_crop(int index, string cropname, double qty){
        tcrop.push_back({index, {cropname, qty}});
    }

    void show_crop(){
        for(auto &it : tcrop){
            cout << "Product index: " << it.first 
                 << ", Name: " << it.second.first 
                 << ", Quantity: " << it.second.second << endl;
        }
    }
};

// Company class
class company {
public:
    string cname;
    string cid;
    string pass;
    long number;
    string location;
    vector<string> orders; // orders placed

    company(string id1, string password) {
        cid = id1;
        pass = password;
    }

    void take_order(int ordernum) {
        for (auto &f : farm) { // iterate global vector of farmers
            for(auto &it : f.tcrop){
                if(ordernum == it.first){
                    orders.push_back(it.second.first);   // company records order
                    f.orders.push_back(it.second.first); // farmer notified
                }
            }
        }
    }
};

// Function declarations
int menu();
void farmer_register(string id, string pass);
void company_register(string id, string pass);
void login_farmer(string id, string pass);
void login_company(string id, string pass);
void farmer_page(farmer &f);
void company_page(company &c);

// Menu
int menu() {
    cout << "1) Farmer\n2) Industry\n3) Exit\nChoose: ";
    int choice;
    cin >> choice;
    return choice;
}

// Farmer Registration
void farmer_register(string id, string pass) {
    string name, location;
    int age;
    long number;

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Location: ";
    cin >> location;
    cout << "Enter Phone Number: ";
    cin >> number;

    farmer f(id, pass);
    f.fname = name;
    f.age = age;
    f.location = location;
    f.number = number;

    farm.push_back(f);
    u_farmer.insert(id);
    cout << "Farmer Registered Successfully!\n";
}

// Company Registration
void company_register(string id, string pass) {
    string name, location;
    long number;

    cout << "Enter Company Name: ";
    cin >> name;
    cout << "Enter Location: ";
    cin >> location;
    cout << "Enter Phone Number: ";
    cin >> number;

    company c(id, pass);
    c.cname = name;
    c.location = location;
    c.number = number;

    comp.push_back(c);
    u_company.insert(id);
    cout << "Company Registered Successfully!\n";
}

// Farmer Login
void login_farmer(string id, string pass) {
    for (auto &f : farm) {
        if (f.eid == id && f.pass == pass) {
            cout << "Welcome, Farmer " << f.fname << "!\n";
            farmer_page(f);
            return;
        }
    }
    cout << "Invalid Farmer Credentials!\n";
}

// Company Login
void login_company(string id, string pass) {
    for (auto &c : comp) {
        if (c.cid == id && c.pass == pass) {
            cout << "Welcome, Company " << c.cname << "!\n";
            company_page(c);
            return;
        }
    }
    cout << "Invalid Company Credentials!\n";
}

// Farmer Page
void farmer_page(farmer &f){
    while(true){
        int ch;
        cout<<"1)Add crop \n3)Order detail \n4)User detail\n5)Support\n6)Logout\nChoice: ";
        cin>>ch;

        switch(ch){
            case 1: {
                int n;
                cout<<"How many crops: ";
                cin>>n;
                for(int i=0;i<n;i++){
                    string crop;
                    double qty;
                    cout<<"Enter crop "<<i+1<<" name: ";
                    cin>>crop;
                    cout<<"Enter Quantity in quentle: ";
                    cin>>qty;
                    f.add_crop(i+1,crop,qty);
                }
                cout<<"Crops added successfully\n";
                break;
            }
            case 3:
                if(f.orders.empty()){
                    cout<<"No orders\n";
                } else {
                    cout<<"----Order details----\n";
                    for(auto &o:f.orders) cout<<o<<endl;
                }
                break;
            case 4:
                cout<<"Name: "<<f.fname<<endl;
                cout<<"Age: "<<f.age<<endl;
                cout<<"Email: "<<f.eid<<endl;
                break;
            case 5:
                cout<<"Contact number: 999999999\nEmail-id: help@gmail.com\n"<<endl;
                break;
            case 6:
                return;
            default:
                cout<<"Invalid choice"<<endl;
                break;
        }
    }
}

// Company Page
void company_page(company &c){
    while(true){
        int ch;
        cout<<"1)Detail\n2)Place order\n3)Order history\n4)Support\n5)Logout\nChoice: ";
        cin>>ch;

        switch (ch){
            case 1:
                cout<<"Company Name: "<<c.cname<<endl;
                cout<<"Email: "<<c.cid<<endl;
                cout<<"Location: "<<c.location<<endl;
                cout<<"Phone: "<<c.number<<endl;
                break;
            case 2: {
                cout<<"Available crops:\n";
                for(auto &f : farm){
                    cout<<"Farmer: "<<f.fname<<" ("<<f.location<<")\n";
                    f.show_crop();
                    cout<<"----------------------\n";
                }
                int opt;
                cout<<"How many orders to place: ";
                cin>>opt;
                for(int i=0;i<opt;i++){
                    int ordernum;
                    cout<<"Enter crop index to order: ";
                    cin>>ordernum;
                    c.take_order(ordernum);
                }
                break;
            }
            case 3:
                if(c.orders.empty()){
                    cout<<"No orders\n";
                } else {
                    cout<<"----Order history----\n";
                    for(auto &it:c.orders) cout<<it<<endl;
                }
                break;
            case 4:
                cout<<"Contact number: 999999999\nEmail-id: help@gmail.com\n"<<endl;
                break;
            case 5:
                return;
            default:
                cout<<"Invalid choice"<<endl;
                break;
        }
    }
}

// Main
int main() {
    while(true){
        int choose = menu();
        if(choose == 3) break;

        int option;
        cout << "1) Login\n2) Register\nChoice: ";
        cin >> option;

        string id, pass;
        cout << "Enter email-id: ";
        cin >> id;

        if(option == 2){ // Register
            if(choose==1 && u_farmer.count(id)){
                cout<<"Email already registered!\n";
                continue;
            }
            if(choose==2 && u_company.count(id)){
                cout<<"Email already registered!\n";
                continue;
            }

            cout<<"Enter password: ";
            cin>>pass;

            if(choose==1)
                farmer_register(id, pass);
            else
                company_register(id, pass);
        }
        else if(option == 1){ // Login
            cout<<"Enter password: ";
            cin>>pass;

            if(choose==1)
                login_farmer(id, pass);
            else
                login_company(id, pass);
        }
    }

    return 0;
}

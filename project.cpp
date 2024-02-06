#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class Contact
{
public:
    string name;
    vector <string> phone;
    string email;
    string address;
    static vector<Contact> contacts;
    Contact(string name, const vector <string> phone, string email, string address)
    {
        this->name = name;
        this->phone = phone;
        this->email = email;
        this->address = address;
    }
    static void create_contact();
    static void modify_contact();
    static void delete_contact();
    static void search_contact();
    static void display_contact();
    static void save_contacts(const string &filename);
    static void load_contacts(const string &filename);
};

vector<Contact> Contact::contacts;

void Contact::create_contact()
{
    string name, phone, email, address;
    vector <string> phones;
    cout << "Enter name: ";
    getline(cin, name);
    char choice;
    do
    {
        cout<<"Enter Phone: ";
        getline(cin, phone);
        phones.push_back(phone);
        cout<<"Do you want to add another phone number? (y/n): ";
        cin>>choice;
        cin.ignore();
    } while (choice=='y' || choice=='Y');
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter address: ";
    getline(cin, address);
    Contact contact(name, phones, email, address);
    contacts.push_back(contact);
    cout << endl;
    cout << "Contact Created Successfully!" << endl;
}
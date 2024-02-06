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
  vector<string> phone;
  string email;
  string address;
  static vector<Contact> contacts;
  Contact(string name, const vector<string> phone, string email, string address)
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
  vector<string> phones;
  cout << "Enter name: ";
  getline(cin, name);
  char choice;
  do
  {
    cout << "Enter Phone: ";
    getline(cin, phone);
    phones.push_back(phone);
    cout << "Do you want to add another phone number? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice == 'y' || choice == 'Y');
  cout << "Enter email: ";
  getline(cin, email);
  cout << "Enter address: ";
  getline(cin, address);
  Contact contact(name, phones, email, address);
  contacts.push_back(contact);
  cout << endl;
  cout << "Contact Created Successfully!" << endl;
}

void Contact::modify_contact()
{
  string name;
  cout << "Enter the name of the contact you want to modify: ";
  getline(cin, name);

  auto it = find_if(contacts.begin(), contacts.end(), [name](const Contact &c)
                    { return c.name == name; });

  if (it != contacts.end())
  {
    int modifyChoice;
    do
    {
      cout << endl;
      cout << "Modify Contact: " << it->name << endl;
      cout << "1. Name" << endl;
      cout << "2. Phone " << endl;
      cout << "3. Email" << endl;
      cout << "4. Address" << endl;
      cout << "5. Finish Modification" << endl;
      cout << "Enter your choice: ";
      cin >> modifyChoice;
      cin.ignore();

      switch (modifyChoice)
      {
      case 1:
        cout << "Enter new name: ";
        getline(cin, it->name);
        break;
      case 2:
        cout << "Phone Numbers:" << endl;
        for (size_t i = 0; i < it->phone.size(); ++i)
        {
          cout << i + 1 << ". " << it->phone[i] << endl;
        }
        cout << "a. Add Phone Number" << endl;
        cout << "r. Remove Phone Number" << endl;
        cout << "Enter index to modify existing phone number: ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (isdigit(choice))
        {
          int index = choice - '0';
          if (index >= 1 && index <= it->phone.size())
          {
            cout << "Enter new phone number: ";
            getline(cin, it->phone[index - 1]);
          }
          else
          {
            cout << "Invalid index!" << endl;
          }
        }
        else if (choice == 'a' || choice == 'A')
        {
          cout << "Enter new phone number: ";
          string newPhone;
          getline(cin, newPhone);
          it->phone.push_back(newPhone);
        }
        else if (choice == 'r' || choice == 'R')
        {
          cout << "Enter index to remove phone number: ";
          int index;
          cin >> index;
          cin.ignore();
          if (index >= 1 && index <= it->phone.size())
          {
            it->phone.erase(it->phone.begin() + index - 1);
          }
          else
          {
            cout << "Invalid index!" << endl;
          }
        }
        else
        {
          cout << "Invalid choice!" << endl;
        }
        break;
      case 3:
        cout << "Enter new email: ";
        getline(cin, it->email);
        break;
      case 4:
        cout << "Enter new address: ";
        getline(cin, it->address);
        break;
      case 5:
        cout << "Contact modified successfully!" << endl;
        break;
      default:
        cout << "Invalid Choice!" << endl;
        break;
      }
    } while (modifyChoice != 5);
  }
  else
  {
    cout << "Contact not found!" << endl;
  }
}

void Contact::delete_contact()
{
  string name;
  cout << "Enter the name of the contact you want to delete: ";
  getline(cin, name);

  vector<Contact>::iterator it = find_if(contacts.begin(), contacts.end(), [name](const Contact &c)
                                         { return c.name == name; });

  if (it != contacts.end())
  {
    contacts.erase(it);
    cout << "Contact deleted successfully!" << endl;
  }
  else
  {
    cout << endl;
    cout << "Contact not found!" << endl;
  }
}

void Contact::search_contact()
{
  string name;
  cout << "Enter the name you want to search: ";
  getline(cin, name);
  bool found = false;
  for (int i = 0; i < contacts.size(); i++)
  {
    if (contacts[i].name == name)
    {
      cout << "--------------------------------------" << endl;
      cout << "Name: " << contacts[i].name << endl;
      cout << "Phone Numbers:" << endl;
      for (const string &phoneNumber : contacts[i].phone)
      {
        cout << phoneNumber << endl;
      }
      cout << "Email: " << contacts[i].email << endl;
      cout << "Address: " << contacts[i].address << endl;
      cout << "--------------------------------------" << endl;
      found = true;
      break;
    }
  }
  if (!found)
  {
    cout << endl;
    cout << "Contact not Found!" << endl;
  }
}

void Contact::display_contact()
{
  if (contacts.size() == 0)
  {
    cout << endl
         << "No Contacts Found!" << endl;
  }
  else
  {
    sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b)
         { return a.name < b.name; });
    cout << "======================================" << endl;
    cout << "Contacts List:" << endl;
    cout << "======================================" << endl;

    for (const Contact &contact : contacts)
    {
      cout << "Name: " << contact.name << endl;
      cout << "Phone: ";
      for (const string &phoneNumber : contact.phone)
      {
        cout << phoneNumber << " " << endl;
      }
      cout << "Email: " << contact.email << endl;
      cout << "Address: " << contact.address << endl;
      cout << "--------------------------------------" << endl;
    }
  }
}

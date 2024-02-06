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
  string phone;
  string email;
  string address;
  static vector<Contact> contacts;
  Contact(string name, string phone, string email, string address)
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

  cout << "Enter name: ";
  getline(cin, name);
  cout << "Enter phone: ";
  getline(cin, phone);
  cout << "Enter email: ";
  getline(cin, email);
  cout << "Enter address: ";
  getline(cin, address);
  Contact contact(name, phone, email, address);
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
      cout << "2. Phone" << endl;
      cout << "3. Email" << endl;
      cout << "4. Address" << endl;
      cout << "5. Finish Modification" << endl;
      cout << "Enter your choice: ";
      cin >> modifyChoice;
      cin.ignore(); // Consume the newline character left in the buffer

      switch (modifyChoice)
      {
      case 1:
        cout << "Enter new name: ";
        getline(cin, it->name);
        break;
      case 2:
        cout << "Enter new phone: ";
        getline(cin, it->phone);
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
      cout << "Phone: " << contacts[i].phone << endl;
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
    cout << endl;
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
      cout << "Name:    " << contact.name << endl;
      cout << "Phone:   " << contact.phone << endl;
      cout << "Email:   " << contact.email << endl;
      cout << "Address: " << contact.address << endl;
      cout << "--------------------------------------" << endl;
    }
  }
}

void Contact::save_contacts(const string &filename)
{
  ofstream outFile(filename);
  if (!outFile.is_open())
  {
    cerr << "Error opening file for writing: " << filename << endl;
    return;
  }

  for (const Contact &contact : contacts)
  {
    outFile << contact.name << ',' << contact.phone << ',' << contact.email << ',' << contact.address << '\n';
  }

  outFile.close();
  cout << "Contacts saved to file successfully!" << endl;
}

void Contact::load_contacts(const string &filename)
{
  ifstream inFile(filename);
  if (!inFile.is_open())
  {
    cerr << "Error opening file for reading: " << filename << endl;
    return;
  }

  contacts.clear();

  string line;
  while (getline(inFile, line))
  {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    size_t pos3 = line.find(',', pos2 + 1);

    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos)
    {
      string name = line.substr(0, pos1);
      string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
      string email = line.substr(pos2 + 1, pos3 - pos2 - 1);
      string address = line.substr(pos3 + 1);

      Contact contact(name, phone, email, address);
      contacts.push_back(contact);
    }
  }

  inFile.close();
  cout << "Contacts loaded from file successfully!" << endl;
}

int main()
{
  int choice;
  const string filename = "contacts.txt";
  Contact::load_contacts(filename);
  do
  {
    cout << endl;
    cout << "Welcome to Contact Management System!" << endl;
    cout << endl;
    cout << "1. Create Contact" << endl;
    cout << "2. Modify Contact" << endl;
    cout << "3. Delete Contact" << endl;
    cout << "4. Search Contact" << endl;
    cout << "5. Display Contact" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      cin.ignore();
      Contact::create_contact();
      break;
    case 2:
      cin.ignore();
      Contact::modify_contact();
      break;
    case 3:
      cin.ignore();
      Contact::delete_contact();
      break;
    case 4:
      cin.ignore();
      Contact::search_contact();
      break;
    case 5:
      Contact::display_contact();
      break;
    case 6:
      Contact::save_contacts(filename);
      cout << "Exiting the Program..." << endl;
      exit(0);
    default:
      cout << "Invalid Choice!" << endl;
      break;
    }
  } while (choice != 6);
  return 0;
}
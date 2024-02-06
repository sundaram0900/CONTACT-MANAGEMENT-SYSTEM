void Contact::modify_contact()
{
    string name;
    cout << "Enter the name of the contact you want to modify: ";
    getline(cin, name);

    auto it = find_if(contacts.begin(), contacts.end(), [name](const Contact &c) {
        return c.name == name;
    });

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
                    } else
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

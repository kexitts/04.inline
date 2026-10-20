
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Abonent
{
private:
    string name;
    string homePhone;
    string workPhone;
    string mobilePhone;
    string info;

    static int count;

public:
    Abonent() : Abonent("", "", "", "", "")
    {
    }

    Abonent(string n, string mobile)
        : Abonent(n, "", "", mobile, "")
    {
    }

    Abonent(string n, string h, string w, string m, string i)
    {
        name = n;
        homePhone = h;
        workPhone = w;
        mobilePhone = m;
        info = i;
        count++;
    }

    Abonent(const Abonent& a)
        : Abonent(a.name, a.homePhone, a.workPhone,
            a.mobilePhone, a.info)
    {
    }

    ~Abonent()
    {
        count--;
    }

    void Input()
    {
        cout << "Enter full name: ";
        getline(cin >> ws, name);

        cout << "Enter home phone: ";
        getline(cin, homePhone);

        cout << "Enter work phone: ";
        getline(cin, workPhone);

        cout << "Enter mobile phone: ";
        getline(cin, mobilePhone);

        cout << "Enter additional info: ";
        getline(cin, info);
    }

    void Show() const
    {
        cout << "\nName: " << name << endl;
        cout << "Home phone: " << homePhone << endl;
        cout << "Work phone: " << workPhone << endl;
        cout << "Mobile phone: " << mobilePhone << endl;
        cout << "Info: " << info << endl;
        cout << "------------------------" << endl;
    }

    string GetName() const
    {
        return name;
    }

    bool HasPhone(string phone) const
    {
        return homePhone == phone ||
            workPhone == phone ||
            mobilePhone == phone;
    }

    static int GetCount()
    {
        return count;
    }

    void SaveToFile(string filename) const
    {
        ofstream file(filename);

        if (!file)
        {
            cout << "File error!" << endl;
            return;
        }

        file << name << endl;
        file << homePhone << endl;
        file << workPhone << endl;
        file << mobilePhone << endl;
        file << info << endl;

        file.close();
        cout << "Abonent saved!" << endl;
    }

    bool LoadFromFile(string filename)
    {
        ifstream file(filename);

        if (!file)
        {
            cout << "File not found!" << endl;
            return false;
        }

        string n, h, w, m, i;

        if (!getline(file, n) ||
            !getline(file, h) ||
            !getline(file, w) ||
            !getline(file, m) ||
            !getline(file, i))
        {
            cout << "Invalid file!" << endl;
            return false;
        }

        name = n;
        homePhone = h;
        workPhone = w;
        mobilePhone = m;
        info = i;

        return true;
    }
};

int Abonent::count = 0;


class PhoneBook
{
private:
    Abonent* abonents;
    int countAbonent;

public:
    PhoneBook()
    {
        abonents = nullptr;
        countAbonent = 0;
    }

    PhoneBook(const PhoneBook&) = delete;
    PhoneBook& operator=(const PhoneBook&) = delete;

    ~PhoneBook()
    {
        delete[] abonents;
    }

    void Add(const Abonent& a)
    {
        Abonent* temp = new Abonent[countAbonent + 1];

        for (int i = 0; i < countAbonent; i++)
        {
            temp[i] = abonents[i];
        }

        temp[countAbonent] = a;

        delete[] abonents;
        abonents = temp;
        countAbonent++;

        cout << "Abonent added!" << endl;
    }

    void Delete(string phone)
    {
        int index = -1;

        for (int i = 0; i < countAbonent; i++)
        {
            if (abonents[i].HasPhone(phone))
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Abonent not found!" << endl;
            return;
        }

        Abonent* temp = nullptr;

        if (countAbonent > 1)
        {
            temp = new Abonent[countAbonent - 1];

            int j = 0;

            for (int i = 0; i < countAbonent; i++)
            {
                if (i != index)
                {
                    temp[j] = abonents[i];
                    j++;
                }
            }
        }

        delete[] abonents;
        abonents = temp;
        countAbonent--;

        cout << "Abonent deleted!" << endl;
    }

    void SearchByName(string name) const
    {
        bool found = false;

        for (int i = 0; i < countAbonent; i++)
        {
            if (abonents[i].GetName() == name)
            {
                abonents[i].Show();
                found = true;
            }
        }

        if (!found)
        {
            cout << "Abonent not found!" << endl;
        }
    }

    void SearchByPhone(string phone) const
    {
        bool found = false;

        for (int i = 0; i < countAbonent; i++)
        {
            if (abonents[i].HasPhone(phone))
            {
                abonents[i].Show();
                found = true;
            }
        }

        if (!found)
        {
            cout << "Abonent not found!" << endl;
        }
    }

    void ShowAll() const
    {
        if (countAbonent == 0)
        {
            cout << "Phone book is empty!" << endl;
            return;
        }

        for (int i = 0; i < countAbonent; i++)
        {
            abonents[i].Show();
        }
    }

    int GetCount() const
    {
        return countAbonent;
    }

    void SaveOne(int index, string filename) const
    {
        if (index < 0 || index >= countAbonent)
        {
            cout << "Invalid abonent number!" << endl;
            return;
        }

        abonents[index].SaveToFile(filename);
    }

    void LoadOne(string filename)
    {
        Abonent a;

        if (a.LoadFromFile(filename))
        {
            Add(a);
        }
    }
};


int main()
{
    PhoneBook book;
    int choice;

    do
    {
        cout << "\n===== PHONE BOOK =====" << endl;
        cout << "1. Add abonent" << endl;
        cout << "2. Delete abonent" << endl;
        cout << "3. Search by name" << endl;
        cout << "4. Search by phone" << endl;
        cout << "5. Show all" << endl;
        cout << "6. Save one abonent to file" << endl;
        cout << "7. Load one abonent from file" << endl;
        cout << "8. Show abonent count" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1)
        {
            Abonent a;
            a.Input();
            book.Add(a);
        }
        else if (choice == 2)
        {
            string phone;

            cout << "Enter phone: ";
            cin >> phone;

            book.Delete(phone);
        }
        else if (choice == 3)
        {
            string name;

            cout << "Enter full name: ";
            getline(cin >> ws, name);

            book.SearchByName(name);
        }
        else if (choice == 4)
        {
            string phone;

            cout << "Enter phone: ";
            cin >> phone;

            book.SearchByPhone(phone);
        }
        else if (choice == 5)
        {
            book.ShowAll();
        }
        else if (choice == 6)
        {
            int number;

            book.ShowAll();

            cout << "Enter abonent number (1-"
                << book.GetCount() << "): ";
            cin >> number;

            book.SaveOne(number - 1, "abonent.txt");
        }
        else if (choice == 7)
        {
            book.LoadOne("abonent.txt");
        }
        else if (choice == 8)
        {
            cout << "Abonents in phone book: "
                << book.GetCount() << endl;

            cout << "Existing Abonent objects: "
                << Abonent::GetCount() << endl;
        }

    } while (choice != 0);

    return 0;
}

#include<iostream>
#include<string>
#include<fstream>
#include<sstream> //string stream
using namespace std;

class User {
private:
    string userID;
    string password;
    string name;
    string bloodGroup;

    bool registered = false;

public:

    void saveUser()
    {
        ofstream file("Data/users.txt", ios::app);

        file << userID << ","
             << password << ","
             << name << ","
             << bloodGroup << endl;

        file.close();
    }
    bool loadUser(string loginID, string loginPassword)
    {
        ifstream file("Data/users.txt");

        if(!file.is_open())
        {
            cout << "File failed to open." << endl;
            return false;
        }


        string line;

        while(getline(file, line))
        {

            stringstream ss(line);

            string fileID;
            string filePassword;

            getline(ss, fileID, ',');
            getline(ss, filePassword, ',');
            

            if(fileID == loginID && filePassword == loginPassword)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void registration() {
        if (registered == false) {
            cout << "======User Registration======" << endl;

            cout << "Enter User ID: ";
            cin >> userID;

            cout << "Enter Password: ";
            cin >> password;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Blood Group: ";
            cin >> bloodGroup;

            cout << "Registration Successful." << endl;

            registered = true;

            saveUser();
        }
        else {
            cout << "User already registered. Please login." << endl;
        }
    }

    bool login() {
        string loginID;
        string loginPassword;

        cout << "======User Login======" << endl;

        cout << "Enter User ID: ";
        cin >> loginID;

        cout << "Enter Password: ";
        cin >> loginPassword;


        if(loadUser(loginID, loginPassword))
        {
            return true;
        }
        else
        {
            cout << "Invalid User ID or Password." << endl;
            return false;
        }
    }


};

class Donor {
public:
    void donorMenu() {
        int choice;

        while (true) {
            cout << "\n======Donor Menu======" << endl;
            cout << "1. History" << endl;
            cout << "2. Donate" << endl;
            cout << "3. Notification" << endl;
            cout << "4. Logout" << endl;

            cout << "Enter choice: ";
            cin >> choice;


            switch (choice) {
                case 1:
                    cout << "======Donation History======" << endl;
                    cout << "No donation history available." << endl;
                    break;


                case 2: {
                    int donationType;
                    string details;
                    string address;

                    cout << "======Donate Blood======" << endl;

                    cout << "1. Regular" << endl;
                    cout << "2. Emergency" << endl;

                    cout << "Select Donation Type: ";
                    cin >> donationType;

                    cin.ignore();

                    cout << "Enter Donation Details: ";
                    getline(cin, details);

                    cout << "Enter Address: ";
                    getline(cin, address);


                    if (donationType == 1) {
                        cout << "Donation Type: Regular" << endl;
                    } else if (donationType == 2) {
                        cout << "Donation Type: Emergency" << endl;
                    }


                    cout << "Hospital Name: City Hospital" << endl;
                    cout << "Donation Time: 10:00 AM" << endl;

                    break;
                }


                case 3:
                    cout << "======Notification======" << endl;
                    cout << "No new notifications available." << endl;
                    break;


                case 4:
                    return;


                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }
};

class Receiver {
public:

    void receiverMenu() {
        int choice;

        while (true) {
            cout << "\n======Receiver Menu======" << endl;
            cout << "1. History" << endl;
            cout << "2. Notification" << endl;
            cout << "3. Apply" << endl;
            cout << "4. Logout" << endl;

            cout << "Enter choice: ";
            cin >> choice;


            switch (choice) {
                case 1:
                    cout << "======Request History======" << endl;
                    cout << "No request history available." << endl;
                    break;


                case 2:
                    cout << "======Notifications======" << endl;
                    cout << "No new notifications available." << endl;
                    break;


                case 3:
                    cout << "Application Submitted." << endl;
                    break;


                case 4:
                    return;


                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }
};

class Hospital
{
public:

    void hospitalMenu()
    {
        int donor;
        int decision;


        cout << "======Hospital Menu======" << endl;

        cout << "Donor Requests Available." << endl;

        cout << "Select Donor:" << endl;
        cout << "1. Donor 1" << endl;
        cout << "2. Donor 2" << endl;

        cin >> donor;


        cout << "Selected Donor: Donor " << donor << endl;


        cout << "1. Approve" << endl;
        cout << "2. Reject" << endl;

        cout << "Enter choice: ";
        cin >> decision;


        if (decision == 1) {
            cout << "Donor Approved." << endl;
        } else if (decision == 2) {
            cout << "Donor Rejected." << endl;
        } else {
            cout << "Invalid Choice." << endl;
        }


        cout << "======Updated Blood Stock======" << endl;
        cout << "Blood Stock Updated Successfully." << endl;
    }

};

class Admin
{
public:

    void adminMenu()
    {
        int choice;

        while (true) {
            cout << "\n======Admin Menu======" << endl;
            cout << "1. Donor View" << endl;
            cout << "2. Receiver View" << endl;
            cout << "3. Hospital Bank Queue" << endl;
            cout << "4. Live Stock" << endl;
            cout << "5. Logout" << endl;

            cout << "Enter choice: ";
            cin >> choice;


            switch (choice) {
                case 1:
                    cout << "======Donor Information======" << endl;
                    cout << "No donor information available." << endl;
                    break;


                case 2:
                    cout << "======Receiver Information======" << endl;
                    cout << "No receiver information available." << endl;
                    break;


                case 3:
                    cout << "======Hospital Bank Queue======" << endl;
                    cout << "No pending blood requests." << endl;
                    break;


                case 4:
                    cout << "======Blood Stock======" << endl;
                    cout << "No blood stock information available." << endl;
                    break;


                case 5:
                    return;


                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }

};
class BloodBankSystem {

public:

    User user;

    void userTypeMenu() {

        int choice;


        while (true) {
            cout << "\n======User Type======" << endl;

            cout << "1. Donor" << endl;
            cout << "2. Receiver" << endl;
            cout << "3. Admin" << endl;
            cout << "4. Hospital" << endl;
            cout << "5. Exit" << endl;


            cout << "Enter choice: ";
            cin >> choice;


            switch (choice) {
                case 1:
                    Donor donor;
                    donor.donorMenu();
                    break;

                case 2:
                    Receiver receiver;
                    receiver.receiverMenu();
                    break;

                case 3:
                    Admin admin;
                    admin.adminMenu();
                    break;

                case 4:
                    Hospital hospital;
                    hospital.hospitalMenu();
                    break;

                case 5:
                    return;

                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }

    void start() {
        bool firstTime = true;
        int choice;

        while (true) {
            if (firstTime) {
                cout << "======Welcome to Blood Bank Life======" << endl;
                firstTime = false;
            }


            cout << "\n======Main Menu======" << endl;
            cout << "1. User Registration" << endl;
            cout << "2. User Login" << endl;
            cout << "3. Exit" << endl;


            cout << "Enter choice: ";
            cin >> choice;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Input." << endl;
                continue;
            }


            switch (choice) {
                case 1:
                    user.registration();
                    break;


                case 2:
                    if (user.login()) {
                        userTypeMenu();
                    }
                    break;


                case 3:
                    cout << "Exiting program..." << endl;
                    return;


                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }

};


int main() {

    BloodBankSystem bankSystem;

    bankSystem.start();

    return 0;
}


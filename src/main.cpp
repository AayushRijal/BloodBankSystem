#include<iostream>
#include<string>
using namespace std;

string userID;
string password;
string name;
string bloodGroup;

bool registered = false;


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
    } else {
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


    if (loginID == userID && loginPassword == password) {
        return true;
    } else {
        cout << "Invalid User ID or Password." << endl;
        return false;
    }
}


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


void adminMenu() {
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


void hospitalMenu() {
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
                donorMenu();
                break;

            case 2:
                receiverMenu();
                break;

            case 3:
                adminMenu();
                break;

            case 4:
                hospitalMenu();
                break;

            case 5:
                return;

            default:
                cout << "Invalid Choice." << endl;
        }
    }
}


int main() {
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


        switch (choice) {
            case 1:
                registration();
                break;


            case 2:
                if (login()) {
                    userTypeMenu();
                }
                break;


            case 3:
                cout << "Exiting program..." << endl;
                return 0;


            default:
                cout << "Invalid Choice." << endl;
        }
    }
    return 0;
}



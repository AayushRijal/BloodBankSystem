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
            string fileName;
            string fileBloodGroup;

            getline(ss, fileID, ',');
            getline(ss, filePassword, ',');
            getline(ss, fileName, ',');
            getline(ss, fileBloodGroup, ',');

            if(fileID == loginID && filePassword == loginPassword)
            {
                userID = fileID;
                password = filePassword;
                name = fileName;
                bloodGroup = fileBloodGroup;

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool userExists(string id)
    {
        ifstream file("Data/users.txt");

        if (!file.is_open())
        {
            return false;
        }

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string fileID;

            getline(ss, fileID, ',');

            if (fileID == id)
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

            if (userExists(userID))
            {
                cout << "User ID already exists. Please use a different User ID." << endl;
                return;
            }

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
    string getUserID() {
        return userID;
    }


};

class Donor {
public:

    void donorHistory(string userID) {
        ifstream file("Data/donations.txt");

        if (!file.is_open()) {
            cout << "No donation history available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "======Donation History======" << endl;

        while (getline(file, line)) {

            stringstream ss(line);

            string donorID;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorID, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (donorID == userID) {
                cout << "\nDonation Type: " << donationType;
                cout << "\nDetails: " << details;
                cout << "\nAddress: " << address;
                cout << "\nStatus: " << status << endl;

                found = true;
            }
        }

        file.close();

        if (!found) {
            cout << "No donation history available." << endl;
        }
    }


    void donateBlood(string userID) {

        int donationType;
        string details;
        string address;

        cout << "======Donate Blood======" << endl;

        cout << "1. Regular" << endl;
        cout << "2. Emergency" << endl;

        cout << "Select Donation Type: ";
        cin >> donationType;

        if (donationType != 1 && donationType != 2) {
            cout << "Invalid Donation Type." << endl;
            return;
        }

        cin.ignore();

        cout << "Enter Donation Details: ";
        getline(cin, details);

        cout << "Enter Address: ";
        getline(cin, address);

        string type;

        if (donationType == 1) {
            type = "Regular";
        }
        else {
            type = "Emergency";
        }

        ofstream file("Data/donations.txt", ios::app);

        if (!file.is_open()) {
            cout << "Unable to save donation." << endl;
            return;
        }

        file << userID << ","
             << type << ","
             << details << ","
             << address << ","
             << "Pending" << endl;

        file.close();

        saveNotification(userID, "Your donation request has been submitted and is pending approval.");

        cout << "\nDonation Request Submitted." << endl;
        cout << "Status: Pending" << endl;
    }


    void donorMenu(string userID) {

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
                    donorHistory(userID);
                    break;

                case 2:
                    donateBlood(userID);
                    break;

                case 3:
                    showNotifications(userID);
                    break;

                case 4:
                    return;

                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }
    void saveNotification(string userID, string message) {

        ofstream file("Data/notifications.txt", ios::app);

        if (!file.is_open()) {
            cout << "Unable to save notification." << endl;
            return;
        }

        file << userID << "," << message << endl;

        file.close();
    }
    void showNotifications(string userID) {

        ifstream file("Data/notifications.txt");

        if (!file.is_open()) {
            cout << "No notifications available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "======Notifications======" << endl;

        while (getline(file, line)) {

            stringstream ss(line);

            string notificationUserID;
            string message;

            getline(ss, notificationUserID, ',');
            getline(ss, message);

            if (notificationUserID == userID) {

                cout << "- " << message << endl;

                found = true;
            }
        }

        file.close();

        if (!found) {
            cout << "No new notifications available." << endl;
        }
    }
};

class Receiver {
public:

    void receiverHistory(string userID) {

        ifstream file("Data/requests.txt");

        if (!file.is_open()) {
            cout << "No request history available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "======Request History======" << endl;

        while (getline(file, line)) {

            stringstream ss(line);

            string receiverID;
            string bloodGroup;
            string quantity;
            string reason;
            string status;

            getline(ss, receiverID, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');
            getline(ss, reason, ',');
            getline(ss, status, ',');

            if (receiverID == userID) {

                cout << "\nBlood Group: " << bloodGroup;
                cout << "\nQuantity: " << quantity;
                cout << "\nReason: " << reason;
                cout << "\nStatus: " << status << endl;

                found = true;
            }
        }

        file.close();

        if (!found) {
            cout << "No request history available." << endl;
        }
    }


    void applyBlood(string userID) {

        string bloodGroup;
        string quantity;
        string reason;

        cout << "======Apply for Blood======" << endl;

        cout << "Enter Blood Group: ";
        cin >> bloodGroup;

        cout << "Enter Quantity: ";
        cin >> quantity;

        cin.ignore();

        cout << "Enter Reason: ";
        getline(cin, reason);


        ofstream file("Data/requests.txt", ios::app);

        if (!file.is_open()) {
            cout << "Unable to save blood request." << endl;
            return;
        }

        file << userID << ","
             << bloodGroup << ","
             << quantity << ","
             << reason << ","
             << "Pending" << endl;

        file.close();


        // Save notification
        ofstream notificationFile("Data/notifications.txt", ios::app);

        if (notificationFile.is_open()) {

            notificationFile
                << userID << ","
                << "Your blood request has been submitted and is pending approval."
                << endl;

            notificationFile.close();
        }


        cout << "\nBlood Request Submitted." << endl;
        cout << "Status: Pending" << endl;
    }


    void showNotifications(string userID) {

        ifstream file("Data/notifications.txt");

        if (!file.is_open()) {
            cout << "No notifications available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "======Notifications======" << endl;

        while (getline(file, line)) {

            stringstream ss(line);

            string notificationUserID;
            string message;

            getline(ss, notificationUserID, ',');
            getline(ss, message);

            if (notificationUserID == userID) {

                cout << "- " << message << endl;

                found = true;
            }
        }

        file.close();

        if (!found) {
            cout << "No new notifications available." << endl;
        }
    }


    void receiverMenu(string userID) {

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
                    receiverHistory(userID);
                    break;

                case 2:
                    showNotifications(userID);
                    break;

                case 3:
                    applyBlood(userID);
                    break;

                case 4:
                    return;

                default:
                    cout << "Invalid Choice." << endl;
            }
        }
    }
};

class BloodStock
{
public:

    void showStock()
    {
        ifstream file("Data/bloodstock.txt");

        if (!file.is_open())
        {
            cout << "Blood stock file not found." << endl;
            return;
        }

        string line;

        cout << "\n======Blood Stock======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string bloodGroup;
            string quantity;

            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');

            cout << bloodGroup << " : " << quantity << " units" << endl;
        }

        file.close();
    }


    int getStock(string bloodGroup)
    {
        ifstream file("Data/bloodstock.txt");

        if (!file.is_open())
        {
            return 0;
        }

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string fileBloodGroup;
            string quantity;

            getline(ss, fileBloodGroup, ',');
            getline(ss, quantity, ',');

            if (fileBloodGroup == bloodGroup)
            {
                file.close();
                return stoi(quantity);
            }
        }

        file.close();

        return 0;
    }


    void updateStock(string bloodGroup, int change)
    {
        ifstream file("Data/bloodstock.txt");

        if (!file.is_open())
        {
            cout << "Blood stock file not found." << endl;
            return;
        }

        string lines[8];
        int total = 0;

        string line;

        while (getline(file, line))
        {
            lines[total] = line;
            total++;
        }

        file.close();


        for (int i = 0; i < total; i++)
        {
            stringstream ss(lines[i]);

            string fileBloodGroup;
            string quantity;

            getline(ss, fileBloodGroup, ',');
            getline(ss, quantity, ',');

            if (fileBloodGroup == bloodGroup)
            {
                int currentStock = stoi(quantity);
                int newStock = currentStock + change;

                if (newStock < 0)
                {
                    cout << "Not enough blood in stock." << endl;
                    return;
                }

                lines[i] = bloodGroup + "," + to_string(newStock);

                break;
            }
        }


        ofstream outputFile("Data/bloodstock.txt");

        if (!outputFile.is_open())
        {
            cout << "Unable to update blood stock." << endl;
            return;
        }

        for (int i = 0; i < total; i++)
        {
            outputFile << lines[i] << endl;
        }

        outputFile.close();
    }
};

class Hospital
{
public:

    void showDonorRequests()
    {
        ifstream file("Data/donations.txt");

        if (!file.is_open())
        {
            cout << "No donor requests available." << endl;
            return;
        }

        string line;
        int count = 0;

        cout << "\n======Donor Requests======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string donorID;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorID, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                count++;

                cout << "\nDonor " << count << endl;
                cout << "User ID: " << donorID << endl;
                cout << "Donation Type: " << donationType << endl;
                cout << "Details: " << details << endl;
                cout << "Address: " << address << endl;
                cout << "Status: " << status << endl;
            }
        }

        file.close();

        if (count == 0)
        {
            cout << "No pending donor requests." << endl;
        }
    }


    void updateDonorRequest()
    {
        ifstream file("Data/donations.txt");

        if (!file.is_open())
        {
            cout << "No donor requests available." << endl;
            return;
        }

        string lines[100];
        int total = 0;

        string line;

        while (getline(file, line))
        {
            lines[total] = line;
            total++;
        }

        file.close();

        int pendingCount = 0;

        cout << "\n======Pending Donor Requests======" << endl;

        for (int i = 0; i < total; i++)
        {
            stringstream ss(lines[i]);

            string donorID;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorID, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                pendingCount++;

                cout << pendingCount << ". "
                     << "Donor ID: " << donorID
                     << " | Blood Group: " << donationType
                     << " | Address: " << address << endl;
            }
        }

        if (pendingCount == 0)
        {
            cout << "No pending donor requests." << endl;
            return;
        }

        int selected;
        cout << "\nSelect Donor: ";
        cin >> selected;

        if (selected < 1 || selected > pendingCount)
        {
            cout << "Invalid Choice." << endl;
            return;
        }

        int currentPending = 0;

        for (int i = 0; i < total; i++)
        {
            stringstream ss(lines[i]);

            string donorID;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorID, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                currentPending++;

                if (currentPending == selected)
                {
                    int decision;

                    cout << "\nSelected Donor: " << donorID << endl;

                    cout << "1. Approve" << endl;
                    cout << "2. Reject" << endl;

                    cout << "Enter choice: ";
                    cin >> decision;

                    if (decision == 1)
                    {
                        status = "Approved";
                        addDonatedBlood(donorID);

                        lines[i] = donorID + "," +
                                   donationType + "," +
                                   details + "," +
                                   address + "," +
                                   status;

                        ofstream notificationFile(
                            "Data/notifications.txt",
                            ios::app
                        );

                        if (notificationFile.is_open())
                        {
                            notificationFile
                                << donorID << ","
                                << "Your donation request has been approved."
                                << endl;

                            notificationFile.close();
                        }

                        cout << "\nDonor Approved." << endl;
                    }
                    else if (decision == 2)
                    {
                        status = "Rejected";

                        lines[i] = donorID + "," +
                                   donationType + "," +
                                   details + "," +
                                   address + "," +
                                   status;

                        ofstream notificationFile(
                            "Data/notifications.txt",
                            ios::app
                        );

                        if (notificationFile.is_open())
                        {
                            notificationFile
                                << donorID << ","
                                << "Your donation request has been rejected."
                                << endl;

                            notificationFile.close();
                        }

                        cout << "\nDonor Rejected." << endl;
                    }
                    else
                    {
                        cout << "Invalid Choice." << endl;
                        return;
                    }

                    break;
                }
            }
        }

        ofstream outputFile("Data/donations.txt");

        if (!outputFile.is_open())
        {
            cout << "Unable to update donation records." << endl;
            return;
        }

        for (int i = 0; i < total; i++)
        {
            outputFile << lines[i] << endl;
        }

        outputFile.close();
    }


    void hospitalMenu()
    {
        int choice;

        while (true)
        {
            cout << "\n======Hospital Menu======" << endl;

            cout << "1. View Donor Requests" << endl;
            cout << "2. Approve / Reject Donor" << endl;
            cout << "3. View Blood Requests" << endl;
            cout << "4. Approve / Reject Blood Request" << endl;
            cout << "5. Logout" << endl;
            cout << "6. View Blood Stock" << endl;

            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    showDonorRequests();
                    break;

                case 2:
                    updateDonorRequest();
                    break;

                case 3:
                    showReceiverRequests();
                    break;

                case 4:
                    updateReceiverRequest();
                    break;

                case 5:
                    return;

                case 6:
                {
                    BloodStock stock;
                    stock.showStock();
                    break;
                }

                default:
                    cout << "Invalid Choice." << endl;
            }
        }

    }
    void showReceiverRequests()
    {
        ifstream file("Data/requests.txt");

        if (!file.is_open())
        {
            cout << "No blood requests available." << endl;
            return;
        }

        string line;
        int count = 0;

        cout << "\n======Blood Requests======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string receiverID;
            string bloodGroup;
            string quantity;
            string reason;
            string status;

            getline(ss, receiverID, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');
            getline(ss, reason, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                count++;

                cout << "\nRequest " << count << endl;
                cout << "Receiver ID: " << receiverID << endl;
                cout << "Blood Group: " << bloodGroup << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Reason: " << reason << endl;
                cout << "Status: " << status << endl;
            }
        }

        file.close();

        if (count == 0)
        {
            cout << "No pending blood requests." << endl;
        }
    }

    void updateReceiverRequest()
{
    ifstream file("Data/requests.txt");

    if (!file.is_open())
    {
        cout << "No blood requests available." << endl;
        return;
    }

    string lines[100];
    int total = 0;

    string line;

    while (getline(file, line))
    {
        lines[total] = line;
        total++;
    }

    file.close();

    int pendingCount = 0;

    cout << "\n======Pending Blood Requests======" << endl;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string receiverID;
        string bloodGroup;
        string quantity;
        string reason;
        string status;

        getline(ss, receiverID, ',');
        getline(ss, bloodGroup, ',');
        getline(ss, quantity, ',');
        getline(ss, reason, ',');
        getline(ss, status, ',');

        if (status == "Pending")
        {
            pendingCount++;

            cout << pendingCount << ". "
                 << "Receiver ID: " << receiverID
                 << " | Blood Group: " << bloodGroup
                 << " | Quantity: " << quantity << endl;
        }
    }

    if (pendingCount == 0)
    {
        cout << "No pending blood requests." << endl;
        return;
    }

    int selected;

    cout << "\nSelect Request: ";
    cin >> selected;

    if (selected < 1 || selected > pendingCount)
    {
        cout << "Invalid Choice." << endl;
        return;
    }

    int currentPending = 0;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string receiverID;
        string bloodGroup;
        string quantity;
        string reason;
        string status;

        getline(ss, receiverID, ',');
        getline(ss, bloodGroup, ',');
        getline(ss, quantity, ',');
        getline(ss, reason, ',');
        getline(ss, status, ',');

        if (status == "Pending")
        {
            currentPending++;

            if (currentPending == selected)
            {
                int decision;

                cout << "\nSelected Receiver: " << receiverID << endl;
                cout << "Blood Group: " << bloodGroup << endl;
                cout << "Quantity Requested: " << quantity << endl;

                cout << "1. Approve" << endl;
                cout << "2. Reject" << endl;

                cout << "Enter choice: ";
                cin >> decision;

                if (decision == 1)
                {
                    int requestedQuantity = stoi(quantity);

                    BloodStock stock;

                    int availableStock = stock.getStock(bloodGroup);

                    if (availableStock < requestedQuantity)
                    {
                        cout << "\nNot enough blood in stock." << endl;
                        cout << "Available: "
                             << availableStock << " units" << endl;
                        cout << "Requested: "
                             << requestedQuantity << " units" << endl;

                        return;
                    }

                    stock.updateStock(
                        bloodGroup,
                        -requestedQuantity
                    );

                    status = "Approved";

                    lines[i] = receiverID + "," +
                               bloodGroup + "," +
                               quantity + "," +
                               reason + "," +
                               status;

                    ofstream notificationFile(
                        "Data/notifications.txt",
                        ios::app
                    );

                    if (notificationFile.is_open())
                    {
                        notificationFile
                            << receiverID << ","
                            << "Your blood request has been approved."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nBlood stock updated: -"
                         << requestedQuantity
                         << " " << bloodGroup << endl;

                    cout << "Blood Request Approved." << endl;
                }
                else if (decision == 2)
                {
                    status = "Rejected";

                    lines[i] = receiverID + "," +
                               bloodGroup + "," +
                               quantity + "," +
                               reason + "," +
                               status;

                    ofstream notificationFile(
                        "Data/notifications.txt",
                        ios::app
                    );

                    if (notificationFile.is_open())
                    {
                        notificationFile
                            << receiverID << ","
                            << "Your blood request has been rejected."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nBlood Request Rejected." << endl;
                }
                else
                {
                    cout << "Invalid Choice." << endl;
                    return;
                }

                break;
            }
        }
    }

    ofstream outputFile("Data/requests.txt");

    if (!outputFile.is_open())
    {
        cout << "Unable to update request records." << endl;
        return;
    }

    for (int i = 0; i < total; i++)
    {
        outputFile << lines[i] << endl;
    }

    outputFile.close();
}

    void addDonatedBlood(string donorID)
{
    ifstream file("Data/users.txt");

    if (!file.is_open())
    {
        cout << "Unable to find user data." << endl;
        return;
    }

    string line;
    string bloodGroup;

    while (getline(file, line))
    {
        stringstream ss(line);

        string fileID;
        string password;
        string name;
        string fileBloodGroup;

        getline(ss, fileID, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, fileBloodGroup, ',');

        if (fileID == donorID)
        {
            bloodGroup = fileBloodGroup;
            break;
        }
    }

    file.close();

    if (bloodGroup.empty())
    {
        cout << "Donor blood group not found." << endl;
        return;
    }

    BloodStock stock;

    stock.updateStock(bloodGroup, 1);

    cout << "Blood stock updated: +" << bloodGroup << endl;
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
                    donor.donorMenu(user.getUserID());
                    break;

                case 2:
                    Receiver receiver;
                    receiver.receiverMenu(user.getUserID());
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


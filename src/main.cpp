#include<iostream>
#include<string>
#include<fstream>
#include<sstream> //string stream -> allows to combine multiple outputs in 1 string
#include<cctype> // For character checking functions like isdigit()
using namespace std;

// Helper: accept only the eight standard blood-group labels used by this program.
bool validBloodGroup(string bloodGroup)
{
    return bloodGroup == "A+" ||
           bloodGroup == "A-" ||
           bloodGroup == "B+" ||
           bloodGroup == "B-" ||
           bloodGroup == "AB+" ||
           bloodGroup == "AB-" ||
           bloodGroup == "O+" ||
           bloodGroup == "O-";
}

// Helper: phone number must contain exactly 10 numeric digits.
bool validPhoneNumber(string phoneNumber)
{
    if (phoneNumber.length() != 10)
    {
        return false;
    }

    for (char c : phoneNumber)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}
//Removes unnecessary spaces, tabs, and carriage returns from the beginning and end of a string.
string trim(string text)
{
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t'))
    {
        text.erase(text.begin());
    }

    while (!text.empty() && (text.back() == ' ' || text.back() == '\t' || text.back() == '\r'))
    {
        text.pop_back();
    }

    return text;
}

// SECTION 1 — USER: stores account details and handles registration, login, and personal reports.
class User {
private:
    string phoneNumber;
    string password;
    string name;
    string bloodGroup;
    string accountType;
    bool registered = false;  // Tracks whether registration has occurred during the current program session.

public:

    // Saves a newly registered user's information by appending a record to the users file.
    bool saveUser()
    {
        ofstream file("Data/users.txt", ios::app); //append mode to prevent overwriting

        if (!file.is_open())
        {
            cout << "Unable to save user data." << endl;
            return false;
        }
        //store info in file
        file << phoneNumber << ","
        << password << ","
        << name << ","
        << bloodGroup << ","
        << accountType << endl;

        file.close();

        return true;
    }

    // Read users.txt, split each comma-separated record, and find matching login credentials.
    bool loadUser(string loginPhoneNumber, string loginPassword)
    {
        ifstream file("Data/users.txt");

        if(!file.is_open())
        {
            cout << "File failed to open." << endl;
            return false;
        }

        string line;

        //reads and checks each saved user records.
        while(getline(file, line))
        {
            // Split this comma-separated line into its individual fields.
            stringstream ss(line);

            string filePhoneNumber;
            string filePassword;
            string fileName;
            string fileBloodGroup;
            string fileAccountType;

            //split csv records to fields
            getline(ss, filePhoneNumber, ',');
            getline(ss, filePassword, ',');
            getline(ss, fileName, ',');
            getline(ss, fileBloodGroup, ',');
            getline(ss, fileAccountType, ',');

            //trim/remove unwanted spaces
            filePhoneNumber = trim(filePhoneNumber);
            filePassword = trim(filePassword);
            fileName = trim(fileName);
            fileBloodGroup = trim(fileBloodGroup);
            fileAccountType = trim(fileAccountType);

            if(filePhoneNumber == loginPhoneNumber && filePassword == loginPassword)
            { //load saved info to User object
                phoneNumber = filePhoneNumber;
                password = filePassword;
                name = fileName;
                bloodGroup = fileBloodGroup;
                accountType = fileAccountType;

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    // Search existing user records to prevent registering the same phone number twice.
    bool userExists(string phoneNumberToCheck)
    {
        // ifstream opens saved user records for reading.
        ifstream file("Data/users.txt");

        if (!file.is_open())
        {
            return false;
        }

        string line;

        //search each record for the phone number
        while (getline(file, line))
        {
            stringstream ss(line);

            string filePhoneNumber;

            getline(ss, filePhoneNumber, ',');

            if (filePhoneNumber == phoneNumberToCheck)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

//register a user after validating input
    void registration() {
        if (registered == false) {
            cout << "======User Registration======" << endl;

            cout << "Enter Phone Number: ";
            cin >> phoneNumber;

            if (!validPhoneNumber(phoneNumber))
            {
                cout << "Invalid Phone Number. Enter exactly 10 digits." << endl;
                return;
            }

            if (userExists(phoneNumber))
            {
                cout << "Phone Number already exists. Please use a different Phone Number." << endl;
                return;
            }

            cout << "Enter Password: ";
            cin >> password;

            if (!validPassword(password))
            {
                cout << "Invalid Password. Password must be at least 4 characters." << endl;
                return;
            }


            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Blood Group: ";
            cin >> bloodGroup;

            if (!validBloodGroup(bloodGroup))
            {
                cout << "Invalid blood group." << endl;
                return;
            }

            accountType = "User"; //default

            if (saveUser())
            {
                cout << "Registration Successful." << endl;
                registered = true;
            }
        }
        else {
            cout << "User already registered. Please login." << endl;
        }
    }


    bool login() {
        string loginPhoneNumber;
        string loginPassword;

        cout << "======User Login======" << endl;

        cout << "Enter Phone Number: ";
        cin >> loginPhoneNumber;

        cout << "Enter Password: ";
        cin >> loginPassword;

        if(loadUser(loginPhoneNumber, loginPassword))
        {
            return true;
        }
        else
        {
            cout << "Invalid Phone Number or Password." << endl;
            return false;
        }
    }


    string getPhoneNumber() {
        return phoneNumber; //returns the phone number when function called. getter functio
    }


    string getAccountType()
    {
        return accountType;
    }


    bool validPassword(string password)
    {
        return password.length() >= 4;
    }


    // Generates and saves a report containing personal details,
    // donation history, blood requests, and notifications.

    void generateReport()
{
        // Create a separate report filename for each user.
    string reportFileName = "Data/report_" + phoneNumber + ".txt";

    ofstream reportFile(reportFileName);

    if (!reportFile.is_open())
    {
        cout << "Unable to generate report." << endl;
        return;
    }

    string donationHistory[100];
    int donationHistoryCount = 0;

    string receivingHistory[100];
    int receivingHistoryCount = 0;

    string notificationHistory[100];
    int notificationHistoryCount = 0;

    int totalDonations = 0;
    int approvedDonations = 0;
    int pendingDonations = 0;
    int rejectedDonations = 0;

    int totalRequests = 0;
    int approvedRequests = 0;
    int pendingRequests = 0;
    int rejectedRequests = 0;

    int totalBloodReceived = 0;

    // Read donation history
    ifstream donationFile("Data/donations.txt");

    if (donationFile.is_open())
    {
        string line;

        while (getline(donationFile, line))
        {
            stringstream ss(line);

            string donorPhoneNumber;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorPhoneNumber, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (donorPhoneNumber == phoneNumber)
            {
                totalDonations++;

                if (status == "Approved")
                {
                    approvedDonations++;
                }
                else if (status == "Pending")
                {
                    pendingDonations++;
                }
                else if (status == "Rejected")
                {
                    rejectedDonations++;
                }

                if (donationHistoryCount < 100)
                {
                    donationHistory[donationHistoryCount] =
                        donationType + " | " +
                        details + " | Address: " +
                        address + " | Status: " +
                        status;

                    donationHistoryCount++;
                }
            }
        }

        donationFile.close();
    }

    // Read blood receiving history
    ifstream requestFile("Data/requests.txt");

    if (requestFile.is_open())
    {
        string line;

        while (getline(requestFile, line))
        {
            stringstream ss(line);

            string receiverPhoneNumber;
            string bloodGroup;
            string quantity;
            string reason;
            string status;

            getline(ss, receiverPhoneNumber, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');
            getline(ss, reason, ',');
            getline(ss, status, ',');

            if (receiverPhoneNumber == phoneNumber)
            {
                totalRequests++;

                if (status == "Approved")
                {
                    approvedRequests++;
                    if (!quantity.empty())
                    {
                        totalBloodReceived += stoi(quantity);
                    }
                }
                else if (status == "Pending")
                {
                    pendingRequests++;
                }
                else if (status == "Rejected")
                {
                    rejectedRequests++;
                }

                if (receivingHistoryCount < 100)
                {
                    receivingHistory[receivingHistoryCount] =
                        bloodGroup + " | " +
                        quantity + " units | Reason: " +
                        reason + " | Status: " +
                        status;

                    receivingHistoryCount++;
                }
            }
        }

        requestFile.close();
    }

    // Read notifications from file
    ifstream notificationFile("Data/notifications.txt");

    if (notificationFile.is_open())
    {
        string line;

        while (getline(notificationFile, line))
        {
            stringstream ss(line);

            string notificationPhoneNumber;
            string message;

            getline(ss, notificationPhoneNumber, ',');
            getline(ss, message);

            if (notificationPhoneNumber == phoneNumber)
            {
                if (notificationHistoryCount < 100)
                {
                    notificationHistory[notificationHistoryCount] = message;
                    notificationHistoryCount++;
                }
            }
        }

        notificationFile.close();
    }

    stringstream report;

    report << "========================================" << endl;
    report << "       BLOOD BANK LIFE - MY REPORT      " << endl;
    report << "========================================" << endl;

    report << "\nPersonal Information" << endl;
    report << "Phone Number: " << phoneNumber << endl;
    report << "Name: " << name << endl;
    report << "Blood Group: " << bloodGroup << endl;

    report << "\n------ Donation Summary ------" << endl;
    report << "Total Donation Requests: " << totalDonations << endl;
    report << "Approved: " << approvedDonations << endl;
    report << "Pending: " << pendingDonations << endl;
    report << "Rejected: " << rejectedDonations << endl;

    report << "\n------ Blood Receiving Summary ------" << endl;
    report << "Total Blood Requests: " << totalRequests << endl;
    report << "Approved: " << approvedRequests << endl;
    report << "Pending: " << pendingRequests << endl;
    report << "Rejected: " << rejectedRequests << endl;
    report << "Total Blood Received: "
           << totalBloodReceived << " units" << endl;

    report << "\n------ Donation History ------" << endl;

    if (donationHistoryCount == 0)
    {
        report << "No donation history available." << endl;
    }
    else
    {
        for (int i = 0; i < donationHistoryCount; i++)
        {
            report << i + 1 << ". "
                   << donationHistory[i] << endl;
        }
    }

    report << "\n------ Blood Receiving History ------" << endl;

    if (receivingHistoryCount == 0)
    {
        report << "No blood receiving history available." << endl;
    }
    else
    {
        for (int i = 0; i < receivingHistoryCount; i++)
        {
            report << i + 1 << ". "
                   << receivingHistory[i] << endl;
        }
    }

    report << "\n------ Notifications ------" << endl;

    if (notificationHistoryCount == 0)
    {
        report << "No notifications available." << endl;
    }
    else
    {
        for (int i = 0; i < notificationHistoryCount; i++)
        {
            report << i + 1 << ". "
                   << notificationHistory[i] << endl;
        }
    }

    report << "\n========================================" << endl;
    report << "              End of Report             " << endl;
    report << "========================================" << endl;

    cout << "\n" << report.str();

    reportFile << report.str();

    reportFile.close();

    cout << "\nReport saved to: " << reportFileName << endl;
}

};

// SECTION 2 — DONOR: handles donation requests, donation history, and donor notifications.
class Donor {
public:

    // Read donation records and display only records belonging to this donor.

    void donorHistory(string phoneNumber)
    {
        ifstream file("Data/donations.txt");

        if (!file.is_open())
        {
            cout << "No donation history available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "\n====== Donation History ======" << endl;

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

            if (donorID == phoneNumber)
            {
                cout << "\nDonation Type: " << donationType << endl;
                cout << "Details: " << details << endl;
                cout << "Address: " << address << endl;
                cout << "Status: " << status << endl;

                found = true;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No donation history available." << endl;
        }
    }


    void donateBlood(string phoneNumber) {

        int donationType;
        string details;
        string address;

        cout << "====== Donate Blood ======" << endl;

        cout << "1. Regular" << endl;
        cout << "2. Emergency" << endl;

        cout << "\nSelect Donation Type: ";
        cin >> donationType;

        if (donationType != 1 && donationType != 2) {
            cout << "\nInvalid Donation Type." << endl;
            return;
        }

        cin.ignore(1000, '\n');

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
            cout << "\nUnable to save donation." << endl;
            return;
        }

        file << phoneNumber << ","
             << type << ","
             << details << ","
             << address << ","
             << "Pending" << endl;

        file.close();

        saveNotification(phoneNumber, "Your donation request has been submitted and is pending approval.");

        cout << "\nDonation Request Submitted." << endl;
        cout << "Status: Pending" << endl;
    }


    void donorMenu(string phoneNumber)
    {
        int choice;

        while (true)
        {
            cout << "\n====== Donor Menu ======" << endl;
            cout << "1. History" << endl;
            cout << "2. Donate" << endl;
            cout << "3. Notification" << endl;
            cout << "4. Logout" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            // Clear invalid input state and discard the bad input before showing the menu again.
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                    donorHistory(phoneNumber);
                    break;

                case 2:
                    donateBlood(phoneNumber);
                    break;

                case 3:
                    showNotifications(phoneNumber);
                    break;

                case 4:
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }


    void saveNotification(string phoneNumber, string message) {

        ofstream file("Data/notifications.txt", ios::app);

        if (!file.is_open()) {
            cout << "Unable to save notification." << endl;
            return;
        }

        file << phoneNumber << "," << message << endl;

        file.close();
    }

    // Read notifications and display only messages addressed to this user.
    void showNotifications(string phoneNumber)
    {
        ifstream file("Data/notifications.txt");

        if (!file.is_open())
        {
            cout << "No notifications available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "\n====== Notifications ======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string notificationphoneNumber;
            string message;

            getline(ss, notificationphoneNumber, ',');
            getline(ss, message);

            if (notificationphoneNumber == phoneNumber)
            {
                cout << "- " << message << endl;

                found = true;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No new notifications available." << endl;
        }
    }
};

// SECTION 3 — RECEIVER: handles blood requests, request history, and receiver notifications.
class Receiver {
public:

    // Read request records and show the logged-in receiver's own history.
    void receiverHistory(string phoneNumber)
    {
        ifstream file("Data/requests.txt");

        if (!file.is_open())
        {
            cout << "No request history available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "\n====== Request History ======" << endl;

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

            if (receiverID == phoneNumber)
            {
                cout << "\nBlood Group: " << bloodGroup << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Reason: " << reason << endl;
                cout << "Status: " << status << endl;

                found = true;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No request history available." << endl;
        }
    }

    // Validate blood group and quantity, then save a new request as Pending.
    void applyBlood(string phoneNumber)
    {
        string bloodGroup;
        int quantity;
        string reason;

        cout << "====== Apply for Blood ======" << endl;

        cout << "Enter Blood Group: ";
        cin >> bloodGroup;

        if (!validBloodGroup(bloodGroup))
        {
            cout << "\nInvalid Blood Group." << endl;
            return;
        }

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (cin.fail() || quantity <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid Quantity." << endl;
            return;
        }

        cin.ignore(1000, '\n');

        cout << "Enter Reason: ";
        getline(cin, reason);

        ofstream file("Data/requests.txt", ios::app);

        if (!file.is_open())
        {
            cout << "\nUnable to save blood request." << endl;
            return;
        }

        file << phoneNumber << ","
             << bloodGroup << ","
             << quantity << ","
             << reason << ","
             << "Pending" << endl;

        file.close();

        ofstream notificationFile("Data/notifications.txt", ios::app);

        if (notificationFile.is_open())
        {
            notificationFile
                << phoneNumber << ","
                << "Your blood request has been submitted and is pending approval."
                << endl;

            notificationFile.close();
        }

        cout << "\nBlood request submitted successfully." << endl;
        cout << "Status: Pending" << endl;
    }


    // Read notifications and display only messages addressed to this user.
    void showNotifications(string phoneNumber)
    {
        ifstream file("Data/notifications.txt");

        if (!file.is_open())
        {
            cout << "No notifications available." << endl;
            return;
        }

        string line;
        bool found = false;

        cout << "\n====== Notifications ======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string notificationphoneNumber;
            string message;

            getline(ss, notificationphoneNumber, ',');
            getline(ss, message);

            if (notificationphoneNumber == phoneNumber)
            {
                cout << "- " << message << endl;

                found = true;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No new notifications available." << endl;
        }
    }

    // Receiver navigation menu; options lead to history, notifications, or a new request.
    void receiverMenu(string phoneNumber)
    {
        int choice;

        while (true)
        {
            cout << "\n====== Receiver Menu ======" << endl;
            cout << "1. History" << endl;
            cout << "2. Notification" << endl;
            cout << "3. Apply" << endl;
            cout << "4. Logout" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            // Clear invalid input state and discard the bad input before showing the menu again.
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                    receiverHistory(phoneNumber);
                    break;

                case 2:
                    showNotifications(phoneNumber);
                    break;

                case 3:
                    applyBlood(phoneNumber);
                    break;

                case 4:
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }
};

// SECTION 4 — BLOOD STOCK: displays, checks, and updates available units for each blood group.
class BloodStock{
public:

    // Read and display the current stock for each blood group.

    void showStock()
    {
        ifstream file("Data/bloodstock.txt");

        if (!file.is_open())
        {
            cout << "Blood stock file not found." << endl;
            return;
        }

        string line;

        cout << "\n====== Blood Stock ======" << endl;

        while (getline(file, line))
        {
            // Split this comma-separated line into its individual fields.
            stringstream ss(line);

            string bloodGroup;
            string quantity;

            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');

            cout << bloodGroup << " : " << quantity << " units" << endl;
        }

        file.close();
    }

    // Return the currently available quantity for the requested blood group.
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


    // Change stock by the supplied amount: positive adds units, negative removes units.
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

// SECTION 5 — HOSPITAL: reviews pending requests and records approvals/rejections.
class Hospital{
public:

    // Display donation requests waiting for hospital review.
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

            string donorPhoneNumber;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorPhoneNumber, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                count++;

                cout << "\nDonor " << count << endl;
                cout << "Phone Number: " << donorPhoneNumber << endl;
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

    // Let the hospital approve/reject a donation, update its status, and notify the donor.
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

    cout << "\n====== Pending Donor Requests ======" << endl;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string donorPhoneNumber;
        string donationType;
        string details;
        string address;
        string status;

        getline(ss, donorPhoneNumber, ',');
        getline(ss, donationType, ',');
        getline(ss, details, ',');
        getline(ss, address, ',');
        getline(ss, status, ',');

        if (status == "Pending")
        {
            pendingCount++;

            cout << pendingCount << ". "
                 << "Phone Number: " << donorPhoneNumber
                 << " | Donation Type: " << donationType
                 << " | Address: " << address << endl;
        }
    }

    if (pendingCount == 0)
    {
        cout << "No pending donor requests." << endl;
        return;
    }

    int selected;

    cout << "\nSelect donor request: ";
    cin >> selected;

    if (selected < 1 || selected > pendingCount)
    {
        cout << "\nInvalid Choice." << endl;
        return;
    }

    int currentPending = 0;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string donorPhoneNumber;
        string donationType;
        string details;
        string address;
        string status;

        getline(ss, donorPhoneNumber, ',');
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

                cout << "\nSelected Donor: " << donorPhoneNumber << endl;

                cout << "\n1. Approve" << endl;
                cout << "2. Reject" << endl;

                cout << "\nEnter choice: ";
                cin >> decision;

                if (decision == 1)
                {
                    status = "Approved";

                    addDonatedBlood(donorPhoneNumber);

                    lines[i] = donorPhoneNumber + "," +
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
                            << donorPhoneNumber << ","
                            << "Your donation request has been approved."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nDonor request approved." << endl;
                }
                else if (decision == 2)
                {
                    status = "Rejected";

                    lines[i] = donorPhoneNumber + "," +
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
                            << donorPhoneNumber << ","
                            << "Your donation request has been rejected."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nDonor request rejected." << endl;
                }
                else
                {
                    cout << "\nInvalid Choice." << endl;
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

    // Hospital navigation menu for viewing and processing donation/blood requests.
    void hospitalMenu()
    {
        int choice;

        while (true)
        {
            cout << "\n====== Hospital Menu ======" << endl;
            cout << "1. View Donor Requests" << endl;
            cout << "2. Approve / Reject Donor" << endl;
            cout << "3. View Blood Requests" << endl;
            cout << "4. Approve / Reject Blood Request" << endl;
            cout << "5. View Blood Stock" << endl;
            cout << "6. Logout" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

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
                {
                    BloodStock stock;
                    stock.showStock();
                    break;
                }

                case 6:
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }

    // Display receiver blood requests and their current statuses.
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
                cout << "Phone Number: " << receiverID << endl;
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

    // Process a receiver request; approval requires enough stock and subtracts the quantity.
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

    cout << "\n====== Pending Blood Requests ======" << endl;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string receiverPhoneNumber;
        string bloodGroup;
        string quantity;
        string reason;
        string status;

        getline(ss, receiverPhoneNumber, ',');
        getline(ss, bloodGroup, ',');
        getline(ss, quantity, ',');
        getline(ss, reason, ',');
        getline(ss, status, ',');

        if (status == "Pending")
        {
            pendingCount++;

            cout << pendingCount << ". "
                 << "Phone Number: " << receiverPhoneNumber
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

    cout << "\nSelect blood request: ";
    cin >> selected;

    if (selected < 1 || selected > pendingCount)
    {
        cout << "\nInvalid Choice." << endl;
        return;
    }

    int currentPending = 0;

    for (int i = 0; i < total; i++)
    {
        stringstream ss(lines[i]);

        string receiverPhoneNumber;
        string bloodGroup;
        string quantity;
        string reason;
        string status;

        getline(ss, receiverPhoneNumber, ',');
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

                cout << "\nSelected Receiver: " << receiverPhoneNumber << endl;
                cout << "Blood Group: " << bloodGroup << endl;
                cout << "Quantity Requested: " << quantity << endl;

                cout << "\n1. Approve" << endl;
                cout << "2. Reject" << endl;

                cout << "\nEnter choice: ";
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

                    // Approved request: subtract the requested number of units from stock.
                    stock.updateStock(
                        bloodGroup,
                        -requestedQuantity
                    );

                    status = "Approved";

                    lines[i] = receiverPhoneNumber + "," +
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
                            << receiverPhoneNumber << ","
                            << "Your blood request has been approved."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nBlood stock updated: -"
                         << requestedQuantity
                         << " " << bloodGroup << endl;

                    cout << "Blood request approved." << endl;
                }
                else if (decision == 2)
                {
                    status = "Rejected";

                    lines[i] = receiverPhoneNumber + "," +
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
                            << receiverPhoneNumber << ","
                            << "Your blood request has been rejected."
                            << endl;

                        notificationFile.close();
                    }

                    cout << "\nBlood request rejected." << endl;
                }
                else
                {
                    cout << "\nInvalid Choice." << endl;
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

    // Find the donor's blood group in users.txt and add one unit after approval.
    void addDonatedBlood(string donorPhoneNumber)
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

        string filePhoneNumber;
        string password;
        string name;
        string fileBloodGroup;

        getline(ss, filePhoneNumber, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, fileBloodGroup, ',');

        if (filePhoneNumber == donorPhoneNumber)
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

// SECTION 6 — ADMIN: provides an overview of donor records, receiver records, queue, and stock.
class Admin{
public:

    // Admin navigation menu; it mainly displays and monitors system information.
    void adminMenu()
    {
        int choice;

        while (true)
        {
            cout << "\n====== Admin Menu ======" << endl;
            cout << "1. Donor View" << endl;
            cout << "2. Receiver View" << endl;
            cout << "3. Hospital Bank Queue" << endl;
            cout << "4. Live Stock" << endl;
            cout << "5. Logout" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                    donorView();
                    break;

                case 2:
                    receiverView();
                    break;

                case 3:
                    hospitalQueue();
                    break;

                case 4:
                {
                    BloodStock stock;
                    stock.showStock();
                    break;
                }

                case 5:
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }

    // Read and display all saved donation records for administrative review.
    void donorView()
    {
        ifstream file("Data/donations.txt");

        if (!file.is_open())
        {
            cout << "No donor records available." << endl;
            return;
        }

        string line;
        int count = 0;

        cout << "\n====== Donor Records ======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string donorPhoneNumber;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorPhoneNumber, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            count++;

            cout << "\nDonor " << count << endl;
            cout << "Phone Number: " << donorPhoneNumber << endl;
            cout << "Donation Type: " << donationType << endl;
            cout << "Details: " << details << endl;
            cout << "Address: " << address << endl;
            cout << "Status: " << status << endl;
        }

        file.close();

        if (count == 0)
        {
            cout << "No donor records available." << endl;
        }
    }

    // Read and display all saved blood-request records for administrative review.
    void receiverView()
    {
        ifstream file("Data/requests.txt");

        if (!file.is_open())
        {
            cout << "No receiver records available." << endl;
            return;
        }

        string line;
        int count = 0;

        cout << "\n====== Receiver Information ======" << endl;

        while (getline(file, line))
        {
            stringstream ss(line);

            string receiverPhoneNumber;
            string bloodGroup;
            string quantity;
            string reason;
            string status;

            getline(ss, receiverPhoneNumber, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');
            getline(ss, reason, ',');
            getline(ss, status, ',');

            count++;

            cout << "\nReceiver " << count << endl;
            cout << "Phone Number: " << receiverPhoneNumber << endl;
            cout << "Blood Group: " << bloodGroup << endl;
            cout << "Quantity: " << quantity << endl;
            cout << "Reason: " << reason << endl;
            cout << "Status: " << status << endl;
        }

        file.close();

        if (count == 0)
        {
            cout << "No receiver records available." << endl;
        }
    }


    void hospitalQueue(){
    cout << "\n====== Hospital Bank Queue ======" << endl;

    // Pending donor requests
    ifstream donorFile("Data/donations.txt");

    if (donorFile.is_open())
    {
        string line;
        int count = 0;

        cout << "\n--- Pending Donor Donations ---" << endl;

        while (getline(donorFile, line))
        {
            stringstream ss(line);

            string donorPhoneNumber;
            string donationType;
            string details;
            string address;
            string status;

            getline(ss, donorPhoneNumber, ',');
            getline(ss, donationType, ',');
            getline(ss, details, ',');
            getline(ss, address, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                count++;

                cout << "\nDonor Request " << count << endl;
                cout << "Phone Number: " << donorPhoneNumber << endl;
                cout << "Donation Type: " << donationType << endl;
                cout << "Details: " << details << endl;
                cout << "Address: " << address << endl;
            }
        }

        donorFile.close();

        if (count == 0)
        {
            cout << "No pending donor donations." << endl;
        }
    }
    else
    {
        cout << "Donor records file not found." << endl;
    }

    // Pending receiver requests
    ifstream receiverFile("Data/requests.txt");

    if (receiverFile.is_open())
    {
        string line;
        int count = 0;

        cout << "\n--- Pending Blood Requests ---" << endl;

        while (getline(receiverFile, line))
        {
            stringstream ss(line);

            string receiverPhoneNumber;
            string bloodGroup;
            string quantity;
            string reason;
            string status;

            getline(ss, receiverPhoneNumber, ',');
            getline(ss, bloodGroup, ',');
            getline(ss, quantity, ',');
            getline(ss, reason, ',');
            getline(ss, status, ',');

            if (status == "Pending")
            {
                count++;

                cout << "\nBlood Request " << count << endl;
                cout << "Phone Number: " << receiverPhoneNumber << endl;
                cout << "Blood Group: " << bloodGroup << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Reason: " << reason << endl;
            }
        }

        receiverFile.close();

        if (count == 0)
        {
            cout << "No pending blood requests." << endl;
        }
    }
    else
    {
        cout << "Receiver records file not found." << endl;
    }
}

};

// SECTION 7 — MAIN SYSTEM: connects the menus and routes users to the correct role.
class BloodBankSystem {

public:

    User user;
    // Normal users can choose Donor, Receiver, My Report, or Logout.
    void userMenu()
    {
        int choice;

        while (true)
        {
            cout << "\n====== User Menu ======" << endl;
            cout << "1. Donor" << endl;
            cout << "2. Receiver" << endl;
            cout << "3. My Report" << endl;
            cout << "4. Logout" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                {
                    Donor donor;
                    donor.donorMenu(user.getPhoneNumber());
                    break;
                }

                case 2:
                {
                    Receiver receiver;
                    receiver.receiverMenu(user.getPhoneNumber());
                    break;
                }

                case 3:
                    user.generateReport();
                    break;

                case 4:
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }

    // Main loop: show registration/login/exit and route successful logins by accountType.
    void start()
    {
        bool firstTime = true;
        int choice;

        while (true)
        {
            if (firstTime)
            {
                cout << "====== Welcome to Blood Bank Life ======" << endl;
                firstTime = false;
            }

            cout << "\n====== Main Menu ======" << endl;
            cout << "1. User Registration" << endl;
            cout << "2. User Login" << endl;
            cout << "3. Exit" << endl;

            cout << "\nEnter choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input." << endl;
                continue;
            }

            switch (choice)
            {
                case 1:
                    user.registration();
                    break;

                case 2:
                    if (user.login())
                    {
                        string accountType = trim(user.getAccountType());

                        if (accountType == "Admin")
                        {
                            Admin admin;
                            admin.adminMenu();
                        }
                        else if (accountType == "Hospital")
                        {
                            Hospital hospital;
                            hospital.hospitalMenu();
                        }
                        else
                        {
                            userMenu();
                        }
                    }
                    break;

                case 3:
                    cout << "\nExiting program..." << endl;
                    return;

                default:
                    cout << "\nInvalid Choice." << endl;
            }
        }
    }

};

// Program entry point: create the system object and start the application.
int main() {

    BloodBankSystem bankSystem;

    bankSystem.start();

    return 0;
}

//Bank.cpp
#include<unistd.h>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<limits>
#include<ctime>
#include"Bank.h"
#include"Shopping.h"

//-------------------------------------------------------------------------------------
//  User-defined Terminal Controller
//  Controls terminal echo using only system() — no termios, no external headers
//-------------------------------------------------------------------------------------
struct TerminalControl
{
        static void hideInput()          //turn OFF echo — typed chars won't show
        {
                system("stty -echo -icanon");
        }
        static void showInput()          //turn ON echo — restore normal terminal
        {
                system("stty echo icanon");
        }
};

//-------------------------------------------------------------------------------------
//  User-defined hidden password reader
//  Reads char-by-char, prints '*' for each character, handles backspace too
//-------------------------------------------------------------------------------------
std :: string getHiddenPassword()
{
        std :: string password = "";
        char ch;

        TerminalControl :: hideInput();              //disable terminal echo

        while(true)
        {
                ch = getchar();                      //read one character at a time

                if(ch == '\n' || ch == '\r')        //Enter pressed → stop reading
                {
                        std :: cout << std :: endl;
                        break;
                }
                else if(ch == 127 || ch == '\b')    //Backspace → erase last *
                {
                        if(!password.empty())
                        {
                                password.pop_back();
                                std :: cout << "\b \b" << std :: flush;  //erase * on screen
                        }
                }
                else                                //normal char → store & print *
                {
                        password += ch;
                        std :: cout << '*' << std :: flush;
                }
        }

        TerminalControl :: showInput();              //restore terminal echo

        return password;
}
//namespace A;
A :: Bank :: Bank()
{
        std :: cout<<"Welcome :: You enetr in Base class of Bank Constructor ++++"<<std::endl;
        std :: cout<<"So, for a new person have to create a new account.\nRead the instructions given below and follow it to create a new account\n\t\t************"<<std::endl;
        create_acc();
}

A :: Bank :: ~Bank()
{
        std :: cout<<"Destructor called from Base Bank class ----"<<std::endl;
}

void A :: Bank :: create_acc()
{
        int Yes;
        char t;
        std::cout << "You must deposit a minimum of 500 rupees to open a new account."<<std::endl;
        std::cout << "Maintain at least 500 to keep your account active.\n";
        std::cout << "Would you like to open a new account ?"<<std::endl;
again :
        std::cout << "Press 1 for Yes, 0 for No: \n";
        std::cin >> Yes;
        if(Yes == 1)
        {
                set_balance(500.00);
                std :: cout<<"Enter the Name: "<<std::endl;
                std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                //std :: cin.getline(Name, sz);
                std :: getline(std::cin, Name);
                std :: cout<<"Set your security/transaction password"<<std::endl;
                std :: getline(std::cin, pswd);
                //-----------------------------------Name---------------------------------------------------------------
                /*
                //std :: cout<<"Enter the Account_No: "<<std::endl;
                //std :: cin>>Account_No;
                std :: cout<<"Account_No generated automatically: "<<std::endl;
                srand(time(0));
                Account_No = rand()%(((100000000000)+1)+10000000000);  //rand%(((max-min)+1)+min)
                std :: cout<<Account_No;          */
                //---------------------------------Account_No[1]----------------------------------------------------------
                /*      static long long nextAccNo = 6534789037LL;  // starting at 1,000,000,000 (10 digits)
                        Account_No = nextAccNo++;    */
                //---------------------------------Account_No[2]----------------------------------------------------------
                srand(time(0));

                // Generate a 10-digit number:
                long long Account_Num = (long long)(rand()) * RAND_MAX + rand();

                //generate 10-digit number
                Account_No = Account_Num % 900000000LL + 100000000LL;
                std :: cout<<"Account_No generated automatically: "<< Account_No<<std::endl;

                //------------------------------Account_No[3]-----------------------------------------------------------
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                std :: cout<<"Enter the Account_Type: "<<std::endl;
                std :: cin.getline(Account_Type, sz);              //for char ___
                //std :: getline(std::cin, Account_Type);         //for std::string ___
                //---------------------------------Account_Type------------------------------------------------------------
                std :: cout<<"Account created successfully with initial deposit of ₹ "<<get_balance()<<".00 /- balance."<<std::endl;
        }
        else if (Yes == 0)
        {
                std :: cout<<" See You Later_Thank You !!"<<std::endl;
                exit(0);
        }
        else
        {
                std :: cout<<" *** Invalid Choicr ***" <<std::endl;
                std :: cout<<" Do U wanna Try it Again ?" <<std::endl << "Press (Y/y) for Yes || Else random default Press means No."<<std::endl;
                std :: cin>>t;
                if(t == 'Y' || t == 'y')
                {
                        std :: cout<<" Glad to see you here again.."<<std::endl;
                        goto again;
                }
                else if(t != 'Y' && t != 'y')
                {
                        std :: cout<<" Sorry see U nxt time " <<std::endl;
                        exit(0);
                }
        }
        //return Yes;
}
bool A :: Bank :: verify_pswd(char *ptr)
{
    return strcmp(pswd.c_str(), ptr) == 0;
}

bool A::Bank::deposit_amt(float a)
{
        std :: cout <<"Enter your pswd __ to deposit money__ "<<std::endl;
        std :: string password;
        password = getHiddenPassword();
        //std :: getline(std::cin, password);
        char pass_char[100];
        strcpy(pass_char, password.c_str());
        if(verify_pswd(pass_char))
        {
                std :: cout <<"Enter your amount: ₹ ";
                std :: cin>>a;
                if(a > 0)
                {
                        set_balance(get_balance() + a);
                        std :: cout<<"++Deposited Amount: Rs " <<a<<std::endl;
                        std :: cout<<"Added Balance: ₹ "<<get_balance()<<std::endl;
                        std :: cout<<std::endl;
                        return true;
                }
                else
                {
                        std :: cout<<"Invalid Deposit Amount. It should be greater than 0.00 "<<std::endl;
                        return false;
                }
        }
        else
        {
                std :: cout<<"oops you have entered a wrong pswd !!"<<std::endl;
                return false;
        }
}

bool A :: Bank :: withdraw_amt(float b)
{
        std :: cout<<"Enter your pswd__ to withdraw money__"<<std::endl;
        std :: string password;
        password = getHiddenPassword();
        //std :: getline(std::cin, password);
        char pass_char[100];
        strcpy(pass_char, password.c_str());
        if(!verify_pswd(pass_char))
        {
                std :: cout<<"Incorrect password !! Withdrawal denied.\n";
                return false;
        }
        std :: cout<<"Enter your amount to withdraw: ₹ ";
        std :: cin>>b;
        if(get_balance() - b < 500)
        {
                std :: cout<<"**please wait Withdrawl is in process**"<<std::endl;
                sleep(2);
                std :: cout<<"Withdrawal denied! Minimum balance of Rs "<<get_balance()<<"must be maintained."<<std::endl;
                std :: cout<<"**Balance_Left: ₹ "<<get_balance()<<std::endl;
                return false;
        }
        else if(b > 0)
        {
                set_balance(get_balance() - b);
                std :: cout<<"*please wait Withdrawl is in process*"<<std::endl;
                std :: cout<<"\twill get successfull soon"<<std::endl;
                sleep(4);
                std :: cout<<"--Your Withdrawl_Amount : ₹ "<< b<<std::endl;
                std :: cout<<"**Your Balance_Left : ₹ "<<get_balance()<<std::endl;
                return true;
        }
        else
        {
                std :: cout<<"Withdrawal denied! It must be a +ve value greater than zero."<<std::endl;
                std :: cout<<"**Balance_Left: ₹ "<<get_balance()<<std::endl;
                return false;
        }
}

bool A :: Bank :: display_data()
{
        std :: cout<<"Enter your pswd__ to see account details ___ "<<std::endl;
        std :: string password;
        password = getHiddenPassword();
        //std :: getline(std::cin, password);
        char pass_char[100];
        strcpy(pass_char, password.c_str());
        if(verify_pswd(pass_char))
        {
                std :: cout<<std::endl;
                std :: cout<<"-----*---------------*------"<<std::endl;
                std :: cout<<"-----*Account Details*------"<<std::endl;
                std :: cout<<"-----*---------------*------"<<std::endl;
                std :: cout<<"Name         : "<<Name<<std::endl;
                std :: cout<<"Account No   : "<<Account_No<<std::endl;
                std :: cout<<"Account Type : "<<Account_Type<<std::endl;
                std :: cout<<"Balance Left : ₹ "<<get_balance()<<" /-"<<std::endl;
                return true;
        }
        else
        {
                std :: cout<<"oops you have entered a wrong pswd!!"<<std::endl;
                return false;
        }
}
/*
bool A :: Bank :: processPayment(float amount, const std::string &password)
{
        char pass_char[100];
        strcpy(pass_char, password.c_str());
        if(!verify_pswd(pass_char))
        {
                std :: cout<<"Incorrect password! Payment denied."<<std::endl;
                return false;
        }
        if(get_balance() - amount < 500.00) {
                std :: cout<<"Insufficient balance! Minimum balance of ₹ 500.00 must be maintained."<<std::endl;
                std :: cout<<"Current balance: ₹ "<<get_balance()<<std::endl;
                std :: cout<<"Required payment: ₹ "<<amount<<std::endl;
                return false;
        }

        if(amount > 0) {
                set_balance(get_balance() - amount);
                std :: cout<<"Payment processed: ₹ "<<amount<<" deducted from your account."<<std::endl;
                std :: cout<<"Remaining balance: ₹ "<<get_balance()<<std::endl;
                return true;
        }
        else
        {
                std :: cout<<"Invalid payment amount!. It must a greater than zero.."<<std::endl;
                return false;
        }
}*/
bool A :: Bank :: verifyPassword(char *pass)
{
        return verify_pswd(pass);
}
void A :: Bank :: set_balance(float bal)          //to update Balance_Left with new deposited or wd amont
{
        Balance_Left = bal;
}
float A :: Bank :: get_balance() const           //to get the current remaining balance
{
        return Balance_Left;
}
std :: string A :: Bank :: getAccountType() const
{
        return std :: string(Account_Type);
}
//namespace B;
using namespace B;
Bank :: Bank()
{
        std :: cout<<"Now, You are inside the Derived Bank class of Constructor ++++."<<std::endl;
        set_address();
        menu();
}

Bank::~Bank()
{
        std :: cout<<"Destructor called from Derived Bank class."<<std::endl;
}

void Bank::menu()
{
        int i = 0;
        std :: cout<<"\n\nPick any of the menu option to continue further or else can take exit from process.\n";
        int option;
        std :: cout<<"\t\tPick your choice from below list"<<std::endl;
        do{
                std :: cout<<"\n\n1 : Account Details & Balance Enquiry"<<std::setw(6)<<" "<<"*"<<std::setw(6)<<" "<<"2 : Deposit"<<std::setw(6)<<" "<<"**"<<std::setw(6)<<" "<<"3 : Proceed to Shopping"<<std::setw(6)<<" "<<"***"<<std::setw(6)<<" "<<"4 : Withdraw Balance"<<std::setw(6)<<" "<<"****"<<std::setw(6)<<" "<<"5 : Exit"<<std::setw(6)<<" "<<"*****"<<std::setw(6)<<" "<<std::endl;
                if(i == 0)
                {
                        std :: cout<<"\nEnter your choice"<<std::endl;
                }
                else
                {
                        std :: cout<<"\nEnter your choice again !!"<<std::endl;
                }
                std :: cin>>option;
                std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                ++i;
                switch(option)
                {
                        case 1:
                                if(display_data())
                                {
                                        std :: cout<<"\nDo you wannt to view address details? (y/n): ";
                                        char viewAddress;
                                        std :: cin>>viewAddress;
                                        std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        //if(toupper(viewAddress) == 'Y')
                                        if(viewAddress >= 'a' && viewAddress <= 'z')
                                        {
                                                viewAddress = viewAddress - ('a' - 'A');
                                        }
                                        if(viewAddress == 'Y')
                                        {
                                                std :: cout<<"Displaying address details..."<<std::endl;
                                                display_address();
                                        }
                                        else
                                        {
                                                std :: cout<<"Address details view skipped."<<std::endl;
                                        }
                                }
                                else
                                {
                                        std :: cout<<"Incorrect password, try again!!"<<std::endl;
                                }
                                break;
                        case 2:
                                {
                                        float a;
                                        std :: cout<<"Enter amount to be deposit__: ₹ 0.00"<<std::endl;
                                        //std :: cin>>a;
                                        //std :: cin.ignore();
                                        deposit_amt(a);
                                }
                                break;        
                        case 3:
                                {
                                        std :: cout<<std::endl;
                                        std :: cout<<"---*-------------------*---"<<std::endl;
                                        std :: cout<<"---*Proceed to Shopping*---"<<std::endl;
                                        std :: cout<<"---*-------------------*---"<<std::endl;
                                        Shopping shop;
                                        int shoppingChoice = shop.menu();
                                        if(shoppingChoice == 1)
                                        {
                                                std :: cout<<"\nProcessing billing..."<<std::endl;
                                                int billingResult = shop.billing(*this);
                                                if(billingResult == 1)
                                                {
                                                        std :: cout<<"Billing completed successfully! Returning to Bank Menu..."<<std::endl;
                                                }
                                                else
                                                {
                                                        std :: cout<<"Billing failed/cancelled. Returning to Bank Menu..."<<std::endl;
                                                }
                                        }
                                        else if(shoppingChoice == 2)
                                        {
                                                std :: cout<<"Returning to Bank Menu...!"<<std::endl;
                                        }
                                }
                                break;
                        case 4:
                                {
                                        float b;
                                        std :: cout<<"Enter amount to withdraw__: ₹ 0.00"<<std::endl;
                                        //std :: cin>>b;
                                        //std :: cin.ignore();
                                        withdraw_amt(b);
                                }
                                break;
                                
                        case 5:
                                {
                                        std :: cout<<"Now, its a Time to take an exit from the process"<<std::endl;
                                        exit(0);
                                }
                                break;
                                
                        default:
                                std :: cout<<"Please select from the given option\nAnd Try It Again !!"<<std::endl;
                }
        } while(option != 5);
}
/*
bool Bank :: processPayment(float amount, const std::string &password)
{
        return processPayment(amount, password);
}
*/
bool Bank :: processPayment(float amount, const std::string &password)
{
        char pass_char[100];
        strcpy(pass_char, password.c_str());
        if(!verifyPassword(pass_char))
        {
                std :: cout<<"Incorrect password! Payment denied."<<std::endl;
                return false;
        }
        if(get_balance() - amount < 500.00) {
                std :: cout<<"Insufficient balance! Minimum balance of ₹ 500.00 must be maintained."<<std::endl;
                std :: cout<<"Current balance: ₹ "<<get_balance()<<std::endl;
                std :: cout<<"Required payment: ₹ "<<amount<<std::endl;
                return false;
        }

        if(amount > 0)
        {
                std :: cout<<"pswd verifying"<<std::endl;
                sleep(1);
                std :: cout<<"pswd verified"<<std::endl;
                std :: cout<<"fetching account balance/details for transaction"<<std::endl;
                set_balance(get_balance() - amount);
                std :: cout<<"Payment processed: ₹ "<<amount<<" /-"<<" deducted from your "<<getAccountType()<<"."<<std::endl;
                std :: cout<<"Remaining balance: ₹ "<<get_balance()<<" /-"<<std::endl;
                return true;
        }
        else
        {
                std :: cout<<"Invalid payment amount!. It must a greater than zero.."<<std::endl;
                return false;
        }
}
void Bank :: set_address()
{
        std :: cout<<"Enter your/customer full address details"<<std::endl;
        std :: cout<<"Enter House_No.: ";
        std :: cin>>addr.House_No;
        std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std :: cout << "Enter Landmark: ";
        std :: cin.getline(addr.Landmark, sz);
        std :: cout<<"Enter Full Address: ";
        std :: getline(std::cin, addr.Full_addr);
        std :: cout<<"Enter Your/Customer State: ";
        std :: getline(std::cin, addr.State);
        std :: cout<<"Enter Your/Customer City: ";
        std :: cin.getline(addr.City, sz);
        std :: cout<<"Enter Your/Customer Zip/Pin/Postal Code: ";
        std :: cin>>addr.Postal_Code;
        std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std :: cout<<"Enter Customer Mail_ID: ";
        std :: getline(std::cin, addr.Mail_ID);
        std :: cout<<"Your/Customer Mobile Number will be generated automatically: \n";
        std :: cout<<"Mobile_No generated automatically: "<<std::endl;
        srand(time(0));
        long long Number = (long long)(rand()) * RAND_MAX + rand();
        addr.Mobile_No = Number % 3000000000LL + 300000000LL;
}

void Bank :: display_address()
{
        std :: cout<<std::endl;
        std :: cout<<"--------*---------------*---------"<<std::endl;
        std :: cout<<"--------*Address Details*---------"<<std::endl;
        std :: cout<<"--------*---------------*---------"<<std::endl;
        std :: cout<<"House No.     : "<<addr.House_No<<std::endl;
        std :: cout<<"Landmark      : "<<addr.Landmark<<std::endl;
        std :: cout<<"Full Address  : "<<addr.Full_addr<<std::endl;
        std :: cout<<"City          : "<<addr.City<<std::endl;
        std :: cout<<"State         : "<<addr.State<<std::endl;
        std :: cout<<"Postal Code   : "<<addr.Postal_Code<<std::endl;
        std :: cout<<"Email ID      : "<<addr.Mail_ID<<std::endl;
        std :: cout<<"Mobile No.    : "<<addr.Mobile_No<<std::endl;
}
~
~
~
~

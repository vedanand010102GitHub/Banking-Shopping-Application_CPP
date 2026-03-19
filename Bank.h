//Bank.h

#ifndef BANK_H
#define BANK_H

#include<iostream>
//#include"Shopping.h"
class Shopping;
#define sz 30
//Base Class of Bank class -----------------------------------------------------
namespace A
{
        class Bank                                         //user defined datatype class + classname
        {                                                 //menbers of the class
                private :                                //data member which are sensitive & can't be accessed directly, for i.e to enhance safety and security use : private
                float Balance_Left;                     //Balance as a private data member
                std :: string pswd;                    //string data type passwoed at run time by progr.
                bool verify_pswd(char *);             //to verify password for aceess the transaction and balance details
        protected :                                  //access specifier : protected
                //char Name[sz];                    //data member of Base class
                //int Account_No;
                std::string Name;
                long long Account_No;                     //of ten digits in it too long long integer type
                //std::string Account_Type;              //choice of account_type
                char Account_Type[sz];                  //limit is [sz-1] it reads upto in char p.d_t and it overcome in string s.d_t
                void set_balance(float );              //to update Balance_Left with new deposited or wd amont
                float get_balance() const;            //to get the current remaining balace
        public:                                      //access specifier : public
                Bank();                             //member function of Base class and constructor
                void create_acc();                 //account created with added sone amount
                bool deposit_amt(float );         //to deposti amount
                bool withdraw_amt(float );       //To withdraw an amount after checking the balance and a min. balancd mantaned.
                bool display_data();            //To display the name and balance
                ~Bank();                       //Base class destructor
                bool verifyPassword(char * );
                std :: string getAccountType() const;
        };
}
namespace B
{
        class Bank : public A :: Bank                                  //Derived class from nameespace A :: Bank Base class
        {                                                             //members od derived class
                protected :
                //private:                                          //: private access specifier
                        //std :: string pswd;// = "vt@01";         //added pswd
                        typedef struct customer_address           //customer address
                        {
                        int House_No;
                        char Landmark[sz];
                        std :: string Full_addr;
                        std :: string State;
                        char City[sz];
                        int Postal_Code;
                        std :: string Mail_ID;
                        long long Mobile_No;
                        }address;                       //alias name for structure (customer_address TO  address)
                        address addr;                  //Instance of Structure
                public :                              //: public access specifier
                        Bank();                      //  derived class constructor
                        void menu();                //     to select diff. bank appl.op. Bank menu inside deeived class
                        void set_address();        //        to set customer address
                        void display_address();   //            to display customer address
                        ~Bank();                 //                derived class destructor
                        bool processPayment(float , const std::string & );  //to process or sum of all the added products from basket
                        friend class Shopping;
        };
}
std :: string getHiddenPassword();           //user-defined hidden password input
#endif

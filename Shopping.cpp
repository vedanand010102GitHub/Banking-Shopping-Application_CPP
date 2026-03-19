//Shopping.cpp
#include "Shopping.h"
#include "Bank.h"


int Shopping :: i = 0;
product_data Shopping :: Product[SZ];
int Shopping :: total_items = 0;
float Shopping :: total_amount = 0.0f;
Shopping :: Shopping()
{
        std :: cout<<"Constructor invoked: you are Inside Shopping class.  ++++"<<std::endl;
        std :: cout<<"You’re most welcome! "<<std::endl;
        //clearCart();
}

int Shopping :: menu()
{
        char option;
        std :: cout<<"We are inside Menu function. Pick any of your choice:"<<std::endl;
        do{
                std :: cout<<std::left;
                std :: cout<<std::setw(10)<<"\tA : Add to Cart           "<<" *"<<std::endl;
                std :: cout<<std::setw(10)<<"\tB : Billing               "<<" **"<<std::endl;
                std :: cout<<std::setw(10)<<"\tC : Clear Cart            "<<" ***"<<std::endl;
                std :: cout<<std::setw(10)<<"\tD : Delete Item           "<<" ****"<<std::endl;
                std :: cout<<std::setw(10)<<"\tE : Exit                  "<<" *****"<<std::endl;
                std :: cout<<std::setw(10)<<"\tR : Return Back in Bank   "<<" ******"<<std::endl;
                std :: cout<<std::setw(10)<<"\tV : View Cart             "<<" *******"<<std::endl;
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
                //option = toupper(option);
                switch(option)
                {
                        case 'A':
                                add_to_Cart();
                                break;
                        case 'B':
                                return 1;
                        case 'C':
                                clearCart();
                                //view_Cart();
                                //debugCart();
                                break;
                        case 'D':
                                delete_Items();
                                break;
                        case 'E':
                                std :: cout<<"Now, its a Time to take exit from the process"<<std::endl;
                                exit(0);
                                //break;
                        case 'R':
                                return 2;
                        case 'V':
                                view_Cart();
                                break;
                        default:
                                std :: cout<<"Please select from the given option\nAnd Try It Again !!"<<std::endl;
                }
        }
        while(option != 'E' && option != 'R');
        return 2;
}

void Shopping :: add_to_Cart()
{
        if (total_items >= SZ)
        {
                std :: cout<<"Your basket/cart is full/max. [" <<SZ<< "] can't be add more items further."<<std::endl;
                return;
        }
        std :: cout<<"Adding of product into basket/cart"<<std::endl;
        std :: cout<<"\nEnter Product Name: "<<std::endl;
        std :: getline(std::cin, Product[total_items].name);
        std :: cout<<"Enter Price: ₹ "<<std::endl;
        std :: cin>>Product[total_items].price;
        std :: cout<<"Enter Quantity: ";
        std :: cin>>Product[total_items].quantity;
        std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(Product[total_items].price < 0 || Product[total_items].quantity <= 0)
        {
                std :: cout<<"Invalid price or quantity! Item didn't added."<<std::endl;
                return;
        }
        float item_total = Product[total_items].price * Product[total_items].quantity;
        total_amount += item_total;
        total_items++;
        std :: cout<<"Item added successfully!"<<std::endl;
        std :: cout<<"Item Total: ₹ "<<item_total<<std::endl;
}

void Shopping :: view_Cart()
{
        if(total_items == 0)
        {
                std :: cout<<"\nYour Basket/Cart is empty now!\nYou have to add the product by pressing 'A'"<<std::endl;
                return;
        }
        std :: cout<<"\n======== YOUR SHOPPING CART ========"<<std::endl;
        std :: cout<<std :: left<<std :: setw(20)<<"Product"<<std :: setw(12)<<"Price (₹)"<<std :: setw(10)<<"  Qty"<<std :: setw(15)<<"Total Price (₹)"<<std::endl;
        std :: cout<<std :: string(60, '-')<<std::endl;
        for(i = 0; i < total_items; i++)
        {
                float item_total = Product[i].price * Product[i].quantity;
                std :: cout<<std::left<<std::setw(20)<<Product[i].name<<std::setw(12)<<Product[i].price<<std::setw(8)<<Product[i].quantity<<std::setw(1)<<item_total<<" /-"<<std::endl;
        }
        std :: cout<<std::string(60, '-')<<std::endl;
        std :: cout<<"Total Amount: ₹ "<<total_amount<<" /-"<<std::endl;
}

void Shopping :: delete_Items()
{
        if (total_items == 0)
        {
                std :: cout<<"Your Basket/Cart is empty now. Nothing to be remove/delete. !"<<std::endl;
                return;
        }
        std :: string productName;
        std :: cout<<"Enter product name to delete/remove: "<<std::endl;
        std :: getline(std::cin, productName);
        bool check_prd = false;
        for(i = 0; i < total_items; i++)
        {
                if(Product[i].name == productName)
                {
                        float item_total = Product[i].price * Product[i].quantity;
                        total_amount -= item_total;
                        for(int j = i; j < total_items - 1; j++)
                        {
                                Product[j] = Product[j + 1];
                        }
                        total_items--;
                        check_prd = true;
                        std :: cout<<"Item '"<<productName<<"'deleted successfully!"<<std::endl;
                        break;
                }
        }
        if(!check_prd)
        {
                std :: cout<<"Product '"<<productName<<"' not found in cart!"<<std::endl;
        }
}
int Shopping :: billing(B::Bank &bank)
{
        if(total_items == 0)
        {
                std :: cout<<"Cart is empty now! can't be proceed with billing."<<std::endl;
                return 0;
        }
        std :: cout<<std::endl;
        std :: cout<<"------*---------------*------"<<std::endl;
        std :: cout<<"------*Billing Summary*------"<<std::endl;
        std :: cout<<"------*---------------*------"<<std::endl;
        view_Cart();
        std :: cout<<"\n-wanna proceed with payment? (y/n): ";
        char choice;
        std :: cin>>choice;
        std :: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(toupper(choice) == 'Y')
        {
                std :: cout<<"Enter your pswd to authorize/approve payment: ";
                std :: string password;
                password = getHiddenPassword();
                //std :: getline(std::cin, password);
                if(bank.processPayment(total_amount, password))
                {
                        //std :: cout<<"pswd verifying"<<std::endl;
                        sleep(1);
                        //std :: cout<<"pswd verified"<<std::endl;
                        //std :: cout<<"fetching account balance/details for transaction"<<std::endl;
                        //sleep(2);
                        //std :: cout<<"Payment successfull! Amount has beed Debited : ₹ "<<total_amount<<" /- from your "<<bank.getAccountType()<<"."<<std::endl;
                        clearCart();
                        return 1;
                }
                else
                {
                        std :: cout<<"Payment failed!! Insufficient balance or incorrect password."<<std::endl;
                        return 0;
                }
        }
        else
        {
                std :: cout<<"Billing cancelled."<<std::endl;
                return 0;
        }
}
/*
void Shopping :: debugCart()
{
        std :: cout<<std::endl;
        std :: cout<<"------*-------------------*------"<<std::endl;
        std :: cout<<"------*DEBUG CART CONTENTS*------"<<std::endl;
        std :: cout<<"------*-------------------*------"<<std::endl;
        std :: cout<<"Total items: "<<total_items<<std::endl;
        for(i = 0; i < total_items; i++)
        {
                std :: cout<<"Item "<<i<<": Name = "<<Product[i].name<<", Price =  "<<Product[i].price<<", Qty =  "<<Product[i].quantity<<std::endl;
        }
        std :: cout<<"Total amount: "<<total_amount<<std::endl;
}
*/
void Shopping :: clearCart()
{
        total_items = 0;
        total_amount = 0.0f;
        std :: cout<<"Your cart has been cleared successfully. \nYou're all set for a fresh start!"<<std::endl;
        //std :: cout<<"Cart is empty successfully!!"<<std::endl;
}
Shopping :: ~Shopping()
{
        std :: cout<<"Shopping Destructor called! ----"<<std::endl;
}

float Shopping :: getTotalAmount() const
{
        return total_amount;
}
int Shopping :: getTotalItems() const
{
        return total_items;
}

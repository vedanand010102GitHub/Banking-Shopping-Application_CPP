//Shopping.h

#ifndef SHOPPING_H
#define SHOPPING_H

#include"Bank.h"
//#include<unistd.h>
//#include<iostream>
#include<string>
//#include<iomanip>
//#include<limits>
#define SZ 4
typedef struct product_data
{
        std :: string name;
        float price;
        int quantity;
}pdct;          //allias name for product_data

class Shopping
{
        private:
                static pdct Product[SZ];  //here Product is an array name pdct is user defib=ned d_t
                static int total_items;
                static float total_amount;
                static int i;
        public:
                Shopping();
                int menu();
                void add_to_Cart();
                void view_Cart();
                void delete_Items();
                int billing(B :: Bank &bank); // Accesses Bank instance
                ~Shopping();

                //void debugCart();   //check
                float getTotalAmount() const;
                int getTotalItems() const;
                void clearCart();

                friend void billing(Shopping &shop, B :: Bank &bank, const std :: string &pass);
};
#endif
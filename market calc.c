#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Product {
    int quantity;
    int price;
    char name[50];
};

struct Customer {
    char name[MAX_NAME_LENGTH];
    int phone_number;
    int customer_id;
};

int main(void) {
    struct Product products[15];
    struct Customer customer;

    printf("------------------------------------------------------------------------------------------\n");
    printf("Medyo billing system(presyong bongbong)\n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("::::::Customer Details::::::\n\n");

    printf("Customer Name: ");
    scanf("%49s", customer.name); 
    printf("Customer Phone Number: ");
    scanf("%d", &customer.phone_number);
    printf("Customer ID (kahit ML id nalang sir): ");
    scanf("%d", &customer.customer_id);

    printf("-----------------\n");

    //lalagay ng name and price sa products by using the structured variable "Product"
    strcpy(products[0].name, "Body Soap");
    products[0].price = 40;
    strcpy(products[1].name, "Shampoo");
    products[1].price = 10;
    strcpy(products[2].name, "Conditioner");
    products[2].price = 8;
    strcpy(products[3].name, "Perfume");
    products[3].price = 150;
    strcpy(products[4].name, "Sugar");
    products[4].price = 25;
    strcpy(products[5].name, "Tea");
    products[5].price = 15;
    strcpy(products[6].name, "Coffee");
    products[6].price = 15;
    strcpy(products[7].name, "Rice");
    products[7].price = 55;
    strcpy(products[8].name, "Butter");
    products[8].price = 30;
    strcpy(products[9].name, "Pepsi");
    products[9].price = 20;
    strcpy(products[10].name, "Sprite");
    products[10].price = 20;
    strcpy(products[11].name, "Coke");
    products[11].price = 22;
    strcpy(products[12].name, "Fruit Soda");
    products[12].price = 15;
    strcpy(products[13].name, "Royal");
    products[13].price = 20;

    //looping the variable para makuha yung ii-input na quantity ng bibilhin na product
    for (int i = 0; i < 14; i++) {
        printf("%s (%d Php): ", products[i].name, products[i].price);
        scanf("%d", &products[i].quantity);
    }

    //computes the total price :))
    int cosmetics_total = 0;
    int grocery_total = 0;
    int drinks_total = 0;
    int total = 0;

    for (int i = 0; i < 14; i++) {
        products[i].price *= products[i].quantity;
        total += products[i].price;

        if (i < 4) {
            cosmetics_total += products[i].price;
        } else if (i < 9) {
            grocery_total += products[i].price;
        } else {
            drinks_total += products[i].price;
        }
    }

    //details ng customer pati yung list ng products :))
    printf("----------------------------------\n");
    printf("UNSAMANIDONG MARKET WKWKWK\n\n");

    printf("Customer Name: %s\n", customer.name);
    printf("Customer Phone Number: %d\n", customer.phone_number);
    printf("Customer ID: %d\n\n", customer.customer_id);

    printf("---------------------------------------------------------------------------------------\n");

    printf("Product Name                          Quantity                              Price\n\n");
    for (int i = 0; i < 14; i++) {
        printf("%-30s %10d %37d\n", products[i].name, products[i].quantity, products[i].price);
    }

    printf("\nCosmetics Total Price: %d php\n\n", cosmetics_total);
    printf("Groceries Total Price: %d php\n\n", grocery_total);
    printf("Drinks Total Price: %d php\n\n", drinks_total);
    printf("Total Price: %d php\n\n", total);

}
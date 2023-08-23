//A Mini-Project from team ProjektVM [CSE,P2]

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_NAME_LENGTH 30

//These are (ANSI escape codes) color codes used for print statements  
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// Global arrays to store item name, item price, and available stock
const char items[MAX_ITEMS][MAX_NAME_LENGTH] = 
{
    "Coke", "Pepsi", "Water", "Snickers", "Fanta",
    "Gatorade", "Cheetos", "Lay's Sizzlin' hot chips",
    "Monster Energy Ultra", "RedBull Energy drink"
};
const double prices[MAX_ITEMS] = {1.50, 1.50, 1.00, 1.25, 1.50, 2.00, 1.00, 1.25, 5.25, 4.20};
int stock[MAX_ITEMS] = {10, 15, 20, 12, 8, 5, 10, 7, 3, 6};
int cart[MAX_ITEMS] = {0};

// Function prototypes
void displayMenu();
void checkout();
void removeItem();

int main() 
{
    int option;
    do 
    {
        // Display the menu
        displayMenu();

        // Ask for user input
        printf("Select your option: ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1 ... 10: 
            {
                // Add item to cart
                int itemquantity;
                printf("Enter the quantity to purchase for %s: ", items[option - 1]);
                scanf("%d", &itemquantity);
                if (itemquantity <= stock[option - 1]) 
                {
                    cart[option - 1] += itemquantity;
                    stock[option - 1] -= itemquantity;
                    printf(ANSI_COLOR_GREEN"Added %d %s to cart."ANSI_COLOR_RESET"\n\n", itemquantity, items[option - 1]);
                } 
                else 
                {
                    printf(ANSI_COLOR_RED"Not enough stock available for %s."ANSI_COLOR_RESET"\n\n", items[option - 1]);
                }
                break;
            }

            case 11:
                // Checkout
                checkout();
                break;

            case 12:
                // Remove item from cart
                removeItem();
                break;

            case 0:
                // Exit
                printf(ANSI_COLOR_BLUE"Thank you for using the Vending Machine! Goodbye."ANSI_COLOR_RESET"\n");
                break;

            default:
                printf(ANSI_COLOR_RED"Invalid option. Please try again."ANSI_COLOR_RESET"\n\n");
                break;
        }
    } 
    while (option != 0);

    return 0;
}

// Function to display the vending machine menu
void displayMenu() 
{
    printf("+----------------------------------------------------------+\n");
    printf("|"ANSI_COLOR_GREEN"              Welcome to the Vending Machine!             "ANSI_COLOR_RESET"|\n");
    printf("+----------------------------------------------------------+\n");
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        printf("| %2d. |"ANSI_COLOR_BLUE" %-30s"ANSI_COLOR_RESET " - "ANSI_COLOR_GREEN"$%.2f "ANSI_COLOR_RESET"| Stock:"ANSI_COLOR_CYAN" %2d "ANSI_COLOR_RESET"|\n", i + 1, items[i], prices[i], stock[i]);
    }
    printf("+----------------------------------------------------------+\n");
    printf("|"ANSI_COLOR_GREEN" 11. |||||||||||||||||||||||Checkout||||||||||||||||||||||"ANSI_COLOR_RESET"|\n");
    printf("+----------------------------------------------------------+\n");
    printf("|"ANSI_COLOR_RED" 12. |||||||||||||||||||||Remove item|||||||||||||||||||||"ANSI_COLOR_RESET"|\n");
    printf("+----------------------------------------------------------+\n");
    printf("|"ANSI_COLOR_YELLOW"  0. |||||||||||||||||||||||||EXIT||||||||||||||||||||||||"ANSI_COLOR_RESET"|\n");
    printf("+----------------------------------------------------------+\n");
}

// Function to calculate and handle checkout process
void checkout() 
{
    double totalAmount = 0;
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        if (cart[i] > 0) 
        {
            printf("|"ANSI_COLOR_BLUE" %-30s"ANSI_COLOR_RESET" | x%d -"ANSI_COLOR_GREEN" $%.2f"ANSI_COLOR_RESET"|\n", items[i], cart[i], prices[i] * cart[i]);
            totalAmount += prices[i] * cart[i];
        }
    }

    if (totalAmount == 0) 
    {
        printf(ANSI_COLOR_RED"Cart is empty. Nothing to checkout :( "ANSI_COLOR_RESET"\n\n");
        return;
    }

    printf("|Total amount to pay: "ANSI_COLOR_GREEN"|$%.2f|"ANSI_COLOR_RESET"\n", totalAmount);

    double amountPaid;
    do 
    {   
        printf(ANSI_COLOR_YELLOW"Press '0' to cancel\n"ANSI_COLOR_RESET);
        printf("Enter amount to pay: $");
        scanf("%lf", &amountPaid);
        if(amountPaid == 0)
        {
            printf(ANSI_COLOR_YELLOW"\n----PAYMENT CANCELED----\n"ANSI_COLOR_RESET);
            return;
        }

        if (amountPaid < totalAmount) 
        {
            printf(ANSI_COLOR_RED"Oops... Insufficient amount! \npaid amount returned, Please pay the full amount!"ANSI_COLOR_RESET"\n");
        } 
        else
        {
            printf(ANSI_COLOR_GREEN"Payment successful. Thank you! :)"ANSI_COLOR_RESET"\n");
            double remainingChange = amountPaid - totalAmount;
            if (remainingChange > 0) 
            {
                printf("Change: "ANSI_COLOR_GREEN"$%.2f"ANSI_COLOR_RESET"\n", remainingChange);
            }
            for (int i = 0; i < MAX_ITEMS; i++) 
            {
                cart[i] = 0;
            }
            printf("\n");
            break;
        }
    } while (1);
}

// Function to remove an item from the cart

void removeItem() 
{
    int totalAmount = 0, itemIndex, quantityToRemove;
    
    
    // Display the items in the cart along with their indices
    printf("Items in the cart:\n");
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        if (cart[i] > 0) 
        {
            printf("| %2d. |"ANSI_COLOR_BLUE" %-30s "ANSI_COLOR_RESET"| x%d -"ANSI_COLOR_GREEN" $%-2.2f"ANSI_COLOR_RESET"|\n", i + 1, items[i], cart[i], prices[i] * cart[i]);
        }
    }
    
    printf("Enter the item number to remove from the cart "ANSI_COLOR_YELLOW"[Enter '0' to cancel]: "ANSI_COLOR_RESET);
    scanf("%d", &itemIndex);
    
    //cancels removal
    if (itemIndex == 0)
    {
        printf("\n"ANSI_COLOR_RED" ----REMOVAL CANCELED---- "ANSI_COLOR_RESET"\n");
        return;
    }
    
    itemIndex--; // Convert to array index

    //checks if item is in menu
    if (itemIndex < 0 || itemIndex > MAX_ITEMS) 
    {
        printf(ANSI_COLOR_RED"Invalid item number. Please provide a valid item number."ANSI_COLOR_RESET"\n\n");
        return;
    }

    //checks if item is in cart
    int isItemInCart = 0;  // Initialize a flag
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        if (cart[i] > 0) 
        {
            isItemInCart = 1;  // Set the flag if the item is found in the cart
            break;             // No need to continue checking if the item is found
        }
    }
    if (!isItemInCart) 
    {
        printf(ANSI_COLOR_RED"No item(s) in Cart!"ANSI_COLOR_RESET"\n");
        return;
    }


    printf("Enter the quantity to remove for %s: ", items[itemIndex]);
    scanf("%d", &quantityToRemove);

    if (quantityToRemove <= 0) 
    {
        printf(ANSI_COLOR_RED"Invalid quantity. Please provide a valid quantity."ANSI_COLOR_RESET"\n\n");
        return;
    }

    if (cart[itemIndex] == 0) 
    {
        printf(ANSI_COLOR_RED"Item %s not found in the cart."ANSI_COLOR_RESET"\n\n", items[itemIndex]);
        return;
    }

    if (quantityToRemove > cart[itemIndex]) 
    {
        printf(ANSI_COLOR_RED"Quantity to remove exceeds the quantity of %s in the cart."ANSI_COLOR_RESET"\n\n", items[itemIndex]);
        return;
    }

    cart[itemIndex] -= quantityToRemove;
    stock[itemIndex] += quantityToRemove;
    printf(ANSI_COLOR_GREEN"Removed %d %s from the cart."ANSI_COLOR_RESET"\n\n", quantityToRemove, items[itemIndex]);
    
}

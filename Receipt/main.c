#include <stdio.h>
#include <stdlib.h>

#define VAT_RATE 0.18
#define NORMAL_DISCOUNT 0.1
#define STUDENT_DISCOUNT 0.125

// This function shows the contents of a file named "menu.txt" on the console.
void show_menu()
{
    // Open the "menu.txt" file in read mode and get a pointer to it.
    FILE *menu_file = fopen("menu.txt", "r");

    // Define a character variable to hold the current character read from the file.
    char c;

    // Loop through the file until the end of file (EOF) is reached.
    while ((c = fgetc(menu_file)) != EOF)
    {

        // Print the current character to the console.
        printf("%c", c);
    }

    // Close the file to release its resources.
    fclose(menu_file);
}

double vat(double total_price) // Function to add VAT value to the final price.
{
    total_price += (total_price * VAT_RATE); // Multiply the vat rate with total price and add the result with total price again.
    return total_price;
}

// This function calculates the discounted price of a purchase based on the total price and whether the customer is a student.
// Then returns the discounted price.
double discounter(double total_price, char if_student)
{
    // Check if the customer is a student by comparing the input character to 'Y' or 'y'.
    if (if_student == 'Y' || if_student == 'y')
    {
        // If the customer is a student but the total price is less than 150, only apply the student discount.
        if (total_price < 150)
        {
            total_price -= (total_price * STUDENT_DISCOUNT);
            return total_price;
        }

        // If the customer is a student and the total price is greater or equal to 150, apply both the student discount and normal discount.
        else
        {

            total_price -= ((total_price * STUDENT_DISCOUNT) + (total_price * NORMAL_DISCOUNT));
            return total_price;
        }
    }
    // If the customer is not a student and the total price is less than 150, do not apply any discount.
    else
    {
        if (total_price < 150)
        {
            return total_price;
        }
        // If the customer is not a student, only apply the normal discount if the total price is not lower than 150.
        else
        {
            total_price -= (total_price * NORMAL_DISCOUNT);
            return total_price;
        }
    }
}

// This function writes the selected product and its serving size to a file.
void txt_writer(int product_choice, double serving, FILE *fp)
{
    // Cast the serving size to an integer
    int flag_serving = (int)serving;
    // In this block, if serving size is more than 1 it will print the serving size.
    if (serving > 1)
    {
        // Print the serving size.
        fprintf(fp, "%d* ", flag_serving);
        // Print the meal names.
        if (product_choice == 1)
        {
            fprintf(fp, "Kebap                   75,99\n");
        }
        else if (product_choice == 2)
        {
            fprintf(fp, "Lahmacun                21,50\n");
        }
        else if (product_choice == 3)
        {
            fprintf(fp, "Pide                    40,00\n");
        }
        else if (product_choice == 4)
        {
            fprintf(fp, "Döner                   55,60\n");
        }
        else if (product_choice == 5)
        {
            fprintf(fp, "Kola                    15.00\n");
        }
        else if (product_choice == 6)
        {
            fprintf(fp, "Su                      5,00\n");
        }
        else if (product_choice == 7)
        {
            fprintf(fp, "Künefe                  60.00\n");
        }
        else if (product_choice == 8)
        {
            fprintf(fp, "Sütlaç                  32,50\n");
        }
    }
    // If the serving size is 1, this block will be activated and it will not print the serving size.
    else if (serving == 1)
    {
        if (product_choice == 1)
        {
            fprintf(fp, "Kebap                      75,99\n");
        }
        else if (product_choice == 2)
        {
            fprintf(fp, "Lahmacun                   21,50\n");
        }
        else if (product_choice == 3)
        {
            fprintf(fp, "Pide                       40,00\n");
        }
        else if (product_choice == 4)
        {
            fprintf(fp, "Döner                      55,60\n");
        }
        else if (product_choice == 5)
        {
            fprintf(fp, "Kola                       15.00\n");
        }
        else if (product_choice == 6)
        {
            fprintf(fp, "Su                         5,00\n");
        }
        else if (product_choice == 7)
        {
            fprintf(fp, "Künefe                     60.00\n");
        }
        else if (product_choice == 8)
        {
            fprintf(fp, "Sütlaç                     32,50\n");
        }
    }
}

int main()
{
    int product_choice;     // Variable to store product choice and use.
    double serving;         // Variable to store serving size.
    double price;           // Variable to store meal prices.
    double total_price = 0; // Variable to store total price.
    char if_student;        // Variable to check if the user is student or not.

    printf("Yemek listesi:\n");
    show_menu(); // Read the txt file named menu, and print it to the console.

    // Creating a file to fill it with recipe.
    FILE *fp;                       // Declare a pointer to the file.
    fp = fopen("receipt.txt", "w"); // Open the file for writing ("w" mode).

    // Check if file was successfully opened
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return 0;
    }

    // Printing the recipe things.
    fprintf(fp, "------------------------------------\n");
    fprintf(fp, " Product                 Price(TL)  \n");
    fprintf(fp, "------------------------------------\n");

    // Do while loop to store the users choice and calculate the total_price.
    do
    {
        printf("\nPlease choose a product (1-8) <If you want to stop choosing press 0>: ");
        scanf("%d", &product_choice);

        // If product choice is not valid, ask user to enter a valid number.
        while (product_choice != 0 && product_choice != 1 && product_choice != 2 && product_choice != 3 && product_choice != 4 && product_choice != 5 && product_choice != 6 && product_choice != 7 && product_choice != 8)
        {
            // Store users choice.
            printf("Please enter a valid product: ");
            scanf("%d", &product_choice);
        }
        // If product choice is 0, break the loop and stop asking user.
        if (product_choice == 0)
        {
            break;
        }
        // Store the serving size.
        printf("How many servings do you want? <If you want to stop choosing press 0>: ");
        scanf("%lf", &serving);

        // If user did not stop making choices, call the txt_writer function and fill the recipe txt with values.
        if (serving != 0 && product_choice != 0)
        {
            txt_writer(product_choice, serving, fp);
        }
        // If user want to stop, stop here and break the loop.
        if (serving == 0)
        {
            break;
        }
        // Declare a price depending on users choice.
        switch (product_choice)
        {
        case 1:
            price = 75.99;
            break;
        case 2:
            price = 21.50;
            break;
        case 3:
            price = 40.00;
            break;
        case 4:
            price = 55.60;
            break;
        case 5:
            price = 15.00;
            break;
        case 6:
            price = 5.00;
            break;
        case 7:
            price = 60.00;
            break;
        case 8:
            price = 32.50;
            break;
        default:
            break;
        }
        // If serving is not 0, do the following equation to calculate the total price.
        if (serving != 0)
        {
            total_price += price * serving;
            product_choice = 0;
        }
    } while (serving != 0); // When the serving becomes 0 the do while loop will stop.
    // Fill recipe.
    fprintf(fp, "Total:                     %.2lf\n", total_price);
    // Ask the user to learn if he/she is student or not.
    printf("\nAre you a student? (Y or y for yes, N or n for no.): ");
    scanf(" %c", &if_student);
    // If user enters something not valid, ask user again.
    while (if_student != 'Y' && if_student != 'y' && if_student != 'N' && if_student != 'n')
    {
        printf("Please enter a valid answer. Are you student or not? (Y or y for yes, N or n for no.): ");
        scanf(" %c", &if_student);
    }

    // If user is student fill the recipe txt with student discount value.
    if (if_student == 'y' || if_student == 'Y')
    {
        fprintf(fp, "Student discount:         -%.2lf\n", total_price * STUDENT_DISCOUNT);
    }
    // Fill the recipe txt with values.
    fprintf(fp, "-----------------------------------\n");
    // Call the discounter function to apply the discount to the price, then print it to the recipe txt.
    total_price = discounter(total_price, if_student);
    fprintf(fp, "Price:                     %.2lf\n", total_price);
    // Call the VAT function to apply the VAT to the price, then print it to the recipe txt.
    total_price = vat(total_price);
    fprintf(fp, "Price + VAT:               %.2lf", total_price);
    // Close the recipe txt.
    fclose(fp);
    // Print a goodbye message :)
    printf("\nEnjoy your meal!");

    return 0;
}
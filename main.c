/********* main.c ********
    Student Name 	= Anirudh Sridhar
    Student Number	= 
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);
    while (true)
    {
        print_menu();

        switch (user_choice())
        {
        case 1:
            register_user(users);
            break;
        case 2:
            update_password(users);
            break;
        case 3:
            manage_posts(users); // do
            break;
        case 4:
            manage_friends(users);
            break;
        case 5:
            display_posts_by_n(users, 3); // fix only 1 post bug
            break;
        case 6:
            teardown(users);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}
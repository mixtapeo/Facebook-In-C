/*****************
    Student Name 	= Anirudh Sridhar
    Student Number	= 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   // Allocate memory for the new user
   user_t *new_user = (user_t *)malloc(sizeof(user_t));
   if (new_user == NULL)
   {
      printf("Memory allocation failed\n");
      return users;
   }

   // Initialize new user fields
   strncpy(new_user->username, username, sizeof(new_user->username) - 1);
   new_user->username[sizeof(new_user->username) - 1] = '\0';
   strncpy(new_user->password, password, sizeof(new_user->password) - 1);
   new_user->password[sizeof(new_user->password) - 1] = '\0';
   new_user->friends = NULL;
   new_user->posts = NULL;
   new_user->next = NULL;

   // If the list is empty or the new user should be inserted at the beginning
   if (users == NULL || strcmp(new_user->username, users->username) < 0)
   {
      new_user->next = users;
      printf("*** User Added! ***\n");
      return new_user;
   }

   // Traverse the list to find the correct insertion point
   user_t *current = users;
   while (current->next != NULL && strcmp(new_user->username, current->next->username) > 0)
   {
      current = current->next;
   }

   // Insert the new user
   new_user->next = current->next;
   current->next = new_user;

   printf("*** User Added! ***\n");
   return users;
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   while (users != NULL)
   {
      if (strcmp(users->username, username) == 0)
      {
         return users;
      }
      users = users->next;
   }
   return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));
   assert(new_friend != NULL);
   strncpy(new_friend->username, username, sizeof(new_friend->username) - 1);
   new_friend->username[sizeof(new_friend->username) - 1] = '\0';
   new_friend->next = NULL;
   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   if (user == NULL || friend == NULL)
   {
      printf("Invalid user or friend username.\n");
      return;
   }

   // Create a new friend node
   friend_t *new_friend = (friend_t *)malloc(sizeof(friend_t));

   // Initialize the new friend node
   strncpy(new_friend->username, friend, sizeof(new_friend->username) - 1);
   // new_friend->username[sizeof(new_friend->username) - 1] = '\0';
   new_friend->next = NULL;

   // Insert the new friend into the sorted linked list
   friend_t *current = user->friends;
   friend_t *previous = NULL;

   while (current != NULL && strcmp(current->username, friend) < 0)
   {
      previous = current;
      current = current->next;
   }

   new_friend->next = current;

   if (previous == NULL)
   {
      // Insert at the beginning
      user->friends = new_friend;
   }
   else
   {
      // Insert between previous and current
      previous->next = new_friend;
   }

   printf("Friend '%s' added successfully.\n", friend);
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   if (user == NULL || friend_name == NULL)
   {
      printf("Invalid user or friend name.\n");
      return false;
   }

   friend_t *current = user->friends;
   friend_t *previous = NULL;

   while (current != NULL)
   {
      if (strcmp(current->username, friend_name) == 0)
      {
         if (previous == NULL)
         {
            // The friend to be deleted is the first node
            user->friends = current->next;
         }
         else
         {
            // The friend to be deleted is in the middle or end
            previous->next = current->next;
         }

         // Free the memory allocated for the deleted friend
         free(current);
         printf("Friend '%s' deleted successfully.\n", friend_name);
         return true;
      }

      // Move to the next friend in the list
      previous = current;
      current = current->next;
   }

   // Friend not found
   printf("Friend '%s' not found.\n", friend_name);
   return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   // Go to last post entry, then add new node and set next as NULL
   post_t *new_post = (post_t *)malloc(sizeof(post_t));
   assert(new_post != NULL);
   strncpy(new_post->content, text, sizeof(new_post->content) - 1);
   new_post->content[sizeof(new_post->content) - 1] = '\0'; // Ensure null-termination
   new_post->next = NULL;
   return new_post;
};

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
   post_t *new_post = create_post(text);
   if (user->posts == NULL)
   {
      user->posts = new_post;
      return;
   }
   post_t *current = user->posts;
   while (current->next != NULL)
   {
      current = current->next;
   }
   current->next = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
   if (user->posts == NULL)
   {
      return false;
   }
   post_t *temp = user->posts;
   user->posts = user->posts->next;
   free(temp);
   return true;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
   int post_count = 0;
   int display_count = 0;
   post_t *current_post = user->posts;
   while (current_post != NULL)
   {
      printf("Post %d: %s\n", ++post_count, current_post->content);
      current_post = current_post->next;
      display_count++;
      display_count = 0;
   }
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
   if (user == NULL)
   {
      printf("Invalid user.\n");
      return;
   }

   if (user->friends == NULL)
   {
      printf("%s has no friends.\n", user->username);
      return;
   }

   printf("\n%s's Friends:\n", user->username);
   printf("---------------------\n");
   friend_t *current = user->friends;
   while (current != NULL)
   {
      printf("- %s\n", current->username);
      current = current->next;
   }
   printf("---------------------\n");
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *users, int number)
{
   char username[30];
   printf("\nEnter the username to display their posts: ");
   scanf(" %[^\n]", username);
   user_t *user = find_user(users, username);
   if (user == NULL)
   {
      printf("\nError: Username '%s' not found.\n", username);
      return;
   }

   if (user->posts == NULL)
   {
      printf("\n%s has no posts.\n", user->username);
      return;
   }

   post_t *current_post = user->posts;
   int post_count = 0;
   int display_count = 0;
   char choice;

   printf("\nDisplaying posts for %s:\n", user->username);
   printf("------------------------------\n");

   while (current_post != NULL)
   {
      printf("Post %d: %s\n", ++post_count, current_post->content);
      current_post = current_post->next;
      display_count++;

      if (display_count == 3)
      {
         display_count = 0;
         if (current_post != NULL)
         {
            printf("\nDo you want to display more posts? (Y/N): ");
            scanf(" %c", &choice);

            if (choice == 'N' || choice == 'n')
            {
               printf("\nReturning to main menu.\n");
               return;
            }
            else if (choice != 'Y' && choice != 'y')
            {
               printf("\nInvalid input. Returning to main menu.\n");
               return;
            }
         }
      }
   }

   printf("\nAll posts have been displayed.\n");
};

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *current_user = users;
   user_t *next_user;

   while (current_user != NULL)
   {
      // Free friends
      friend_t *current_friend = current_user->friends;
      friend_t *next_friend;

      while (current_friend != NULL)
      {
         next_friend = current_friend->next;
         free(current_friend);
         current_friend = next_friend;
      }

      // Free posts
      post_t *current_post = current_user->posts;
      post_t *next_post;

      while (current_post != NULL)
      {
         next_post = current_post->next;
         free(current_post);
         current_post = next_post;
      }

      // Free user
      next_user = current_user->next;
      free(current_user);
      current_user = next_user;
   }

   printf("Goodbye!\n");
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n");
   printf("1. Register a new user\n");
   printf("2. Manage a user's profile (change password)\n");
   printf("3. Manage a user's posts (add/remove)\n");
   printf("4. Manage a user's friends (add/remove)\n");
   printf("5. Display a user’s posts\n");
   printf("6. Exit\n");
   printf("\nEnter your choice: ");
}

/* Updates user password (Choice 2). Calls find_user to find correct username, if present.*/
void update_password(user_t *users)
{
   printf("\nEnter a username to update their password: ");

   char username[30];
   if (scanf(" %[^\n]", username) != 1)
   {
      printf("Error reading username.\n");
      // Clear the input buffer
      while (getchar() != '\n')
         ;
      return;
   }

   user_t *p = find_user(users, username);

   if (p == NULL)
   {
      printf("\nInvalid username / User not found.\n");
   }
   else
   {
      char old_password[15];
      printf("\nEnter the OLD password: ");
      if (scanf(" %[^\n]", old_password) != 1)
      {
         printf("Error reading old password.\n");
         // Clear the input buffer
         while (getchar() != '\n')
            ;
         return;
      }

      if (strcmp(old_password, p->password) == 0)
      {
         char new_password[15];
         printf("\nEnter new password up to 15 characters: ");
         if (scanf(" %[^\n]", new_password) != 1)
         {
            printf("Error reading new password.\n");
            // Clear the input buffer
            while (getchar() != '\n')
               ;
            return;
         }

         // Update the password ensuring no buffer overflow
         strncpy(p->password, new_password, sizeof(p->password) - 1);
         p->password[sizeof(p->password) - 1] = '\0';

         printf("\n**** Password changed! ****\n");
      }
      else
      {
         printf("\nWrong password.\n");
      }
   }
}

/* Choice 3: get username and manage a post */
void manage_posts(user_t *users)
{
   printf("\nEnter a username to manage their posts: ");
   char choice[15];
   scanf(" %[^\n]s", choice);

   user_t *user = find_user(users, choice);

   if (user == NULL)
   {
      // If the user is not found, print an error message
      printf("\nUsername not found.");
   }
   else
   {
      // If the user is found, print a message indicating that their posts are being managed
      printf("\n ----------- \n Managing %s's posts \n -----------", user->username);
      if (user->posts == NULL)
      {
         printf("\nNo posts available for %s", choice);
      }

      int response;

      // Prompt the user to choose an action: add a new post, remove a post, or return to the main menu
      printf("\n1. Add a new post\n2. Remove a post\n3. Return to main menu\n\nEnter your choice: ");
      scanf("%d", &response); // Read the user's choice

      char text[250];
      switch (response)
      {
      case 1:
         // If the user chooses to add a new post, prompt for the post content and add the post
         printf("\nEnter your post content: ");
         scanf(" %[^\n]s", &text);
         add_post(user, text); // todo contiue flow check it adds and prints out
         display_all_user_posts(user);
         break;
      case 2:
         printf("\nRemoving latest post (if present)...");
         delete_post(users);
         display_all_user_posts(user);
         break;
      case 3:
         print_menu();
         break;
      }
   }
}

/*
Prompts the user to enter their choice.
Uses scanf to read an integer input.
Validates the input to ensure it's a valid integer.
Handles invalid inputs by prompting the user again.
Returns the valid choice as an int.
*/
int user_choice()
{
   int choice;

   while (1)
   {
      if (scanf("%d", &choice) == 1)
      {
         return choice;
      }
      else
      {
         printf("Invalid input. Please enter a number.\n");
      }
   }
}

/*
Register a user (Choice 1).
*/
void register_user(user_t *users)
{
   // Prompt the user to enter a username and password
   printf("\nEnter a username: ");
   char username[30];
   scanf(" %[^\n]s", username);
   // Clear the input buffer
   while (getchar() != '\n')
      ;

   printf("\nEnter a password (up to 15 characters): ");
   char password[15];
   scanf(" %[^\n]s", password);
   // Clear the input buffer
   while (getchar() != '\n')
      ;

   // Add the user to the database
   add_user(users, username, password);
}

void manage_friends(user_t *users)
{
   printf("\nEnter a username to manage their friends: ");
   char choice[15];
   scanf(" %[^\n]s", choice);
   user_t *user = find_user(users, choice);

   if (user == NULL)
   {
      printf("\nUsername not found.");
   }
   else
   {
      printf("\n ----------- \n Managing %s's friends \n -----------\n", user->username);
      if (user->friends == NULL)
      {
         printf("No friends available for %s", user->username);
      }
      else
      {
         printf("\n1. Add a new friend\n2. Remove a friend\n3. Return to main menu\nEnter your choice: ");

         char response[15];
         int choice;
         scanf("%d", &choice);
         switch (choice)
         {
         case 1:
            printf("\nEnter your friend's username: ");
            scanf("%s", &response);
            add_friend(user, response);
            display_user_friends(user);
            break;
         case 2:
            display_user_friends(user);
            printf("\nEnter a friend's name to delete: ");
            scanf(" %[^\n]s", &response);

            bool friend_exists = delete_friend(user, response);
            if (friend_exists == true)
            {
               printf("\nUpdated list of %s's friends: ", user->username);
               display_user_friends(user);
            }
            else
            {
               printf("\nInvalid friend name.\n");
            }
            break;
         case 3:
            print_menu();
            break;
         }
      }
   }
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   srand(time(NULL));
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
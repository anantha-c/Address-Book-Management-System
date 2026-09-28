#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"

#include "address_book_menu.h"
#include "address_book.h"

int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	int num;
	char ch;

	printf("%s", msg);

	if (type == NUM)
	{
		scanf("%d", &num);
		return num;
	}
	else if (type == CHAR)
	{
		scanf(" %c", &ch);
		return toupper(ch);
	}
	else
	{
		printf("%s\n", msg);
		return 0;
	}
	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 
	printf("\nContact List:\n");

	for(int i=0;i<address_book->count;i++)
	{
		printf("%d | %s | %s | %s\n",
		address_book->list[i].si_no,
		address_book->list[i].name,
		address_book->list[i].phone_numbers,
		address_book->list[i].email_addresses);
	}
	printf("\nPress Enter to continue...");
	getchar();
	getchar();


	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("cls");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				list_contacts(address_book,NULL,NULL,NULL,e_list);
				break;
				/* Add your implementation to call list_contacts function here */
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	address_book->count++;

	address_book->list =
	realloc(address_book->list,
	sizeof(ContactInfo)*address_book->count);

	ContactInfo *new_contact =
	&address_book->list[address_book->count-1];

	new_contact->si_no = address_book->count;

	printf("Enter Name: ");
	scanf(" %[^\n]", new_contact->name);

	printf("Enter Phone: ");
	scanf("%s", new_contact->phone_numbers);

	printf("Enter Email: ");
	scanf("%s", new_contact->email_addresses);

	printf("Contact Added Successfully\n");

	return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
	char input[NAME_LEN];

	printf("%s", msg);

	scanf(" %[^\n]", input);

	int found = 0;

	for(int i = 0; i < loop_count; i++)
	{
		if(field == 0)
		{
			if(strcmp(input,
			   address_book->list[i].name) == 0)
			{
				found = 1;
			}
		}
		else if(field == 1)
		{
			if(strcmp(input,
			   address_book->list[i].phone_numbers) == 0)
			{
				found = 1;
			}
		}
		else if(field == 2)
		{
			if(strcmp(input,
			   address_book->list[i].email_addresses) == 0)
			{
				found = 1;
			}
		}

		if(found)
		{
			printf("\nMatch Found:\n");

			printf("%d | %s | %s | %s\n",
			       address_book->list[i].si_no,
			       address_book->list[i].name,
			       address_book->list[i].phone_numbers,
			       address_book->list[i].email_addresses);

			return e_success;
		}
	}

	printf("\nNo Match Found\n");
	return e_no_match;
	
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
	char name[NAME_LEN];
	int found =0 ;

	printf("Enter name to search: ");
	scanf(" %[^\n]", name);

	for(int i=0;i<address_book->count;i++)
	{
		if(strcmp(name,address_book->list[i].name)==0)
		{
			

			printf("%d | %s | %s | %s\n",
			address_book->list[i].si_no,
			address_book->list[i].name,
			address_book->list[i].phone_numbers,
			address_book->list[i].email_addresses);
			found = 1;
			break;
		}

		
	}
	
	if(!found)
	{
		printf("\nContact not found\n");
	}

	printf("\nPress Enter to continue...");
	getchar();
	getchar();

	return found ? e_success : e_no_match;
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	char name[NAME_LEN];

	printf("Enter contact name to edit: ");
	scanf(" %[^\n]", name);

	for(int i=0;i<address_book->count;i++)
	{
		if(strcmp(name,address_book->list[i].name)==0)
		{
			printf("Enter new phone: ");
			scanf("%s",
			address_book->list[i].phone_numbers);

			printf("Enter new email: ");
			scanf("%s",
			address_book->list[i].email_addresses);

			printf("Contact updated successfully\n");

			return e_success;
		}
	}

	printf("Contact not found\n");

	return e_no_match;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	char name[NAME_LEN];

	printf("Enter name to delete: ");
	scanf(" %[^\n]", name);

	for(int i=0;i<address_book->count;i++)
	{
		if(strcmp(name,address_book->list[i].name)==0)
		{
			for(int j=i;j<address_book->count-1;j++)
			{
				address_book->list[j]=address_book->list[j+1];
			}

			address_book->count--;
			address_book->list =
			realloc(address_book->list,
			sizeof(ContactInfo)*address_book->count);
			printf("Deleted successfully\n");
			return e_success;
		}
	}
	printf("Contact not found\n");
	return e_no_match;
}

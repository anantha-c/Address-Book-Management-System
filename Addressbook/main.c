#include <stdio.h>

#include "address_book.h"
#include "address_book_menu.h"
#include "address_book_fops.h"

int main()
{
	AddressBook address_book;

	load_file(&address_book);

	menu(&address_book);

	save_prompt(&address_book);

	return 0;
}
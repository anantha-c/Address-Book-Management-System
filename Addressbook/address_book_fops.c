#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	struct stat st;

	if (stat(DEFAULT_FILE, &st) == 0)
	{
		address_book->fp = fopen(DEFAULT_FILE, "r");

		if (address_book->fp == NULL)
			return e_fail;
		address_book->count = 0;

		char line[200];

		while (fgets(line, sizeof(line), address_book->fp))
			address_book->count++;

		rewind(address_book->fp);

		if (address_book->count == 0)
		{
			address_book->list = NULL;
			fclose(address_book->fp);
			return e_success;
		}

		address_book->list = malloc(sizeof(ContactInfo) *
		                           address_book->count);

		int i = 0;

		while (fscanf(address_book->fp,
		              "%d,%[^,],%[^,],%[^\n]\n",
		              &address_book->list[i].si_no,
		              address_book->list[i].name,
		              address_book->list[i].phone_numbers,
		              address_book->list[i].email_addresses) != EOF)
		{
			i++;
		}

		fclose(address_book->fp);
	}
	else
	{
		address_book->fp = fopen(DEFAULT_FILE, "w");

		if (address_book->fp == NULL)
			return e_fail;

		address_book->count = 0;
		address_book->list = NULL;

		fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 

	for (int i = 0; i < address_book->count; i++)
	{

		
		fprintf(address_book->fp,
		        "%d,%s,%s,%s\n",
		        address_book->list[i].si_no,
		        address_book->list[i].name,
		        address_book->list[i].phone_numbers,
		        address_book->list[i].email_addresses);
	}

	fclose(address_book->fp);

	return e_success;
}

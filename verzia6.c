#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct book {
	char *signature;
	char *isbn;
	char *name;
	char *authors;
	char *date;
	char *id;
	struct book *next;
} BOOK;

/* load all books' data to linked list */
BOOK *n(BOOK *first) {

	FILE *fr;
	int i, count;
	char ch, *p_string;
	BOOK *last = NULL, *book;

	// free existing linked list
	while (first != NULL) {
		book = first->next;
		free(first);
		first = book;
	}

	if ((fr = fopen("kniznica.txt", "r")) == NULL) {
		printf("Zaznamy neboli nacitane\n");
	}
	else {
		count = 0;
		p_string = (char *)malloc(5 * sizeof(char));
		while (fgets(p_string, 5, fr) != NULL) {

			book = NULL;
			// initialize new entry
			book = (BOOK *)malloc(sizeof(BOOK));
			book->signature = (char *)malloc(11*sizeof(char));
			book->isbn = (char *)malloc(14*sizeof(char));
			book->name = (char *)malloc(101*sizeof(char));
			book->authors = (char *)malloc(101*sizeof(char));
			book->date = (char *)malloc(9*sizeof(char));
			book->id = (char *)malloc(8*sizeof(char));

			// always 6 details per book
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->signature + i) = ch;
				i++;
			}
			*(book->signature + i) = '\0';
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->isbn + i) = ch;
				i++;
			}
			*(book->isbn + i) = '\0';
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->name + i) = ch;
				i++;
			}
			*(book->name + i) = '\0';
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->authors + i) = ch;
				i++;
			}
			*(book->authors + i) = '\0';
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->date + i) = ch;
				i++;
			}
			*(book->date + i) = '\0';
			i = 0;
			while ((ch = getc(fr)) != '\n') {
				*(book->id + i) = ch;
				i++;
			}
			*(book->id + i) = '\0';

			// this will be the last one
			book->next = NULL;

			// incorporate book to linked list
			if (first == NULL)
				first = book;
			else if (last == NULL)
				first->next = last = book;
			else {
				last->next = book;
				last = book;
			}
			count++;

		}

		printf("Nacitalo sa %d zaznamov\n", count);

		free(p_string);
		if (fclose(fr) == EOF)
			printf("Subor nezatvoreny\n");
	}

	return first;
}

/* output all books' details */
void v(BOOK *first) {

	BOOK *book = first;
	int i = 1;

	while (book != NULL) {
		printf("%d.\n", i);
		printf("signatura: %s\n", book->signature);
		printf("isbn: %s\n", book->isbn);
		printf("nazov: %s\n", book->name);
		printf("autori: %s\n", book->authors);
		printf("datum: %s\n", book->date);
		printf("preukaz: %s\n", book->id);
		book = book->next;
		i++;
	}
}

/* add a book to the collection */
BOOK *p(BOOK *first) {

	BOOK *book, *current;
	int i, position;
	char ch;

	scanf("%d\n", &position);

	if (position > 0) {

		// initialize new entry
		book = (BOOK *)malloc(sizeof(BOOK));
		book->signature = (char *)malloc(11 * sizeof(char));
		book->isbn = (char *)malloc(14 * sizeof(char));
		book->name = (char *)malloc(101 * sizeof(char));
		book->authors = (char *)malloc(101 * sizeof(char));
		book->date = (char *)malloc(9 * sizeof(char));
		book->id = (char *)malloc(8 * sizeof(char));

		// always 6 details per book
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->signature + i) = ch;
			i++;
		}
		*(book->signature + i) = '\0';
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->isbn + i) = ch;
			i++;
		}
		*(book->isbn + i) = '\0';
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->name + i) = ch;
			i++;
		}
		*(book->name + i) = '\0';
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->authors + i) = ch;
			i++;
		}
		*(book->authors + i) = '\0';
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->date + i) = ch;
			i++;
		}
		*(book->date + i) = '\0';
		i = 0;
		while ((ch = getchar()) != '\n') {
			*(book->id + i) = ch;
			i++;
		}
		*(book->id + i) = '\0';

		// temporary asignment
		book->next = NULL;

		// incorporate book to linked list
		if (first == NULL)
			first = book;
		else if (position == 1) {
			book->next = first;
			first = book;
		}
		else {
			current = first;
			i = 1;
			while (i < position - 1 && current->next != NULL) {
				current = current->next;
				i++;
			}
			book->next = current->next;
			current->next = book;
		}

	}

	return first;
}

/*
	delete all books matching phrase in authors' substring
	! case doesn't matter
*/
BOOK *z(BOOK *first) {

	BOOK *previous, *current;
	int i, count = 0;
	char ch, *phrase, *author;

	// scan search phrase in lower case
	phrase = (char *)calloc(102, sizeof(char));
	i = 0;
	while (getchar() != '\n');
	while ((ch = getchar()) != '\n') {
		*(phrase + i) = ch;
		i++;
	}
	*(phrase + i) = '\0';
	if (phrase != NULL) {
		i = 0;
		while (*(phrase + i) != '\0') {
			if (isupper(*(phrase + i)))
				*(phrase + i) = tolower(*(phrase + i));
			i++;
		}

		previous = NULL;
		current = first;
		author = (char *)malloc(101 * sizeof(char));

		while (current != NULL) {

			// particular authors to lower case
			i = 0;
			while (*(current->authors + i) != '\0') {
				if (isupper(*(current->authors + i)))
					*(author + i) = tolower(*(current->authors + i));
				else
					*(author + i) = *(current->authors + i);
				i++;
			}
			*(author + i) = '\0';

			if (strstr(author, phrase) == NULL) {
				// no match
				previous = current;
				current = current->next;
			}
			else if (previous == NULL) {
				// match in the first book
				first = first->next;
				free(current);
				current = first;
				count++;
			}
			else {
				// match in another than the first
				previous->next = current->next;
				free(current);
				current = previous->next;
				count++;
			}

		}
	}

	printf("Vymazalo sa %d zaznamov\n", count);

	return first;
}

/* output specified id linked books' details */
void h(BOOK *first) {

	BOOK *book = first;
	int i = 1;
	char *id;

	id = (char *)malloc(8 * sizeof(char));
	scanf("%s", id);

	while (book != NULL) {
		if (strcmp(id, book->id) == 0) {

			printf("%d.\n", i);
			printf("signatura: %s\n", book->signature);
			printf("isbn: %s\n", book->isbn);
			printf("nazov: %s\n", book->name);
			printf("autori: %s\n", book->authors);
			printf("datum: %s\n", book->date);
			printf("preukaz: %s\n", book->id);
			i++;
		}
		book = book->next;
	}

	if (i == 1)
		printf("Pre dane cislo preukazu neevidujeme vypozicky\n");
}

/* prolong term of loan by 1 year in books with older date than specified */
void a(BOOK *first) {

	BOOK *book = first;
	int i, count, year;
	char *date, *yearStr;

	date = (char *)malloc(9 * sizeof(char));
	yearStr = (char *)malloc(5 * sizeof(char));
	scanf("%s", date);

	count = 0;
	while (book != NULL) {
		if (strcmp(date, book->date) >= 0) {

			// increment year within the string
			strncpy(yearStr, book->date, 4);
			year = atoi(yearStr);
			year++;
			for (i = 3; i >= 0; i--) {
				*(book->date + i) = '0' + year % 10;
				year /= 10;
			}
			count++;
		}
		book = book->next;
	}

	printf("Aktualizovalo sa %d zaznamov\n", count);
}

int main() {

	char ch;
	BOOK *first = NULL, *book;

	while ((ch = tolower(getchar())) != 'k') {
		switch (ch) {
		case 'n':
			first = n(first);
			break;
		case 'v':
			v(first);
			break;
		case 'p':
			first = p(first);
			break;
		case 'z':
			first = z(first);
			break;
		case 'h':
			h(first);
			break;
		case 'a':
			a(first);
			break;
		default:
			// only specified letters matter
			break;
		}
	}

	// free existing linked list
	while (first != NULL) {
		book = first->next;
		free(first);
		first = book;
	}

	return 0;
}

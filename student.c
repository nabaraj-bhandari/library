#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers.h"

#define BOOKS_FILE "books.dat"

// Function prototypes (student.c)
int borrow_book(const char *username, const char *book_id);
int return_book(const char *username, const char *book_id);
int reserve_book(const char *username, const char *book_id);
int check_book_availability(const char *book_id);

// Function definitions
int check_book_availability(const char* book_id) {
    FILE* fp = fopen(BOOKS_FILE, "rb");
    if (!fp) {
        printf("Error opening books file.\n");
        return -1;  // Error
    }

    Book book;
    while (fread(&book, sizeof(Book), 1, fp)) {
        if (strcmp(book.book_id, book_id) == 0) {
            fclose(fp);
            return book.is_available;
        }
    }

    fclose(fp);
    printf("Book ID %s not found.\n", book_id);
    return -1;  // Not found
}

int borrow_book(const char* username, const char* book_id) {
    int available = check_book_availability(book_id);
    if (available == -1) {
        return 0;  // Book not found or error
    }
    if (!available) {
        printf("Book %s is already borrowed.\n", book_id);
        return 0;
    }

    FILE* fp = fopen(BOOKS_FILE, "rb+");
    if (!fp) {
        printf("Error opening books file.\n");
        return 0;
    }

    Book book;
    long pos;
    while (fread(&book, sizeof(Book), 1, fp)) {
        if (strcmp(book.book_id, book_id) == 0) {
            pos = ftell(fp) - sizeof(Book);
            book.is_available = 0;
            fseek(fp, pos, SEEK_SET);
            fwrite(&book, sizeof(Book), 1, fp);
            fclose(fp);
            if (issue_book(username, book_id)) {
                printf("Book %s borrowed successfully!\n", book_id);
                return 1;
            }
            return 0;
        }
    }

    fclose(fp);
    return 0;  // Shouldn’t reach here due to availability check
}


int return_book(const char* username, const char* book_id) {
    int available = check_book_availability(book_id);
    if (available == -1) {
        return 0;  // Book not found or error
    }
    if (available) {
        printf("Book %s is not borrowed.\n", book_id);
        return 0;
    }

    FILE* fp = fopen(BOOKS_FILE, "rb+");
    if (!fp) {
        printf("Error opening books file.\n");
        return 0;
    }

    Book book;
    long pos;
    while (fread(&book, sizeof(Book), 1, fp)) {
        if (strcmp(book.book_id, book_id) == 0) {
            pos = ftell(fp) - sizeof(Book);
            book.is_available = 1;
            fseek(fp, pos, SEEK_SET);
            fwrite(&book, sizeof(Book), 1, fp);
            fclose(fp);
            if (return_book_transaction(username, book_id)) {
                printf("Book %s returned successfully!\n", book_id);
                double fine = calculate_fine(username, book_id);
                if (fine > 0) {
                    printf("Fine incurred: ₹%.2f\n", fine);
                    update_fine(username, fine);
                }
                return 1;
            }
            return 0;
        }
    }

    fclose(fp);
    return 0;
}

int reserve_book(const char* username, const char* book_id) {
    int available = check_book_availability(book_id);
    if (available == -1) {
        return 0;  // Book not found or error
    }
    if (available) {
        printf("Book %s is already available. Use borrow instead.\n", book_id);
        return 0;
    }

    // Simple reservation logic: just print for now (could be expanded with a reservation file)
    printf("Book %s reserved for %s. You’ll be notified when available.\n", book_id, username);
    return 1;
}

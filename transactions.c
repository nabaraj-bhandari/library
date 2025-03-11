#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers.h"

#define TRANSACTIONS_FILE "transactions.dat"
#define FINES_FILE "fines.dat"
#define FINE_PER_5_MINUTES 100.0  // 100 rupees per 5 minutes overdue
#define MAX_LOAN_DAYS 14   // 14-day loan period
#define GRACE_PERIOD_MINUTES 10  // 10-minute grace period

// Function prototypes
int issue_book(const char* username, const char* book_id);
int return_book_transaction(const char* username, const char* book_id);
double calculate_fine(const char* username, const char* book_id);
void update_fine(const char* username, double amount);
double get_user_fines(const char* username);

// Function definitions
int issue_book(const char* username, const char* book_id) {
    FILE* fp = fopen(TRANSACTIONS_FILE, "ab");
    if (!fp) {
        printf("Error opening transactions file.\n");
        return 0;
    }

    Transaction trans;
    strncpy(trans.book_id, book_id, MAX_BOOK_ID - 1);
    trans.book_id[MAX_BOOK_ID - 1] = '\0';
    strncpy(trans.username, username, MAX_USERNAME - 1);
    trans.username[MAX_USERNAME - 1] = '\0';
    trans.issue_date = time(NULL);
    trans.return_date = 0;  // Not returned yet

    fwrite(&trans, sizeof(Transaction), 1, fp);
    fclose(fp);
    return 1;
}

int return_book_transaction(const char* username, const char* book_id) {
    FILE* fp = fopen(TRANSACTIONS_FILE, "rb+");
    if (!fp) {
        printf("Error opening transactions file.\n");
        return 0;
    }

    Transaction trans;
    long pos;
    while (fread(&trans, sizeof(Transaction), 1, fp)) {
        if (strcmp(trans.book_id, book_id) == 0 &&
            strcmp(trans.username, username) == 0 &&
            trans.return_date == 0) {
            pos = ftell(fp) - sizeof(Transaction);
            trans.return_date = time(NULL);
            fseek(fp, pos, SEEK_SET);
            fwrite(&trans, sizeof(Transaction), 1, fp);
            fclose(fp);
            generate_reports(); // Add this line to update reports
            return 1;
        }
    }

    fclose(fp);
    printf("Transaction not found or already returned.\n");
    return 0;
}

double calculate_fine(const char* username, const char* book_id) {
    FILE* fp = fopen(TRANSACTIONS_FILE, "rb");
    if (!fp) {
        printf("Error opening transactions file.\n");
        return 0.0;
    }

    Transaction trans;
    while (fread(&trans, sizeof(Transaction), 1, fp)) {
        if (strcmp(trans.book_id, book_id) == 0 &&
            strcmp(trans.username, username) == 0 &&
            trans.return_date != 0) {
            time_t due_date = trans.issue_date + (MAX_LOAN_DAYS * 24 * 60 * 60);
            if (trans.return_date > due_date) {
                double minutes_overdue = difftime(trans.return_date, due_date) / 60;
                if (minutes_overdue > GRACE_PERIOD_MINUTES) {
                    minutes_overdue -= GRACE_PERIOD_MINUTES;
                    double fine = (minutes_overdue / 5) * FINE_PER_5_MINUTES;
                    fclose(fp);
                    return fine;
                }
            }
            fclose(fp);
            return 0.0;
        }
    }

    fclose(fp);
    return 0.0;  // No fine if transaction not found or not returned
}

void update_fine(const char* username, double amount) {
    FILE* fp = fopen(FINES_FILE, "rb+");
    if (!fp) {
        fp = fopen(FINES_FILE, "wb");  // Create if doesn’t exist
        if (!fp) {
            printf("Error creating fines file.\n");
            return;
        }
    }

    Fine fine;
    long pos;
    int found = 0;
    while (fread(&fine, sizeof(Fine), 1, fp)) {
        if (strcmp(fine.username, username) == 0 && !fine.is_paid) {
            pos = ftell(fp) - sizeof(Fine);
            fine.amount += amount;
            fseek(fp, pos, SEEK_SET);
            fwrite(&fine, sizeof(Fine), 1, fp);
            found = 1;
            break;
        }
    }

    if (!found) {
        strncpy(fine.username, username, MAX_USERNAME - 1);
        fine.username[MAX_USERNAME - 1] = '\0';
        fine.amount = amount;
        fine.is_paid = 0;
        fseek(fp, 0, SEEK_END);
        fwrite(&fine, sizeof(Fine), 1, fp);
    }

    fclose(fp);
}

double get_user_fines(const char* username) {
    FILE* fp = fopen(FINES_FILE, "rb");
    if (!fp) {
        return 0.0;  // No fines if file doesn’t exist
    }

    Fine fine;
    double total = 0.0;
    while (fread(&fine, sizeof(Fine), 1, fp)) {
        if (strcmp(fine.username, username) == 0 && !fine.is_paid) {
            total += fine.amount;
        }
    }

    fclose(fp);
    return total;
}

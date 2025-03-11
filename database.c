#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"

#define USER_FILE "users.dat"
#define SESSION_FILE "session.dat"

// Function prototypes
int validate_string(const char *str, int max_len);
void database_init();

// Function definitions
int validate_string(const char *str, int max_len) {
    int len = strlen(str);
    return (len > 0 && len < max_len && strchr(str, ' ') == NULL);
}

void database_init() {
    FILE *fp = fopen(USER_FILE, "rb");
    if (!fp) {
        fp = fopen(USER_FILE, "wb");
        if (!fp) {
            printf("Error creating users file!\n");
            return;
        }

        User admin = {"admin", "admin123", 0, 1};
        fwrite(&admin, sizeof(User), 1, fp);
        fclose(fp);
        printf("Initialized database with default admin user\n");
    } else {
        fclose(fp);
    }
}

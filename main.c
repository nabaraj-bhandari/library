#include <stdio.h>
#include <string.h>
#include "headers.h"

#define USERS_FILE "users.dat"
#define TRANSACTIONS_FILE "transactions.dat"
#define FINES_FILE "fines.dat"


// Session
Session current_session = {{{0}}, 0};

// Function prototypes
void display_menu(const char* header, MenuItem* items, int count);
void handle_admin_menu();
void handle_student_menu();
void handle_admin_login();
void handle_student_login();
void exit_program();
void wait_for_enter();


int main() {
    database_init();
    load_session(&current_session);
    display_welcome_page();

    while (1) {
        if (!current_session.is_logged_in) {
            MenuItem main_items[] = {
                {"Admin Login", handle_admin_login},
                {"Student Login", handle_student_login},
                {"Create Account", create_account},
                {"Exit", exit_program}
            };
            display_menu("Library Management System", main_items, 4);
        } else {
            if (current_session.current_user.is_admin) {
                handle_admin_menu();
            } else {
                handle_student_menu();
            }
        }
        wait_for_enter();
    }

    return 0;
}

// Function definitions
void display_main_menu() {
    clear_screen();
    print_header("Library Management System");
    print_centered("| Welcome to the Library System!        |");
    print_divider();
    print_centered("| 1. Admin Login                       |");
    print_centered("| 2. Student Login                     |");
    print_centered("| 3. Create Account                    |");
    print_centered("| 4. Exit                              |");
    print_divider();
}



void handle_admin_menu() {
    MenuItem admin_items[] = {
        {"Manage Books", manage_books},
        {"Manage Users", manage_users},
        {"Generate Reports", generate_reports},
        {"View Reports", view_reports},
        {"Fine Revenue", fine_revenue},
        {"Logout", logout_system}
    };
    
    display_menu("Admin Menu", admin_items, 7);
}

void fine_revenue() {
    FILE *fp = fopen(FINES_FILE, "rb");
    if (!fp) {
        printf("Error opening fines file.\n");
        return;
    }

    double total_revenue = 0.0;
    Fine fine;
    while (fread(&fine, sizeof(Fine), 1, fp)) {
        if (fine.is_paid) {
            total_revenue += fine.amount;
        }
    }
    fclose(fp);

    printf("Total revenue from fines: $%.2f\n", total_revenue);
}


void logout_system() {
    if (current_session.is_logged_in) {
        printf("Logging out %s...\n", current_session.current_user.name);
        current_session.is_logged_in = 0;
        memset(&current_session.current_user, 0, sizeof(User));
        save_session(&current_session);
        printf("Logged out successfully.\n");
    }
}

void handle_student_menu() {
    MenuItem student_items[] = {
        {"Borrow Book", borrow_book},
        {"Return Book", return_book},
        {"Reserve Book", reserve_book},
        {"Check Book Availability", check_book_availability},
        {"Change Details", change_own_details},
        {"Logout", logout_system}
    };
    
    display_menu("Student Menu", student_items, 4);
}


void change_own_details() {
    User user = current_session.current_user;
    printf("Enter new Password: ");
    fgets(user.password, MAX_PASSWORD, stdin);
    user.password[strcspn(user.password, "\n")] = 0;
    printf("Enter new Full Name: ");
    fgets(user.name, MAX_NAME, stdin);
    user.name[strcspn(user.name, "\n")] = 0;

    FILE *fp = fopen(USERS_FILE, "rb+");
    if (!fp) {
        printf("Error opening users file.\n");
        return;
    }

    User temp;
    long pos;
    while (fread(&temp, sizeof(User), 1, fp)) {
        if (strcmp(temp.username, user.username) == 0) {
            pos = ftell(fp) - sizeof(User);
            fseek(fp, pos, SEEK_SET);
            fwrite(&user, sizeof(User), 1, fp);
            current_session.current_user = user;
            save_session(&current_session);
            printf("Details updated successfully!\n");
            break;
        }
    }

    fclose(fp);
}



void handle_admin_login() {
    login_system("Admin");
}

void handle_student_login() {
    login_system("Student");
}

void exit_program() {
    printf("Exiting...\n");
    exit(0);
}

void wait_for_enter() {
    printf("Press Enter to continue...");
    getchar();
}
#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <time.h>

#define MAX_USERNAME 20 // Maximum length of username
#define MAX_PASSWORD 20 // Maximum length of password
#define MAX_NAME 50 // Maximum length of name
#define MAX_ROLE 10 // Maximum length of role
#define MAX_TITLE 100  // Maximum length of title
#define MAX_AUTHOR 50 // Maximum length of author
#define MAX_BOOK_ID 13 // Maximum length of book id

// MenuItem structure
typedef struct {
    const char* title;
    void (*function)();
} MenuItem;

// User structure
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD]; 
    char name[MAX_NAME];
    char role[MAX_ROLE];
    int failed_attempts; // Number of failed login attempts
    int is_admin; // 1 if user is admin, 0 otherwise
} User;

// Book structure
typedef struct {
    char book_id[MAX_BOOK_ID];
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int published_year; // Year of publication
    int is_available; // 1 if book is available, 0 otherwise
} Book;

// Transaction structure
typedef struct {
    char book_id[MAX_BOOK_ID];
    char username[MAX_USERNAME];
    time_t issue_date; // Date of issue
    time_t return_date; // 0 if not returned yet
} Transaction;

// Fine structure
typedef struct {
    char username[MAX_USERNAME];
    double amount; // Amount of fine
    int is_paid; // 1 if fine is paid, 0 otherwise
} Fine;

// Session structure
typedef struct {
    User current_user; // Current user
    int is_logged_in;  // 1 if user is logged in, 0 otherwise
} Session;






// Function prototypes (database.c)
int authenticate_user(char *username, char *password, const char *role, User *user);
int create_user(char *username, char *password, char *name, int is_admin);
void save_session(Session *session);
void load_session(Session *session);
void database_init();
int validate_string(const char *str, int max_len);

// Function prototypes (utils.c)
void print_header(const char *title);
void print_divider();
void print_centered(const char *text);
void clear_screen();
int get_menu_choice(int min, int max);
void display_admin_menu();
void display_student_menu();
void display_welcome_page();

// Function prototypes (student.c)
int borrow_book(const char *username, const char *book_id);
int return_book(const char *username, const char *book_id);
int reserve_book(const char *username, const char *book_id);
int check_book_availability(const char *book_id);

// Function prototypes (transactions.c)
int issue_book(const char *username, const char *book_id);
int return_book_transaction(const char *username, const char *book_id);
double calculate_fine(const char *username, const char *book_id);
void update_fine(const char *username, double amount);
double get_user_fines(const char *username);

// Function prototypes (admin.c)
void manage_books();
void add_book();
void remove_book();
void update_book();
void display_all_books();
void generate_reports();
void view_reports();

void generate_book_id(const char *title_code, const char *author_code, int year, char *book_id);

void manage_users();
void update_user();
void delete_user();
void display_all_users();

// Menu function prototypes
void display_menu(const char* header, MenuItem* items, int count);
void handle_admin_menu();
void handle_student_menu();
void handle_admin_login();
void handle_student_login();
void create_account();
void exit_program();
void wait_for_enter();







#endif
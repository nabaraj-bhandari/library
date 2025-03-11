#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

#define SCREEN_WIDTH 80

// Function prototypes
void print_header(const char *title);
void print_divider();
void print_centered(const char *text);
void clear_screen();
int get_menu_choice(int min, int max);
void display_admin_menu();
void display_student_menu();
void display_welcome_page();

// Function definitions
void print_header(const char *title) {
    print_divider();
    print_centered(title);
    print_divider();
}

void print_divider() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        printf("=");
    }
    printf("\n");
}

void print_centered(const char *text) {
    int len = strlen(text);
    int padding = (SCREEN_WIDTH - len) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int get_menu_choice(int min, int max) {
    int choice;
    char input[10];
    printf("Enter your choice (%d-%d): ", min, max);
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);
    if (choice < min || choice > max) {
        printf("Invalid choice. Please try again.\n");
        return get_menu_choice(min, max);
    }
    return choice;
}

void display_admin_menu() {
    clear_screen();
    print_header("Admin Menu");
    print_centered("| 1. Manage Books                     |");
    print_centered("| 2. Manage Users                     |");
    print_centered("| 3. Generate Reports                 |");
    print_centered("| 4. View Reports                     |");
    print_centered("| 5. Popular Books                    |");
    print_centered("| 6. Fine Revenue                     |");
    print_centered("| 7. Logout                           |");
    print_divider();
}

void display_student_menu() {
    clear_screen();
    print_header("Student Menu");
    print_centered("| 1. Borrow Book                      |");
    print_centered("| 2. Return Book                      |");
    print_centered("| 3. Change Own Details               |");
    print_centered("| 4. Logout                           |");
    print_divider();
}

void display_welcome_page() {
    clear_screen();
    print_divider();
    print_centered("Welcome to the Library Management System");
    print_divider();
    print_centered("Developed by: \n");
    print_centered("Dhiraj Shrestha\n");
    print_centered("Nabaraj Bhandari\n");
    print_centered("Nikunj Bhusal\n");
    print_centered("Nirdesh Joshi\n");
    print_divider();
    print_centered("\n-= Press 'ENTER' =-");
    getchar();
}
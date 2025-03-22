#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

#define ADMIN_FILE "admins.txt"


// 函数声明
void registerAdmin();
int loginAdmin();
void displayMenu();
void clearScreen();

int main() {
    int choice;
    int loggedIn = 0;

    do {
        clearScreen();
        displayMenu();
        printf("请选择操作：");
        // (void) 显式忽略 scanf 返回值
        (void)scanf("%d", &choice);
        (void)getchar(); // 清除输入缓冲区的换行符

        switch (choice) {
        case 1:
            registerAdmin();
            break;
        case 2:
            loggedIn = loginAdmin();
            if (loggedIn) {
                printf("登录成功！\n");
                // 在此处添加管理员登录后的操作
            }
            else {
                printf("登录失败，请检查用户名或密码。\n");
            }
            break;
        case 3:
            printf("退出系统。\n");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
        }

        if (choice != 3) {
            printf("按回车键继续...");
            (void)getchar();
        }
    } while (choice != 3);

    return 0;
}

void registerAdmin() {
    FILE* file = fopen(ADMIN_FILE, "a");
    if (file == NULL) {
        perror("无法打开管理员文件");
        return;
    }

    Admin newAdmin;
    printf("请输入管理员用户名：");
    (void)fgets(newAdmin.adminName, NAME_LEN, stdin);
    newAdmin.adminName[strcspn(newAdmin.adminName, "\n")] = '\0'; // 去除换行符

    printf("请输入管理员密码：");
    (void)fgets(newAdmin.password, PASSWORD_LEN, stdin);
    newAdmin.password[strcspn(newAdmin.password, "\n")] = '\0'; // 去除换行符

    fprintf(file, "%s %s\n", newAdmin.adminName, newAdmin.password);
    fclose(file);

    printf("管理员注册成功！\n");
}

int loginAdmin() {
    FILE* file = fopen(ADMIN_FILE, "r");
    if (file == NULL) {
        perror("无法打开管理员文件");
        return 0;
    }

    char inputName[NAME_LEN];
    char inputPassword[PASSWORD_LEN];

    printf("请输入管理员用户名：");
    (void)fgets(inputName, NAME_LEN, stdin);
    inputName[strcspn(inputName, "\n")] = '\0';

    printf("请输入管理员密码：");
    (void)fgets(inputPassword, PASSWORD_LEN, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    char storedName[NAME_LEN];
    char storedPassword[PASSWORD_LEN];
    while (fscanf(file, "%s %s", storedName, storedPassword) != EOF) {
        if (strcmp(inputName, storedName) == 0 && strcmp(inputPassword, storedPassword) == 0) {
            fclose(file);
            return 1; // 登录成功
        }
    }

    fclose(file);
    return 0; // 登录失败
}

void displayMenu() {
    printf("=====================================\n");
    printf("     菜鸟驿站管理系统\n");
    printf("=====================================\n");
    printf("1. 注册管理员\n");
    printf("2. 登录管理员\n");
    printf("3. 退出\n");
    printf("=====================================\n");
}

void clearScreen() {
#ifdef _WIN32
    (void) system("cls");    // Windows 系统
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    (void)system("clear");  // Linux、Unix 或 macOS 系统
#else
    printf("\033[2J\033[H"); // 其他系统，使用 ANSI 转义序列
#endif
}

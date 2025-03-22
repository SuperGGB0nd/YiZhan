#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

#define ADMIN_FILE "admins.txt"


// ��������
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
        printf("��ѡ�������");
        // (void) ��ʽ���� scanf ����ֵ
        (void)scanf("%d", &choice);
        (void)getchar(); // ������뻺�����Ļ��з�

        switch (choice) {
        case 1:
            registerAdmin();
            break;
        case 2:
            loggedIn = loginAdmin();
            if (loggedIn) {
                printf("��¼�ɹ���\n");
                // �ڴ˴���ӹ���Ա��¼��Ĳ���
            }
            else {
                printf("��¼ʧ�ܣ������û��������롣\n");
            }
            break;
        case 3:
            printf("�˳�ϵͳ��\n");
            break;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }

        if (choice != 3) {
            printf("���س�������...");
            (void)getchar();
        }
    } while (choice != 3);

    return 0;
}

void registerAdmin() {
    FILE* file = fopen(ADMIN_FILE, "a");
    if (file == NULL) {
        perror("�޷��򿪹���Ա�ļ�");
        return;
    }

    Admin newAdmin;
    printf("���������Ա�û�����");
    (void)fgets(newAdmin.adminName, NAME_LEN, stdin);
    newAdmin.adminName[strcspn(newAdmin.adminName, "\n")] = '\0'; // ȥ�����з�

    printf("���������Ա���룺");
    (void)fgets(newAdmin.password, PASSWORD_LEN, stdin);
    newAdmin.password[strcspn(newAdmin.password, "\n")] = '\0'; // ȥ�����з�

    fprintf(file, "%s %s\n", newAdmin.adminName, newAdmin.password);
    fclose(file);

    printf("����Աע��ɹ���\n");
}

int loginAdmin() {
    FILE* file = fopen(ADMIN_FILE, "r");
    if (file == NULL) {
        perror("�޷��򿪹���Ա�ļ�");
        return 0;
    }

    char inputName[NAME_LEN];
    char inputPassword[PASSWORD_LEN];

    printf("���������Ա�û�����");
    (void)fgets(inputName, NAME_LEN, stdin);
    inputName[strcspn(inputName, "\n")] = '\0';

    printf("���������Ա���룺");
    (void)fgets(inputPassword, PASSWORD_LEN, stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    char storedName[NAME_LEN];
    char storedPassword[PASSWORD_LEN];
    while (fscanf(file, "%s %s", storedName, storedPassword) != EOF) {
        if (strcmp(inputName, storedName) == 0 && strcmp(inputPassword, storedPassword) == 0) {
            fclose(file);
            return 1; // ��¼�ɹ�
        }
    }

    fclose(file);
    return 0; // ��¼ʧ��
}

void displayMenu() {
    printf("=====================================\n");
    printf("     ������վ����ϵͳ\n");
    printf("=====================================\n");
    printf("1. ע�����Ա\n");
    printf("2. ��¼����Ա\n");
    printf("3. �˳�\n");
    printf("=====================================\n");
}

void clearScreen() {
#ifdef _WIN32
    (void) system("cls");    // Windows ϵͳ
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    (void)system("clear");  // Linux��Unix �� macOS ϵͳ
#else
    printf("\033[2J\033[H"); // ����ϵͳ��ʹ�� ANSI ת������
#endif
}

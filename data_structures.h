#pragma once
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// ��������
#define NAME_LEN         50
#define PHONE_LEN        20
#define PASSWORD_LEN     20
#define STATUS_LEN       20
#define LOCATION_LEN     20
#define PICKUP_CODE_LEN  10
#define MESSAGE_LEN      100
#define COMPANY_LEN      50
#define SPEED_LEN      10

// ����Ա��Ϣ�ṹ�壨���ڵ�¼��֤��
typedef struct Admin {
    int adminID;                    // ����ԱΨһ��ʶ
    char adminName[NAME_LEN];       // ����Ա�û���
    char password[PASSWORD_LEN];    // ��¼����
    struct Admin* next;             // ָ����һ������Ա�ڵ�
} Admin;

// ��ͨ�û���Ϣ�ṹ�壨����Ҫ��¼�����洢������Ϣ��
typedef struct User {
    int id;                         // �û�Ψһ��ʶ
    char name[NAME_LEN];            // �û�����
    char phone[PHONE_LEN];          // ��ϵ�绰
    int isVIP;                      // �Ƿ�ΪVIP��1���ǣ�0����
    struct User* next;              // ָ����һ���û��ڵ�
} User;

// ������Ϣ�ṹ��
typedef struct Package {
    int packageID;                  // ����Ψһ��ʶ
    int userID;                     // ��������ͨ�û�ID
    int category;                   // �������ࣨ1~6:ʳƷ������Ʒ���ļ����������Ʒ��������
    char status[STATUS_LEN];        // ����״̬���� "���"��"����"��"�쳣"
    char location[LOCATION_LEN];    // �������λ��
    char pickupCode[PICKUP_CODE_LEN];// ȡ����
    struct Package* next;           // ָ����һ�������ڵ�
} Package;

// ֪ͨ��Ϣ�ṹ�壨ȡ��֪ͨ��ļ����ѣ�
typedef struct Notification {
    int notificationID;             // ֪ͨΨһ��ʶ
    int packageID;                  // �����İ���ID
    char message[MESSAGE_LEN];      // ֪ͨ����
    struct Notification* next;      // ָ����һ��֪ͨ�ڵ�
} Notification;

// ���Ա��Ϣ�ṹ��
typedef struct Courier {
    int courierID;                  // ���ԱΨһ��ʶ
    double postage;                 // �ʷ�
    char speed[SPEED_LEN];          // �ٶȵȼ����� "����"��"�е�"��"����"
    char company[COMPANY_LEN];      // ������˾
    struct Courier* next;           // ָ����һ�����Ա�ڵ�
} Courier;

#endif // DATA_STRUCTURES_H

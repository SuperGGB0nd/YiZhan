#pragma once
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// 常量定义
#define NAME_LEN         50
#define PHONE_LEN        20
#define PASSWORD_LEN     20
#define STATUS_LEN       20
#define LOCATION_LEN     20
#define PICKUP_CODE_LEN  10
#define MESSAGE_LEN      100
#define COMPANY_LEN      50
#define SPEED_LEN      10

// 管理员信息结构体（用于登录验证）
typedef struct Admin {
    int adminID;                    // 管理员唯一标识
    char adminName[NAME_LEN];       // 管理员用户名
    char password[PASSWORD_LEN];    // 登录密码
    struct Admin* next;             // 指向下一个管理员节点
} Admin;

// 普通用户信息结构体（不需要登录，仅存储基本信息）
typedef struct User {
    int id;                         // 用户唯一标识
    char name[NAME_LEN];            // 用户姓名
    char phone[PHONE_LEN];          // 联系电话
    int isVIP;                      // 是否为VIP（1：是，0：否）
    struct User* next;              // 指向下一个用户节点
} User;

// 包裹信息结构体
typedef struct Package {
    int packageID;                  // 包裹唯一标识
    int userID;                     // 关联的普通用户ID
    int category;                   // 包裹种类（1~6:食品，贵重品，文件，衣物，日用品，其他）
    char status[STATUS_LEN];        // 包裹状态，如 "入库"、"出库"、"异常"
    char location[LOCATION_LEN];    // 包裹存放位置
    char pickupCode[PICKUP_CODE_LEN];// 取件码
    struct Package* next;           // 指向下一个包裹节点
} Package;

// 通知信息结构体（取件通知或寄件提醒）
typedef struct Notification {
    int notificationID;             // 通知唯一标识
    int packageID;                  // 关联的包裹ID
    char message[MESSAGE_LEN];      // 通知内容
    struct Notification* next;      // 指向下一个通知节点
} Notification;

// 快递员信息结构体
typedef struct Courier {
    int courierID;                  // 快递员唯一标识
    double postage;                 // 邮费
    char speed[SPEED_LEN];          // 速度等级，如 "快速"、"中等"、"较慢"
    char company[COMPANY_LEN];      // 所属公司
    struct Courier* next;           // 指向下一个快递员节点
} Courier;

#endif // DATA_STRUCTURES_H

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TimeInfo {
    int month;
    int day;
    int hour;
    int minute;
} TimeInfo;

typedef struct Item {
    char shelfID;
    int itemID;
    char recipient[20];
    int volume;
    int mass;
    TimeInfo time;
    struct Item* next;
} Item;

Item* load() {
    FILE* fp = fopen("inv/inv.txt", "r");
    if (!fp) {
        printf("文件打开失败\n");
        return NULL;
    }

    Item* head = (Item*)malloc(sizeof(Item));
    head->next = NULL;
    Item* tail = head;

    while (!feof(fp)) {
        Item* newItem = (Item*)malloc(sizeof(Item));
        if (fscanf(fp, "%c %d 收货人：%s 体积：%d 质量：%d 时间：%d月 %d日 %d时 %d分\n",
            &newItem->shelfID, &newItem->itemID, newItem->recipient,
            &newItem->volume, &newItem->mass,
            &newItem->time.month, &newItem->time.day,
            &newItem->time.hour, &newItem->time.minute) != 9) {
            free(newItem);
            break;
        }
        newItem->next = NULL;
        tail->next = newItem;
        tail = newItem;
    }
    fclose(fp);
    return head;
}

void quit(Item* head) {
    Item* node = head;
    while (node) {
        Item* temp = node;
        node = node->next;
        free(temp);
    }
    printf("程序退出\n");
}

void saveToFile(Item* head) {
    FILE* fp = fopen("inv/inv.txt", "w");
    if (!fp) {
        printf("无法打开文件进行保存\n");
        return;
    }

    Item* node = head->next;
    while (node) {
        fprintf(fp, "%c %d 收货人：%s 体积：%d 质量：%d 时间：%d月 %d日 %d时 %d分\n",
            node->shelfID, node->itemID, node->recipient, node->volume,
            node->mass, node->time.month, node->time.day, node->time.hour, node->time.minute);
        node = node->next;
    }
    fclose(fp);
    printf("数据已保存\n");
}

void addItem(Item* head) {
    Item* node = (Item*)malloc(sizeof(Item));
    printf("请输入货物货架编号: ");
    getchar();
    scanf("%c", &node->shelfID);

    srand((unsigned)time(NULL));
    Item* temp;
    do {
        node->itemID = rand() % 10000;
        temp = head->next;
        while (temp && temp->itemID != node->itemID) {
            temp = temp->next;
        }
    } while (temp);

    printf("已生成货物ID：%c%04d\n", node->shelfID, node->itemID);
    printf("请输入收货人: ");
    scanf("%s", node->recipient);
    printf("请输入货物体积: ");
    scanf("%d", &node->volume);
    printf("请输入货物质量: ");
    scanf("%d", &node->mass);
    printf("请输入入库时间（月 日 时 分）: ");
    scanf("%d %d %d %d", &node->time.month, &node->time.day, &node->time.hour, &node->time.minute);

    node->next = head->next;
    head->next = node;
    saveToFile(head);
}

void removeItem(Item* head) {
    int id;
    printf("请输入要出库的货物ID: ");
    scanf("%d", &id);

    Item* p = head->next;
    Item* prev = head;
    while (p) {
        if (p->itemID == id) {
            prev->next = p->next;
            free(p);
            saveToFile(head);
            printf("删除成功！\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("未找到该商品！\n");
}

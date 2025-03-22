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
        printf("�ļ���ʧ��\n");
        return NULL;
    }

    Item* head = (Item*)malloc(sizeof(Item));
    head->next = NULL;
    Item* tail = head;

    while (!feof(fp)) {
        Item* newItem = (Item*)malloc(sizeof(Item));
        if (fscanf(fp, "%c %d �ջ��ˣ�%s �����%d ������%d ʱ�䣺%d�� %d�� %dʱ %d��\n",
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
    printf("�����˳�\n");
}

void saveToFile(Item* head) {
    FILE* fp = fopen("inv/inv.txt", "w");
    if (!fp) {
        printf("�޷����ļ����б���\n");
        return;
    }

    Item* node = head->next;
    while (node) {
        fprintf(fp, "%c %d �ջ��ˣ�%s �����%d ������%d ʱ�䣺%d�� %d�� %dʱ %d��\n",
            node->shelfID, node->itemID, node->recipient, node->volume,
            node->mass, node->time.month, node->time.day, node->time.hour, node->time.minute);
        node = node->next;
    }
    fclose(fp);
    printf("�����ѱ���\n");
}

void addItem(Item* head) {
    Item* node = (Item*)malloc(sizeof(Item));
    printf("�����������ܱ��: ");
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

    printf("�����ɻ���ID��%c%04d\n", node->shelfID, node->itemID);
    printf("�������ջ���: ");
    scanf("%s", node->recipient);
    printf("������������: ");
    scanf("%d", &node->volume);
    printf("�������������: ");
    scanf("%d", &node->mass);
    printf("���������ʱ�䣨�� �� ʱ �֣�: ");
    scanf("%d %d %d %d", &node->time.month, &node->time.day, &node->time.hour, &node->time.minute);

    node->next = head->next;
    head->next = node;
    saveToFile(head);
}

void removeItem(Item* head) {
    int id;
    printf("������Ҫ����Ļ���ID: ");
    scanf("%d", &id);

    Item* p = head->next;
    Item* prev = head;
    while (p) {
        if (p->itemID == id) {
            prev->next = p->next;
            free(p);
            saveToFile(head);
            printf("ɾ���ɹ���\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("δ�ҵ�����Ʒ��\n");
}

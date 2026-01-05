//
// Created by ritno on 2026/1/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct parker)

typedef struct parker {
    int pos_id;
    char car_id[10];
    struct time {
        int year;
        int month;
        int day;
        int hour;
        int minute;
    }park;
    struct time leave;
    int price;
    int capacity;
    char aera;
    struct parker *next;
} PARKER;

void menu(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void park(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void engage(PARKER * head);
double leave_fee(PARKER * head,int * tot);
void fee(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void search(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void stat(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void load_file(FILE * fp);
void save_file(FILE * fp, PARKER * head);
PARKER * create_node(char aera);
void park_info(PARKER * head);
void stat_paking_car(PARKER * head) ;
void stat_old_car(PARKER * head);
double stat_moon_fee(FILE *fp, int tag_year, int tag_moon) ;
void find_vacant(PARKER *head);
int  find_posid(PARKER *head);

int main(void) {
    FILE * fp;
    fp=fopen("park.txt","r");
    if (fp==NULL) {
        printf("初次启动程序，正在初始化\n");
        PARKER *head_A = create_node('A'), *head_B = create_node('B'), *head_C = create_node('C');
    }else {
        printf("正在加载文件\n");
        load_file("park.txt");
    }

    menu(head_A, head_B, head_C);

    return 0;
}

void menu(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    printf("-------------------------\n");
    printf("|欢迎使用PV‘s停车场管理系统！|\n");
    printf("-------------------------\n");
    printf("请输入数字选择功能，输入q退出程序：\n");
    printf("(1)停车管理\n(2)收费管理\n(3)查询\n(4)统计\n");
    while (scanf("%d", &option) == 1) {
        if (option == 1) {
            park(head_A, head_B, head_C);
        } else if (option == 2) {
            fee(head_A, head_B, head_C);
        } else if (option == 3) {
            search(head_A, head_B, head_C);
        } else if (option == 4) {
            stat(head_A, head_B, head_C);
        } else {
            printf("只有四个功能哦");
        }
    }
}

void park(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    printf("请输入车型:(按0返回上级,q退出程序)\n(1)大型\n(2)中型\n(3)小型\n");
    while (scanf("%d", &option) == 1) {
        if (option == 0) {
            menu(head_A, head_B, head_C);
        } else if (option == 1) {
            engage(head_A);
        } else if (option == 2) {
            engage(head_B);
        } else if (option == 3) {
            engage(head_C);
        } else {
            printf("没有既不大又不小还不中的车！");
        }
    }
}
void engage(PARKER *head) {
    int count=0;
    PARKER *p = head;
    while (p->next != NULL) {
        p = p->next;
        count++;
    }
    if (count > head->capacity) {
        head->pos_id = 0;
        strcpy(head->car_id,"空A00000");
        head->park.hour = 0;
        head->park.minute = 0;
        head->leave.hour = 0;
        head->leave.minute = 0;
        printf("车位已满~\n");
    }
    if (head->pos_id != 0) {
        PARKER *newcar = (PARKER *) malloc(LEN);
        newcar->next=NULL;
        p->next = newcar;
        printf("请输入当前时间:\n");
        printf("格式-时:分：\n");
        if (scanf("%d时%d分", &newcar->park.hour, &newcar->park.minute)) {
            printf("请输入车牌号:\n");
            scanf("%s", newcar->car_id);
            newcar->pos_id = head->pos_id;
            head->pos_id++;
            printf("停车成功,你的车位号为%c%d\n",p->aera,p->pos_id);
            printf("按q退出\n");
        } else {
            printf("输入不合法,即将返回上级\n");
        }
    }
}

void fee(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    int tot=0;
    while (scanf("%d", &option) == 1) {
        if (option == 0) {
            menu(head_A, head_B, head_C);
        } else if (option == 1) {
            printf("您本次停车费用为%f,祝您一路顺风", leave_fee(head_A,&tot));
        } else if (option == 2) {
            printf("您本次停车费用为%f,祝您一路顺风", leave_fee(head_B,&tot));
        } else if (option == 3) {
            printf("您本次停车费用%f,为祝您一路顺风", leave_fee(head_C,&tot));
        } else {
            printf("没有既不大又不小还不中的车！");
        }
        FILE * fp;
        fp=fopen("day_total_fee.txt","a");
        fprintf(fp,"%d年%d月%d日,%.1f元",tot);
        fclose(fp);
    }
}
double leave_fee(PARKER * head,int * tot) {
    double fee;
    PARKER * pre_p=head,*p=head->next;
    char cur_car_id[10];
    printf("请输入车牌号:\n");
    scanf("%d",&cur_car_id);

    while (p!=NULL) {
        if (!strcmp(p->car_id,cur_car_id)){
            printf("请输入当前时间,格式为——小时:分钟：(按0返回上级,q退出程序)\n");
            scanf("%d:%d", &p->leave.hour, &p->leave.minute);

            int start = p->park.hour * 60 + p->park.minute;
            int end = p->leave.hour * 60 + p->leave.minute;
            int during =end-start;

            double h = (double)during/60;
            int minute=during % 60;
            if (minute<=30) {
                h+=0.5;
            }else {
                h+=1;
            }
            head->pos_id=p->pos_id;
            pre_p->next=p->next;
            fee=head->price*h;
            free(p);
            *tot+=fee;
            return fee;
        }
        pre_p=p;
        p=p->next;
    }
}
void park_info(PARKER * head) {
    PARKER *p = head;
    while (p != NULL) {
        printf("%c区 车位号:%d 车牌号:%s 停放时间:%d时%02d分\n",p->aera,p->pos_id,p->car_id,p->park.hour,p->park.minute);
        p=p->next;
    }
}
void find_vacant(PARKER *head) {
    PARKER * p=head;
    int flag[21]={0};
    if (p->pos_id==0) {
        printf("无空闲车位\n");
    }else {
        while (p != NULL) {
            if (p->pos_id <= p->capacity) {
                flag[p->pos_id]=1;
            }
            p=p->next;
        }
        for (int i=1;i<=head->capacity;i++) {
            if (flag[i]==0) {
                printf("%c区%d号车位空闲\n",head->aera,i);
            }
        }
    }
}
int  find_posid(PARKER *head) {
    PARKER * p=head;
    char cur_car_id[10];
    int find=0;
    printf("请输入车牌号");
    scanf("%s",cur_car_id);
    while (p->next != NULL) {
        if (!strcmp(p->car_id,cur_car_id)) {
            find=1;
            printf("该车停在%c区%02d\n",p->aera,p->pos_id);
        }
        p=p->next;
    }
    return find;
}
void search(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    printf("请选择查询操作:(按0返回上级,q退出程序)");
    printf("(1)停车信息查询\n(2)空闲车位号查询\n(3)汽车车位号查询\n");
    while (scanf("%d", &option) == 1) {
        if (option == 0) {
            menu(head_A, head_B, head_C);
        } else if (option == 1) {
            park_info(head_A);
            park_info(head_B);
            park_info(head_C);
        } else if (option == 2) {
            find_vacant(head_A);
            find_vacant(head_B);
            find_vacant(head_C);
        } else if (option == 3) {
            if (!find_posid(head_A)) {
                if (!find_posid(head_B)) {
                    if (!find_posid(head_C)) {
                        printf("全场都没找到你的车\n");
                    }
                }
            }
        } else {
            printf("只有三个功能哦");
        }
    }
}

void stat(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    printf("请选择统计操作:(按0返回上级,q退出程序)\n");
    printf("(1)停车数量统计\n(2)长时间停车统计\n(3)月收费统计\n");
    while (scanf("%d", &option) == 1) {
        if (option == 0) {
            menu(head_A, head_B, head_C);
        } else if (option == 1) {
            stat_paking_car(head_A);
            stat_paking_car(head_B);
            stat_paking_car(head_C);
        } else if (option == 2) {
            stat_old_car(head_A);
            stat_old_car(head_B);
            stat_old_car(head_C);

        } else if (option == 3) {
            FILE *fp;
            fp=fopen("day_total_fee.txt","r");
            int tag_year,tag_moon;
            printf("请输入待查询月份(格式-年:月):\n");
            scanf("%d:%d", &tag_year, &tag_moon);
            printf("停车场%d年%d月总营业额为:%f\n",tag_year,tag_moon,stat_moon_fee(fp,tag_year,tag_moon));

        } else {
            printf("只有三个功能哦");
        }
    }
}
void stat_paking_car(PARKER * head) {
    PARKER * p=head;
    int count_parking_car=0;
    while (p->next != NULL) {
        count_parking_car++;
        p=p->next;
    }
    printf("%c区共有%d辆车正在停放.\n");
}
void stat_old_car(PARKER * head) {
    PARKER * p=head;
    int count_old=0;
    int hour,minute;
    printf("请输入当前时间,格式为——小时:分钟：(按0返回上级,q退出程序)\n");
    scanf("%d:%d", &hour, &minute);

    while (p->next != NULL) {
        int end=hour*60+minute;
        int start = p->park.hour * 60 + p->park.minute;
        int during =end-start;

        if (during>300) {
            count_old++;
            printf("%c区 车位号%d 车牌号%s 停放时间%d时%02d分",p->aera,p->pos_id,p->car_id,p->park.hour,p->park.minute);
        }
        printf("停车炒股票5小时的车辆共有%d辆",count_old);

        p=p->next;
    }
}
double stat_moon_fee(FILE *fp, int tag_year, int tag_moon) {

    int ori_year,ori_moon;
    int moon_fee=0,day_money;
    rewind(fp);
    while (fscanf(fp,"%d年%d月%d日,%.1f元\n", &ori_year, &ori_moon,&day_money)!=EOF) {
        if (ori_year==tag_year && ori_moon==tag_moon) {
            moon_fee+=day_money;
        }
    }
    return moon_fee;
}
PARKER *create_node(char aera) {
    PARKER *cur_p = NULL;
    cur_p = malloc(LEN);
    if (cur_p == NULL) {
        printf("内存分配失败!\n");
        exit(0);
    }
    cur_p->pos_id = 1;
    cur_p->next = NULL;
    if (aera=='A') {
        cur_p->price=3;
        cur_p->capacity=20;
        cur_p->aera='A';
    }else if (aera=='B') {
        cur_p->price=4;
        cur_p->capacity=15;
        cur_p->aera='B';
    }else if (aera=='C') {
        cur_p->price=5;
        cur_p->capacity=10;
        cur_p->aera='C';
    }
    return cur_p;
}

void load_file(FILE * fp) {

}

void save_file(FILE * fp, PARKER * head) {
    fwrite(head,LEN,1,fp);
}

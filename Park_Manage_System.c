//
// Created by PaleVerge on 2026/1/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LEN sizeof(struct parker)
#include <windows.h>


typedef struct parker {
    int pos_id;
    char car_id[9];
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
    char area;
    struct parker *next;
} PARKER;

PARKER * create_node(char area);
void menu(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void park(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void engage(PARKER * head_A,PARKER * head_B,PARKER * head_C);
void fee(PARKER * head_A, PARKER * head_B, PARKER * head_C);
double leave_fee(PARKER * head,char cur_car_id[],double * tot);
void day_fee(int tag_year,int tag_month,int tag_day,double fee);
void search(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void find_space(PARKER *head);
int  find_car(PARKER *head,char cur_car_id[]);
void park_info(PARKER * head);
void stat(PARKER * head_A, PARKER * head_B, PARKER * head_C);
void stat_paking_car(PARKER * head) ;
void stat_old_car(PARKER * head,int cur_year,int cur_month,int cur_day, int cur_hour, int cur_minute);
double stat_moon_fee(FILE *fp, int tag_year, int tag_moon) ;
void  load_file(char filename[], PARKER * head);
void save_file(char filename[], PARKER * head);
int find_min_space(PARKER *head);
void back(void);
int find(PARKER *head,char cur_car_id[]);

int main(void) {
    SetConsoleOutputCP(65001);
    PARKER * head_A = create_node('A');
    PARKER * head_B = create_node('B');
    PARKER * head_C = create_node('C');

    load_file("area_A.dat",head_A);
    load_file("area_B.dat",head_B);
    load_file("area_C.dat",head_C);

    menu(head_A, head_B, head_C);

    return 0;
}

void menu(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    while (1) {
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║             欢迎使用停车场管理系统        ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║                                           ║\n");
        printf("\t║         [1]我要停车     [2]我要交费       ║\n");
        printf("\t║                                           ║\n");
        printf("\t║         [3]信息查询     [4]数据统计       ║\n");
        printf("\t║                                           ║\n");
        printf("\t║               [5]退出系统                 ║\n");
        printf("\t║                                           ║\n");
        printf("\t╚═══════════════════════════════════════════╝\n");
        printf("\t输入数字选择功能:");

        if (scanf("%d", &option) != 1) {
            printf("\t只能输入数字1-5选择功能哦,回车键继续\n");
            back();
            continue;//继续循环
        }else {
            switch (option) {
                case 1: {
                    system("cls");
                    park(head_A, head_B, head_C);
                    break;
                }
                case 2: {
                    system("cls");
                    fee(head_A, head_B, head_C);
                    break;
                }
                case 3: {
                    system("cls");
                    search(head_A, head_B, head_C);
                    break;
                }
                case 4: {
                    system("cls");
                    stat(head_A, head_B, head_C);
                    break;
                }
                case 5: {
                    save_file("area_A.dat",head_A);
                    save_file("area_B.dat",head_B);
                    save_file("area_C.dat",head_C);
                    return ;
                }
                default: {
                    printf("\t只能输入数字1-5选择功能哦,回车键继续\n");
                    back();
                    break;
                }
            }
        }
        save_file("area_A.dat",head_A);
        save_file("area_B.dat",head_B);
        save_file("area_C.dat",head_C);
    }
}
void park(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    while (1) {
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║                 我 要 停 车               ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║                  (1)轿车                  ║\n");
        printf("\t║                                           ║\n");
        printf("\t║                  (2)中型/货车             ║\n");
        printf("\t║                                           ║\n");
        printf("\t║                  (3)大型/货车             ║\n");
        printf("\t║                                           ║\n");
        printf("\t║   (4)返回菜单                             ║\n");
        printf("\t╚═══════════════════════════════════════════╝\n");
        printf("\t选择车型或返回:");

        if (scanf("%d", &option) != 1) {
            printf("\t只能输入数字1-4选择功能哦,回车键继续:");
            while (getchar()!='\n');
            getchar();
            system("cls");
            continue;//继续循环
        }
        switch (option) {
            case 1: {
                engage(head_A,head_B,head_C);
                save_file("area_A.dat",head_A);
                return ;
            }
            case 2: {
                engage(head_B,head_A,head_C);
                save_file("area_B.dat",head_B);
                return ;
            }
            case 3: {
                engage(head_C,head_B,head_A);
                save_file("area_C.dat",head_C);
                return ;
            }
            case 4: {
                system("cls");
                return;
            }
            default: {
                printf("\t只能输入数字1-4哦");
                back();
                break;
            }
        }
    }
}
int find_min_space(PARKER *head) {
    for (int i=1;i<=head->capacity;i++) { //包括容量要有等于
        int found=0;
        PARKER *p=head->next;
        while (p!=NULL) {
            if (p->pos_id==i) {
                found=1;
                break;
            }
            p=p->next;
        }
        if (!found) {
            return i;
        }
    }
    return 0;
}

void engage(PARKER *head_A,PARKER *head_B,PARKER *head_C) {
    if (head_A->pos_id == 0) { //头节点为0，已满
        printf("\t车位已满~\n");
        back();
        return ;
    }
    PARKER *newcar = (PARKER *) malloc(LEN);

    printf("\t═════════════════════════════════════════════\n\t请输入当前时间\t格式yyyy m d h m,数字间以空格隔开即可:");

    if (scanf("%d %d %d %d %d",&newcar->park.year,&newcar->park.month,&newcar->park.day,&newcar->park.hour, &newcar->park.minute)!=5) {
        printf("\t日期格式错了哦\n");
        free(newcar);//输入失败释放内存
        back();
        return;
    }else {
        if (newcar->park.year<=1970) {
            free(newcar);
            printf("\n\t╔═══════════════════════════════════════════╗\n");
            printf("\t║            输入年份不可早于1970           ║\n");
            printf("\t╚═══════════════════════════════════════════╝\n");
            back();
            return;
        }else {
            printf("\t请输入车牌号,如鲁D12345,不分大小写:");
            scanf("%9s", newcar->car_id);
            strupr(newcar->car_id);

            if (find(head_A,newcar->car_id)) {
                printf("\t%c车库里已经有你的车了.\n",head_A->area);
                free(newcar);
                back();
                return ;
            }else if (find(head_B,newcar->car_id)){
                printf("\t%c车库里已经有你的车了.\n",head_B->area);
                free(newcar);
                back();
                return ;
            }else if (find(head_C,newcar->car_id)) {
                printf("\t%c车库里已经有你的车了.\n",head_C->area);
                free(newcar);
                back();
                return ;
            }else {
                strupr(newcar->car_id);
                newcar->area=head_A->area;
                newcar->pos_id = head_A->pos_id;

                newcar->next=head_A->next;
                head_A->next = newcar;//挂载新节点

                head_A->pos_id=find_min_space(head_A);

                printf("\t停车成功,你的车位号为%c%02d.\n",newcar->area,newcar->pos_id);
                back();
                return ;
            }
        }
    }
}
void fee(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    double tot=0;
    int option=0;
    char cur_car_id[9];
    while (1) {
        int found=0;
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║                  我 要 交 费              ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║                                           ║\n");
        printf("\t║                  (1)交费                  ║\n");
        printf("\t║                                           ║\n");
        printf("\t║   (4)返回菜单                             ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║选择交费或返回:");

        if (scanf("%d", &option) != 1) {
            printf("\t只能输入数字1或4选择功能哦,回车键继续\n");
            back();
            continue;//继续循环
        }
        switch (option) {
            case 1: {
                printf("\t╚═══════════════════════════════════════════╝\n");
                printf("\t请输入车牌号,如鲁D12345,不分大小写:");
                if (scanf("%9s",cur_car_id)==1) {
                    if (find(head_A,cur_car_id)) {
                        double fee=leave_fee(head_A,cur_car_id,&tot);
                        if (fee>1e-6) {
                            found=1;
                            printf("\t═════════════════════════════════════════════\n");
                            printf("\t尊敬的%s您本次停车%.1f元，祝您一路顺丰~\n",cur_car_id,fee);
                            back();
                            return ;
                        }else {
                            printf("\t交费失败.\n");
                            back();
                            return ;
                        }
                    }
                    if (find(head_B,cur_car_id)) {
                        double fee=leave_fee(head_B,cur_car_id,&tot);
                        if (fee>1e-6) {
                            found=1;
                            printf("\t═════════════════════════════════════════════\n");
                            printf("\t尊敬的%s您本次停车%.1f元，祝您一路顺丰~\n",cur_car_id,fee);
                            back();
                            return ;
                        } else {
                            printf("\t交费失败.\n");
                            back();
                            return ;
                        }
                    }
                    if (find(head_C,cur_car_id)) {
                        double fee=leave_fee(head_C,cur_car_id,&tot);
                        if (fee>1e-6) {
                            found=1;
                            printf("\t═════════════════════════════════════════════\n");
                            printf("\t尊敬的%s您本次停车%.1f元，祝您一路顺丰~\n",cur_car_id,fee);
                            back();
                            return ;
                        }else {
                            printf("\t交费失败.\n");
                            back();
                            return ;
                        }
                    }
                    if (!found) { //不可以没停车就交费
                        printf("\t车库里没有您的车。\n");
                        back();
                    }
                }else {
                    printf("\t我国车牌号只有8位哦\n");
                    back();
                    return ;
                }
            }
            case 4: {
                system("cls");
                return;
            }
            default: {
                printf("\t只能输入数字1或4哦,回车键继续\n");
                back();
                break;
            }
        }
    }
}
void day_fee(int tag_year,int tag_month,int tag_day,double add_fee) {
    FILE * fp=fopen("day_total_fee.txt","r");
    int found=0,count=0;
    struct temp {
        int year;
        int month;
        int day;
        double fee;
    }data[366];

    if (fp) { //找记录，有则临时存，无则新建，全部重写
        while (fscanf(fp,"%d年%d月%d日,%lf元",&data[count].year,&data[count].month,&data[count].day,&data[count].fee)==4) {
            if (tag_year==data[count].year && tag_month==data[count].month && tag_day==data[count].day) {
                data[count].fee+=add_fee;
                found=1;
            }
            count++;
        }
        fclose(fp);
    }
    if (!found) {
        data[count].year=tag_year;
        data[count].month=tag_month;
        data[count].day=tag_day;
        data[count].fee=add_fee;
        count++;
    }
    //全部重写
    fp=fopen("day_total_fee.txt","w");
    for (int i=0;i<count;i++) {
        fprintf(fp,"%d年%d月%d日,%.1f元\n",data[i].year,data[i].month,data[i].day,data[i].fee);
    }
    fclose(fp);
}
double leave_fee(PARKER * head,char cur_car_id[],double * tot) { //汽车离开，计算并返回停车费
    PARKER * pre_p=head,*p=head->next;
    while (p!=NULL) {
        if (!strcmp(p->car_id,strupr(cur_car_id))) {
            printf("\t═════════════════════════════════════════════\n");
            printf("\t请输入当前离场时间(格式yyyy m d h m,数字间以空格隔开即可):");

            if (scanf("%d %d %d %d %d",&p->leave.year,&p->leave.month,&p->leave.day,&p->leave.hour, &p->leave.minute)!=5) {
                printf("\t═════════════════════════════════════════════\n");
                printf("\t日期格式错误,请输入数字\n");
                return -1.0;
            }else {
                struct tm start={0},end={0};
                start.tm_year = p->park.year-1900;
                start.tm_mon = p->park.month-1;
                start.tm_mday = p->park.day;
                start.tm_hour = p->park.hour;
                start.tm_min = p->park.minute;

                end.tm_year = p->leave.year-1900;
                end.tm_mon = p->leave.month-1;
                end.tm_mday = p->leave.day;
                end.tm_hour = p->leave.hour;
                end.tm_min = p->leave.minute;

                time_t start_sec=mktime(&start);
                time_t end_sec=mktime(&end);

                if (start_sec == -1 || end_sec == -1) {
                    printf("\t═════════════════════════════════════════════\n");
                    printf("\t日期不存在\n");
                    return 0;
                }
                if (difftime(end_sec, start_sec)<=0) {
                    printf("\t═════════════════════════════════════════════\n");
                    printf("\t入场时间不能早于出场时间.\n");
                    return 0;
                }

                int during = (int)difftime(end_sec, start_sec)/60;
                int hour = during/60;
                int minute = during % 60;
                double fee_time;

                if (minute==0) { //整小时不变
                    fee_time=hour;
                }else {
                    if(minute<=30) {
                        fee_time=hour+0.5;
                    }else {
                        fee_time=hour+1;
                    }
                }

                pre_p->next=p->next;
                    //存入当天营业额
                double fee=head->price * fee_time;
                day_fee(p->leave.year,p->leave.month,p->leave.day,fee);
                free(p);
                head->pos_id = find_min_space(head);
                return fee;
            }
        }
        pre_p=p;
        p=p->next;
    }
    return 0;
}
void search(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    int found=0;
    char cur_car_id[9];
    while (1) {
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║                  信息查询                 ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║             (1)停车信息查询               ║\n");
        printf("\t║                                           ║\n");
        printf("\t║             (2)空闲车位号查询             ║\n");
        printf("\t║                                           ║\n");
        printf("\t║             (3)汽车车位号查询             ║\n");
        printf("\t║                                           ║\n");
        printf("\t║   (4)返回菜单                             ║\n");
        printf("\t╚═══════════════════════════════════════════╝\n");
        printf("\t请选择查询操作:");
        if (scanf("%d", &option) != 1) {
            while (getchar() != '\n');
            system("cls");
            printf("\t只能输入数字1-4,请重新输入.\n");
            continue;
        }
        switch (option) {
            case 1: {
                system("cls");
                printf("\n\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  停车信息查询             ║\n");
                printf("\t╠═══════════════════════════════════════════╝\n");
                park_info(head_A);
                printf("\t╠═══════════════════════════════════════════════\n");
                park_info(head_B);
                printf("\t╠═══════════════════════════════════════════════\n");
                park_info(head_C);
                printf("\t╚═══════════════════════════════════════════════\n");

                back();
                return;
            }
            case 2: {
                system("cls");
                printf("\n\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  空闲车位查询             ║\n");
                printf("\t╠═══════════════════════════════════════════╝\n");
                find_space(head_A);
                printf("\n\t╠═══════════════════════════════════════════════\n");
                find_space(head_B);
                printf("\n\t╠═══════════════════════════════════════════════\n");
                find_space(head_C);
                printf("\n\t╚═══════════════════════════════════════════════\n");
                back();
                return;
            }
            case 3: {
                found=0;
                system("cls");
                printf("\n\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  车位信息查询             ║\n");
                printf("\t╠═══════════════════════════════════════════╝\n");
                printf("\t║请输入车牌号,如鲁D12345,不分大小写:");
                if (scanf("%9s", cur_car_id)==1) {
                    if (find_car(head_A,cur_car_id)) found=1;
                    if (find_car(head_B,cur_car_id)) found=1;
                    if (find_car(head_C,cur_car_id)) found=1;
                    if (!found) {
                        printf("\t═════════════════════════════════════════════\n");
                        printf("\t全场都没找到你的车\n");
                    }
                    back();
                    break;
                }else {
                    printf("车牌号输入不合法\n");
                    while (getchar() != '\n');
                    return ;
                }
            }
            case 4: {
                system("cls");
                return ;
            }
            default: {
                printf("\t只能输入数字1-4选择功能哦\n");
                break;
            }
        }
    }
}
void park_info(PARKER * head) {
    PARKER * p = head->next;//跳过头节点
    if (p==NULL) {
        printf("\t║%c区还没有车辆停进来.\n",head->area);
    }
    while (p != NULL) {
        printf("\t║%c区 车位%c%02d 车牌号:%s 停放时间:%4d年%02d月%02d日%02d时%02d分\n",p->area,p->area,p->pos_id,p->car_id,p->park.year,p->park.month,p->park.day,p->park.hour,p->park.minute);
        p=p->next;
    }
}
void find_space(PARKER *head) {
    PARKER * p=head->next;
    int flag[21]={0};
    if (head->pos_id==0) { //
        printf("\t║%c区无空闲车位\n",head->area);
    }else {
        while (p != NULL) {
            if (p->pos_id <= p->capacity) {
                flag[p->pos_id]=1;
            }
            p=p->next;
        }
        printf("\t║\t\t%c区空闲车位\n",head->area);
        printf("\t║");
        for (int i=1;i<=head->capacity;i++) {
            if (flag[i]==0) {
                printf("%d|",i);
            }
        }
    }
}
int  find_car(PARKER *head,char cur_car_id[]) {
    PARKER * p=head->next;//从第二个节点开始
    int find=0;
    while (p != NULL) {
        if (!strcmp(p->car_id,strupr(cur_car_id))) {
            find=1;
            printf("\t╠═══════════════════════════════════════════╗\n");
            printf("\t║                                           ║\n");
            printf("\t║  尊贵的%s,您的爱车停放在%c区%02d.\n",strupr(cur_car_id),head->area,p->pos_id);
            printf("\t║                                           ║\n");
            printf("\t╚═══════════════════════════════════════════╝\n");
        }
        p=p->next;
    }
    return find;
}
void stat(PARKER *head_A, PARKER *head_B, PARKER *head_C) {
    int option;
    while (1) {
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║                  数据统计                 ║\n");
        printf("\t╠═══════════════════════════════════════════╣\n");
        printf("\t║             (1)停车数量统计               ║\n");
        printf("\t║                                           ║\n");
        printf("\t║             (2)久停信息统计               ║\n");
        printf("\t║                                           ║\n");
        printf("\t║             (3)某月收费统计               ║\n");
        printf("\t║                                           ║\n");
        printf("\t║   (4)返回菜单                             ║\n");
        printf("\t╚═══════════════════════════════════════════╝\n");
        printf("\t请选择统计操作:");

        if (scanf("%d", &option) != 1) {
            system("cls");
            printf("\t只能输入数字1-4选择功能哦\n");
            while (getchar() != '\n');
            continue;
        }
        switch (option) {
            case 1: {
                system("cls");
                printf("\n\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  停车信息统计             ║\n");
                printf("\t╠═══════════════════════════════════════════╣\n");
                stat_paking_car(head_A);
                printf("\t╠═══════════════════════════════════════════╣\n");
                stat_paking_car(head_B);
                printf("\t╠═══════════════════════════════════════════╣\n");
                stat_paking_car(head_C);
                printf("\t╚═══════════════════════════════════════════╝\n");
                back();
                return;
            }
            case 2: {
                int cur_year,cur_month,cur_day,cur_hour,cur_minute;
                system("cls");
                printf("\n\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  久停信息查询             ║\n");
                printf("\t╠═══════════════════════════════════════════╝\n");
                printf("\t║请输入当前时间(格式yyyy m d h m,数字间以空格隔开):\n");
                printf("\t║ ");
                if (scanf("%d %d %d %d %d",&cur_year,&cur_month,&cur_day, &cur_hour, &cur_minute)!=5) {
                    printf("\n\t╔═══════════════════════════════════════════╗\n");
                    printf("\t║                  日期格式错误             ║\n");
                    printf("\t╚═══════════════════════════════════════════╝\n");
                    back();
                    return;
                }else {
                    if (cur_year<=1970) {
                        printf("\n\t╔═══════════════════════════════════════════╗\n");
                        printf("\t║            输入年份不可早于1970           ║\n");
                        printf("\t╚═══════════════════════════════════════════╝\n");
                        back();
                        return;
                    }else {
                        system("cls");
                        printf("\n\t╔═══════════════════════════════════════════╗\n");
                        printf("\t║                  久停信息查询             ║\n");
                        printf("\t╚═══════════════════════════════════════════╝\n");
                        stat_old_car(head_A,cur_year,cur_month,cur_day, cur_hour, cur_minute);
                        stat_old_car(head_B,cur_year,cur_month,cur_day, cur_hour, cur_minute);
                        stat_old_car(head_C,cur_year,cur_month,cur_day, cur_hour, cur_minute);

                        back();
                        return;
                    }
                }
            }
            case 3: {
                system("cls");
                printf("\t╔═══════════════════════════════════════════╗\n");
                printf("\t║                  某月收费查询             ║\n");
                printf("\t╠═══════════════════════════════════════════╣\n");
                FILE * fp=fopen("day_total_fee.txt","r");
                if (fp==NULL) {
                    printf("\t║                                           ║\n");
                    printf("\t║\t不用查啦,当前还没有任何收费.        ║\n");
                    printf("\t║                                           ║\n");
                    printf("\t╚═══════════════════════════════════════════╝\n");

                    back();
                    return;
                }else {
                    int tag_year,tag_moon;
                    printf("\t║请输入查询月份(yyyy m 数字间以空格隔开即可):\n");
                    printf("\t║ ");
                    if (scanf("%d %d", &tag_year, &tag_moon)!=2) {
                        printf("\n\t╔═══════════════════════════════════════════╗\n");
                        printf("\t║                  日期格式错误             ║\n");
                        printf("\t╚═══════════════════════════════════════════╝\n");
                        back();
                        return;
                    }else {

                        if (tag_year<=1970) {
                            printf("\n\t╔═══════════════════════════════════════════╗\n");
                            printf("\t║            输入年份不可早于1970           ║\n");
                            printf("\t╚═══════════════════════════════════════════╝\n");
                            back();
                            return;
                        }else {
                            printf("\t停车场%d年%d月总营业额为:%.2f\n",tag_year,tag_moon,stat_moon_fee(fp,tag_year,tag_moon));
                            fclose(fp);

                            back();
                            return;
                        }
                    }
                }
            }
            case 4: {
                system("cls");
                return ;
            }
            default: {
                printf("\t只能输入数字1-5选择功能哦\n");
                back();
                break;
            }
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
    printf("\t║\t\t%c区共有%02d辆车正在停放.\t    ║\n",head->area,count_parking_car);
}
void stat_old_car(PARKER * head,int cur_year,int cur_month,int cur_day, int cur_hour, int cur_minute) {
    PARKER * p=head->next;
    int count_old=0;
    while (p != NULL) {
        struct tm start={0},end={0};
        start.tm_year = p->park.year-1900;
        start.tm_mon = p->park.month-1;
        start.tm_mday = p->park.day;
        start.tm_hour = p->park.hour;
        start.tm_min = p->park.minute;

        end.tm_year = cur_year-1900;
        end.tm_mon = cur_month-1;
        end.tm_mday = cur_day;
        end.tm_hour = cur_hour;
        end.tm_min = cur_minute;
        //转换时间戳
        time_t start_sec=mktime(&start);
        time_t end_sec=mktime(&end);

        if (difftime(end_sec, start_sec)<0) {
            printf("\t╔═══════════════════════════════════════════╗\n");
            printf("\t║          截至当前时间%c还没有车辆          ║\n",p->area);
            printf("\t╚═══════════════════════════════════════════╝\n");
            return ;
        }
        int during = (int)difftime(end_sec, start_sec)/60;
        double hour = (double)during/60;
        if (hour>5) {
            count_old++;
            printf("\t║%c区%02d 车辆%s %04d年%02d月%02d日%d时%d分停车,已经%.1f小时.\n",p->area,p->pos_id,p->car_id,p->park.year,p->park.month,p->park.day,p->park.hour,p->park.minute,(double)hour);
        }
        p=p->next;
    }
    printf("\n\t╔═══════════════════════════════════════════╗\n");
    printf("\t║      %c区停车超过5小时的车辆共有%02d辆       ║\n",head->area,count_old);
    printf("\t╚═══════════════════════════════════════════╝\n\n");
}
double stat_moon_fee(FILE *fp, int tag_year, int tag_moon) {
    int ori_year,ori_moon;
    double day_money,moon_fee=0;
    rewind(fp);
    while (fscanf(fp,"%d年%d月%*d日,%lf元\n", &ori_year, &ori_moon,&day_money)!=EOF) {
        if (ori_year==tag_year && ori_moon==tag_moon) {
            moon_fee+=day_money;
        }
    }
    return moon_fee;
}
PARKER *create_node(char area) {
    PARKER *head = NULL;
    head = malloc(LEN);
    if (head == NULL) {
        printf("\n\t╔═══════════════════════════════════════════╗\n");
        printf("\t║                  内存分配失败             ║\n");
        printf("\t╚═══════════════════════════════════════════╝\n\t");
        exit(0);
    }
    head->pos_id = 1;
    head->next = NULL;
    if (area=='A') {
        head->price=3;
        head->capacity=20;
        head->area='A';
    }else if (area=='B') {
        head->price=4;
        head->capacity=15;
        head->area='B';
    }else if (area=='C') {
        head->price=5;
        head->capacity=10;
        head->area='C';
    }
    return head;
}
void  load_file(char filename[], PARKER * head) {
    FILE * fp=fopen(filename,"rb");
    if (fp==NULL) { //空链表不读
        return;
    }
    PARKER tmp;
    if (fread(&tmp,LEN,1,fp)==1) {
        head->pos_id=tmp.pos_id;
    }
    PARKER * p=head;
    while (fread(&tmp,LEN,1,fp)==1) {
        PARKER * new_car = malloc(LEN);
        *new_car=tmp;
        new_car->next=NULL;
        p->next=new_car;
        p=new_car;
    }
    fclose(fp);
}
void save_file(char filename[], PARKER * head) {
    FILE * fp=fopen(filename,"wb");
    if (fp==NULL) {
        return;
    }
    PARKER * p=head;
    while (p != NULL) {
        PARKER tmp=*p; //清空残留的next,tmp防止截断链表
        tmp.next= NULL;
        fwrite(&tmp,LEN,1,fp);
        p=p->next;
    }
    fclose(fp);
}
void back(void) {
    printf("\n\t╔═══════════════════════════════════════════╗\n");
    printf("\t║                  按任意键返回             ║\n");
    printf("\t╚═══════════════════════════════════════════╝\n\t");
    int c;
    while ((c=getchar())!='\n' && c!=EOF) ;
    getchar();
    system("cls");
}
int find(PARKER *head,char cur_car_id[]) {
    PARKER * p=head->next; //从第二个节点开始
    while (p != NULL) {
        if (!strcmp(p->car_id,strupr(cur_car_id))) {
            return 1;
        }
        p=p->next;
    }
    return 0;
}
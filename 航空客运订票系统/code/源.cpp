#include<iostream>
#include<new>
#include<Windows.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<io.h>
#include<process.h>
#include<conio.h>
#include"rotation.h"
#define MAX(a,b) ((a)>(b)?(a):(b))

using namespace std;
//菜单初始化
void SetUp() {
    cout << endl << endl;
    cout << "             **        *        ** ****** *       ****    ****       *         *      ******" << endl;
    cout << "              **      ***      **  *      *      *       *    *     * *       * *     *     " << endl;
    cout << "               **    ** **    **   *****  *      *       *    *    *   *     *   *    ***** " << endl;
    cout << "                **  **   **  **    *      *      *       *    *   *     *   *     *   *     " << endl;
    cout << "                 ***      ***      *      *      *       *    *  *       * *       *  *     " << endl;
    cout << "                  *        *       ****** ******  ****    ****  *         *         * ******" << endl;
    cout << endl << endl << endl;
    cout << "          ☆☆☆☆☆☆☆☆☆☆☆☆☆ Airplane Servervice System ☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
    cout << endl;
    cout << "                              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "                              ┃      欢迎使用航空客运订票系统      ┃\n";
    cout << "                              ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n";
    cout << "                              ┃ 1.录入航班信息    5.购票           ┃\n";
    cout << "                              ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n";
    cout << "                              ┃ 2.加载航班数据    6.退票           ┃\n";
    cout << "                              ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n";
    cout << "                              ┃ 3.清除航班记录    7.保存航班信息   ┃\n";
    cout << "                              ┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n";
    cout << "                              ┃ 4.查询航班        0.退出           ┃\n";
    cout << "                              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

}
//根据地点构建AVL树的航班插入
void Plane_Insert(Flight_End* End, Plane_Node* New) {
    Plane_Node* T = End->data;
    if (!T) {
        End->data = new Plane_Node;
        End->data->start = New->start;
        End->data->end = New->end;
        End->data->saplnext = New;
        New->saplpre = End->data;
    }
    else {
        for (; T->saplnext; T = T->saplnext) {
            if (T->saplnext->FlightNum == New->FlightNum && T->saplnext->date == New->date) {
                return;
            }
            if (T->saplnext->date > New->date) break;
        }

        New->saplnext = T->saplnext;
        if (New->saplnext)
            New->saplnext->saplpre = New;
        T->saplnext = New;
        New->saplpre = T;
    }

    return;
};
//根据航班号构建AVL树的航班插入
void Plane_Insert(Flight_Num*& FNT, Plane_Node* New) {
    Plane_Node* T = FNT->data;
    if (!T) {
        FNT->data = new Plane_Node;
        FNT->data->FlightNum = New->FlightNum;
        FNT->data->safnnext = New;
        New->safnpre = FNT->data;
    }
    else {
        for (; T->safnnext; T = T->safnnext) {
            if (T->safnnext->date == New->date) {
                return;
            }
            if (T->safnnext->date > New->date) break;
        }
        New->safnnext = T->safnnext;
        if (New->safnnext)
            New->safnnext->safnpre = New;
        T->safnnext = New;
        New->safnpre = T;
    }
    return;
}
//根据时间构建的链表的航班插入
void Plane_Insert(Flight_Time*& FTT, Plane_Node* New) {
    Plane_Node* T = FTT->data;
    for (; T->satmnext; T = T->satmnext) {
        if (T->satmnext->FlightNum == New->FlightNum) {
            return;
        }
        if (T->satmnext->FlightNum > New->FlightNum) break;
    }
    FTT->count++;
    FlightCount++;
    New->satmnext = T->satmnext;
    if (New->satmnext)
        New->satmnext->satmpre = New;
    T->satmnext = New;
    New->satmpre = T;


}
//航班号AVL树的插入调整
Flight_Num* FN_Insert(Flight_Num*& FNT, Plane_Node* New) {
    if (FNT == NULL) {
        FNT = new Flight_Num;
        Plane_Insert(FNT, New);
        FNT->height = 0;
    }
    else if (New->FlightNum == FNT->data->FlightNum) {
        Plane_Insert(FNT, New);
    }
    else if (New->FlightNum < FNT->data->FlightNum) {
        FNT->left = FN_Insert(FNT->left, New);
        if (abs(GetH(FNT->left) - GetH(FNT->right)) == 2) {
            if (New->FlightNum < FNT->left->data->FlightNum) {
                FNT = SigleLeftRotation(FNT);
            }
            else {
                FNT = DoubleleftrightRotation(FNT);
            }
        }
    }
    else if (New->FlightNum > FNT->data->FlightNum) {
        FNT->right = FN_Insert(FNT->right, New);
        if (abs(GetH(FNT->left) - GetH(FNT->right)) == 2) {
            if (New->FlightNum > FNT->right->data->FlightNum) {
                FNT = SigleRightRotation(FNT);
            }
            else {
                FNT = DoublerightleftRotation(FNT);
            }
        }
    }
    FNT->height = MAX(GetH(FNT->left), GetH(FNT->right)) + 1;
    return FNT;
}
//终点站AVL树的插入调整
Flight_End* FE_Insert(Flight_End* End, string end, Plane_Node* New) {
    if (End == NULL) {
        End = new Flight_End;
        End->End = end;
        End->height = 0;
        Plane_Insert(End, New);
    }
    else if (End->End == end) {
        Plane_Insert(End, New);
    }
    else if (end < End->End) {
        End->left = FE_Insert(End->left, end, New);
        if (abs(GetH(End->left) - GetH(End->right)) == 2) {
            if (end < End->left->End) {
                End = SigleLeftRotation(End);
            }
            else {
                End = DoubleleftrightRotation(End);
            }
        }
    }
    else if (end > End->End) {
        End->right = FE_Insert(End->right, end, New);
        if (abs(GetH(End->left) - GetH(End->right)) == 2) {
            if (end > End->right->End) {
                End = SigleRightRotation(End);
            }
            else {
                End = DoublerightleftRotation(End);
            }
        }
    }
    End->height = MAX(GetH(End->left), GetH(End->right)) + 1;
    return End;
}
//起点站AVL树的插入调整
Flight_Start* FS_Insert(Flight_Start*& Start, string start, string end, Plane_Node* New) {
    if (Start == NULL) {
        Start = new Flight_Start;
        Start->start = start;
        Start->height = 0;
        Start->FENode = FE_Insert(Start->FENode, end, New);
    }
    else if (Start->start == start) {
        Start->FENode = FE_Insert(Start->FENode, end, New);
    }
    else if (start < Start->start) {
        Start->left = FS_Insert(Start->left, start, end, New);
        if (abs(GetH(Start->left) - GetH(Start->right)) == 2) {
            if (start < Start->left->start) {
                Start = SigleLeftRotation(Start);
            }
            else {
                Start = DoubleleftrightRotation(Start);
            }
        }
    }
    else if (start > Start->start) {
        Start->right = FS_Insert(Start->right, start, end, New);
        if (abs(GetH(Start->left) - GetH(Start->right)) == 2) {
            if (start > Start->right->start) {
                Start = SigleRightRotation(Start);
            }
            else {
                Start = DoublerightleftRotation(Start);
            }
        }
    }
    Start->height = MAX(GetH(Start->left), GetH(Start->right)) + 1;
    return Start;
}
//时间轴的插入调整
Flight_Time* FT_Insert(Flight_Time*& FTT, Plane_Node* New) {
    Flight_Time* T = FTT;
    for (; T->next; T = T->next) {
        if (T->next->date == New->date) {
            Plane_Insert(T->next, New);
            return FTT;
        }
        else if (T->next->date > New->date) break;
    }

    Flight_Time* N = new Flight_Time;
    N->count++;
    FlightCount++;
    N->next = T->next;
    T->next = N;
    N->date = New->date;
    N->data = new Plane_Node;
    N->data->date = New->date;
    N->data->satmnext = New;
    return FTT;
}

//航班录入
void Entry(Flight_Num*& FNT, Flight_Start*& FST, Flight_Time*& FTT) {
    system("cls");
    Plane_Node* New = new Plane_Node;
    bool sign[8] = { 0 }, flag = false;
    char ch;
    int order;
    string od;
    cout << "请 录 入 航 班，选 择 菜 单 录 入 航 班 信 息\n" << endl;
    while (1) {
        cout << "\n";
        cout << "1. 起 点 站";
        if (sign[1])cout << ":" << New->start;
        cout << '\n' << endl;
        cout << "2. 终 点 站";
        if (sign[2])cout << ":" << New->end;
        cout << '\n' << endl;
        cout << "3. 航 班 号";
        if (sign[3])cout << ":" << New->FlightNum;
        cout << '\n' << endl;
        cout << "4. 飞 机 号";
        if (sign[4])cout << ":" << New->PlaneNum;
        cout << '\n' << endl;
        cout << "5. 飞 行 日 期";
        if (sign[5])cout << ":" << New->date;
        cout << '\n' << endl;
        cout << "6. 乘 载 量";
        if (sign[6])cout << ":" << New->cap;
        cout << '\n' << endl;
        cout << "7. 余 票 量";
        if (sign[7])cout << ":" << New->lecap;
        cout << '\n' << endl;
        cout << "8. 录 入";
        cout << '\n' << endl;
        cout << "0. 退 出 录 入\n" << endl;
        cout << "请 选 择 菜 单：";
        ch = getche();
        order = ch - '0';
        cout << endl << endl;
        /* cin >> od;
         cout << endl;
         getchar();
         int order = od[0] - '0';*/
        switch (order) {
        case 1:
            cout << "\n起 点 站：";
            cin >> New->start;
            sign[order] = true;
            break;
        case 2:
            cout << "\n终 点 站：";
            cin >> New->end;
            sign[order] = true;
            break;
        case 3:
            cout << "\n航 班 号：";
            cin >> New->FlightNum;
            sign[order] = true;
            break;
        case 4:
            cout << "\n飞 机 号：";
            cin >> New->PlaneNum;
            sign[order] = true;
            break;
        case 5:
            while (1) {
                cout << "\n飞 行 日 期（如20010102)：";
                cin >> New->date;
                if (atoi(New->date.c_str()) && New->date.size() == 8) {
                    sign[order] = true;
                    break;
                }
                else {
                    cout << "\n请 输 入 正 确 的 飞 行 日 期！" << endl;
                }
            }
            break;
        case 6:
            while (1) {
                cout << "\n乘 载 量：";
                cin >> New->cap;
                if (atoi(New->cap.c_str())) {
                    sign[order] = true;
                    break;
                }
                else {
                    cout << "\n请 输 入 正 确 的 乘 载 量！" << endl;
                }
            }
            break;
        case 7:
            while (1) {
                cout << "\n余 票 量：";
                cin >> New->lecap;
                if (atoi(New->lecap.c_str())) {
                    sign[order] = true;
                    break;
                }
                else {
                    cout << "\n请 输 入 正 确 的 余 票 量！" << endl;
                }
                break;
            }
            break;
        case 8:
            for (int i = 1; i < 8; i++) {
                if (!sign[i]) {
                    cout << "\n信 息 键 入 未 完 全！\n" << endl;
                    Sleep(700);
                    flag = true;
                    break;
                }
            }
            if (flag)break;
            printf("        起 点 站        终 点 站        飞 行 日 期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");

            printf("%16s  --->  %8s        %11s        %8s        %8s        %8s        %8s\n", New->start.c_str(), New->end.c_str(), New->date.c_str(), New->FlightNum.c_str(), New->PlaneNum.c_str(), New->cap.c_str(), New->lecap.c_str());

            cout << "确 认 录 入 以 上 内 容？(Y/N)" << endl;
            ch = getch();
            if (ch == 'y' || ch == 'Y') {

                FST = FS_Insert(FST, New->start, New->end, New);
                FNT = FN_Insert(FNT, New);
                FTT = FT_Insert(FTT, New);
                cout << "录 入 成 功！" << endl;
                Sleep(700);
                cout << "是 否 继 续 录 入？(Y/N)" << endl;
                ch = getch();
                if (ch == 'y' || ch == 'Y') {
                    memset(sign, 0, 8);
                    New = new Plane_Node;
                    flag = 0;
                }
                else return;
                break;
            }
            break;
        case 0:
            delete  New;
            return;
        default:
            cout << "请 选 择 正 确 的 菜 单！" << endl;
            Sleep(700);
            break;
        }

        system("cls");
    }
}

//从文件加载航班信息
void Install_Buyer(Plane_Node* PN) {
    Tickets_Node* T = PN->ticket;
    if (PN->lecap == PN->cap)return;
    string root = PN->date + "\\" + PN->date + PN->start + "-" + PN->end + PN->FlightNum;
    string mkdir = "mkdir " + root, filename = root + "\\" + "订 票 名 单.txt";
    if (access(root.c_str(), 00) == -1) {
        system(mkdir.c_str());
    }
    FILE* fp = fopen(filename.c_str(), "r+");
    if (fp == NULL) {
        return;
    }
    else {
        char ch[100], name[100];
        ch[0] = fgetc(fp);
        while (!feof(fp)) {

            int i;
            fscanf(fp, "%s %d", ch, &i);
            fscanf(fp, "%s %s", ch, name);
            Passenger_Node* New = new Passenger_Node;
            New->name = name;
            New->seat = i;
            T->Buyer[i] = New;
            ch[0] = fgetc(fp);
            ch[0] = fgetc(fp);
        }
    }
    fclose(fp);
}
void Install_Waiter(Plane_Node* PN) {
    Tickets_Node* T = PN->ticket;
    string root = PN->date + "\\" + PN->date + PN->start + "-" + PN->end + " " + PN->FlightNum;
    string  mkdir = "mkdir " + root, filename = root + "候 补 名 单.txt";
    FILE* fp = fopen(filename.c_str(), "r+");
    if (fp == NULL) {
        return;
    }
    if (access(root.c_str(), 00) == -1) {
        system(mkdir.c_str());
    }

    else {
        char ch[100], name[100];
        ch[0] = fgetc(fp);
        while (!feof(fp)) {
            int i;
            fscanf(fp, "%s", name);
            Passenger_Node* New = new Passenger_Node;
            T->Waiter.push(New);
            ch[0] = fgetc(fp);
            ch[0] = fgetc(fp);
        }
    }
    fclose(fp);
}
void Install(Flight_Num*& FNT, Flight_Start*& FST, Flight_Time*& FTT) {
    string filename;
    ifstream in;
    while (1) {
        cout << "请 输 入 需 要 载 入 的 文 件 名：";
        cin >> filename;
        if (filename == "Q" || filename == "q")return;
        filename.append(".txt");
        in.open(filename);
        if (!(in)) {
            cout << "\n请 先 创 建 航 班 记 录 文 件！\n" << endl;
            cout << "输 入 Q 返 回 主 菜 单\n" << endl;
        }
        else break;
    }
    string ch;
    getline(in, ch);
    /*getline(in, ch);*/
    while (1) {
        Plane_Node* New = new Plane_Node;
        if (!(in >> New->start >> ch >> New->end >> New->date >> New->FlightNum >> New->PlaneNum >> New->cap >> New->lecap))break;
        ch[0] = in.get();

        Install_Buyer(New);
        Install_Waiter(New);
        FS_Insert(FST, New->start, New->end, New);
        FN_Insert(FNT, New);
        FT_Insert(FTT, New);
    }
    cout << "\n航 班 记 录 文 件 载 入 成 功！" << endl;
    Sleep(700);
}
//清除航班记录
void Del_Flight(Flight_Num* FNT, string date) {
    Plane_Node* T = FNT->data->safnnext;
    for (; T; ) {
        Plane_Node* del = T;
        if (del->date < date) {
            del->saplpre->saplnext = del->saplnext;
            if (del->saplnext)
                del->saplnext->saplpre = del->saplpre;
            del->safnpre->safnnext = del->safnnext;
            if (del->safnnext)
                del->safnnext->safnpre = del->safnpre;
            del->satmpre->satmnext = del->satmnext;
            if (del->satmnext)
                del->satmnext->satmpre = del->satmpre;
            FlightCount--;
            T = T->safnnext;
            delete del;
        }
        else break;
    }
    return;
}
void Clear_Flight(Flight_Num* FNT, string date) {
    if (!FNT)return;
    else if (!FNT->data)return;
    else if (FNT->data->date < date) Del_Flight(FNT, date);
    Clear_Flight(FNT->left, date);
    Clear_Flight(FNT->right, date);
}
void Clear(Flight_Num* FNT) {
    string date;
    while (1) {
        system("cls");
        cout << "此 日 期 前 的 航 班 记 录 将 被 删 除：";
        cin >> date;
        cout << endl;
        if (date == "Q" || date == "q")return;
        if (!atoi(date.c_str()) || date.size() != 8) {
            cout << "请 输 入 正 确 的 日 期！\n" << endl;
            cout << "输 入 Q 返 回 主 菜 单\n" << endl;
            Sleep(700);
        }
        else {
            cout << "确 认 删 除 " << date << " 前 的 航 班 记 录？（Y/N）\n" << endl;
            /*string judge;
            cin >> judge;*/
            char ch;
            ch = getch();
            cout << endl << endl;
            if (ch == 'Y' || ch == 'y') {
                Clear_Flight(FNT, date);
                break;
            }
        }
    }
    cout << "航 班 记 录 删 除 成 功！\n" << endl;
    Sleep(700);
}
//查询航班
string week(string date) {
    string W[7] = { "星期日","星期一","星期二","星期三","星期四","星期五","星期六" };
    int da = atoi(date.c_str());
    int y = da / 10000, m = da % 1000 / 100, d = da % 100;
    if (m == 1 || m == 2) {
        m = m + 12;
        y = y - 1;
    }
    int ret = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
    if (ret > 6 && ret < 0)return "ERROR";
    if (atoi(date.c_str()) && date.size() != 8) {
        return "ERROR";
    }
    else {
        return W[ret];
    }

}
void SearchFlight_E(Flight_End* FET, string end) {
    if (!FET)return;
    if (FET->End == end)
        Search_r = FET->data;
    else if (FET->End > end)
        SearchFlight_E(FET->left, end);
    else if (FET->End < end)
        SearchFlight_E(FET->right, end);
}
void SearchFlight_S(Flight_Start* FST, string start, string end) {
    if (!FST)return;
    if (FST->start == start)
        SearchFlight_E(FST->FENode, end);
    else if (FST->start > start)
        SearchFlight_S(FST->left, start, end);
    else if (FST->start < start)
        SearchFlight_S(FST->right, start, end);

}

void Check(Flight_Start* FST) {
    system("cls");
    string start, end;
    cout << "起 点 站：";
    cin >> start;
    cout << endl;
    cout << "终 点 站：";
    cin >> end;
    cout << endl;
    SearchFlight_S(FST, start, end);
    Plane_Node* r = NULL;
    if (Search_r)r = Search_r->saplnext;
    Search_r = NULL;
    if (!r) {
        cout << "暂 无 该 航 线！\n" << endl;
        Sleep(700);
        return;
    }
    else {
        printf("           起 点 站        终 点 站        飞 行 日 期        星  期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");

        for (int i = 1; r; i++, r = r->saplnext) {
            printf("%2d.%16s  --->  %8s        %11s        %6s        %8s        %8s        %8s        %8s\n", i, r->start.c_str(), r->end.c_str(), r->date.c_str(), week(r->date).c_str(), r->FlightNum.c_str(), r->PlaneNum.c_str(), r->cap.c_str(), r->lecap.c_str());

        }
    }
    cout << endl;

    cout << "按 任 意 键 回 到 主 菜 单！" << endl;
    char ch;
    ch = getch();
    return;
}
//订票
void SearchFlight_N(Flight_Num* FNT, string FlightNum) {
    if (!FNT)return;
    if (FNT->data->FlightNum == FlightNum)  Search_r = FNT->data;
    else if (FlightNum < FNT->data->FlightNum)SearchFlight_N(FNT->left, FlightNum);
    else if (FlightNum > FNT->data->FlightNum)SearchFlight_N(FNT->right, FlightNum);
}
void Book_Tickets(Plane_Node* PN, int tickets) {
    for (int j = 1; j <= tickets; ) {
        string name, order;
        cout << "购 票 者 " << j << " 姓 名：";
        cin >> name;
        cout << endl;
        cout << "确 认 购 票 ？（Y/N/Q)";
        char ch;
        ch = getch();
        cout << endl << endl;
        if (ch == 'Y' || ch == 'y') {
            Passenger_Node* New = new Passenger_Node;
            New->name = name;
            if (PN->ticket->Refund.isempty())
                New->seat = atoi(PN->cap.c_str()) - atoi(PN->lecap.c_str()) + 1;
            else
                New->seat = PN->ticket->Refund.front();
            stringstream in;
            in << atoi(PN->lecap.c_str()) - 1;
            in >> PN->lecap;
            PN->ticket->Buyer[New->seat] = New;
            j++;
            cout << "座 位 号：" << New->seat << endl << endl;
            cout << "订 票 成 功！\n" << endl;
            Sleep(700);
        }
        else if (ch == 'Q' || ch == 'q')return;

    }
}
void Wait_Tickets(Plane_Node* PN) {
    while (1) {
        string name, order;
        cout << "候 补 者 姓 名：";
        cin >> name;
        cout << endl;
        cout << "确 认 候 补？（Y/N/Q)" << endl;
        char ch;
        ch = getch();
        cout << endl;
        if (ch == 'Y' || ch == 'y') {
            Passenger_Node* New = new Passenger_Node;
            New->name = name;
            if (PN->ticket->Waiter.l() < atoi(PN->cap.c_str())) {
                PN->ticket->Waiter.push(New);
                cout << "候 补 成 功！" << endl << endl;
                Sleep(700);
            }
            else {
                cout << "本 航 班 无 法 候 补 更 多 的 人！" << endl;
                return;
                Sleep(700);
            }
            cout << "停 止 候 补？（Y/N)" << endl << endl;
            ch = getch();
            if (ch == 'Y' || ch == 'y')return;
        }
        else if (ch == 'Q' || ch == 'q')return;
    }

}
int Check_No(int max, int mode) {
    string od;
    int order;
    if (mode == 0)
        cout << "订 票 航 班 序 号：";
    else if (mode == 1)
        cout << "退 票 航 班 序 号：";
    else if (mode == 2)
        cout << "候 补 航 班 序 号：";
    while (1) {
        cin >> od;
        cout << endl;
        if (od == "Q" || od == "q")return -1;
        order = atoi(od.c_str());
        if (order && order > 0 && order < max) {
            return order;
        }
        else {
            cout << "请 输 入 正 确 的 航 班 序 号:";
        }

    }
}
int CheckTicket_N(Plane_Node* Buy) {
    string od;
    int order, cap = atoi(Buy->cap.c_str()), lecap = atoi(Buy->lecap.c_str());
    cout << "订 票 数：";
    while (1) {
        cin >> od;
        cout << endl;
        if (od == "Q" || od == "q")return -1;
        order = atoi(od.c_str());
        if (!order || order <= 0) {
            cout << "请 输 入 正 确 的 订 票 数：";
        }
        else if (order <= lecap) {
            return order;
        }
        else if (order > lecap) {
            cout << "余 票 量 不 足！\n" << endl;
            Sleep(700);
            return -1;
        }

    }
}
void Book(Flight_Num* FNT) {
    string FlightNum;
    if (!FNT) {
        cout << "暂 无 航 班 记 录！\n" << endl;
        Sleep(700);
        return;
    }
    while (1) {
        cout << "请 输 入 需 订 票 的 航 班 号：";
        cin >> FlightNum;
        cout << endl;

        SearchFlight_N(FNT, FlightNum);
        Plane_Node* r = NULL;
        if (Search_r)r = Search_r->safnnext;
        Search_r = NULL;
        if (!r) {
            cout << "暂 无 该 航 线！\n" << endl;
            Sleep(700);
            return;
        }
        else {
            while (1) {
                system("cls");
                Plane_Node* tail = r;
                int i;
                printf("序号        起 点 站        终 点 站        飞 行 日 期        星  期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");

                for (i = 1; tail; i++, tail = tail->safnnext) {
                    printf("%2d. %16s  --->  %8s        %11s        %6s        %8s        %8s        %8s        %8s\n", i, tail->start.c_str(), tail->end.c_str(), tail->date.c_str(), week(tail->date).c_str(), tail->FlightNum.c_str(), tail->PlaneNum.c_str(), tail->cap.c_str(), tail->lecap.c_str());

                }
                cout << endl;
                /*string od;*/
                char ch;
                int order, No, ticket;
                cout << "按 B 订 票，W 候 补，Q 退 回 上 级 菜 单，其 余 键 返 回 主 菜 单" << endl;
                /*cin >> od;*/
                ch = getch();
                cout << endl;
                if (ch == 'B' || ch == 'b') {
                    No = Check_No(i, 0);
                    if (No == -1)continue;
                    tail = r;
                    for (int j = 1; j < No; j++, tail = tail->safnnext);
                    ticket = CheckTicket_N(tail);
                    if (ticket == -1)continue;
                    else Book_Tickets(tail, ticket);
                }
                else if (ch == 'W' || ch == 'w') {
                    No = Check_No(i, 2);
                    if (No == -1)continue;
                    tail = r;
                    for (int j = 1; j < No; j++, tail = tail->safnnext);
                    Wait_Tickets(tail);
                }
                else return;
            }
        }
    }
}
//退票
void Refound_Tickets(Plane_Node* PN) {
    while (1) {
        string name, order;
        char ch;
        cout << "退 票 者 姓 名：";
        cin >> name;
        cout << endl;
        cout << "确 认 退 票？（Y/N/Q)" << endl;
        ch = getch();
        cout << endl;
        if (ch == 'y' || ch == 'Y') {
            int i;
            for (i = 1; i <= atoi(PN->cap.c_str()); i++) {
                if (PN->ticket->Buyer[i] && PN->ticket->Buyer[i]->name == name) {
                    delete PN->ticket->Buyer[i];
                    if (!PN->ticket->Waiter.isempty()) {
                        PN->ticket->Buyer[i] = PN->ticket->Waiter.front();
                    }
                    else {
                        PN->ticket->Refund.push(i);
                        PN->ticket->Buyer[i] = NULL;
                        stringstream in;
                        in << atoi(PN->lecap.c_str()) + 1;
                        in >> PN->lecap;
                    }
                    cout << "退 票 成 功！" << endl << endl;
                    Sleep(700);
                    break;
                }
            }
            if (i == atoi(PN->cap.c_str()) + 1) {
                cout << "退 票 失 败！\n" << endl;
                cout << "查 无 此 人！\n" << endl;
                Sleep(700);
                return;
            }
        }
        else if (ch == 'Q' || ch == 'q')return;
    }
}
void Refund(Flight_Num* FNT) {
    string FlightNum;
    if (!FNT) {
        cout << "暂 无 航 班 记 录！\n" << endl;
        Sleep(700);
        return;
    }
    while (1) {
        cout << "请 输 入 需 退 票 的 航 班 号：";
        cin >> FlightNum;
        cout << endl;

        SearchFlight_N(FNT, FlightNum);
        Plane_Node* r = NULL;
        if (Search_r)r = Search_r->safnnext;
        Search_r = NULL;
        if (!r) {
            cout << "暂 无 该 航 线！\n" << endl;
            Sleep(700);
            return;
        }
        else {
            while (1) {
                system("cls");
                Plane_Node* tail = r;
                int i;
                printf("序号        起 点 站        终 点 站        飞 行 日 期        星  期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");

                for (i = 1; tail; i++, tail = tail->safnnext) {
                    printf("%d.  %16s  --->  %8s        %11s        %6s        %8s        %8s        %8s        %8s\n", i, tail->start.c_str(), tail->end.c_str(), tail->date.c_str(), week(tail->date).c_str(), tail->FlightNum.c_str(), tail->PlaneNum.c_str(), tail->cap.c_str(), tail->lecap.c_str());

                }
                cout << endl;
                /*
                string od;*/
                int order, No;
                char ch;
                cout << "按 R 退 票，Q 返 回 上 级 菜 单，其 余 键 返 回 主 菜 单" << endl;
                ch = getch();
                cout << endl;
                if (ch == 'R' || ch == 'r') {
                    No = Check_No(i, 1);
                    tail = r;
                    for (int j = 1; j < No; j++, tail = tail->safnnext);
                    Refound_Tickets(tail);
                }
                else return;
            }
        }
    }
}
//保存航班信息
void Del_Flight(Flight_Time* FTT) {
    Plane_Node* del = FTT->data, * T;
    for (; del->satmnext; del = del->satmnext);
    for (; del->satmpre && FlightCount > 10000;) {
        string root = del->date + "\\" + del->date + del->start + "-" + del->end + del->FlightNum;
        string rd = "rd/s/q " + root;
        if (access(root.c_str(), 00) == 0) {
            system(rd.c_str());
        }
        del->saplpre->saplnext = del->saplnext;
        if (del->saplnext)
            del->saplnext->saplpre = del->saplpre;
        del->safnpre->safnnext = del->safnnext;
        if (del->safnnext)
            del->safnnext->safnpre = del->safnpre;
        del->satmpre->satmnext = del->satmnext;
        if (del->satmnext)
            del->satmnext->satmpre = del->satmpre;
        FlightCount--;
        T = del->satmpre;
        delete del;
        del = T;
    }
}
void Save_Buyer(Plane_Node* PN) {
    Tickets_Node* T = PN->ticket;
    string root = PN->date + "\\" + PN->date + PN->start + "-" + PN->end + PN->FlightNum;
    string mkdir = "mkdir " + root, filename = root + "\\" + "订 票 名 单.txt";

    if (PN->lecap == PN->cap) {
        FILE* fp = fopen(filename.c_str(), "wt+");
        if (fp)
            fclose(fp);
        return;
    }
    if (access(root.c_str(), 00) == -1) {
        system(mkdir.c_str());
    }

    FILE* fp = fopen(filename.c_str(), "wt+");
    for (int i = 1; i < 500; i++) {
        if (T->Buyer[i]) {
            fprintf(fp, "座位： %d\n", i);
            fprintf(fp, "姓名： %s\n\n", T->Buyer[i]->name.c_str());
        }
    }
    fclose(fp);
}
void Save_Waiter(Plane_Node* PN) {
    Tickets_Node* T = PN->ticket;

    string root = PN->date + "\\" + PN->date + PN->start + "-" + PN->end + PN->FlightNum;
    string  mkdir = "mkdir " + root, filename = root + "\\" + "候 补 名 单.txt";
    if (T->Waiter.isempty()) {
        FILE* fp = fopen(filename.c_str(), "wt+");
        if (fp)
            fclose(fp);
        return;
    }

    if (access(root.c_str(), 00) == -1) {
        system(mkdir.c_str());
    }

    FILE* fp = fopen(filename.c_str(), "wt+");
    queue<Passenger_Node*>tmp;
    for (int j = 1; !T->Waiter.isempty(); j++) {
        Passenger_Node* t = T->Waiter.front();
        fprintf(fp, "%15s", t->name.c_str());
        tmp.push(t);
        if (j % 5 == 0) {
            fprintf(fp, "\n");
        }
    }
    for (; !tmp.isempty();) {
        T->Waiter.push(tmp.front());
    }
    fclose(fp);
}
void Save_Flight(Flight_Time* FTT, FILE* FP) {
    Plane_Node* T = FTT->data->satmnext;
    FILE* fp;
    string filename = FTT->date + "\\" + FTT->date + "航班记录.txt";
    string rd = "rd /s/q " + FTT->date;
    if (!T) {
        system(rd.c_str());
        return;
    }
    fp = fopen(filename.c_str(), "wt+");
    fprintf(fp, "        起 点 站        终 点 站        飞 行 日 期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");
    int i = 0;
    for (; T; T = T->satmnext) {
        fprintf(fp, "%16s  --->  %8s        %11s        %8s        %8s        %8s        %8s\n", T->start.c_str(), T->end.c_str(), T->date.c_str(), T->FlightNum.c_str(), T->PlaneNum.c_str(), T->cap.c_str(), T->lecap.c_str());

        fprintf(FP, "%16s  --->  %8s        %11s        %8s        %8s        %8s        %8s\n", T->start.c_str(), T->end.c_str(), T->date.c_str(), T->FlightNum.c_str(), T->PlaneNum.c_str(), T->cap.c_str(), T->lecap.c_str());
        i++;
        Save_Buyer(T);
        Save_Waiter(T);
    }
    fclose(fp);
}

void Save(Flight_Time* FTT) {
    Flight_Time* T = FTT->next;
    FILE* fp;
    for (; FlightCount > 10000;) {
        Del_Flight(FTT->next);
        if (!FTT->next->data->satmnext)FTT->next = FTT->next->next;
    }
    if (!FTT->next) {
        cout << "暂 无 航 班 信 息 可 保 存！\n" << endl;
        Sleep(700);
    }
    else {
        fp = fopen("航班记录.txt", "wt+");
        fprintf(fp, "        起 点 站        终 点 站        飞 行 日 期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");

        for (; T; T = T->next) {
            string mkdir = "mkdir " + T->date;
            if (access(T->date.c_str(), 00) == -1) {
                system(mkdir.c_str());
            }
            Save_Flight(T, fp);
        }
        fclose(fp);
        cout << "航班记录保存成功！" << endl;
        Sleep(700);

    }

}
int main() {

    Flight_Start* FST = NULL;
    Flight_Num* FNT = NULL;
    Flight_Time* FTT = new Flight_Time;
    string od;
    int order;
    while (1) {
        system("cls");
        SetUp();
        cout << "请 选 择 菜 单：";
        /*cin >> od;
        cout << endl;
        order = od[0] - '0';*/
        char ch;
        ch = getche();
        order = ch - '0';
        cout << endl << endl;
        switch (order)
        {
        case 1:
            Entry(FNT, FST, FTT);
            break;
        case 2:
            Install(FNT, FST, FTT);
            break;
        case 3:
            Clear(FNT);
            break;
        case 4:
            Check(FST);
            break;
        case 5:
            Book(FNT);
            break;
        case 6:
            Refund(FNT);
            break;
        case 7:
            Save(FTT);
            break;
        case 0:
            return 0;
        default:
            cout << "请 选 择 正 确 的 菜 单！" << endl;
            Sleep(700);
            break;
        }
    }
    return 0;
}

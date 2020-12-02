#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<time.h>
#include<sstream>
using namespace std;
int main() {
	FILE* fp;
	const char* ch[10] = { "北京","上海","成都","广州","西安","深圳","香港","昆明","杭州","厦门" };
	const char* bh[10] = { "JD","FM","EU","BY","PN","ZH","HK","KY","GJ","MF" };
	int cnt = 100;
	string date;
	cin >> date;
	srand(time(0));
	fp = fopen("测试.txt"/*(date + ".txt").c_str()*/, "wt+");
	fprintf(fp, "        起 点 站        终 点 站        飞 行 日 期        航 班 号        飞 机 号        乘 载 量        余 票 量\n");
	for (int i=0;i<30;i++) {
		stringstream ss;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i != j) {
					fprintf(fp, "%16s  --->  %8s        %11s          %s%04d           P%04d        %8s        %8s\n", ch[i], ch[j], date.c_str(), bh[i], rand() % 10000, rand() % 1000, "100", "100");
					cnt++;
				}
			}
		}
		
		ss << atoi(date.c_str()) + 1;
		ss >> date;
	}
	fclose(fp);
}

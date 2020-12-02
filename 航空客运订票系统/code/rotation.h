#include<algorithm>
#include"struct.h"
#define MAX(a,b) ((a)>(b)?(a):(b))

int GetH(Flight_Start* Start) {
    if (!Start)return 0;
    return Start->height;
}
int GetH(Flight_End* End) {
    if (!End)return 0;
    return End->height;
}
int GetH(Flight_Num* FHT) {
    if (!FHT)return 0;
    return FHT->height;
}
//各种ll，lr，rr，rl旋转
//起点站的旋转
Flight_Start* SigleLeftRotation(Flight_Start* A) {
    Flight_Start* B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_Start* SigleRightRotation(Flight_Start* A) {
    Flight_Start* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_Start* DoubleleftrightRotation(Flight_Start* A) {
    A->left = SigleRightRotation(A->left);
    return SigleLeftRotation(A);
}
Flight_Start* DoublerightleftRotation(Flight_Start* A) {
    A->right = SigleLeftRotation(A->right);
    return SigleRightRotation(A);
}
//终点站的旋转
Flight_End* SigleLeftRotation(Flight_End* A) {
    Flight_End* B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_End* SigleRightRotation(Flight_End* A) {
    Flight_End* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_End* DoubleleftrightRotation(Flight_End* A) {
    A->left = SigleRightRotation(A->left);
    return SigleLeftRotation(A);
}
Flight_End* DoublerightleftRotation(Flight_End* A) {
    A->right = SigleLeftRotation(A->right);
    return SigleRightRotation(A);
}
//航班号的旋转
Flight_Num* SigleLeftRotation(Flight_Num* A) {
    Flight_Num* B = A->left;
    A->left = B->right;
    B->right = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_Num* SigleRightRotation(Flight_Num* A) {
    Flight_Num* B = A->right;
    A->right = B->left;
    B->left = A;
    A->height = MAX(GetH(A->left), GetH(A->right)) + 1;
    B->height = MAX(GetH(B->left), GetH(B->right)) + 1;
    return B;
}
Flight_Num* DoubleleftrightRotation(Flight_Num* A) {
    A->left = SigleRightRotation(A->left);
    return SigleLeftRotation(A);
}
Flight_Num* DoublerightleftRotation(Flight_Num* A) {
    A->right = SigleLeftRotation(A->right);
    return SigleRightRotation(A);
}

#include "pch.h"
#include <time.h>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

enum { max_arr = 17, max_arr_res = 68};

void Randomize(char Arr[]) {
    int wA = 0;
    wA = rand() % 0xFFFF;
    for (int i = 0, k = 0; i < 16; i++)
        if ((wA >> i) & 1)
            Arr[k++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);
}

struct mas {
    char a;
    mas *next;

    mas(char b = '\0', mas *p = nullptr) {
        next = p;
        a = b;
    }
    ~mas() {
        delete next;
    }
};

void out(mas *p) {
    while (p != nullptr) {
        cout << p->a << " ";
        p = p->next;
    }
    cout << endl;
}

bool check(mas *p, char a){
    while(p != nullptr && p->a != a){
        p = p->next;
    }
	//if(p == nullptr) return false; else return true;
	return (p) ? true : false;
}

int main() {
    srand(time(nullptr));
    char a[max_arr] = {}, b[max_arr] = {}, c[max_arr] = {}, d[max_arr] = {}, res_1[max_arr_res] = {};
    char U[] = {"123456789ABCDEF"};
    /*std::cin.getline(a, 16,'\n');
    std::cin.getline(b, 16,'\n');
    std::cin.getline(c, 16,'\n');
    std::cin.getline(d, 16,'\n');*/
    Randomize(a);
    Randomize(b);
    Randomize(c);
    Randomize(d);
    mas *res = nullptr;

    cout << "Generated array A: ";
    cout << a << endl;

    cout << "Generated array B: ";
    cout << b << endl;

    cout << "Generated array C: ";
    cout << c << endl;

    cout << "Generated array D: ";
    cout << d << endl;

    int k = 0; // 1.1 array;
    bool flag;
    unsigned long t1 = clock();
    for (int i = 0; a[i] != '\0'; i++) {
        res_1[i] = a[i];
        k++;
    }

    for (int i = 0; b[i] != '\0'; i++) {
        flag = false;
        for (int i1 = 0; i1 < k && !flag; i1++) {
            if (b[i] == res_1[i1]) {
                flag = true;
            }
        }
        if (!flag) {
            res_1[k++] = b[i];
        }
    }

    for (int i = 0; c[i] != '\0'; i++) {
        flag = false;
        for (int i1 = 0; i1 < k && !flag; i1++) {
            if (c[i] == res_1[i1]) {
                flag = true;
            }
        }
        if (!flag) {
            res_1[k++] = c[i];
        }
    }

    for (int i = 0; d[i] != '\0'; i++) {
        flag = false;
        for (int i1 = 0; i1 < k && !flag; i1++) {
            if (d[i] == res_1[i1]) {
                flag = true;
            }
        }
        if (!flag) {
            res_1[k++] = d[i];
        }
    }

    unsigned long t2 = clock();
    unsigned long t = t2 - t1;

    cout << "Result array: " << res_1 << endl;

	mas *A = new mas(a[0]);
	mas *B = new mas(b[0]);
	mas *C = new mas(c[0]);
	mas *D = new mas(d[0]);

	for (int i = 1; a[i] != '\0'; i++) {
		A = new mas(a[i], A);
	}
	
	for (int i = 1; b[i] != '\0'; i++) {
		B = new mas(b[i], B);
	}

	for (int i = 1; c[i] != '\0'; i++) {
		C = new mas(c[i], C);
	}

	for (int i = 1; d[i] != '\0'; i++) {
		D = new mas(d[i], D);
	}


    cout << "Array time = " << t / 1000.0 << endl;

    cout << "Work with list" << endl;
    t1 = clock();
    for(A; A != nullptr; A = A->next){ //1.1 list;
        res = new mas(A->a, res);
    }

    for(B; B!= nullptr; B = B->next) {
        if(!check(res, B->a)){
            res = new mas(B->a, res);
        }
    }

	for (C; C != nullptr; C = C->next) {
		if (!check(res, C->a)) {
			res = new mas(C->a, res);
		}
	}

	for (D; D != nullptr; D = D->next) {
		if (!check(res, D->a)) {
			res = new mas(D->a, res);
		}
	}
    t2 = clock();
    t = t2 - t1;
    cout << "Result list: ";
    out(res);

    cout << "List time = " << t / 1000.0 << endl;
    cout << "Work with Vector" << endl;

    bool vA[max_arr - 1];
    bool vB[max_arr - 1];
    bool vC[max_arr - 1];
    bool vD[max_arr - 1];
    bool vO[max_arr - 1];

    t1 = clock();

    for (int i = 0; a[i]; i++)
        vA[a[i] <= '9' ? a[i] + '0' : a[i] + 'A' - 10] = true;
    for (int i = 0; b[i]; i++)
        vB[b[i] <= '9' ? b[i] + '0' : b[i] + 'A' - 10] = true;
    for (int i = 0; c[i]; i++)
        vC[c[i] <= '9' ? c[i] + '0' : c[i] + 'A' - 10] = true;
    for (int i = 0; d[i]; i++)
        vD[d[i] <= '9' ? d[i] + '0' : d[i] + 'A' - 10] = true;
    for (int i = 0; i < max_arr - 1; i++) {
        vO[i] = vA[i] || vB[i] || vC[i] || vD[i];
    }

    for (int i = 0, k = 0; i < max_arr - 1; i++)
        if (vO[i])
            res_1[k++] = (char)(i <= 9 ? i + '0' : i + 'A' - 10);

    t2 = clock();
    t = t2-t1;

    cout << "Result vector: ";
    for (int i = 0;res_1[i] != '\0'; i++) {
        cout << res_1[i];
    }
    cout <<endl << "Vector time: " << t / 1000.0 << endl;

    delete res;

    std::cin.get();

    return 0;
}

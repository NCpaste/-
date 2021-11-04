/*************************************************************************
    > File Name: test.cpp
    > Author: zzg
    > Mail: zzg645453374@163.com 
    > Created Time: 2021年11月03日 星期三 05时29分01秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
const int max_size = 100;
const int INF = 0x3f3f3f3f;
#define for(i, a, b) for(int i = a; i <= b; i ++)

struct sp {
	int st;
	int size;
	bool flag; // 1 for full, 0 for empty
	int pid;
	sp* next;
	sp* ahead;
};

int op;
sp* emp;
sp* ful;

void show_emp(sp* p)
{
	printf("\nShow emp");
	sp* temp = p;
	if(!temp) {
		printf("Emp Zero\n");
		return ;
	}
	printf(" ---------- ---------- ---------- \n");
	printf("address		length		flag\n");
	while(temp){
		printf("%-7d		%-6d		%-4d\n", temp->st, temp->size, temp->flag);
		temp = temp->next;
	}
	return;
}

void show_ful(sp* p)
{
	printf("\nShow ful");
	sp* temp = p;
	if(!temp){
		printf("Ful Zero\n");
		return ;
	}
	printf(" ---------- ---------- ----------\n");
	printf("address		length		pid\n");
	while(temp){
		printf("%-7d		%-6d		%-3d\n", temp->st, temp->size, temp->pid);
		temp = temp->next;
	}
	return;
}

sp* find_t1_bf(sp* a, int size){
    sp* temp;
    int minn = INF;
    while(a){
        if(minn > a->size - size) {
            minn = a->size - size;
            temp = a;
        }
        a = a->next;
    }
    return temp;
}

sp* find_t1_wf(sp* a, int size){
    sp*temp;
    int maxx = -INF;
    while(a){
        if(maxx > a->size - size){
            maxx = a->size - size;
            temp = a;
        }
        a = a->next;
    }
    return temp;
}

sp* find_t1_ff(sp* t1, int size){
    while(t1){
        if(t1->size >= size)
            return t1;
        t1 = t1->next;
    }
    return NULL;
}

void insert(sp* a, sp* b, sp* c){
	// insert a into b,c
	if(b){
		a->next = b->next;
		b->next = a;
		a->ahead = b;
	}
	if(c){
		a->ahead = c->ahead;
		c->ahead = a;
		a->next = c;
	}
	return;
}

void init(sp* a, int st, int size, int pid, bool flag, sp* b, sp* c){
	a->st = st;
	a->size = size;
	a->pid = pid;
	a->flag = flag;
	a->ahead = b;
	a->next = c;
	return; 
}

void ff(sp* a, sp* b, int ch)
{
	printf("\nFunction ff\n");
	// a empty, b full
	sp* t1 = a->next;
	sp* t2 = b;
	int op, pid, siz;
	printf("1.allocate	2.reclaim	0.exit\n");
	printf("select:");
	cin >> op;
	printf("pid:");
	cin >> pid;

	if(op == 1){
		printf("size:");
		cin >> siz;
        
        if(ch == 1){ // ff
            t1 = find_t1_ff(t1, siz);
        }else if(ch == 2){ // CFF
            t1 = find_t1_ff(t1, siz);
        }else if(ch == 3){ // BF
            t1 = find_t1_bf(t1, siz);
        }else if(ch == 4){ // WF
            t1 = find_t1_wf(t1, siz);
        }
        
        // locate position for new full node
        while(t2->next) t2 = t2->next;
        // traverse the full node
            
        sp* ne = new(sp);
        init(ne, t2->st, siz, pid, true, NULL, NULL);
        t1->st = t1->st + siz;
        t1->size = t1->size - siz;
            
        if(t1->size == 0){
            sp* ah = t1->ahead;
            ah->next = t1->next;
            free(t1);
        }
        // full node 
	    insert(ne, t2, NULL);
        t1 = t1->next;
            
		cout << "Allocate successfully !\n";
		show_emp(a);
		show_ful(b);    
	}else if(op == 2){
		// reclaim
		printf("Reclaim\n");
		// traverse the full node
		int fla = 0;
		while(t2){
			if(t2->pid == pid)
			{
				printf("Loc successfully\n");
				fla = 1;
				// find claimed node
				sp* temp = t2;
				// find the space around t2, ta, tb
				while(t1->st < t2->st) t1 = t1->next;
				sp* ta = t1->next;
				sp* tb = t1;

				// reclaim t2
				if(ta->st + ta->size == temp->st){
					// change ta
					ta->size = temp->size + ta->size;
					free(temp);
				}else if(temp->st + temp->size == tb->st){
					// change tb
					tb->st = temp->st;
					tb->size = temp->size + tb->size;
					free(temp);
				}else{
					// mk new empty node
					insert(temp, ta, tb);
				}
			
			t2 = t2->next;
		}
		if(fla == 0) {
			printf("Wrong , Please cin again\n");
		}else {
			printf("Claim Successfully\n");
		}
	}else {
		return ;
	}
}

int main()
{
	emp = new(sp);
	emp->next = new(sp);
	ful = new(sp);
	// void init(sp* a, int st, int size, int pid, bool flag, sp* b, sp* c)
	init(emp, 0, 0, -1, false, NULL, emp->next);
	init(emp->next, 0, 1000, 0, false, emp, NULL);
	init(ful, 0, 0, -1, false, NULL, NULL);
	show_emp(emp);
	show_ful(ful);  
	while(1)
	{
		printf("\nDynamic partition allocation algorithm simulation \n");
		printf("1.FF	2.CFF	3.BF	4.WF\n");
		printf("algorithm select : ");
		
		cin >> op;
		ff(emp, ful, op);
	}
	show_emp(emp);
	show_ful(ful);
}



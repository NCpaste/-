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
#define for(i, a, b) for(int i = a; i <= b; i ++)

struct sp {
	int st;
	int size;
	bool flag; // 1 for full, 0 for empty
	int pid;
	sp* next;
	sp* ahead;
};

int op1;
sp* emp;
sp* ful;

//void init(sp* p)
//{
//	p->st = 0;
//	p->siz = 1000;
//	p->flag = 0;
//	p->next = NULL;
//	p->ahead = NULL;
//}

void show_emp(sp* p)
{
	sp* temp = p->next;
	printf("~~~~~~~~~~~~~~~\n");
	printf("address		length		flag\n");
	while(temp){
		printf("%-7d		%-6d		%-4d\n", temp->st, temp->siz, temp->flag);
		temp = temp->next;
	}
	return;
}

void show_ful(sp* p)
{
	sp* temp = p->next;
	printf("~~~~~~~~~~~~~~~\n");
	printf("address		length		pid\n");
	while(temp){
		printf("%-7d		%-6d		%-3d\n", temp->st, temp->siz, temp->pid);
		temp = temp->next;
	}
	return;
}

void ff(sp* a, sp* b)
{
	// a empty, b full
	sp* t1 = a->next;
	sp* t2 = b;
	show_emp(a);
	show_ful(b);
	int op, pid, siz;
	printf("1.allocate	2.reclaim	0.exit\n");
	printf("select:");
	cin >> op;
	printf("pid:");
	cin >> pid;
	printf("size:");
	cin >> siz;

	if(op == 1){

		t1 = find_t1_ff(t1, siz);
		//while(t1){
			// traverse the empty node	
			// different start
			//if(t1->size >= siz){
				// different end
			
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
				mknew(ne, t2->next, NULL);
			}
			t1 = t1->next;
		}
		cout << "Allocate successfully !";
	}else if(op == 2){
		// reclaim
		// traverse the full node
		int fla = 0;
		while(t2){
			if(t2->pid == pid)
			{
				fla = 1;
				// find claimed node
				sp* tmep = t2;
				// find the space around t2, ta, tb
				while(t1->st < t2->st) t1 = t1->next;
				sp* ta = t1->next;
				sp* tb = t1;

				// reclaim t2
				if(ta->st + ta.size == temp.st){
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
					mknew(temp, ta, tb);
				}
			}
			t2 = t2->next;
		}
		if(fla == 0) {
			printf("Wrong , Please cin again\n");
		}else {
			printf("Claim Successfully\n");
		}
	}

}

sp* find_t1_ff(sp* t1, int size){
    while(t1){
        if(t1->size >= size)
            return t1;
        t1 = t1->next;
    }
    return NULL;
}

void mknew(sp* a, sp* b, sp* c){
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

int main()
{
	emp = new(sp);
	ful = NULL;
	init(emp, 0, 1000, 0, false, NULL, NULL);
	printf("Dynamic partition allocation algorithm simulation \n");
	printf("1.FF	2.CFF	3.BF	4.WF\n");
	printf("algorithm select : ");
	cin >> op1;
	if(op1 == 1){
		ff(emp, ful);
	}else if(op1 == 2){
		cff(emp, ful);
	}else if(op1 == 3){
		bf(emp. ful);
	}else if(op1 == 4){
		wf(emp, ful);
	}
}



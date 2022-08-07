#include<iostream>
#include<pthread.h>
using namespace std;

pthread_mutex_t mtlock;
pthread_t tid;
int balance = 100;

void* withdraw(void *tid) {
	for (int i = 0 ; i < 10 ; i++) {
		pthread_mutex_lock(&mtlock);
		if (balance >= 10) {
			int readbalance = balance;
			cout << "At time " << i << ", the balance for withdrawal thread " << pthread_self() << " is " << balance << endl;
			readbalance -= 10;
			balance = readbalance;
			cout << "At time " << i << ", the balance after withdrawal thread " << pthread_self() << " is " << balance << endl;
			pthread_mutex_unlock(&mtlock);
		}

		else {
			pthread_mutex_unlock(&mtlock);	
			while(balance < 10) {
				//keep waiting
			}
		}
	}
}

void* deposit(void* tid) {
	for (int i = 0 ; i < 10; i++) {
		pthread_mutex_lock(&mtlock);
		int readbalance = balance;
		cout << "At time " << i << ", the balance before depositing thread " << pthread_self() << " is " << balance << endl;
		readbalance += 11;
		balance = readbalance;
		cout << "At time " << i << ", the balance after depositing thread " << pthread_self() << " is " << balance << endl;
		pthread_mutex_unlock(&mtlock);
	}
}

int main() {
	pthread_mutex_init(&mtlock, NULL);

	pthread_create(&tid, NULL, withdraw, NULL);
	pthread_create(&tid, NULL, withdraw, NULL);
	pthread_create(&tid, NULL, deposit, NULL);
	pthread_create(&tid, NULL, deposit, NULL);

	pthread_mutex_destroy(&mtlock);

	pthread_exit(NULL);
}
#include "class.h"

#include<iostream>

using namespace std;
int main(int argc, char** argv) 
{
	database db;
	int t;
	do {
		db.print_menu();
		cin >> t;
		cin.get();
		switch (t) {
		case 1:
			db.print_all_customers(); break;
		case 2:
			db.print_all_goods(); break;
		case 3:
			db.add_customer(); break;
		case 4:
			db.delete_customer(); break;
		case 5:
			db.change_password(); break;
		case 6:
			db.deposit(); break;
		case 7:
			db.buy_goods(); break;
		case 8:
			break;
		case 9:
			db.add_goods(); break;
		case 10:
			db.delete_goods(); break;
		case 11:
			db.change_price(); break;
		case 12:
			break;
		case 13:
			save(db); break;
		case 14:
			load(db); break; 
		}
	}while(t);
	
	return 0;
}

#include"class.h"
#include<iostream>
#include<fstream>
using namespace std;
std::istream& operator>>(std::istream& is, Goods& g) {
	static int number = 10000000;
	std::cout << "��������Ʒ����" << std::endl;
	std::getline(std::cin, g.goods_name);
	std::cout << "��������Ʒ���ۣ�" << std::endl;
	std::cin >> g.goods_price;
	std::cout << "��������Ʒ������" << std::endl;
	std::cin >> g.goods_ammounts;
	std::cout << "��������Ʒid������0����ϵͳ�Զ����䣺" << std::endl;
	g.goods_id = std::to_string(number);
	number++;
	return is;
}
std::istream& operator>>(std::istream& is, Customer& c) {
	int number = 10000000;
	std::cout << "�������û�����" << std::endl;
	std::getline(std::cin, c.customer_name);
	std::cout << "���������룺" << std::endl;
	std::getline(std::cin, c.customer_password);
	std::cout << "�������ֻ��ţ�" << std::endl;
	std::getline(std::cin, c.customer_phone);
	std::cout << "�������ֵ��" << std::endl;
	std::cin >> c.balance;
	std::cout << "�����뿨�ţ�����0����ϵͳ�Զ����䣺" << std::endl;
	//��д���Զ�˳�����汾���ֶ�����Ҫ��ѯ���ź���
	c.customer_number = std::to_string(number);
	number++;
	return is;
}
std::ostream& operator<<(std::ostream& os, Goods& g) {
	std::cout << g.goods_name << " " << g.goods_price << " " << g.goods_id;
	return os;
}
std::ostream& operator<<(std::ostream& os, Customer& c) {
	std::cout << c.customer_name << " " << c.customer_number << " " << c.balance << " " << c.customer_phone;
	return os;
}
database::database() {
	customers = new Customer[NEW_SIZE];
	customers_ammount = 0;
	customers_size = 4;
	goods = new Goods[NEW_SIZE];
	goods_kinds = 0;
	goods_size = 4;
}
database::~database() {
	delete[]customers;
	delete[]goods;
}
void database::print_menu(void) {
	std::cout << "�̵����ϵͳ" << std::endl;
	std::cout << "1 ����ӡ���пͻ���Ϣ" << std::endl;
	std::cout << "2 ����ӡ������Ʒ��Ϣ" << std::endl;
	std::cout << "3 �������ͻ�" << std::endl;
	std::cout << "4 ��ɾ���ͻ�" << std::endl;
	std::cout << "5 ���ͻ�����" << std::endl;
	std::cout << "6 ���ͻ����" << std::endl;
	std::cout << "7 ������" << std::endl;
	std::cout << "8 ����ѯ�ͻ���Ϣ" << std::endl;
	std::cout << "9 ��������Ʒ" << std::endl;
	std::cout << "10��ɾ����Ʒ" << std::endl;
	std::cout << "11���޸ļ۸�" << std::endl;
	std::cout << "12����ѯ��Ʒ��Ϣ" << std::endl;
	std::cout << "13: save"<<std::endl;
	std::cout << "14: load"<<std::endl;
	std::cout << "0 ���˳�" << std::endl;
}
void database::print_all_customers() {
	for (int i = 0; i < customers_ammount; i++) {
		std::cout << *(customers + i) << std::endl;
	}
}
void database::print_all_goods() {
	for (int i = 0; i < goods_kinds; i++) {
		std::cout << *(goods + i) << std::endl;
	}
}
void database::add_customer() {
	//��Ҫ�������ռ�
	if (customers_ammount == customers_size) {
		customers_size += NEW_SIZE;
		Customer* temp = new Customer[customers_size];
		//����
		for (int i = 0; i < customers_ammount; i++) {
			*(temp + i) = *(customers + i);
		}
		Customer* temp2 = customers;
		customers = temp;
		delete[]temp2;
	}
	//����
	std::cin >> *(customers + customers_ammount);
	std::cout << "�����ɹ���" << std::endl << *(customers + customers_ammount) << std::endl;
	customers_ammount++;
}
void database::delete_customer() {
	std::string c;
	std::cout << "������Ҫ�����Ŀ��ţ�" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		for (Customer* begin = find_customer(c); begin != customers + customers_ammount - 1; begin++) {
			*begin = *(begin + 1);
		}
		customers_ammount--;
		std::cout << "�û���" << c << "�ѱ�����" << std::endl;
	}
	else {
		std::cout << "���û������ڣ�" << std::endl;
	}
}
void database::change_password() {
	std::string c;
	std::cout << "�������û�����" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		std::cout << "�����������룺" << std::endl;
		std::getline(std::cin, find_customer(c)->customer_password);
		std::cout << "�û���" << c << "���ܳɹ�" << std::endl;
	}
	else {
		std::cout << "���û������ڣ�" << std::endl;
	}
}
void database::deposit() {
	std::string c;
	std::cout << "�������û�����" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		std::cout << "���������" << std::endl;
		double money;
		std::cin >> money;
		find_customer(c)->balance += money;
		std::cout << "�û���" << c << "���ɹ�" << std::endl;
	}
	else {
		std::cout << "���û������ڣ�" << std::endl;
	}
}
void database::buy_goods() {
	std::string g;
	std::cout << "��������Ʒ����" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)) {
		std::string c;
		std::cout << "�������û�����" << std::endl;
		std::getline(std::cin, c);
		if (find_customer(c)) {
			find_customer(c)->balance -= find_goods(g)->goods_price;
			find_goods(g)->goods_ammounts--;
			std::cout << "�û���" << c << "������Ʒ" << g << std::endl;
		}
		else {
			std::cout << "���û������ڣ�" << std::endl;
		}
	}
	else {
		std::cout << "����Ʒ�����ڣ�" << std::endl;
	}
}
Customer* database::find_customer(std::string s) {
	//s�������û����������ǿ��ţ�����Ѱ�ҿ���
	for (int i = 0; i < customers_ammount; i++) {
		if (s == (customers + i)->customer_number) {
			return (customers + i);
		}
	}
	for (int i = 0; i < customers_ammount; i++) {
		if (s == (customers + i)->customer_name) {
			return (customers + i);
		}
	}
	return NULL;
}
void database::add_goods() {
	//��Ҫ�������ռ�
	if (goods_kinds == goods_size) {
		goods_size += NEW_SIZE;
		Goods* temp = new Goods[goods_size];
		//����
		for (int i = 0; i < goods_kinds; i++) {
			*(temp + i) = *(goods + i);
		}
		Goods* temp2 = goods;
		goods = temp;
		delete[]temp2;
	}
	//����
	std::cin >> *(goods + goods_kinds);
	std::cout << "�����ɹ���" << std::endl << *(goods + goods_kinds) << std::endl;
	goods_kinds++;
}
void database::delete_goods() {
	std::string g;
	std::cout << "������Ҫɾ������Ʒ��" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)){
		for (Goods* begin = find_goods(g); begin != goods + goods_kinds - 1; begin++) {
			*begin = *(begin + 1);
		}
		goods_kinds--;
		std::cout << "��Ʒ��" << g << "�ѱ�ɾ��" << std::endl;
	}
	else {
		std::cout << "����Ʒ�����ڣ�" << std::endl;
	}
}
void database::change_price() {
	std::string g;
	std::cout << "��������Ʒ����" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)) {
		std::cout << "�������¼۸�" << std::endl;
		std::cin >> find_goods(g)->goods_price;
		std::cout << "��Ʒ��" << g << "�޸ĳɹ�" << std::endl;
	}
	else {
		std::cout << "����Ʒ�����ڣ�" << std::endl;
	}
}
Goods* database::find_goods(std::string s) {
	//s��������Ʒ����������id������Ѱ����Ʒ��
	for (int i = 0; i < goods_kinds; i++) {
		if (s == (goods + i)->goods_name) {
			return (goods + i);
		}
	}
	for (int i = 0; i < goods_kinds; i++) {
		if (s == (goods + i)->goods_id) {
			return (goods + i);
		}
	}
	return NULL;
}


void load(database & db)
{
	string s, f = "default";
//	cout << "Input the file name";
//	getline(cin,f);
	
	ifstream  fin;
	fin.open(f+"_goods.sp",ios::out);
	
	fin >> (db.goods_size); getline(fin,s);
	fin >> db.goods_kinds; 	getline(fin,s);
	for(int i=0; i < db.goods_size;i++ )
	{
		getline(fin,db.goods[i].goods_name);
		getline(fin,db.goods[i]. goods_id);
		//fin >> goods_name >>endl;
		//fin >> goods_id >>endl;
		fin >> db.goods[i].goods_price >> db.goods[i].goods_ammounts;
		getline(fin,s); // to read the rest  line sign
	}
	fin.close();
	fin.open(f+"_user.sp",ios::out);
	 
	fin >> db.customers_size; 		getline(fin,s);
	fin >> db.customers_ammount;	getline(fin,s);
	for(int i=0; i < db.customers_size;i++ )
	{	
		getline(fin, db.customers[i] . customer_name );
		getline(fin, db.customers[i] . customer_number );
		getline(fin, db.customers[i] . customer_password );
		getline(fin, db.customers[i] . customer_phone );
//		fin >> db.customers[i] . customer_name>> endl;
//		fin >> db.customers[i] . customer_number>> endl;
//		fin >> db.customers[i] . customer_password>> endl;
//		fin >> db.customers[i] . customer_phone>> endl;
		fin >> db.customers[i] . balance; getline(fin,s);
	}
	fin.close();
	
}
void save(database &db)
{
	string f = "default";
//	cout << "Input the file name";
//	getline(cin,f);
	
	ofstream  fout;
	fout.open(f+"_goods.sp",ios::out);
	
	fout << db.goods_size <<endl;
	fout << db.goods_kinds <<endl;
	for(int i=0; i < db.goods_size;i++ )
	{
		fout << db.goods[i] .goods_name <<endl;
		fout << db.goods[i] .goods_id <<endl;
		fout << db.goods[i] .goods_price << " " << db.goods[i] .goods_ammounts <<endl;
	}
	fout.close();
	fout.open(f+"_user.sp",ios::out);
	
	fout << db.customers_size <<endl;
	fout << db.customers_ammount <<endl;
	for(int i=0; i < db.customers_size;i++ )
	{	
		fout << db.customers[i] . customer_name<< endl;
		fout << db.customers[i] . customer_number<< endl;
		fout << db.customers[i] . customer_password<< endl;
		fout << db.customers[i] . customer_phone<< endl;
		fout << db.customers[i] . balance<< endl;
	}
	fout.close();
}

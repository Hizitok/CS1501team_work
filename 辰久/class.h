#ifndef CLASS_H
#define CLASS_H

#include<string>
#include<iostream>

const unsigned int NEW_SIZE = 4;

class database;
struct Customer {
	std::string customer_name;
	std::string customer_number;
	std::string customer_password;
	std::string customer_phone;
	double balance;
	friend void load(database &db);
	friend void save(database &db);
};
struct Goods{
	std::string goods_name;
	double goods_price;
	int goods_ammounts;
	std::string goods_id;
	
	friend void load(database &db);
	friend void save(database &db);
};
class database
{
public:
	database(); 
	~database();
	//���ݿ���� չʾ�˵�,��ӡ�ͻ�����ӡ��Ʒ
	void print_menu(void);
	void print_all_customers();
	void print_all_goods();
	//�ͻ����� ���ӣ�ɾ�������ܣ��������ѯ
	void add_customer();
	void delete_customer();
	void change_password();
	void deposit();
	void buy_goods();
	Customer* find_customer(std::string);
	//��Ʒ���� ���ӣ�ɾ�����޸ģ��۸�����������ѯ
	void add_goods();
	void delete_goods();
	void change_price();
	Goods* find_goods(std::string);	
	friend void load(database &db);
	friend void save(database &db);
	
private:
	Customer* customers;
	int customers_ammount;
	int customers_size;
	Goods* goods;
	int goods_kinds;
	int goods_size;
};
void load(database &db);
void save(database &db);

std::istream& operator>>(std::istream&, Goods&);
std::istream& operator>>(std::istream&, Customer&);
std::ostream& operator<<(std::ostream&, Goods&);
std::ostream& operator<<(std::ostream&, Customer&);


#endif //CLASS_H

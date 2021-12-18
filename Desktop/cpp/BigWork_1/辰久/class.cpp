#include"class.h"
#include<iostream>
#include<fstream>
using namespace std;
std::istream& operator>>(std::istream& is, Goods& g) {
	static int number = 10000000;
	std::cout << "请输入商品名：" << std::endl;
	std::getline(std::cin, g.goods_name);
	std::cout << "请输入商品单价：" << std::endl;
	std::cin >> g.goods_price;
	std::cout << "请输入商品数量：" << std::endl;
	std::cin >> g.goods_ammounts;
	std::cout << "请输入商品id，输入0则由系统自动分配：" << std::endl;
	g.goods_id = std::to_string(number);
	number++;
	return is;
}
std::istream& operator>>(std::istream& is, Customer& c) {
	int number = 10000000;
	std::cout << "请输入用户名：" << std::endl;
	std::getline(std::cin, c.customer_name);
	std::cout << "请输入密码：" << std::endl;
	std::getline(std::cin, c.customer_password);
	std::cout << "请输入手机号：" << std::endl;
	std::getline(std::cin, c.customer_phone);
	std::cout << "请输入充值金额：" << std::endl;
	std::cin >> c.balance;
	std::cout << "请输入卡号，输入0则由系统自动分配：" << std::endl;
	//先写个自动顺序分配版本，手动版需要查询卡号函数
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
	std::cout << "商店管理系统" << std::endl;
	std::cout << "1 ：打印所有客户信息" << std::endl;
	std::cout << "2 ：打印所有商品信息" << std::endl;
	std::cout << "3 ：新增客户" << std::endl;
	std::cout << "4 ：删除客户" << std::endl;
	std::cout << "5 ：客户改密" << std::endl;
	std::cout << "6 ：客户存款" << std::endl;
	std::cout << "7 ：购物" << std::endl;
	std::cout << "8 ：查询客户信息" << std::endl;
	std::cout << "9 ：新增商品" << std::endl;
	std::cout << "10：删除商品" << std::endl;
	std::cout << "11：修改价格" << std::endl;
	std::cout << "12：查询商品信息" << std::endl;
	std::cout << "13: save"<<std::endl;
	std::cout << "14: load"<<std::endl;
	std::cout << "0 ：退出" << std::endl;
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
	//需要分配更大空间
	if (customers_ammount == customers_size) {
		customers_size += NEW_SIZE;
		Customer* temp = new Customer[customers_size];
		//复制
		for (int i = 0; i < customers_ammount; i++) {
			*(temp + i) = *(customers + i);
		}
		Customer* temp2 = customers;
		customers = temp;
		delete[]temp2;
	}
	//输入
	std::cin >> *(customers + customers_ammount);
	std::cout << "创建成功：" << std::endl << *(customers + customers_ammount) << std::endl;
	customers_ammount++;
}
void database::delete_customer() {
	std::string c;
	std::cout << "请输入要销户的卡号：" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		for (Customer* begin = find_customer(c); begin != customers + customers_ammount - 1; begin++) {
			*begin = *(begin + 1);
		}
		customers_ammount--;
		std::cout << "用户：" << c << "已被销户" << std::endl;
	}
	else {
		std::cout << "此用户不存在！" << std::endl;
	}
}
void database::change_password() {
	std::string c;
	std::cout << "请输入用户名：" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		std::cout << "请输入新密码：" << std::endl;
		std::getline(std::cin, find_customer(c)->customer_password);
		std::cout << "用户：" << c << "改密成功" << std::endl;
	}
	else {
		std::cout << "此用户不存在！" << std::endl;
	}
}
void database::deposit() {
	std::string c;
	std::cout << "请输入用户名：" << std::endl;
	std::getline(std::cin, c);
	if (find_customer(c)) {
		std::cout << "请输入存款金额：" << std::endl;
		double money;
		std::cin >> money;
		find_customer(c)->balance += money;
		std::cout << "用户：" << c << "存款成功" << std::endl;
	}
	else {
		std::cout << "此用户不存在！" << std::endl;
	}
}
void database::buy_goods() {
	std::string g;
	std::cout << "请输入商品名：" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)) {
		std::string c;
		std::cout << "请输入用户名：" << std::endl;
		std::getline(std::cin, c);
		if (find_customer(c)) {
			find_customer(c)->balance -= find_goods(g)->goods_price;
			find_goods(g)->goods_ammounts--;
			std::cout << "用户：" << c << "购买商品" << g << std::endl;
		}
		else {
			std::cout << "此用户不存在！" << std::endl;
		}
	}
	else {
		std::cout << "此商品不存在！" << std::endl;
	}
}
Customer* database::find_customer(std::string s) {
	//s可能是用户名，可能是卡号，优先寻找卡号
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
	//需要分配更大空间
	if (goods_kinds == goods_size) {
		goods_size += NEW_SIZE;
		Goods* temp = new Goods[goods_size];
		//复制
		for (int i = 0; i < goods_kinds; i++) {
			*(temp + i) = *(goods + i);
		}
		Goods* temp2 = goods;
		goods = temp;
		delete[]temp2;
	}
	//输入
	std::cin >> *(goods + goods_kinds);
	std::cout << "创建成功：" << std::endl << *(goods + goods_kinds) << std::endl;
	goods_kinds++;
}
void database::delete_goods() {
	std::string g;
	std::cout << "请输入要删除的商品：" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)){
		for (Goods* begin = find_goods(g); begin != goods + goods_kinds - 1; begin++) {
			*begin = *(begin + 1);
		}
		goods_kinds--;
		std::cout << "商品：" << g << "已被删除" << std::endl;
	}
	else {
		std::cout << "此商品不存在！" << std::endl;
	}
}
void database::change_price() {
	std::string g;
	std::cout << "请输入商品名：" << std::endl;
	std::getline(std::cin, g);
	if (find_goods(g)) {
		std::cout << "请输入新价格：" << std::endl;
		std::cin >> find_goods(g)->goods_price;
		std::cout << "商品：" << g << "修改成功" << std::endl;
	}
	else {
		std::cout << "此商品不存在！" << std::endl;
	}
}
Goods* database::find_goods(std::string s) {
	//s可能是商品名，可能是id，优先寻找商品名
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

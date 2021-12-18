#include "ShopSystem.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int User::num=1;
int Goods::num=1;
const int no_object = -1;
User::User(){
	name = "Unknown"+to_string(num);
	ID = 10000+(num++);
	wealth=0,phone=0;
}	
User::~User(){		}
Goods::Goods(){	ID = 100000+(num++)*19 % 10000;}
Goods::~Goods(){	}

ostream& operator<<(ostream& os, User& p )
{
	os << "\t"<<lv_name(p.lvl)<<"\t" << p.ID <<"\t\t";
	os << p.name <<"\t\t"<< p.wealth <<"\t\t"<< p.phone;
}
ostream& operator<<(ostream& os, Goods& p)
{
	os <<"\t"<< p.ID <<"\t "<< p.name <<"\t\t"<< p.price<<"\t"<< p.storage;
}

void DtBase::print_cus(void){
	sort(cus,cus+num_cus);
	cout <<"\n\t Number of Customers: "<< num_cus <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i = 0; i<num_cus ;i++) cout << cus[i] << endl;
	//	( cus[i] ).show_();
}
void DtBase::print_gds(void){
	sort(gds,gds+num_gds);
	cout <<"\n\t Number of Goods: "<< num_gds <<endl;
	cout << "\t ID \t Name  \t\tPrice \tStorage \n";
	for(int i = 0; i<num_gds ;i++) cout << gds[i] << endl;
}
void DtBase::print_cus( vector<int> arr ){
	if(arr.size()==0){
		cout << "\n\tNo Such Customer!\n";	return;
	}
	cout <<"\n\t Number of Customers: "<< arr.size()  <<endl;
	cout <<"\tLevel\t\t ID\t\tName\t\tWealth\t\tPhone Number\n";
	for(int i:arr) cout << cus[i] << endl;
	//	( cus[i] ).show_();
}
void DtBase::print_gds( vector<int> arr ){
	if(arr.size()==0){
		cout << "\n\tNo Such Goods!\n";	return;
	}
	cout <<"\n\t Number of Goods: "<< arr.size() <<endl;
	cout << "\t ID \t Name\t\tPrice\tStorage \n";
	for(int i:arr) cout << gds[i] << endl;
}

int DtBase::save_gds(){
	ofstream  fout;
	fout.open(file_name+"_goods.sp",ios::out);
	fout << num_gds<<endl;
	for(int i = 0;i<num_gds;i++)	gds[i].save_( fout );
	fout.close();	
	return 0;
}
int DtBase::load_gds(){
	ifstream  fin;
		fin.open(file_name+"_goods.sp",ios::in);
		if(!fin){
			cout << "\t Can't find goods file!\n";	return 1;
		}
		fin >> num_gds;
		if(num_gds == 0) return 0; 
		gds = new Goods[num_gds+2];
		for(int i = 0;i<num_gds;i++)	gds[i].load_( fin );	
	fin.close();
	return 0;
}
int DtBase::save_cus(){
	ofstream  fout;
	fout.open(file_name+"_user.sp",ios::out);
	fout << num_cus <<endl;
	for(int i = 0; i< num_cus ; i++)	cus[i].save_( fout );	
	fout.close();
	return 0;
}
int DtBase::load_cus(){
	ifstream  fin;
	fin.open(file_name+"_user.sp",ios::in);
		if(!fin){
			cout << "\t Can't find customer file!\n";	return 1;
		}	
		fin >> num_cus;		
		if(num_cus == 0) return 0; 
		cus = new User[num_cus+2];
		for(int i = 0; i< num_cus ; i++)	cus[i].load_( fin );
	fin.close();
	return 0;
}

void Goods::load_(ifstream &fin){
	fin >> ID >> name;	
	//getline(fin,name,'\n');
	fin >> price >> storage;
}
void Goods::save_(ofstream &fout ){
	fout << ID <<"\n"<< name <<endl;
	fout << price<<" "<<storage<<endl;
}
void User::load_(ifstream &fin){
	fin >>lvl >>ID ;
	getline(fin,name,'\n');	
	// notice that u need to read a "\n" ,btw
	getline(fin,name,'\n');
	getline(fin,encrypt_pswd,'\n');
	fin >>wealth >>phone;
}
void User::save_(ofstream &fout){
	fout << lvl <<" " << ID <<endl;
	fout << name <<endl;
	fout << encrypt_pswd <<endl;
	fout << wealth << " "<<phone<<endl;	
	//cout << encrypt_pswd<<endl;
}
//IO Part Completed 

int User::add_(int level_,const string u_name)
{
	int rpt=0;
	lvl = level_;
	string a,b;
	a = u_name; b = "-";
	// notice that u need to read a "\n"
	// rpt means repeat times
	if(u_name == ""){
		cout << "\t Name:";
		while( rpt++ <2 && a=="")getline(cin,a);
		if( a=="" )	a = "Unknown_"+to_string(num++);	
		name = a;
	}	// do not use content because use Unknown_%d
	name = a;	
	while(a!=b){		
		cout << "\n\t Input password:";
		getline(cin, a);
		cout << "\t Confirm password:";
		getline(cin, b);	
		if( !(a==b) )
			cout << "\t Different password!\n\t Please Try again";
	}
	encrypt_pswd = encrypt(a);
	cout << "\t Password set Successfully!\n\t Input the wealth: ";
	cin >> wealth;
	cout << "\t Input Phone Number: ";
	cin >> phone;
	cout << "\t New user is added Successfully!\n";
	return 0;
} 
int Goods::add_()
{
	int rpt=0;
	cout << "\t Name:";
	get_content(name);
	cout << "\t Input price:";		cin >> price;
	cout << "\t Input storage:";	cin >> storage;
	return 0;	
}
void DtBase::add_cus()
{
	User *cch;
	cch = new User[2+num_cus];
	if(num_cus)
		for(int i=0 ; i<num_cus ; i++ ) cch[i]=cus[i];
	delete[]cus;	cus = cch;	cch = nullptr;
	
	cout << "\t please input your information below\n";
	cout << "Input the privilege (1 for top, 2 for normal,others for customer)";
	int an;	cin >> an;
	
	if( (an-1)*(an-2)!=0 || lvl ==3 ) an = 3 ; 
	// when the shop has no manager, u cant create one
	
	cout << "\tAdding a "<< lv_name(an);
	
	cus[num_cus++] .add_(an);
}
void DtBase::add_goods()
{
	Goods *cch;
	cch = new Goods[2+(num_gds)];
	if(num_gds)
		for(int i = 0;i<num_gds;i++) cch[i]=gds[i];		
	delete[]gds;	gds = cch;	cch = nullptr;
	
	gds[num_gds++].add_();
}

void DtBase::dlt_cus()
{
	if( manager_login() == 0 ) return;
	int sub = Get_Target_Customer(); // return subscript
	User *cch = new User[ num_cus-1 ];
	if(sub != no_object ){
		for(int i = 0; i<sub ; i++) cch[i]=cus[i];	
		for(int i = sub+1 ; i<num_cus ;i++ ) cch[ i-1 ] = cus[i];
	}
	delete[]cus;	cus = cch;	cch = nullptr;
	num_cus--;
	lvl = cus[0].lvl;
	print_cus();
}		
void DtBase::dlt_goods()
{
	if( manager_login() == 0 ) return;
	int sub = Get_Target_Goods(); // return subscript
	Goods *cch = new Goods[ num_gds-1 ];
	if(sub != no_object ){
		for(int i = 0; i<sub ; i++) cch[i]=gds[i];	
		for(int i = sub+1 ; i<num_cus ;i++ ) cch[ i-1 ] = gds[i];
	}
	delete[]gds;	gds = cch;	cch = nullptr;
	num_gds--;
	print_gds();
}	
// Add and Delete Part Completed

void DtBase::chg_cus_info()
{
	int sub = Get_Target_Customer();
	string s,s2;
	cout << "\nPlease check your identity.Password:";
	getline(cin,s);
	if(login(s) == sub )
	{
		cout << "Log in Success!\n\tInput enter to maintain info:";
		cout << "\n\tNew Name:";
		getline(cin,s);
		if( s.size()<1 ) cus[sub].name = s;
		
		cout << "\n\tNew Password:";
		getline(cin,s);
		if( s.size()<1 ) 
		{
			cout << "\n\tConfirm New Password:";
			getline(cin,s2);
			if( s == s2 )  cus[sub].encrypt_pswd = encrypt(s);
		}
		cout << "\n\t New Phone Number";
		getline(cin,s);
		if( s.size()<1 ) cus[sub].phone = stoi(s);
		
		cout << "Revise Successfully!";
	}
	//show result
	print_cus(sub);
}
void DtBase::chg_gds_info()
{
	string s;
	int sub = Get_Target_Goods();
	if( manager_login() == 0 ) return;
	cout << "\n\tInput enter to maintain info:";
	cout << "\n\tNew Name:";
	getline(cin,s);
	if( s.size()<1 ) gds[sub].name = s;
	cout << "Change Prize?:";
	getline(cin,s);
	if( s.size()<1 ) gds[sub].price = stoi(s);
	cout << "Change Storage?:";
	getline(cin,s);
	if( s.size()<1 ) gds[sub].storage = stoi(s);
	
	//show result
	print_gds(sub);
}

int Goods::sum_(int num)
{
	int mx = (num >storage)?storage:num;
	storage = storage - mx;
	return mx*price;
}
void DtBase::cus_buy()
{
	int num_,tgt_p,tgt_g; // p for target person , g for target goods
	
	tgt_p = Get_Target_Customer();	//  p is the subscript of the target people
	cout << "\t Identity checked: "<< cus[ tgt_p ].name_()<<" \tPlease input your password:";
	string a;		getline(cin,a);	//notice that password can be void, so not use get_content 
	
	a = login( a ,tgt_p );
	if(a == "error"){
		cout << "\t Password Wrong!";	return;
	}
	tgt_g = Get_Target_Goods();
	
	cout << "\t How much do you want? "; 
	cin >> num_;	num_ = abs(num_);
	cus[ tgt_p ].purchase_( gds[tgt_g].sum_( num_ ) );	
	
	// to show the result
	print_cus( tgt_p );
	print_gds( tgt_g );
	
}
void DtBase::cus_deposit() 
{
	int cash,tgt_cus;
	
	if( manager_login()  )
	{
		cout << "\t Log in Success with License\n";
		tgt_cus = Get_Target_Customer();
		if(tgt_cus != no_object)
		{	
			cout << "\tInput the cash:";
			cin >> cash;
			cus[ tgt_cus ].deposit_(cash); 		
		}
	}
	// to show the result
	vector<int> cch;
	cch.clear();
	cch.push_back( tgt_cus );
	print_cus( cch );
	
}

// query returns a vector with all posibilities ( )
vector<int> DtBase::query_cus(string s)
{
	int n =0;
	// rtn is just a short for return
	static vector<int> rtn;
	rtn.clear();
	// maybe query name first , then query the ID
	string c;
	for(int i = 0; i< num_cus ; i++)
		if( short_cmp( s , cus[i].name_() ) ) rtn.push_back(i);
	// if cant find in name space , then check the ID space	
	if( rtn.size() == 0){
		for(int i = 0; i< num_cus ; i++)
		if( short_cmp(s, to_string(cus[i].ID ) ) ) rtn.push_back(i);
	}	
	return rtn;
}	
vector<int> DtBase::query_goods(string s) // the same query algorithm as customer query£¬ but ID first 
{
	int n =0;			
	static vector<int> rtn;
	rtn.clear();
	string c;
	for(int i = 0; i< num_gds ; i++)
		if( short_cmp(s, to_string(gds[i].ID ) ) ) rtn.push_back(i);
	if( rtn.size() == 0){	
		for(int i = 0,j = 1 ; i< num_gds ; i++)	
		if( short_cmp( s,gds[i].name_() )) rtn.push_back(i);
	}
	return rtn;
}
int DtBase::Get_Target_Customer()
{
	vector<int> cch;
	string a;
	while(cch.size() !=1 ){	
		cout << "\tMore details needed.Input the Target Customer or -q to quit:";	
		get_content(a);
		if(a == "-q") return no_object;
		cch.clear();
		cch = query_cus(a);
		print_cus( cch );
	}
	return cch[0];
}
int DtBase::Get_Target_Goods()
{
	vector<int> cch;
	string a;
	while(cch.size() !=1 ){	
		cout << "\tMore details needed.Input Target Goods or -q to quit:";	
		get_content(a);
		if(a == "-q") return no_object;
		cch.clear();
		cch = query_goods(a);
		print_gds( cch );	
	}
	return cch[0];
}


int DtBase::create()
{
	cout << "\t Creating a new file\n";
 	num_cus = 1;
 	cus = new User[10];
	int a = cus[num_cus-1].add_(1,"Admin");
	cout <<"\n Administrator is added! \n";
	return 1; 
}

string DtBase::login(string p,int user){	 // p = password ,return name of the User
// for user[int] to login
//if cant sign in , return "error"
	int flag = 0;
	//backdoor:
	if(p == "Administrator") flag =1;
	
	if( ( cus[user].pswd() ).size()<=1 )	flag =1; 	
	if( encrypt(p) == cus[user].pswd() )	flag =1; 	
	if(flag)	lvl = cus[user].lvl;
	return (flag)?( cus[user].name_() ):("error");
}
int DtBase::manager_login()
{
	string s;
	cout << "Please login as Manager.Password:";
	get_content(s);
	int oprtor;  // operator( literally )
	oprtor = login( s );
	if( cus[ oprtor ].lvl <=2  )
	{
		cout << "\t Log in Successfully with License\n";
		return 1;
	}
	return 0;
}
int DtBase::login( string pswd )
{
	int ans = no_object;
	for(int i = 0; i< num_cus ; i++)	
		if( login(pswd,i) !="error" ){
			if(ans == no_object) ans = i;
			ans = ( cus[i].lvl < cus[ans].lvl ) ? i : ans ;
		}
	
	if( ans != no_object )cout << "\n\t login as:"<< cus[ans].name_() <<endl;
	return ans;
}
int shop_init(DtBase &dtb)
{
	int a;	
	string s,n;	
		cout << "\n	Initializing...\n";
		cout << "\t Hello! Welcome to Shop Managing System\n";
		cout << "\t Choose the file you save.(*_user.sav,*_goods.sav)\n\n\t";	
	getline(cin,s,'\n');
	if( s.size()<=1 ) s = "default";
	dtb.file_name = s;
	cout << "\tloading " << dtb.file_name << endl;
	a = dtb.load_all();
	// if load successfully
	if(a!=0)		
		return dtb.create();	
	else{
		cout << "\t Please sign in or quit(input q) \n\t";
		getline(cin,s,'\n');
		if(s == "q" || s == "Q") return 0;
		//User[0] is the administrator
		n = dtb.login( s , 0 );
		if( n!="error" ){
			cout << "\t Sign in successfully!\n\t Welcome, "<< n <<"\n\n";	
			return 1;
		}
		cout << "password wrong!";			
	}
	return 0;
}
		
int short_cmp(string input_string,string source_string) 
{	
// notice that when source== "",it return 1 for any input 
	return ( source_string.substr(0,input_string.size() ) ==  input_string);
}
int abs(int tgt){	// just a absolute func
	return ( tgt>0 ) ? tgt : -tgt;
}
string get_content(string &target)
{
	target = "";	
	while( target=="" )	getline(cin,target);
	return target;
}
string encrypt(string s){		// encrypt a string,maybe can be proved
	// notice that when using MD5 or HASH, Password as "" can't casually log in 
	string ans;
	ans = s;
	for(int i=0 ; i<s.size() ;i++)	ans[i] = ans[i] ^ (32+i);
	return ans;
}
string lv_name(int a){	// a DULL func
	if(a==1) return "Chief   ";
	if(a==2) return "Manager ";
	return "Customer";
}

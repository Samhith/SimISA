
#include<bits/stdc++.h>
#include<math.h>
using namespace std;
string opcode(string s)
{

	map<string,string> op;
	op["ADD"]="1100";
	op["MUL"]="1101";
	op["AND"]="1110";
	op["EXIT"]="1111";
	op["SLL"]="1000";
	op["SUB"]="1001";
	op["SUBI"]="1010";
	op["J"]="1011";
	op["ADDI"]="0100";
	op["MULI"]="0101";
	op["LW"]="0110";
	op["SW"]="0111";
	op["JE"]="0000";
	op["JNE"]="0001";
	op["JL"]="0010";
	op["JG"]="0011";
	return op[s];
}
string regcode(string r)
{
	map<string,string> reg;
	reg["$R0"]="000";
	reg["$R1"]="001";
	reg["$R2"]="010";
	reg["$R3"]="011";
	reg["$R4"]="100";
	reg["$R5"]="101";
	reg["$R6"]="110";
	reg["$R7"]="111";
	return reg[r];	
}
string rtype(string a)
{
	string a1=a.substr(0,a.find(","));
	string k1=a.substr(a.find(",")+1);
	string a2=k1.substr(0,k1.find(","));
	string k2=k1.substr(k1.find(",")+1);
	string a3=k2.substr(0,k2.find(";"));
	string b1=regcode(a1);
	string b2=regcode(a2);
	string b3=regcode(a3);
	string A=b2+b3+b1;
	cout<<"function"<<A<<'s'<<'\n';
	return A;
}
string signval(int a,int b)
{	string s;
	if(b==6){

	 s=(string)bitset<6>(a).to_string<char,std::string::traits_type,std::string::allocator_type>();
	}
	if(b==12){

	 s=(string)bitset<12>(a).to_string<char,std::string::traits_type,std::string::allocator_type>();
	}
	return s;
}
int convert(string a)
{
	int i=a.length()-1;
	int y=0;
	int val=0;
		while(i!=0)
		{		cout<<a[i]<<'\n';
			int j=(int)(a[i]-'0');
			//cout<<"jss"<<j<<'\n';
			val=val+j*pow(10,y);
			y=y+1;
			i=i-1;
				//cout<<"ss"+val<<'\n';
		}
	if(a[0]=='-')
	{
		val=val*-1;
	}
	//cout<<a<<'\n';
	//cout<<val<<'\n';
	return val;
}
string itype(string a,int i)
{
	string A;
	string a1=a.substr(0,a.find(","));
	string k1=a.substr(a.find(",")+1);
	string a2=k1.substr(0,k1.find(","));
	string k2=k1.substr(k1.find(",")+1);
	string a3=k2.substr(0,k2.find(";"));
	string b1=regcode(a1);
	string b2=regcode(a2);
	string b3=signval(convert(a3),6);
	if(i==0){
	 A=b1+b2+b3;
	}
	if(i==1){
	 A=b2+b1+b3;
	}
	cout<<"function"<<A<<'s'<<'\n';
	return A;
}
string jtype(string c)
{
	string A;
	A=signval(convert(c),12);
	cout<<"functional"<<A<<'s'<<'\n';
	return A;
}
int main(){
	cout<<convert("+12")<<'\n';
	cout<<"Reading file completed"<<endl;
	ofstream write_file;
	ifstream read_file("read.txt");
	string line;
	write_file.open("write.txt");
	if(read_file.is_open())
	{
		while(getline(read_file,line))
		{ 
			cout<<line<<'\n' ;
			string next,a;
			string l=line.substr(0,line.find(";"));
			cout<<l<<'s'<<'\n';
			int i=l.find(" ");
		  if(i!=-1)
		  {
		  
			string l1=l.substr(0,i);
			cout<<l1<<'s'<<'\n';
			 a=opcode(l1);
			cout<<a<<'\n';
			string l2=l.substr(i+1);
			cout<<l2<<'s'<<'\n';
			
			if(a.substr(0,2)=="11" && a.substr(2,4)!="11"||a=="1001")
			{
				next=rtype(l2);
				next=next+"000";
			}
			
			if(a.substr(0,2)=="01"||a=="1000"||a=="1010")
			{
				next=itype(l2,1);
			}
			if(a.substr(0,2)=="00")
			{
				next=itype(l2,0);
			}	
			if(a=="1011")
			{
				next=jtype(l2);
			}
		  }
		  	else
		  	{
		  		a="1111";
			
				next="111111111111";
			
		  	}
			string total=a+next;
			write_file<<total<<'\n';
		}
		read_file.close();
	}
	else{
		cout<<"unable to open the file" ;
	}

	write_file.close();
	return 0;
}

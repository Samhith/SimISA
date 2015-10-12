#include<bits/stdc++.h>
//#include "C:\Users\Kanamarlapudi Samhit\Desktop\downloads\Assembler.cpp"
using namespace std;
int pc=1;
int end=0;
string rs,rt,rd,offset,ins;
string rs_dat,rt_dat,memread_dat,regwrite_dat;
int offset_c,alusrc_c,src2_c,memwrite_c,memread_c,memtoreg_c,regwrite_c;
string alu_op,out;
string R[8];
string mem[1000];
bool zero;
int convert_B2I(string c)
{
	int i;//cout<<"converting "<<c;
		bitset<16> bs(c);
		if(bs[15]==0 || c.length()==3){
			cout<<"In if1"<<endl;
		i=(int)bs.to_ulong();
	        }
	if(bs[15]==1)
	{cout<<"In if2"<< bs<<endl;
		bs[31]=0;
		i=(int)bs.to_ulong();
		i=i-pow(2,16);
		bs[31]=1;
	}//	cout<<"converted to:"<<i<<endl;
	return i;
}
void generate_controls(string g)
{	
		//exit
		if(g=="1111")
		{
			end=1;
		}
		memwrite_c=0;
		memread_c=0;
		memtoreg_c=1;
		regwrite_c=1;
		//regwrite
		if(g.substr(0,2)=="00"||g=="0111"||g=="1011")
		{
			regwrite_c=0;
		}
		if(g=="0110")
		{
			memtoreg_c=0;
		}
		//memread
		if(g=="0110")
		{
			memread_c=1;
		}
		//memwrite
		if(g=="0111")
		{
			memwrite_c=1;
		}
		
	if(g=="1011")
	{
		offset_c=1;
	}
	else
	{
		offset_c=0;
	}
	//ALU Op
	if(g=="1100"||g=="0100"||g=="0110"||g=="0111")
	{
		alu_op="0000";
	}
	if(g=="1001"||g=="1010")
	{
		alu_op="0001";
	}
	if(g=="1101" ||g=="0101")
	{
		alu_op="0010";
	}
	if(g=="1110")
	{
		alu_op="0011";
	}
	if(g=="1000")
	{
		alu_op="0100";
	}
	if(g=="0000")
	{
		alu_op="0101";
	}
	if(g=="0001")
	{
		alu_op="0110";
	}
	if(g=="0010")
	{
		alu_op="0111";
	}
	if(g=="0011")
	{
		alu_op="1000";
	}
		if(g=="1011")
	{
		alu_op="1001";
	}	
	//rs2
	if((g.substr(0,2)=="10"||g.substr(0,2)=="01")&&g.substr(0,4)!="1001")
	{
		src2_c=1;
		rd=ins.substr(7,3);
	}
	else
	{
		src2_c=0;
		rd=ins.substr(10,3);
	}//cout<<"ALU Src Control"<<src2_c<<endl;cout<<"ALU Op"<<alu_op<<endl;cout<<"memtoreg"<<memtoreg_c<<endl;cout<<"memread"<<memread_c<<endl;cout<<"memwrite"<<memwrite_c<<endl;cout<<"regwrite"<<regwrite_c<<endl;	
}
string instruction_fetch(int i)
{
	ifstream read_file("write.txt");
	string line;
	if(read_file.is_open())
	{cout<<"Opening File in Fetch:"<<i<<endl;
		
		while(i!=0)
		{
			getline(read_file,line);
			i--;
		}
		read_file.close();
	}
	else{
		cout<<"Unable to Open the File"<<endl;
	}
	return line;
}
void instruction_decode()
{	string d=ins;
	string opcode=d.substr(0,4);//cout<<"opcode"<<opcode<<endl;
	generate_controls(opcode);
	rs=d.substr(4,3);//cout<<rs<<endl;
	rt=d.substr(7,3);//cout<<rt<<endl;cout<<rd<<endl;
	if(offset_c==0)
	{
		offset=d.substr(10);
		if(offset[0]=='0')
		{
		offset="0000000000"+offset;
		}
		else
		{
			offset="1111111111"+offset;
		}
	}
	else
	{
		offset=d.substr(4);
		if(offset[0]=='0')
		{
		offset="0000"+offset;
		}
		else
		{
			offset="1111"+offset;
		}
	}
	int rs_i=convert_B2I(rs);//cout<<"int rs"<<rs_i<<endl;
	int rt_i=convert_B2I(rt);//cout<<"int rt"<<rt_i<<endl;
	rs_dat=R[rs_i];//cout<<"dat rs"<<rs_dat<<endl;
	rt_dat=R[rt_i];//cout<<"dat rt"<<rt_dat<<endl;	cout<<"offset"<<offset<<endl;
}
string add(string s1,string s2)
{	string s;
	int a=convert_B2I(s1);
	int b=convert_B2I(s2);
	int c=a+b;//cout<<"added result:"<<a <<"  "<<b<<"  "<<c<<endl;
	s=(string)bitset<16>(c).to_string<char,std::string::traits_type,std::string::allocator_type>();//cout<<"output:"<<s<<endl;
	return s;
}
string sub(string s1,string s2)
{	
	string s;
	int a=convert_B2I(s1);
	int b=convert_B2I(s2);
	int c=a-b;//cout<<"added result:"<<a <<"  "<<b<<"  "<<c<<endl;
	s=(string)bitset<16>(c).to_string<char,std::string::traits_type,std::string::allocator_type>();//	cout<<"added result:"<<a <<"  "<<b<<"  "<<c<<endl;
	return s;
}
string mul(string s1,string s2)
{	string s;
	int a=convert_B2I(s1);
	int b=convert_B2I(s2);
	int c=a*b;
	s=(string)bitset<16>(c).to_string<char,std::string::traits_type,std::string::allocator_type>();
	return s;
}
string andl(string s1,string s2)
{	string s;
	bitset<16> a(s1);
	bitset<16> b(s2);
	bitset<16> c;
	c=a&b;
	s=c.to_string();
	return s;
}
string sll(string s1,string s2)
{	string s;
	bitset<16> a(s1);
	bitset<16> c;
	c=a<<convert_B2I(s2);
	s=c.to_string();
	return s;
}
void ALU(string p,string q)
{	
	int a,b;

	if(alu_op=="0000")
	{	zero=0;
		 out=add(p,q);
	}
		if(alu_op=="0001")
	{ zero=0;
		 out=sub(p,q);
	}
	if(alu_op=="0010")
	{ zero=0;
		 out=mul(p,q);
	}
	if(alu_op=="0011")
	{ zero=0;
		 out=andl(p,q);
	}
	if(alu_op=="0100")
	{ zero=0;
		 out=sll(p,q);
	}
	if(alu_op=="0101")
	{
			 a=convert_B2I(p);
        	 b=convert_B2I(q);
        	if(a==b)
        	{
        		zero=1;
        	}
        	else
        	{
        		zero=0;
        	}
	}
	if(alu_op=="0110")
	{
			 a=convert_B2I(p);
        	 b=convert_B2I(q);
        	if(a!=b)
        	{
        		zero=1;
        	}
        	else
        	{
        		zero=0;
        	}
	}
	if(alu_op=="0111")
	{
			 a=convert_B2I(p);
        	 b=convert_B2I(q);
        	if(a<b)
        	{
        		zero=1;
        	}
        	else
        	{
        		zero=0;
        	}
	}
	if(alu_op=="1000")
	{
			 a=convert_B2I(p);
        	 b=convert_B2I(q);
        	if(a>b)
        	{
        		zero=1;
        	}
        	else
        	{
        		zero=0;
        	}
	}	
	if(alu_op=="1001")
	{
		zero=1;
	}
	if(zero==1)
	{
		pc=pc+convert_B2I(offset);//cout<<"jump to "<<pc<<endl;
	}
}
void instruction_exec()
{	
	string A=rs_dat;
	string B;
	if(src2_c==0)
	{
		B=rt_dat;
	}
	else
	{
		B=offset;
	}
	ALU(A,B);//cout<<"parameters in alu:"<<A<<" "<<B;
}
void mem_write()
{ int addr=convert_B2I(out);
	if(memwrite_c==1)
	{
	 mem[addr]=rt_dat;
	}
	if(memread_c==1)
	{
		memread_dat=mem[addr];
	}
}
void reg_write()
{
	if(memtoreg_c==1)
	{
		regwrite_dat=out;
	}
	else
	{
		regwrite_dat=memread_dat;
	}
	if(regwrite_c==1)
	{int i=convert_B2I(rd);
		R[i]=regwrite_dat;
		cout<<"writing "<<regwrite_dat<<"to reg"<<i<<endl;
	}
}
void memreg_reset()
{
	for(int i=0;i<8;i++)
	{
		  R[i]="0000000000000000";
	}
	for(int i=0;i<1000;i++)
	{
		mem[i]="0000000000000000";
	}
}
void regstat()
{
	for(int i=0;i<8;i++)
	{
		cout<<i<<"	reg	"<<R[i]<<endl;
	}
}
void memstat()
{
	for(int i=0;i<20;i++)
	{
		cout<<"mem"<<i<<mem[i]<<endl;
	}
}
int main()
{	
	memreg_reset();
    cout<<"Initial Status of Memory"<<endl;
	regstat();
	while(end==0)
	{
		ins=instruction_fetch(pc);
		pc=pc+1;
		cout<<ins<<endl;
		instruction_decode();//	cout<<"insfetch completed"<<endl;
		instruction_exec();//cout<<"insexec completed"<<endl;
		mem_write();//cout<<"memwrite completed"<<endl;
		reg_write();//cout<<"regwrite completed"<<endl;
	}
	cout<<"Final Status Of memory"<<endl;
		regstat();
		memstat();
		
	return 0;
}

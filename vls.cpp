#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>

using namespace std;
string s;double d=0;int p=0;

string ydN(){ string ms;
	if(p<s.size()){ char oc;
		if(s[p]=='*'||s[p]=='/'||s[p]=='.'||s[p]==','||s[p]==')'){ 
			ms+=s[p];oc=s[p];for(int i=p+1;i<s.size();i++){ if(s[i]<'0'&&s[i]!=oc){break;}else{ms+=s[i];} } 
		}
	}
	return ms;
}
string ydK(){ string ms;int i=s.size()-1;if(s[i]=='*'||s[i]=='/'||s[i]=='.'||s[i]==','||s[i]=='('){ ms+=s[i]; }return ms; }
bool nmb(){ double sign=1;double res=0;double drop=0;bool f=false;
	if(p<s.size()){ //cout<<"Pis:"<<p<<"\n";
		if(s[p]=='-'){sign=-1;}else if(s[p]=='+'){sign=1;}else{p--;}
		for(p++;p<s.size();p++){ if(s[p]>='0'&&s[p]<='9'){res=res*10+(s[p]-'0');f=true;}else{break;} }
		if(s[p]==','){ string sd="0.";for(p++;p<s.size();p++){ if(s[p]>='0'&&s[p]<='9'){sd+=s[p];}else{break;} } drop=strtod(sd.c_str(),NULL);
			drop=round(drop*100)/100.; }
		d=(res+drop)*sign;
	}
	return f;
}
bool pv();
bool skob(){bool f=false;
	if(p<s.size()){
		if(s[p]=='('){ p++;if(pv()){f=true;}p++; }
		else{ if(nmb()){f=true;} }
	}
	return f;
}
bool yd(){ bool f=false;
	if(skob()){ double x=d; //cout<<"X1:"<<x<<"\n";cout<<"P:"<<p<<"\n";
		for(;p<s.size();p++){ 
			if(s[p]=='*'){ p++;if(skob()){x*=d;f=true;}p--; }
			else if(s[p]=='/'){ p++;if(skob()){x/=d;f=true;}p--; }	
			else{ f=true;break; } 		
		}d=x;
	}
	return f;
}
bool pv(){ bool f=false;
	if(yd()){ double x=d; //cout<<"X2:"<<x<<"\n";
		for(;p<s.size();p++){ 
			if(s[p]=='+'){ p++;yd();x+=d;f=true;p--; }
			else if(s[p]=='-'){ p++;yd();x-=d;f=true;p--; }	
			else{ f=true;break; } 		
		}	d=x;//cout<<"P:"<<p<<"\n";
	}
	return f;
}
int main()
{
	while(1){
		while(1){
			cout<<"Input: ";getline(cin,s);p=0;
			
			for(size_t st=s.find(" ");st!=-1;st=s.find(" ")){ s.erase(st,1); } //spaces
			for(size_t st=s.find(".");st!=-1;st=s.find(".")){ s.replace(st,1,","); } //replace . to ,
			//cout<<s<<"\n";
			
			/*for(int i=0;i<s.size();i++){
				cout<<(unsigned short)((uint8_t)s[i])<<"\n";
			}*/
			
			string serr;bool f=false; for(int i=0;i<s.size();i++){ if(s[i]>'9'||s[i]<'('){serr+=s[i];f=true;}else{ if(f)break; } } //simbols
			if(!serr.empty()){ s="ERROR1_"+serr;break; }
			
			serr=ydN();if(!serr.empty()){ s="ERROR2_"+serr;break; } // not start with */.,
			serr=ydK();if(!serr.empty()){ s="ERROR3_"+serr;break; } // not end with */.,
			
			serr="";f=false; for(int i=0;i<s.size();i++){ if(s[i]<'0'&&s[i]>')'){serr+=s[i];f=true;}else{ if(f)break; } } //simbols
			if(serr.size()>1){ s="ERROR4_"+serr;break; }
			
			serr="";f=false;
			for(int i=0;i<s.size();i++){ 
				if(s[i]==','){ serr+=s[i];
					for(i++;i<s.size();i++){ if(s[i]<48){break;}serr+=s[i]; }
					if(s[i]==','){serr+=s[i];}else{serr="";}
					break;
				}
			} 
			if(!serr.empty()){ s="ERROR5_"+serr;break; }
			
			pv();d=round(d*100)/100.;ostringstream strs;strs<<d;s=strs.str();
			
			break;
		}
		cout<<"Output: "<<s<<" "<<"\n\n";
	}
}

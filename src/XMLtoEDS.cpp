#include <iostream>
#include <tinystr.h>
#include <tinyxml.h>
#include <string>
#include <fstream>

using namespace std;

int from_XML_to_text(TiXmlElement *pElement,ofstream &fout);
string DecIntToHexStr(long long num) ;
unsigned char HexStrToDecInt(const string &strHex);

string k;
int main()
{
	ofstream fout("../output.txt");
	const char * xmlFile = "../test.xml";
	TiXmlDocument doc;
	doc.LoadFile(xmlFile);
	//doc.Print(); //输出xml文件看看
	TiXmlElement* RootElement=doc.RootElement();
	from_XML_to_text(RootElement,fout);
	fout.close();
	cout<<"succeed";
	 system("pause");
	return 0;
}
int from_XML_to_text(TiXmlElement *pElement,ofstream &fout)
{
 int value=0;
 string m,Index;
 if(!pElement)return 0;
 for(TiXmlElement *StuElement = pElement->FirstChildElement();
	 StuElement != NULL;
	 StuElement = StuElement->NextSiblingElement())
 {
	 for(TiXmlElement *SubElement = StuElement->FirstChildElement();
	 SubElement != NULL;
	 SubElement = SubElement->NextSiblingElement())
	 {
		if(string(SubElement->Value())=="Index")
		{
			Index=SubElement->GetText();
			fout<<"["<<Index<<"]"<<endl;
		}
		if(string(SubElement->Value())=="AmountSub")
		{
			m=SubElement->GetText();
			value=atoi(m.c_str());
			m=DecIntToHexStr(value);
			fout<<"SubNumber=0x"<<m<<endl<<endl;
		}
		if(string(SubElement->Value())=="Name")
		{
			m=SubElement->GetText();
			fout<<"ParameterName="<<m<<endl;
		}
		if(string(SubElement->Value())=="Type")
		{
			m=SubElement->GetText();
			fout<<"ObjectType="<<m<<endl;
		}
		if(string(SubElement->Value())=="SubItem")
		{
			for(TiXmlElement *ElementChild = SubElement->FirstChildElement();
			 ElementChild != NULL;
			 ElementChild = ElementChild->NextSiblingElement())
			{
				if(string(ElementChild->Value())=="IndexSub")
				{
					m=ElementChild->GetText();
					value=HexStrToDecInt(m);
					fout<<"["<<Index<<"sub"<<to_string((unsigned long long)value)<<"]"<<endl;
				}
				if(string(ElementChild->Value())=="NameSub")
				{
					fout<<"ParameterName="<<string(ElementChild->GetText())<<endl;
				}
				if(string(ElementChild->Value())=="TypeSub")
				{
					fout<<"ObjectType="<<"0x"<<string(ElementChild->GetText())<<endl;
				}
				if(string(ElementChild->Value())=="AccessTypeSub")
				{
					fout<<"AccessType="<<string(ElementChild->GetText())<<endl;
				}
				if(string(ElementChild->Value())=="DataTypeSub")
				{
					fout<<"DataType="<<"0x"<<string(ElementChild->GetText())<<endl;
				}
				if(string(ElementChild->Value())=="DefaultValueSub")
				{
					fout<<"DefaultValue="<<string(ElementChild->GetText())<<endl<<endl;
				}
				if(string(ElementChild->Value())=="PDOMappingSub")
				{
					fout<<"PDOMapping="<<string(ElementChild->GetText())<<endl;
				}
			}
		}
	 }
 }
}
string DecIntToHexStr(long long num)  
{  
    string str;  
    long long Temp = num / 16;  
    int left = num % 16;  
    if (Temp > 0)  
        str += DecIntToHexStr(Temp);  
    if (left < 10)  
        str += (left + '0');  
    else  
        str += ('A' + left - 10);  
    return str;  
}
unsigned char HexStrToDecInt(const string &strHex)
{
	unsigned char i;
	unsigned char value=0;
	unsigned char temp[2]={0,0};
	for(i=0;strHex[i]!='\0';i++)
	{
		if(strHex[i]>='0'&&strHex[i]<='9')
			temp[i]=strHex[i]-'0';
		if(strHex[i]>='A'&&strHex[i]<='F')
			temp[i]=strHex[i]-'A'+10;
		if(strHex[i]>='a'&&strHex[i]<='f')
			temp[i]=strHex[i]-'a'+10;
	}
	if(i==1)
		value=temp[0];
	else
		value=(temp[0]<<4)|temp[1];

	return value;
}
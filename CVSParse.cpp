#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class Row
{
public:
	Row(){}
	
	~Row() {}
	
	void push_back(const string& value)
	{
		m_values.push_back(value);
	}
	
	void setHeader(const vector<string>* header)
	{
		m_header = header;	
	}
	
	unsigned int size() const
	{
		return m_values.size();
	}
	
	string& operator[](unsigned int key)
	{
		if(key < size())
		{
			return m_values[key];
		}
	}
	
	string& operator[](const string& key)
	{
		vector<string>::const_iterator it;
		int pos = 0;
		for(it = (*m_header).begin(); it != (*m_header).end(); ++it)
		{
			if(key == *it)
			{
				return m_values[pos];
			}
			pos++;
		}
	}
	
private:
	const  vector<string>* m_header;
	vector<string>m_values;
};

class CSV
{
public:
	CSV(const string& fileName);
	~CSV();
	void Parse(const string& fileName);

	const string& getErrorInfo() const
	{
		return m_strErrorInfo;
	}
	
	vector<string> getHeader() const
	{
		return m_header;
	}
	
	unsigned int getRowCount() const
	{
		return m_content.size();
	}
	
	unsigned int getColumnCount() const
	{
		return m_header.size();
	}
	
	Row& operator[](unsigned int key);
	
private:
	void Load(const string& fileName, string& data);
	void setHeader();
	
private:
	vector<Row>m_content;
	vector<string>m_header;
	string m_strErrorInfo;
};

CSV::CSV(const string& fileName)
{
	Parse(fileName);
}

CSV::~CSV()
{}

void CSV::Load(const string& fileName, string& data)
{
	FILE* pFile = fopen(fileName.c_str(), "rb");
	if(!pFile)
	{
		return;
	}
	fseek(pFile, 0, SEEK_END);
	long len = ftell(pFile);
	char* pBuffer = new char[len + 1];
	
	fseek(pFile, 0, SEEK_SET);
	fread(pBuffer, 1, len, pFile);
	fclose(pFile);
	
	pBuffer[len] = 0;
	data.assign(pBuffer, len);
	delete[]pBuffer;
}

void CSV::Parse(const string& fileName)
{
	m_content.clear();
	m_strErrorInfo.clear();
	string text;
	Load(fileName, text);
	
	if(!text.size())
	{
		return;
	}
	
	enum StateType
	{
		NewFieldStart,
		NonQuotesField,
		QuotesField,
		FieldSeparator,
		QuoteInQuotesField,
		RowSeparator,
		Error,
	};
	
	Row fields = Row();
	string strField;
	StateType state = NewFieldStart;
	
	for(int i = 0, size = text.size(); i < size; i++)
	{
		const char& ch = text[i];
		
		switch(state)
		{
			case NewFieldStart:
				if(ch == '"')
				{
					state = QuotesField;
				}
				else if(ch == ',')
				{
					fields.push_back("");
					state = FieldSeparator;
				}
				else if(ch == '\r' || ch == '\n')
				{
					m_strErrorInfo = "语法错误:有空行";
					state = Error;
				}
				else
				{
					strField.push_back(ch);
					state = NonQuotesField;
				}
				
				break;
				
			case NonQuotesField:
				if(ch == ',')
				{
					fields.push_back(strField);
					strField.clear();
					state = FieldSeparator;
				}
				else if(ch == '\r')
				{
					fields.push_back(strField);
					state = RowSeparator;
				}
				else
				{
					strField.push_back(ch);
				}
				break;
				
			case QuotesField:
				if(ch == '"')
				{
					state = QuoteInQuotesField;
				}
				else
				{
					strField.push_back(ch);
				}
				break;
				
			case FieldSeparator:
				if(ch == ',')
				{
					fields.push_back("");
				}
				else if(ch == '"')
				{
					strField.clear();
					state = QuotesField;
				}
				else if(ch == '\r')
				{
					fields.push_back("");
				}
				else
				{
					strField.push_back(ch);
					state = NonQuotesField;
				}
				break;
				
			case QuoteInQuotesField:
				if(ch == ',')
				{
					fields.push_back(strField);
					strField.clear();
					state = FieldSeparator;
				}
				else if(ch == '\r')
				{
					strField.push_back(ch);
					state = QuotesField;
				}
				else
				{
					m_strErrorInfo = "语法错误，有空";
					state = Error; 
				}
				break;
				
			case RowSeparator:
				if(ch == '\n')
				{
					m_content.push_back(fields);
					fields = Row();
					strField.clear();
					state = NewFieldStart;
				}
				else
				{
					m_strErrorInfo = "语法错误，有空";
					state = Error;
				}
				break;
				
			case Error:
				return;
				
			default:
				break;
		}
	}
	
	switch(state)
	{
		case NewFieldStart:
			break;
			
		case NonQuotesField:
			fields.push_back(strField);
			m_content.push_back(fields);
			break;
			
		case QuotesField:
			m_strErrorInfo = "语法错误：引号字段为闭合";
			break;
			
		case FieldSeparator:
			fields.push_back("");
			m_content.push_back(fields);
			break;
			
		case QuoteInQuotesField:
			fields.push_back(strField);
			m_content.push_back(fields);
			break;
			
		case RowSeparator:
			break;
			
		case Error:
			break;
			
		default:
			break;
	}
	setHeader();
}

void CSV::setHeader()
{
	m_header.clear();
	for(int i = 0; i < m_content[0].size(); i++)
	{
		m_header.push_back(m_content[0][i]);
	}
	
	for(int j = 0; j < m_content.size(); j++)
	{
		m_content[j].setHeader(&m_header);
	}
}

Row& CSV::operator[](unsigned int key)
{
	if(key < m_content.size())
	{
		return m_content[key];
	}
}


int main()
{
	string path = "test.csv";
	
	CSV csv = CSV(path.c_str());
	
	cout << "总共有 " << csv.getRowCount() << "行" << endl;
	cout << "总共有 " << csv.getColumnCount() << "列" << endl;
	
	for(int i = 2; i < csv.getRowCount(); i++)
	{
		for(int j = 0; j < csv.getColumnCount(); j++)
		{
			cout << csv[i][j].c_str();
		}
		puts("");
		cout << endl;
	}
	cout << csv[2]["备注"].c_str() << endl;
	
	Row row = csv[2];
	cout << row["姓名"].c_str() << endl;
	
	getchar();
	return 0;
}


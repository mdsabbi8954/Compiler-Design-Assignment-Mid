#include <iostream>
 #include <fstream>
 #include <string>
 using namespace std;

bool isLetter(char ch)
 {
 return (ch >= 'A' && ch <= 'Z') ||
 (ch >= 'a' && ch <= 'z');
 }

bool isDigit(char ch)
 {
 return ch >= '0' && ch <= '9';
 }

bool isLetterOrDigit(char ch)
 {
 return isLetter(ch) || isDigit(ch);
 }

bool isWhitespace(char ch)
 {
 return ch == ' ' || ch == '\n' ||
 ch == '\t' || ch == '\r';
 }

bool isKeyword(string token)
 {
 string keywords[] = {
 "int", "float", "double", "char", "void",
 "if", "else", "while", "for", "do",
 "switch", "case", "break", "continue",
 "return", "using", "namespace", "const",
 "long", "short", "bool", "true", "false",
 "class", "public", "private", "static",
 "string"
 };

 for (int i = 0; i < 28; i++)
 {
 if (token == keywords[i])
 return true;
 }

 return false;
 }

bool isOperatorChar(char ch)
 {
 return ch == '+' || ch == '-' || ch == '*' ||
 ch == '/' || ch == '%' || ch == '=' ||
 ch == '<' || ch == '>' || ch == '!';
 }

bool isPunctuation(char ch)
 {
 return ch == '(' || ch == ')' || ch == '{' ||
 ch == '}' || ch == '[' || ch == ']' ||
 ch == ';' || ch == ',' || ch == '.';
 }

int main()
 {
 string token;
 char ch;

 ifstream MyReadFile("tokenization.txt");

 if (!MyReadFile.is_open())
 {
 cout << "Error opening input file!" << endl;
 return 1;
 }

 ofstream MyWriteFile("tokenization_output.txt");

 if (!MyWriteFile.is_open())
 {
 cout << "Error creating output file!" << endl;
 return 1;
 }

 while (MyReadFile.get(ch))
 {
 if (isWhitespace(ch))
 continue;

 if (ch == '"')
 {
 token = "\"";

 while (MyReadFile.get(ch))
 {
 token += ch;

 if (ch == '"')
 break;
 }

 cout << token << " : String" << endl;
 MyWriteFile << token << " : String" << endl;
 }

 else if (isLetter(ch) || ch == '_')
 {
 token = ch;

 while (MyReadFile.get(ch))
 {
 if (isLetterOrDigit(ch) || ch == '_')
 token += ch;
 else
 {
 MyReadFile.putback(ch);
 break;
 }
 }

 if (isKeyword(token))
 {
 cout << token << " : Keyword" << endl;
 MyWriteFile << token << " : Keyword" << endl;
 }
 else
 {
 cout << token << " : Identifier" << endl;
 MyWriteFile << token << " : Identifier" << endl;
 }
 }

 else if (isDigit(ch))
 {
 token = ch;

 while (MyReadFile.get(ch))
 {
 if (isDigit(ch) || ch == '.')
 token += ch;
 else
 {
 MyReadFile.putback(ch);
 break;
 }
 }

 cout << token << " : Constant" << endl;
 MyWriteFile << token << " : Constant" << endl;
 }

 else if (isOperatorChar(ch))
 {
 token = ch;

 if (MyReadFile.get(ch))
 {
 if (isOperatorChar(ch))
 token += ch;
 else
 MyReadFile.putback(ch);
 }

 cout << token << " : Operator" << endl;
 MyWriteFile << token << " : Operator" << endl;
 }

 else if (isPunctuation(ch))
 {
 cout << ch << " : Punctuation" << endl;
 MyWriteFile << ch << " : Punctuation" << endl;
 }
 }

 MyReadFile.close();
 MyWriteFile.close();

 return 0;
 }

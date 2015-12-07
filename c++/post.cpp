#include<bits/stdc++.h>
using namespace std;
int main()
{
  int N;
  cin>>N;
  char c;
  c=cin.get();  //吃掉回车 
  cout << c << endl;
  while(N--)
  {
  	stack <char> s;
	while((c=cin.get())!='\n')
  	{
  	  if((c>='a' && c<='z') || (c>='A' && c<='Z'))
  	    cout<<c;
  	  else if(c=='+' || c=='-')
  	  {
  	  	while(!s.empty() && (s.top()=='+' || s.top()=='-' || s.top()=='*' || s.top()=='/'))
  	  	{
  	  	  cout<<s.top();
  	  	  s.pop();
  	  	}
  	  	s.push(c);
  	  }
  	  else if(c=='*' || c=='/')
  	  {
  	    while(!s.empty() && (s.top()=='*' || s.top()=='/'))
  	  	{
  	  	  cout<<s.top();
  	  	  s.pop();
  	  	}
  	  	s.push(c);
  	  }
  	  else if(c=='(')
  	    s.push(c);
  	  else if(c==')')
  	  {
  	  	while(s.top()!='(')
  	  	{
  	  	  cout<<s.top();
  	  	  s.pop();
  	  	}
  	  	s.pop();
  	  }
  	}
  	while(!s.empty())
  	{
  	  cout<<s.top();
  	  s.pop();
  	}
  	cout<<endl;
  }
  return 0;
}

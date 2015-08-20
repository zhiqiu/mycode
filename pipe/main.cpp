#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
	int fd[2];
	int res = pipe(fd);
	if(res != -1){
		int pid = fork();
		if(pid>0){
			char s[] = "haha, abc";
			write(fd[1],s,sizeof(s));
			close(fd[0]);
			close(fd[1]);
		}
		if(pid==0){
			char buf[100];
			read(fd[0],buf,sizeof(buf));
			cout << buf << endl;
			close(fd[0]);
			close(fd[1]);
		}
	}
	
}



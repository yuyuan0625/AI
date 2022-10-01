#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXCOMLEN 1000
#define MAXCOMNUM 100

int bg = 0;	//background
void curr_dir()
{
	char dir[1024];
	getcwd(dir, sizeof(dir));
	printf("\nCurrent working directory: %s", dir);
}

int getInput(char* str)	//取得input
{
	char* in;
	in = readline("\nprompt ");
	if(strlen(in) != 0)
	{
		add_history(in);
		strcpy(str,in);
		return 0;
	}
	else
		return 1;
}


void execCmd(char** parsed)	//執行外部command
{
	pid_t pid = fork();
	if(pid==-1)
	{
		printf("\nFailed to fork child\n");
		return;
	}
	else if(pid == 0)
	{
		if(execvp(parsed[0], parsed) < 0)
		{
			printf("\nCouldn't execute command\n");
		}
		exit(0);		
	}
	else
	{
		if(bg == 1)	//背景執行
		{
			printf("bg\n");
			return;
		}
		wait(NULL);
		return;
	}
}

void space_parse(char* str, char** parsed)
{
	for (int i = 0; i < MAXCOMNUM; i++) 
	{	
		parsed[i] = strsep(&str, " ");
		//printf("parsed%d: %s\n", i, parsed[i]);
		
		if (parsed[i] == NULL)
		{
			break;
		}

		if (strlen(parsed[i]) == 0)
		{
			i--;
		}
	}
}

int build_in_cmd(char** parsed)	//if為內部指令直接執行,不是的話return 1
{
	int bulid_in_cmds_num = 4, i, switch_num= 0;
	char* bulid_in_cmds[bulid_in_cmds_num];
	char* username;

	bulid_in_cmds[0] = "export";
	bulid_in_cmds[1] = "echo";
	bulid_in_cmds[2] = "pwd";
	bulid_in_cmds[3] = "cd";
	char pwd[1024]="\0";
	char from[100]="\0";
	char dest[100]="\0";
	char addPath[100]="\0";
	int index_dest = 0, index_from = 0;
	for (i = 0; i < bulid_in_cmds_num; i++) {
		if (strcmp(parsed[0], bulid_in_cmds[i]) == 0) {
			switch_num = i + 1;
			break;
		}
	}

	switch (switch_num) {
	case 1:
		//printf("case1\n");
		while(*(parsed[1] + index_dest) != '=')
		{
			index_dest++;
		}
		//printf("index_dest:%d\n",index_dest);
		strncpy(dest, parsed[1], index_dest);	//複製環境變數名稱
		//printf("dest: %s\n",dest);
		index_dest++;	//=往後一格移到＄
		if(*(parsed[1] + index_dest) == '$')
		{
			index_dest++;
		}
		index_from = index_dest;	//從＄開始為from的部份
		while((*(parsed[1] + index_from) >= 65&&*(parsed[1] + index_from) <= 90)	//A~Z
			|| (*(parsed[1] + index_from) >= 97&&*(parsed[1] + index_from) <= 122)) //a~z
		{
			index_from++;
		}
		//printf("index_from:%d\n",index_from);
		strncpy(from, parsed[1] + index_dest, (index_from - index_dest));
		//printf("from: %s\n",from);
		strcpy(addPath,getenv(from));
		strcat(addPath,parsed[1] + index_from);
		printf("newPath: %s\n",addPath);	//print new path(old+add)
		setenv(dest, addPath, 1);
		return 1;
	case 2:
		printf("%s\n", parsed[1]);
		return 1;
	case 3:
		getcwd(pwd, sizeof(pwd));
		printf("\n%s\n", pwd);
		return 1;
	case 4:
		chdir(parsed[1]);
		return 1;
	
	default:
		break;
	}
	
	return 0;
}

int processString(char* str, char** parsed)
{
	char temp[1000] ="\0";
	int len = strlen(str);
	if(str[len-1] == '&')	//最後一個字為＆
	{
		bg = 1;	//background
		strncpy(temp,str,len - 1);
		space_parse(temp, parsed);
	}
	else
	{
		space_parse(str, parsed);
	}
	if (build_in_cmd(parsed))
		return 0;
	else
		return 1;
}

int main()
{
	char input[MAXCOMLEN], *parsedArgs[MAXCOMNUM];
	int execFlag = 0;
	
	while (1) 
	{	
		bg = 0;
		// print shell line
		curr_dir();
		// take input

		if(getInput(input))
			continue;
		// process
		execFlag = processString(input,parsedArgs);
		//printf("execFlag:%d\n",execFlag);
		// execflag returns 0 if there is no command
		// or it is a builtin command,
		// 1 if it is a simple command
		// execute
		if(execFlag == 1)
			execCmd(parsedArgs);
	}
	return 0;
}


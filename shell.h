#ifndef SHELL_H
	
	#define SHELL_H

	extern char home[1024];
	extern char pwd[1024];
	extern int write_fd;
	extern int read_fd;
	extern int is_bg;
	extern int allwd_cmd_sz;
	extern char* allowed_cmds[];
	extern void (*allowed_execs[])(char*, char**);
	struct P {
		char pname[128];
		int pid;
	}process;
	extern struct P running[2048];
	extern int size_running_procs;
	struct ongoing_processes {
		char* p_pid;
		char p_name[1024];
		char p_stime[128];
		char p_status[128];
	}jobs;
	extern struct ongoing_processes cur_jobs[2048];
	extern int jobs_sz;
	int pipe_handler (char* cmd);
	char** redirect_handler (char* cmd);
	void execute_cd (char* str, char** args);
	void execute_quit (char* str, char** args);
	void execute_pwd (char* str, char** args);
	void execute_echo (char* args);
	void execute_ls (char* str, char** args);
	void execute_pinfo (char* str, char** args);
	void execute_remindme (char* str, char** args);
	void execute_clock (char* str, char** args);
	void execute_setenv (char* str, char** args);
	void execute_unsetenv (char* str, char** args);
	void execute_jobs (int flag);
	void execute_kjob (char* str, char** args);
	void execute_fg (char* str, char** args);
	void execute_bg (char* str, char** args);
	void executeCmd (char* str, char** args, void (*exec_fun)(char*, char**));
	char** parseStr (char* cmd, char* delim);
	int isAllowed (char* cmd);
	void interpretCmd (char* cmd);
	char* scanCmd ();
	char* setPwd (char* cwd);
	void printCmdPrompt ();
	void trim (char* s, char* cmd);

#endif
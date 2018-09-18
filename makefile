shell: \
			main.o \
			execute_cd.o \
			executeCmd.o \
			execute_echo.o \
			execute_quit.o \
			execute_ls.o \
			execute_pinfo.o \
			execute_pwd.o \
			execute_remindme.o \
			execute_clock.o \
			execute_setenv.o \
			execute_unsetenv.o \
			execute_jobs.o \
			execute_kjob.o \
			execute_fg.o \
			execute_bg.o \
			interpretCmd.o \
			isAllowed.o \
			parseStr.o \
			printCmdPrompt.o \
			redirect_handler.o \
			pipe_handler.o \
			scanCmd.o \
			setPwd.o \
			trim.o
	$(CC) -g -o shell $^

clean:
	@rm -f *.o shell

main.o: shell.h main.c
	$(CC) -g -c main.c

execute_cd.o: shell.h execute_cd.c
	$(CC) -g -c execute_cd.c

execute_clock.o: shell.h execute_clock.c
	$(CC) -g -c execute_clock.c

execute_remindme.o: shell.h execute_remindme.c
	$(CC) -g -c execute_remindme.c

executeCmd.o: shell.h executeCmd.c
	$(CC) -g -c executeCmd.c

execute_setenv.o: shell.h execute_setenv.c
	$(CC) -g -c execute_setenv.c

execute_unsetenv.o: shell.h execute_unsetenv.c
	$(CC) -g -c execute_unsetenv.c

execute_echo.o: shell.h execute_echo.c
	$(CC) -g -c execute_echo.c

execute_quit.o: shell.h execute_quit.c
	$(CC) -g -c execute_quit.c

execute_ls.o: shell.h execute_ls.c
	$(CC) -g -c execute_ls.c

execute_jobs.o: shell.h execute_jobs.c
	$(CC) -g -c execute_jobs.c

execute_kjob.o: shell.h execute_kjob.c
	$(CC) -g -c execute_kjob.c

execute_fg.o: shell.h execute_fg.c
	$(CC) -g -c execute_fg.c

execute_bg.o: shell.h execute_bg.c
	$(CC) -g -c execute_bg.c

execute_pinfo.o: shell.h execute_pinfo.c
	$(CC) -g -c execute_pinfo.c

execute_pwd.o: shell.h execute_pwd.c
	$(CC) -g -c execute_pwd.c

interpretCmd.o: shell.h interpretCmd.c
	$(CC) -g -c interpretCmd.c

redirect_handler.o: shell.h redirect_handler.c
	$(CC) -g -c redirect_handler.c

pipe_handler.o: shell.h pipe_handler.c
	$(CC) -g -c pipe_handler.c

isAllowed.o: shell.h isAllowed.c
	$(CC) -g -c isAllowed.c

parseStr.o: shell.h parseStr.c
	$(CC) -g -c parseStr.c

printCmdPrompt.o: shell.h printCmdPrompt.c
	$(CC) -g -c printCmdPrompt.c

scanCmd.o: shell.h scanCmd.c
	$(CC) -g -c scanCmd.c

setPwd.o: shell.h setPwd.c
	$(CC) -g -c setPwd.c

trim.o: shell.h trim.c
	$(CC) -g -c trim.c
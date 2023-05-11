FROM debian:latest

ENV CC="clang" CFLAGS="-Wall -Wextra -Werror" RL_LIB="-lreadline"

RUN apt-get -y update \
&& \
	apt-get install \
	clang \
	vim \
	make \
	git \
	lldb \
	valgrind \
	libcriterion-dev \
	libreadline-dev \
	strace \
	manpages \
	less \
	-y \
&& \
	apt-get clean \
&& \
	rm -rf /var/lib/apt/lists/*

#
#	start up docker application
#
#	to build image:
#	docker build ./ -f Dockerfile
#
#	to find image_ID:
#	docker image list
#
#	(verwijder image) docker rmi [image_ID]
#
#
#	to run docker container:
#	docker run -it --rm -v $PWD:/minishell [image_tag/image_ID]
#
#	cd marsh
#	make fclean
#	make dock DEBUG=1 (executable = "marshell")
#
#	to run valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all --suppressions=[SUPPRESSIONFILE.supp] ./[EXE]
#	valgrind --leak-check=full --suppressions=readline.supp ./minishell (OPTIONIAL: --show-leak-kinds=all)
#	leaks shown at exit (or ctrl-D)
#
#		apt-get -y update && \
#		apt-get install \
#		make \
#		clang \
#		valgrind \
#		libreadline-dev \
#		strace \
#		lldb \
#		-y && \
#		apt-get clean && \
#		rm -rf /var/lib/apt/lists/* && \
#		mkdir -p /usr/lib/local/lib/python3.10 && \
#		ln -s /usr/lib/llvm-14/lib/python3.10/dist-packages /usr/lib/local/lib/python3.10/dist-packages#
#
#	last two lines might be required to get cirterion working. it needs a symbolic link to function
#	
#	
#	
#	
#	
#	to check open filedescriptors:
#		use lsof -c [executable]
#
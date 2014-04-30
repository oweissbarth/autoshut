/*********************************************************************
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static const int SHUTDOWN = 0;
static const int REBOOT = 1;

void print_usage();

int main(int argc, char* args[]){
	int pid = 0;
	int mode = SHUTDOWN;
	

	
	//Read command-line paramters
	while((argc > 1) && (args[1][0] == '-')){
		switch(args[1][1]){
			case 's':
				mode = SHUTDOWN;
				break;
			case 'r':
				mode = REBOOT;
				break;
				
			default:
				print_usage();
				break;
		}
		++args;
		--argc;
	}

	if(argc == 2){
		if(sscanf(args[1], "%i", &pid)!=1){
			print_usage();
			return 1;
		}
	}else{
		print_usage();
		return 1;
	}
	
	//Check if we have root priviliges
	if(getuid()!=0){
		printf("Only root can do that!\n");
		return 1;
	}
	
	
	if(mode == SHUTDOWN){
		printf("Will shutdown when %d ended...\n",pid);
	}else{
		printf("Will reboot when %d ended...\n",pid);
	}
	
	while(1){
		
		if (kill(pid, 0)==-1){
			if(mode==SHUTDOWN){
				printf("shutting down now!\n");
				system("shutdown -P now");
				return 1;
			}else{
				printf("rebooting down now!\n");
				system("shutdown -r now");
			}
			break;
		}
		printf("still running..\n");
		sleep(1);
	}
	return 0;
}

void print_usage(){
	printf("Usage: [MODE] pid\n\n");
	printf("pid\t The operation specified in MODE will be executed when the process with pid 'pid' finished.\n\n");
	printf("MODE:\n\t-s Shutdown(default)\n\t-r Reboot\n");
	exit(1);
}

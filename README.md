autoshut
========

autoshut is a small utility to shutdown or reboot a linux system when a specified process has ended.

Installation
------------

    git clone https://github.com/oweissbarth/autoshut
    cd autoshut
    make
    sudo make install
    
Usage
-----
Usage: autoshut [MODE] pid

pid:        The operation specified in MODE will be executed when the process with pid 'pid' finished.

MODE:
	
	-s Shutdown(default)
	
	-r Reboot

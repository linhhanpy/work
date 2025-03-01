all:
	make main
	make cmd
	make VMwork
	make simple
	make hacker
	make rain
	make Games
	make exe
	make exe2
	make http
main:
	g++ -o workos main.cpp -std=c++11 -leasyx -lgdi32 -mwindows
cmd:
	g++ -o linuxcmd linuxcmd.cpp -std=c++11
VMwork:
	g++ -o VMwork main.cpp vm.res -std=c++11 -leasyx -lcomdlg32 -lshlwapi -lmsimg32 -mwindows -static-libgcc -static-libstdc++
simple: 
	g++ simple.cpp -o simple.exe -std=c++11
hacker:
	g++ -o hacker hacker.cpp -std=c++11 -lws2_32 -leasyx
rain:
	g++ -o rain rain.cpp -std=c++11 -leasyx
Games:
	g++ -o Gamesbox Gamesbox.cpp -std=c++11 -leasyx
exe:
	g++ Penetration_Testing.cpp -o Penetration_Testing -std=c++11 -lws2_32
exe2:
	g++ Penetration_Testing2.cpp -o Penetration_Testing2 -std=c++11 -lgdiplus -lgdi32 -lws2_32
http:
	g++ http.cpp -o http -std=c++11 -lgdiplus -lgdi32 -lws2_32 -lwininet


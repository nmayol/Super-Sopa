triemain.exe: triemain.o diccTrie.o
	g++ -o triemain.exe triemain.o diccTrie.o
	rm *.o

triemain.o: diccTrie.hh
	g++ -c triemain.cc

diccTrie.o: diccTrie.hh 
	g++ -c diccTrie.cc
	
clean:
	rm *.o
	rm *.exe


all: Sopa main.exe

main.exe:  main.o ./SuperSopa/superSopa.o ./Taula\ Hash/diccDHashing.o ./Filtre\ Bloom/diccBloomFilter.o ./Trie/diccTrie.o ./Sorted\ Vector/diccSortedVector.o
	g++ -o main.exe main.o ./SuperSopa/superSopa.o ./Taula\ Hash/diccDHashing.o ./Filtre\ Bloom/diccBloomFilter.o ./Trie/diccTrie.o ./Sorted\ Vector/diccSortedVector.o

main.o: ./SuperSopa/superSopa.hh
	g++ -c main.cc

Sopa:
	+$(MAKE) -C ./SuperSopa

	
clean:
	rm -f main.exe
	+$(SUBDIRS)	rm -rf *.exe *.o


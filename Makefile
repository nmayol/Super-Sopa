all: main.exe
	+$(MAKE) -C ./SuperSopa

main.exe:  main.o ./SuperSopa/superSopa.o ./Taula\ Hash/diccDHashing.o ./Filtre\ Bloom/diccBloomFilter.o ./Trie/diccTrie.o ./Sorted\ Vector/diccSortedVector.o
	g++ -o main.exe main.o ./SuperSopa/superSopa.o ./Taula\ Hash/diccDHashing.o ./Filtre\ Bloom/diccBloomFilter.o ./Trie/diccTrie.o ./Sorted\ Vector/diccSortedVector.o

main.o: ./SuperSopa/superSopa.hh ./SuperSopa/superSopa.o ./Taula\ Hash/diccDHashing.o ./Filtre\ Bloom/diccBloomFilter.o ./Trie/diccTrie.o ./Sorted\ Vector/diccSortedVector.o
	g++ -c main.cc

	

	
clean:
	rm -f main.exe
	+$(SUBDIRS)	rm -rf *.exe *.o


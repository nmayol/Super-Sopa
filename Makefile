program.exe:  program.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o program.exe program.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

program.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c program.cc

main.exe:  main.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o main.exe main.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

main.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c main.cc

superSopa.o: ./SuperSopa/superSopa.cc ./SuperSopa/superSopa.hh ./Taula\ Hash/diccDHashing.hh ./Filtre\ Bloom/diccBloomFilter.hh ./Trie/diccTrie.hh ./Sorted\ Vector/diccSortedVector.hh
	g++ -c ./SuperSopa/superSopa.cc

diccSortedVector.o: ./Sorted\ Vector/diccSortedVector.hh 
	g++ -c ./Sorted\ Vector/diccSortedVector.cc

diccTrie.o: ./Trie/diccTrie.hh
	g++ -c ./Trie/diccTrie.cc

diccDHashing.o: ./Taula\ Hash/diccDHashing.hh
	g++ -c ./Taula\ Hash/diccDHashing.cc

diccBloomFilter.o: ./Filtre\ Bloom/diccBloomFilter.hh
	g++ -c ./Filtre\ Bloom/diccBloomFilter.cc 

	
clean:
	rm *.exe


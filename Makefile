generar.exe:  generar.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o generar.exe generar.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

generar.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c generar.cc	

experiment_vector.exe:  experiment_vector.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o experiment_vector.exe experiment_vector.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

experiment_vector.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c experiment_vector.cc

experiment_hash.exe:  experiment_hash.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o experiment_hash.exe experiment_hash.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

experiment_hash.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c experiment_hash.cc

experiment_trie.exe:  experiment_trie.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o experiment_trie.exe experiment_trie.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

experiment_trie.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c experiment_trie.cc

experiment_filtre.exe:  experiment_filtre.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o experiment_filtre.exe experiment_filtre.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

experiment_falsos_positius.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c experiment_falsos_positius.cc

experiment_falsos_positius.exe:  experiment_falsos_positius.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -o experiment_falsos_positius.exe experiment_falsos_positius.o superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	rm *.o

experiment_filtre.o: superSopa.o diccDHashing.o diccBloomFilter.o diccTrie.o diccSortedVector.o
	g++ -c experiment_filtre.cc

superSopa.o: ./SuperSopa/superSopa.cc ./SuperSopa/superSopa.hh ./Taula\ Hash/diccDHashing.hh ./Filtre\ Bloom/diccBloomFilter.hh ./Trie/diccTrie.hh ./Sorted\ Vector/diccSortedVector.hh
	g++ -c ./SuperSopa/superSopa.cc

diccSortedVector.o: ./Sorted\ Vector/diccSortedVector.hh 
	g++ -c ./Sorted\ Vector/diccSortedVector.cc

diccTrie.o: ./Trie/diccTrie.hh ./SuperSopa/superSopa.hh
	g++ -c ./Trie/diccTrie.cc

diccDHashing.o: ./Taula\ Hash/diccDHashing.hh
	g++ -c ./Taula\ Hash/diccDHashing.cc

diccBloomFilter.o: ./Filtre\ Bloom/diccBloomFilter.hh
	g++ -c ./Filtre\ Bloom/diccBloomFilter.cc 

	
clean:
	rm *.o
	rm *.exe


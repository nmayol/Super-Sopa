all: superSopa.o
	+$(MAKE) -C ../Filtre\ Bloom
	+$(MAKE) -C ../Taula\ Hash
	+$(MAKE) -C ../Sorted\ Vector
	+$(MAKE) -C ../Trie

superSopa.o: superSopa.cc superSopa.hh ../Taula\ Hash/diccDHashing.hh ../Taula\ Hash/diccDHashing.o ../Filtre\ Bloom/diccBloomFilter.hh ../Filtre\ Bloom/diccBloomFilter.o ../Trie/diccTrie.hh ../Trie/diccTrie.o ../Sorted\ Vector/diccSortedVector.hh ../Sorted\ Vector/diccSortedVector.o
	g++ -c superSopa.cc

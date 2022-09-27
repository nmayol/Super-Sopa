#ifndef BLOOM_FILTER
#define BLOOM_FILTER

class BloomFilterDictionary {
    public:
        BloomFilterDictionary ();

        void afegir (String s);

        bool comprovar(String s);
    private:
        
}


#endif
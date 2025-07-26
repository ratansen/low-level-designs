#include<iostream>
#include<memory>

using namespace std;

class EvictionPolicy{
public:
    virtual void keyAccessed() = 0;
    virtual void evictKey() = 0;
    virtual void say() = 0;
};

class LRUEvictionPolicy : public EvictionPolicy{
private:


public: 

    LRUEvictionPolicy(){
        cout << "LRUEvictionPolicy constructor" << endl;
    }

    void say() override{
        cout << "Hi from LRU Eviction policy" << endl;
    }

    void keyAccessed() override{

    }

    void evictKey() override{

    }
};

class Storage{

public:
    virtual int get(int key) = 0;
    virtual void put(int key, int value) = 0;
    virtual void remove(int key) = 0;
    virtual void say() = 0;
};

class HashMapStorage: public Storage{
private:

public:
    HashMapStorage(){
        cout << "HashmapStorage constructor" << endl;
    }

    void say() override{
        cout << "Hi from HashMapStorage" << endl;
    }

    int get(int key) override{
        
    }

    void put(int key, int value) override{
    }

    void remove(int key) override{

    }

};

class Cache{
private:
public:
    int capacity;
    shared_ptr<EvictionPolicy>evictionPolicy;
    shared_ptr<Storage>storage;

    Cache(int capacity, shared_ptr<EvictionPolicy> evictionPolicy, shared_ptr<Storage> storage){
        this -> capacity = capacity;
        this -> evictionPolicy = evictionPolicy;
        this -> storage = storage;
    }
};


int main(){

    Cache* c = new Cache(10, make_shared<LRUEvictionPolicy>(), make_shared<HashMapStorage>());
    c -> evictionPolicy -> say(); 
    c -> storage -> say();

}
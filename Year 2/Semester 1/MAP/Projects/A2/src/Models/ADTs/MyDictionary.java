package Models.ADTs;

import Models.Exceptions.MyException;
import Models.Values.IValue;

import java.util.HashMap;

public class MyDictionary<K, V> implements MyIDictionary<K, V>{

    HashMap<K, V> dictionary;

    public MyDictionary(){
        this.dictionary = new HashMap<K, V>();
    }

    public HashMap<K, V> getDictionary(){
        return this.dictionary;
    }

    @Override
    public int size() {
        return this.dictionary.size();
    }

    @Override
    public boolean isEmpty() {
        return this.dictionary.isEmpty();
    }

    @Override
    public V get(K key) throws MyException {
        V v = this.dictionary.get(key);
        if(v==null){
            throw new MyException("There's no key " + key + " in symtable");
        }
        return v;
    }

    @Override
    public V put(K key, V value) {
        return this.dictionary.put(key, value);
    }

    @Override
    public V remove(K key) throws MyException{
        V v = this.dictionary.remove(key);
        if(v==null){
            throw new MyException("There's no key " + key + "in symtable");
        }
        return v;
    }

    @Override
    public V lookup(K key) throws MyException {
        V v = this.dictionary.get(key);
        if(v==null){
            throw new MyException("There's no key " + key + " in symtable");
        }
        return v;
    }

    @Override
    public boolean isDefined(K key) throws MyException {
        return this.dictionary.containsKey(key);
    }

    @Override
    public void update(K key, V value) throws MyException {
        V val = this.dictionary.replace(key, value);
        if(val == null)
            throw new MyException("Key wasn't updated because it doesn't exist.");
    }


    public String toString(){
        return this.dictionary.toString();
    }
}

package Models.ADTs;

import Models.Exceptions.MyException;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Set;

public interface MyIDictionary<K, V> {
    public int size();
    public boolean isEmpty();
    public V get(K key) throws MyException;
    public V put(K key, V value);
    public V remove(K key) throws MyException;
    public V lookup(K key) throws MyException;
    public boolean isDefined(K key) throws MyException;
    public void update(K key, V value) throws MyException;
    public HashMap<K, V> getContent();
}

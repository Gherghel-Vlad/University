package Models.ADTs;

import Models.Exceptions.MyException;
import javafx.util.Pair;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class MySemaphore implements MyISemaphore{
    AtomicInteger freeLocation;
    MyIDictionary<Integer, Pair<Integer, List<Integer>>> semaphore;

    public MySemaphore(){
        this.semaphore = new MyDictionary<Integer, Pair<Integer, List<Integer>>>();
        this.freeLocation = new AtomicInteger(0);
    }

    @Override
    public MyIDictionary<Integer, Pair<Integer, List<Integer>>> getSemaphore() {
        return this.semaphore;
    }

    @Override
    public synchronized Integer allocate(Pair<Integer, List<Integer>> value) {
        this.semaphore.put(this.freeLocation.incrementAndGet(), value);
        return this.freeLocation.get();
    }

    @Override
    public synchronized void put(Integer key, Pair<Integer, List<Integer>> value) {
        this.semaphore.put(key, value);
    }

    @Override
    public synchronized Pair<Integer, List<Integer>> lookup(Integer key) throws MyException {
        return this.semaphore.lookup(key);
    }

    @Override
    public synchronized void update(Integer key, Pair<Integer, List<Integer>> value) throws MyException {
        this.semaphore.update(key, value);
    }

    @Override
    public synchronized boolean isDefined(Integer key) {
        return this.semaphore.isDefined(key);
    }

    public String toString(){
        return this.semaphore.toString();
    }

}

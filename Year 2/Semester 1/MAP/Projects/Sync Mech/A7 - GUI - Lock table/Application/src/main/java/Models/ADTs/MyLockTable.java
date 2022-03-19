package Models.ADTs;

import Models.Exceptions.MyException;
import javafx.util.Pair;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class MyLockTable implements MyILockTable{

    AtomicInteger freeLocation;
    MyIDictionary<Integer, Integer> lockTable;

    public MyLockTable(){
        this.lockTable = new MyDictionary<Integer, Integer>();
        this.freeLocation = new AtomicInteger(0);
    }

    @Override
    public MyIDictionary<Integer, Integer> getLockTable() {
        return this.lockTable;
    }

    @Override
    public Integer allocate(Integer value) {
        this.lockTable.put(this.freeLocation.incrementAndGet(), value);
        return this.freeLocation.get();
    }

    @Override
    public synchronized void put(Integer key, Integer value) {
        this.lockTable.put(key, value);
    }

    @Override
    public synchronized Integer lookup(Integer key) throws MyException {
        return this.lockTable.lookup(key);
    }

    @Override
    public synchronized void update(Integer key, Integer value) throws MyException {
        this.lockTable.update(key, value);
    }

    @Override
    public synchronized boolean isDefined(Integer key) {
        return this.lockTable.isDefined(key);
    }
}

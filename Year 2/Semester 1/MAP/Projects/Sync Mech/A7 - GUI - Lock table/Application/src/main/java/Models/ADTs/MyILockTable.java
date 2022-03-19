package Models.ADTs;

import Models.Exceptions.MyException;
import javafx.util.Pair;

import java.util.List;

public interface MyILockTable {

    public MyIDictionary<Integer, Integer> getLockTable();
    public Integer allocate(Integer value);
    public void put(Integer key, Integer value);
    public Integer lookup(Integer key) throws MyException;
    public void update(Integer key, Integer value) throws MyException;
    public boolean isDefined(Integer key);
}

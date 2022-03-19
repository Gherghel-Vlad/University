package Models.ADTs;

import Models.Exceptions.MyException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface MyISemaphore {

    public MyIDictionary<Integer, Pair<Integer, List<Integer>>> getSemaphore();
    public Integer allocate(Pair<Integer, List<Integer>> value);
    public void put(Integer key, Pair<Integer, List<Integer>> value);
    public Pair<Integer, List<Integer>> lookup(Integer key) throws MyException;
    public void update(Integer key, Pair<Integer, List<Integer>> value) throws MyException;
    public boolean isDefined(Integer key);
}

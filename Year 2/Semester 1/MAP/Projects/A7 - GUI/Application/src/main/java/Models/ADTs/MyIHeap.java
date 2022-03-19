package Models.ADTs;

import Models.Exceptions.MyException;
import Models.Values.IValue;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public interface MyIHeap{

    public IValue get(int key) throws MyException;
    public IValue put(IValue value);
    public IValue remove(int key) throws MyException;
    public boolean isDefined(int key) throws MyException;
    public void update(int key, IValue value) throws MyException;
    public int createEntry(IValue value);
    public int getNextFree();
    public Set<?> entrySet();
    public void incrementNextFree();
    public void setContent(Map<Integer, IValue> newHeap);
    public Map<Integer, IValue> getContent();
}

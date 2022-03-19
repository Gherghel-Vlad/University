package Models.ADTs;

import Models.Exceptions.MyException;
import Models.Values.IValue;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyHeap implements MyIHeap {
    private HashMap<Integer, IValue> heap;
    private int position;

    public MyHeap(){
        this.heap = new HashMap<Integer, IValue>();
        this.position = 1;
    }

    @Override
    public IValue get(int key) throws MyException {
        IValue v = this.heap.get(key);
        if(v==null){
            throw new MyException("There's no key " + key + " in heap");
        }
        return v;
    }

    @Override
    public IValue put(IValue value) {
        IValue val = this.heap.put(this.getNextFree(), value);
        this.incrementNextFree();
        return val;
    }

    @Override
    public IValue remove(int key) throws MyException {
        IValue v = this.heap.remove(key);
        if(v==null){
            throw new MyException("There's no key " + key + "in heap");
        }
        return v;
    }

    @Override
    public boolean isDefined(int key) throws MyException {
        return this.heap.containsKey(key);
    }

    @Override
    public void update(int key, IValue value) throws MyException {
        IValue val = this.heap.replace(key, value);
        if(val == null)
            throw new MyException("Key wasn't updated because it doesn't exist.");
    }

    @Override
    public int createEntry(IValue value) {
        IValue val = this.heap.put(this.getNextFree(), value);
        int pos = this.getNextFree();
        this.incrementNextFree();
        return pos;
    }

    @Override
    public int getNextFree() {
        return this.position;
    }

    @Override
    public Set<?> entrySet() {
        return this.heap.entrySet();
    }

    @Override
    public void incrementNextFree() {
        this.position+=1;
    }

    @Override
    public void setContent(Map<Integer, IValue> newHeap) {
        this.heap = (HashMap<Integer, IValue>) newHeap;
    }

    @Override
    public Map<Integer, IValue> getContent() {
        return this.heap;
    }


    public String toString() {
        return this.heap.toString();
    }
}

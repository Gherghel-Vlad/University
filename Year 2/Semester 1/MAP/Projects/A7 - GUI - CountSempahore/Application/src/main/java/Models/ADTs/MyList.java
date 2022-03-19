package Models.ADTs;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T>{
    ArrayList<T> list;

    public MyList(){
        this.list = new ArrayList<T>();
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }

    @Override
    public int indexOf(T item) {
        return this.list.indexOf(item);
    }

    @Override
    public boolean add(T item) {
        return this.list.add(item);
    }

    @Override
    public boolean remove(T item) {
        return this.list.remove(item);
    }

    @Override
    public void clear() {
        this.list.clear();
    }


    public String toString(){
        return this.list.toString();
    }
}

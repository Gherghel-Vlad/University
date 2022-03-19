package Models.ADTs;

public interface MyIList<T> {
    public int size();
    public boolean isEmpty();
    public int indexOf(T item);
    public boolean add(T item);
    public boolean remove(T item);
    public void clear();
}

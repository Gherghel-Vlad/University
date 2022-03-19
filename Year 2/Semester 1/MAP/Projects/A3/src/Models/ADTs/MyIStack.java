package Models.ADTs;

import Models.Exceptions.MyException;

public interface MyIStack<T> {
    public boolean empty();
    public T pop() throws MyException;
    public T push(T item);
    public int search(T item);
    public T peek() throws MyException;
}

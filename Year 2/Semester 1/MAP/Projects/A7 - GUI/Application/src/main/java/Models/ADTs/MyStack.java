package Models.ADTs;

import Models.Exceptions.MyException;

import java.util.EmptyStackException;
import java.util.Stack;

public class MyStack<T> implements MyIStack<T>{
    Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<T>();
    }

    @Override
    public boolean empty() {
        return this.stack.empty();
    }

    @Override
    public T pop() throws MyException {
        try {
            return this.stack.pop();
        }
        catch (EmptyStackException e){
            throw new MyException("Stack is empty." + e.getMessage());
        }
    }

    @Override
    public T push(T item) {
        this.stack.push(item);
        return item;
    }

    @Override
    public int search(T item) {
        return this.stack.search(item);
    }

    @Override
    public T peek() throws MyException{
        try {
            return this.stack.peek();
        }
        catch (EmptyStackException e){
            throw new MyException("Stack is empty." + e.getMessage());
        }
    }

    public String toString(){
        return this.stack.toString();
    }
}

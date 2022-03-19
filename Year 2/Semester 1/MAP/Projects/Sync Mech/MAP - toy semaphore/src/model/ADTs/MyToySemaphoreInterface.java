package model.ADTs;

import java.util.Map;

public interface MyToySemaphoreInterface<T> {
    int allocate(T value);

    T lookup(int address);
    void update(int address, T value);
    boolean exists(int address);

    Map<Integer, T> getContent();
}

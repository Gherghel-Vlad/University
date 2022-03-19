package com.example.application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class LockTableModel {


    private SimpleIntegerProperty location;
    private SimpleIntegerProperty value;

    public LockTableModel(Integer addr, Integer val){
        this.location = new SimpleIntegerProperty(addr);
        this.value = new SimpleIntegerProperty(val);
    }

    public int getLocation() {
        return location.get();
    }

    public SimpleIntegerProperty locationProperty() {
        return location;
    }

    public void setLocation(int location) {
        this.location.set(location);
    }

    public int getValue() {
        return value.get();
    }

    public SimpleIntegerProperty valueProperty() {
        return value;
    }

    public void setValue(int value) {
        this.value.set(value);
    }
}

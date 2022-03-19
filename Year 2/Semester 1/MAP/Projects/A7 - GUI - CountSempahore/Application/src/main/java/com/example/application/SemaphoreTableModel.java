package com.example.application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class SemaphoreTableModel {

    private SimpleIntegerProperty index;
    private SimpleIntegerProperty value;
    private SimpleStringProperty list;

    public SemaphoreTableModel(Integer index, Integer value, String list){
        this.index = new SimpleIntegerProperty(index);
        this.value = new SimpleIntegerProperty(value);
        this.list = new SimpleStringProperty(list);
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

    public String getList() {
        return list.get();
    }

    public SimpleStringProperty listProperty() {
        return list;
    }

    public void setList(String list) {
        this.list.set(list);
    }

    public int getIndex() {
        return index.get();
    }

    public SimpleIntegerProperty indexProperty() {
        return index;
    }

    public void setIndex(int index) {
        this.index.set(index);
    }
}

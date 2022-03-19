package com.example.application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class HeapTableModel {

        private SimpleIntegerProperty address;
        private SimpleStringProperty value;

        public HeapTableModel(Integer addr, String val){
            this.address = new SimpleIntegerProperty(addr);
            this.value = new SimpleStringProperty(val);
        }


    public int getAddress() {
        return address.get();
    }

    public SimpleIntegerProperty addressProperty() {
        return address;
    }

    public void setAddress(int address) {
        this.address.set(address);
    }

    public String getValue() {
        return value.get();
    }

    public SimpleStringProperty valueProperty() {
        return value;
    }

    public void setValue(String value) {
        this.value.set(value);
    }
}

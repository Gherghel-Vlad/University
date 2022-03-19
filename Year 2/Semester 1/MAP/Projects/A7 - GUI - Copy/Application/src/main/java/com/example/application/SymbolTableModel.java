package com.example.application;

import javafx.beans.property.SimpleStringProperty;

public class SymbolTableModel {

    private SimpleStringProperty symbol;
    private SimpleStringProperty value;

    public SymbolTableModel(String s, String v){
        this.symbol = new SimpleStringProperty(s);
        this.value = new SimpleStringProperty(v);
    }

    public String getSymbol() {
        return symbol.get();
    }

    public SimpleStringProperty symbolProperty() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol.set(symbol);
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

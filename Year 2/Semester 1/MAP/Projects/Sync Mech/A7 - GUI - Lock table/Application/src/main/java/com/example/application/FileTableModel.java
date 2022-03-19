package com.example.application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class FileTableModel {

    private StringProperty id;
    private StringProperty file;

    public FileTableModel(String id, String file){
        this.id = new SimpleStringProperty(id);
        this.file = new SimpleStringProperty(file);
    }


    public String getId() {
        return id.get();
    }

    public StringProperty idProperty() {
        return id;
    }

    public void setId(String id) {
        this.id.set(id);
    }

    public String getFile() {
        return file.get();
    }

    public StringProperty fileProperty() {
        return file;
    }

    public void setFile(String file) {
        this.file.set(file);
    }
}

package com.example.application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class ProgramsApplication extends Application {
    @Override
    public void start(Stage programStage) throws IOException {

        try{
            AnchorPane root = (AnchorPane)FXMLLoader.load(getClass().getResource("Programs.fxml"));
            Scene scene= new Scene(root,600,400);
            scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
            programStage.setTitle("Programs");
            programStage.setScene(scene);
            programStage.show();}
        catch(Exception e) { e.printStackTrace();}
    }

    public static void main(String[] args) {
        launch();
    }
}
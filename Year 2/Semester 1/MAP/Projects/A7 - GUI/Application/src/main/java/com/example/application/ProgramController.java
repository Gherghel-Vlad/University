package com.example.application;

import Controller.Controller;
import Models.ADTs.MyDictionary;
import Models.ADTs.MyHeap;
import Models.ADTs.MyList;
import Models.ADTs.MyStack;
import Models.Exceptions.MyException;
import Models.Statements.IStmt;
import Models.States.PrgState;
import Models.Values.IValue;
import Models.Values.StringValue;
import Repository.IRepo;
import Repository.Repo;
import javafx.animation.PauseTransition;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Duration;

import java.io.BufferedReader;

public class ProgramController {

    private IStmt stmt;
    private String fileName;
    private PrgState prg;
    private IRepo repo;
    private Controller ctr;
    private int selectedPrgState;

    public void initData(IStmt s, String fileName){
        this.stmt = s;
        this.fileName = fileName;
        try {
            this.prg = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap(), this.stmt);
            this.repo = new Repo(this.fileName);
            this.repo.addPrgState(this.prg);
            this.ctr = new Controller(this.repo);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
        }

        this.selectedPrgState = 0; // we always start with the first prg state


        this.updateEverything();

        // setting the handler for when you choose a prg state
        this.programStatesListViewId.getSelectionModel().selectedItemProperty().addListener( e -> {

            Platform.runLater(() -> {
                PauseTransition pause = new PauseTransition(Duration.millis(100));
                pause.setOnFinished(event -> {
                    this.updatePrgState();
                    this.updateEverything();

                });

                pause.play();
            });

        });
    }

    @FXML
    private ListView<String> exeStackListViewId;

    @FXML
    private ListView<String> fileTableListViewId;

    @FXML
    private TableView<HeapTableModel> heapTableViewId;

    @FXML
    private ListView<String> outputListViewId;

    @FXML
    private ListView<Integer> programStatesListViewId;

    @FXML
    private TextField programStatesNumberTextFieldId;

    @FXML
    private Button runOneStepAllBtnId;

    @FXML
    private TableView<SymbolTableModel> symbolTableViewId;


    @FXML
    private TableColumn<HeapTableModel, Integer> heapTableViewColumnAddressId;

    @FXML
    private TableColumn<HeapTableModel, String> heapTableViewColumnValueId;

    @FXML
    private TableColumn<SymbolTableModel, String> symbolTableViewColumnSymbolId;

    @FXML
    private TableColumn<SymbolTableModel, String> symbolTableViewColumnValueId;

    @FXML
    public void initialize(){

        // setting the factory cell property for the heap table view
        this.heapTableViewColumnAddressId.setCellValueFactory(new PropertyValueFactory<>("Address"));
        this.heapTableViewColumnValueId.setCellValueFactory(new PropertyValueFactory<>("Value"));

        // setting the factory cell property for the symbol table view
        this.symbolTableViewColumnSymbolId.setCellValueFactory(new PropertyValueFactory<>("Symbol"));
        this.symbolTableViewColumnValueId.setCellValueFactory(new PropertyValueFactory<>("Value"));

    }

    private void updateEverything(){
        //clearing everything at first
        this.clearEverything();

        //populate everything back
        this.populateEverything();
    }

    private void clearEverything(){

        //clearing file table view
        this.fileTableListViewId.getItems().clear();

        // clearing the heap table
        for ( int i = 0; i<this.heapTableViewId.getItems().size(); i++) {
            this.heapTableViewId.getItems().clear();
        }

        // clearing the symbol table
        for ( int i = 0; i<this.symbolTableViewId.getItems().size(); i++) {
            this.symbolTableViewId.getItems().clear();
        }

        // clearing the exe stack list view
        this.exeStackListViewId.getItems().clear();

        // clearing the out list view
        this.outputListViewId.getItems().clear();


    }

    private void  updatePrgState(){
        int id = this.programStatesListViewId.getSelectionModel().getSelectedIndex();
        if(id!=-1) {
            this.selectedPrgState = id;

            this.prg = this.repo.getPrgList().get(this.selectedPrgState);
        }
    }

    private void populateEverything(){

        try {
            // file table populate
            for (StringValue s : this.prg.getFileTable().getContent().keySet()) {
                this.fileTableListViewId.getItems().add(s.toString());
            }

            // heap table populate
            for (Integer s : this.prg.getHeap().getContent().keySet()) {
                this.heapTableViewId.getItems().add(new HeapTableModel(s, this.prg.getHeap().getContent().get(s).toString()));
            }

            // symbol table populate
            for (String s : this.prg.getSymTable().getContent().keySet()) {
                this.symbolTableViewId.getItems().add(new SymbolTableModel(s, this.prg.getSymTable().getContent().get(s).toString()));
            }

            // populating the exe stack list view
            for(String s : this.prg.getExeStackAsStringList()){
                this.exeStackListViewId.getItems().add(s);
            }

            // populating the out list view
            for(String s : this.prg.getOutAsStringList()) {
                this.outputListViewId.getItems().add(s);
            }



            // setting the number of prg states
            this.programStatesNumberTextFieldId.setText(String.valueOf(this.repo.getPrgList().size()));

        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }


    @FXML
    void runOneStepAllOnCick(ActionEvent event) {


        try {
            this.ctr.oneStepForAll();
            this.clearEverything();
            //System.out.println(this.prg.getStk().toString());
            this.populateEverything();


            // clearing the prg states list view
            this.programStatesListViewId.getItems().clear();


            // populating the prg list view
            for(PrgState s : this.repo.getPrgList()){
                this.programStatesListViewId.getItems().add(s.getIdPrgState());
            }

        }
        catch (MyException e)
        {
            Alert a = new Alert(Alert.AlertType.INFORMATION);
            a.setHeaderText("Program done.");
            a.setTitle(":)");
            a.show();
            //System.out.println(e.getMessage());
        }
    }

}

package com.example.application;

import Models.ADTs.MyStack;
import Models.Exceptions.MyException;
import Models.Expressions.*;
import Models.Statements.*;
import Models.Types.*;
import Models.Values.BoolValue;
import Models.Values.IntValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.layout.AnchorPane;
import Models.ADTs.MyDictionary;
import Models.ADTs.MyHeap;
import Models.ADTs.MyList;
import Models.States.PrgState;
import Models.Values.IValue;
import Models.Values.StringValue;
import Repository.IRepo;
import Repository.Repo;
import Controller.Controller;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Objects;

public class ProgramsController {

    private IStmt ex1;
    private IStmt ex2;
    private IStmt ex3;
    private IStmt ex4;
    private IStmt ex5;
    private IStmt ex6;
    private IStmt ex7;
    private IStmt ex8;
    private IStmt ex9;
    private IStmt ex10;
    private IStmt ex11;
    private IStmt ex12;


    @FXML
    private Button loadProgramButtonId;

    @FXML
    private ListView<String> programsListViewId;

    @FXML
    private AnchorPane programsSceneId;

    @FXML
    public void initialize(){

        this.ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                new PrintStmt(new VarExp("v"))));

        this.ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                        new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(new AssignStmt("b", new ArithExp(
                        '+', new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));


        this.ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"),
                        new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));


        this.ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenReadFileStmt(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                new CompStmt(new PrintStmt(new VarExp("varc")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                                new CompStmt(new PrintStmt(new VarExp("varc")), new CloseReadFileStmt(new VarExp("varf"))))))))));


        this.ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new VarDeclStmt("res", new BoolType()),
                                new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                        new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(10))),
                                                new CompStmt(new AssignStmt("res", new RelationalExp(new VarExp("a"), new VarExp("b"), "<")),
                                                        new PrintStmt(new VarExp("res"))))))));


        this.ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));


        this.ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt( new PrintStmt(new rHExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp('+', new rHExp(new rHExp(new VarExp("a"))), new ValueExp(new IntValue(5)))))))));


        this.ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                new CompStmt(new wHStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp('+', new rHExp(new VarExp("v")), new ValueExp(new IntValue(5))))))));


        this.ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rHExp(new rHExp(new VarExp("a")))))))));


        this.ex10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));


        this.ex11 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new forkStmt(new CompStmt(new wHStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rHExp(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new rHExp(new VarExp("a")))))))));

        this.ex12 = new CompStmt(new VarDeclStmt("v", new StringType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                new PrintStmt(new VarExp("v"))));

        this.programsListViewId.getItems().add(this.ex1.toString());
        this.programsListViewId.getItems().add(this.ex2.toString());
        this.programsListViewId.getItems().add(this.ex3.toString());
        this.programsListViewId.getItems().add(this.ex4.toString());
        this.programsListViewId.getItems().add(this.ex5.toString());
        this.programsListViewId.getItems().add(this.ex6.toString());
        this.programsListViewId.getItems().add(this.ex7.toString());
        this.programsListViewId.getItems().add(this.ex8.toString());
        this.programsListViewId.getItems().add(this.ex9.toString());
        this.programsListViewId.getItems().add(this.ex10.toString());
        this.programsListViewId.getItems().add(this.ex11.toString());
        this.programsListViewId.getItems().add(this.ex12.toString());


    }

    @FXML
    void loadProgramButtonClick(ActionEvent event) {
        int selectedEx = this.programsListViewId.getSelectionModel().getSelectedIndex();
        try {
            switch (selectedEx) {
                case -1:
                    Alert a = new Alert(Alert.AlertType.ERROR);
                    a.setTitle("Careful!");
                    a.setHeaderText("You forgot to select a program from the list!");
                    a.show();
                    break;
                case 0:
                    this.ex1.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex1.deepCopy(), "log1.txt");
                    break;
                case 1:
                    this.ex2.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex2.deepCopy(), "log2.txt");
                    break;
                case 2:
                    this.ex3.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex3.deepCopy(), "log3.txt");
                    break;
                case 3:
                    this.ex4.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex4.deepCopy(), "log4.txt");
                    break;
                case 4:
                    this.ex5.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex5.deepCopy(), "log5.txt");
                    break;
                case 5:
                    this.ex6.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex6.deepCopy(), "log6.txt");
                    break;
                case 6:
                    this.ex7.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex7.deepCopy(), "log7.txt");
                    break;
                case 7:
                    this.ex8.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex8.deepCopy(), "log8.txt");
                    break;
                case 8:
                    this.ex9.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex9.deepCopy(), "log9.txt");
                    break;
                case 9:
                    this.ex10.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex10.deepCopy(), "log10.txt");
                    break;
                case 10:
                    this.ex11.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex11.deepCopy(), "log11.txt");
                    break;
                case 11:
                    this.ex12.typecheck(new MyDictionary<String, IType>());
                    createProgramStage(this.ex12.deepCopy(), "log12.txt");
                    break;
                default:
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setTitle("DANGER!");
                    alert.setHeaderText("Something went horribly wrong!");
                    alert.show();
            }
        }
        catch (MyException e){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error!");
            alert.setHeaderText("Program failed at type checker.");
            alert.show();
        }
    }


    private void createProgramStage(IStmt stmt, String fileName){
        Stage stage = new Stage(StageStyle.DECORATED);
        try {
            FXMLLoader loader = new FXMLLoader(
                    getClass().getResource(
                            "program.fxml"
                    )
            );

            stage.setScene(
                    new Scene(loader.load())
            );

            ProgramController controller = loader.getController();
            controller.initData(stmt, fileName);

            stage.show();

        }
        catch (IOException e) {
            e.printStackTrace();
        }

    }
}

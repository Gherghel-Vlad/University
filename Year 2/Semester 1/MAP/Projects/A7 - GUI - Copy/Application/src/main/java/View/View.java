package View;

import Controller.Controller;
import Models.ADTs.*;
import Models.Exceptions.MyException;
import Models.Expressions.ArithExp;
import Models.Expressions.ValueExp;
import Models.Expressions.VarExp;
import Models.Statements.*;
import Models.States.PrgState;
import Models.Types.BoolType;
import Models.Types.IntType;
import Models.Types.StringType;
import Models.Values.BoolValue;
import Models.Values.IValue;
import Models.Values.IntValue;
import Models.Values.StringValue;
import Repository.IRepo;
import Repository.Repo;

import java.io.BufferedReader;
import java.util.Scanner;
/*
public class View {

    public static Controller controller;
    public static boolean displayFlag;

    public static void printMenu(){
        System.out.println("Select program:");
        System.out.println("1. int v; v=2;Print(v)");
        System.out.println("2. int a;int b; a=2+3*5;b=a+1;Print(b)");
        System.out.println("3. bool a; int v; a=true;(If a Then v=2 Else v=3);Print(v)");
        System.out.println("4. Set display flag to " + Boolean.toString(!View.displayFlag));
        System.out.println("5.  string varf;\n" +
                "varf=\"test.in\";\n" +
                "openRFile(varf);\n" +
                "int varc;\n" +
                "readFile(varf,varc);print(varc);\n" +
                "readFile(varf,varc);print(varc)\n" +
                "closeRFile(varf)");
        System.out.println("0. Exit");
    }

    public static void startProgram(){





        boolean done = false;
        Scanner scanner = new Scanner(System.in);
        int nrChoice;
        while(!done){
            View.printMenu();

            System.out.println("Input number: ");
            nrChoice = scanner.nextInt();

            switch (nrChoice){
                case 0:
                    return;
                case 1:
                    View.firstProgram();
                    break;
                case 2:
                    View.secondProgram();
                    break;
                case 3:
                    View.thirdProgram();
                    break;
                case 4:
                    View.displayFlag = !View.displayFlag;
                    break;
                case 5:
                    View.fourthProgram();
                    break;
                default:
                    System.out.println("Wrong number. Try again.");
                    break;
            }

        }

    }

    private static void fourthProgram(){
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, IValue> symTbl = new MyDictionary<String, IValue>();
        MyIList<IValue> out = new MyList<IValue>();
        MyIDictionary<StringValue, BufferedReader> fileTbl = new MyDictionary<StringValue, BufferedReader>();
        IStmt stmt = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                new CompStmt(new OpenReadFile(new VarExp("varf")),
                        new CompStmt(new VarDeclStmt("varc", new IntType()),
                new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                new CompStmt(new ReadFile(new VarExp("varf"), "varc"),
                                        new CompStmt(new PrintStmt(new VarExp("varc")), new CloseReadFile(new VarExp("varf"))))))))));


        PrgState state;
        try {
            state = new PrgState(stk, symTbl, out, fileTbl, stmt);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

        IRepo r = new Repo();
        r.addPrgState(state);

        View.controller = new Controller(r, View.displayFlag);

        try {
            View.controller.allStep();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }
    }

    private static void thirdProgram() {
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, IValue> symTbl = new MyDictionary<String, IValue>();
        MyIList<IValue> out = new MyList<IValue>();
        IStmt stmt = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"),
                        new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
        PrgState state;
        try {
            state = new PrgState(stk, symTbl, out, stmt);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

        IRepo r = new Repo();
        r.addPrgState(state);

        View.controller = new Controller(r, View.displayFlag);

        try {
            View.controller.allStep();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

    }

    private static void secondProgram() {
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, IValue> symTbl = new MyDictionary<String, IValue>();
        MyIList<IValue> out = new MyList<IValue>();
        IStmt stmt = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                        new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(new AssignStmt("b", new ArithExp(
                                '+', new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
        PrgState state;
        try {
            state = new PrgState(stk, symTbl, out, stmt);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

        IRepo r = new Repo();
        r.addPrgState(state);

        View.controller = new Controller(r, View.displayFlag);

        try {
            View.controller.allStep();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

    }

    private static void firstProgram() {
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, IValue> symTbl = new MyDictionary<String, IValue>();
        MyIList<IValue> out = new MyList<IValue>();
        IStmt stmt = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp( new IntValue(2))),
                new PrintStmt(new VarExp("v"))));
        PrgState state;
        try {
            state = new PrgState(stk, symTbl, out, stmt);
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

        IRepo r = new Repo();
        r.addPrgState(state);

        View.controller = new Controller(r, View.displayFlag);

        try {
            View.controller.allStep();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
            return;
        }

    }
}*/

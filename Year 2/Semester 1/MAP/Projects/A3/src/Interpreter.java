import Models.ADTs.MyDictionary;
import Models.ADTs.MyList;
import Models.ADTs.MyStack;
import Models.Exceptions.MyException;
import Models.Expressions.ArithExp;
import Models.Expressions.RelationalExp;
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
import View.ExitCommand;
import View.RunExample;
import View.TextMenu;
import Controller.Controller;

import java.io.BufferedReader;

class Interpreter {
    public static void main(String[] args) {

        try {
            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                    new PrintStmt(new VarExp("v"))));
            PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(), ex1);
            IRepo repo1 = new Repo("log1.txt");
            repo1.addPrgState(prg1);
            Controller ctr1 = new Controller(repo1);

            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                            new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(new AssignStmt("b", new ArithExp(
                            '+', new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
            PrgState prg2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),ex2);
            IRepo repo2 = new Repo("log2.txt");
            repo2.addPrgState(prg2);
            Controller ctr2 = new Controller(repo2);


            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"),
                            new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            PrgState prg3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),ex3);
            IRepo repo3 = new Repo( "log3.txt");
            repo3.addPrgState(prg3);
            Controller ctr3 = new Controller(repo3);

            IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                    new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                            new CompStmt(new OpenReadFileStmt(new VarExp("varf")),
                                    new CompStmt(new VarDeclStmt("varc", new IntType()),
                                            new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                    new CompStmt(new PrintStmt(new VarExp("varc")),
                                                            new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                                    new CompStmt(new PrintStmt(new VarExp("varc")), new CloseReadFileStmt(new VarExp("varf"))))))))));
            PrgState prg4 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),ex4);
            IRepo repo4 = new Repo( "log4.txt");
            repo4.addPrgState(prg4);
            Controller ctr4 = new Controller(repo4);

            IStmt ex5 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("b", new IntType()),
                            new CompStmt(new VarDeclStmt("res", new BoolType()),
                                    new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(5))),
                                            new CompStmt(new AssignStmt("b",new ValueExp(new IntValue(10))),
                                                    new CompStmt(new AssignStmt("res", new RelationalExp(new VarExp("a"), new VarExp("b"), "<")),
                                                            new PrintStmt(new VarExp("res"))))))));
            PrgState prg5 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),ex5);
            IRepo repo5 = new Repo( "log5.txt");
            repo5.addPrgState(prg5);
            Controller ctr5 = new Controller(repo5);

            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "exit"));
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
            menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
            menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
            menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
            menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
            menu.show();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
        }
    }
}
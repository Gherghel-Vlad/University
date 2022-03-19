import Models.ADTs.MyDictionary;
import Models.ADTs.MyHeap;
import Models.ADTs.MyList;
import Models.ADTs.MyStack;
import Models.Exceptions.MyException;
import Models.Expressions.*;
import Models.Statements.*;
import Models.States.PrgState;
import Models.Types.BoolType;
import Models.Types.IntType;
import Models.Types.RefType;
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
import java.sql.Ref;

class Interpreter {
    public static void main(String[] args) {

        try {
            IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                    new PrintStmt(new VarExp("v"))));
            PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(), new MyHeap(), ex1);
            IRepo repo1 = new Repo("log1.txt");
            repo1.addPrgState(prg1);
            Controller ctr1 = new Controller(repo1);

            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                    new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                            new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(new AssignStmt("b", new ArithExp(
                            '+', new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
            PrgState prg2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex2);
            IRepo repo2 = new Repo("log2.txt");
            repo2.addPrgState(prg2);
            Controller ctr2 = new Controller(repo2);


            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))), new CompStmt(new IfStmt(new VarExp("a"),
                            new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new VarExp("v"))))));
            PrgState prg3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex3);
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
            PrgState prg4 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex4);
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
            PrgState prg5 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex5);
            IRepo repo5 = new Repo( "log5.txt");
            repo5.addPrgState(prg5);
            Controller ctr5 = new Controller(repo5);

            IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new VarExp("v")),
                                                    new PrintStmt(new VarExp("a")))))));
            PrgState prg6 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex6);
            IRepo repo6 = new Repo( "log6.txt");
            repo6.addPrgState(prg6);
            Controller ctr6 = new Controller(repo6);

            IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt( new PrintStmt(new rHExp(new VarExp("v"))),
                                                    new PrintStmt(new ArithExp('+', new rHExp(new rHExp(new VarExp("a"))), new ValueExp(new IntValue(5)))))))));
            PrgState prg7 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex7);
            IRepo repo7 = new Repo( "log7.txt");
            repo7.addPrgState(prg7);
            Controller ctr7 = new Controller(repo7);

            IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                    new CompStmt(new wHStmt("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(new ArithExp('+', new rHExp(new VarExp("v")), new ValueExp(new IntValue(5))))))));
            PrgState prg8 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex8);
            IRepo repo8 = new Repo( "log8.txt");
            repo8.addPrgState(prg8);
            Controller ctr8 = new Controller(repo8);

            IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                    new PrintStmt(new rHExp(new rHExp(new VarExp("a")))))))));
            PrgState prg9 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex9);
            IRepo repo9 = new Repo( "log9.txt");
            repo9.addPrgState(prg9);
            Controller ctr9 = new Controller(repo9);


            IStmt ex10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                            new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"),
                                    new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v",new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                    new PrintStmt(new VarExp("v")))));
            PrgState prg10 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex10);
            IRepo repo10 = new Repo( "log10.txt");
            repo10.addPrgState(prg10);
            Controller ctr10 = new Controller(repo10);


            /*
            IStmt ex11 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(10))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),

            new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new NewStmt("v", new VarExp("a")),
                                                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(15))), new NewStmt("a", new ValueExp(new IntValue(20)))))))));
            PrgState prg11 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, IValue>(), new MyList<IValue>(), new MyDictionary<StringValue, BufferedReader>(),new MyHeap(),ex11);
            IRepo repo11 = new Repo( "log11.txt");
            repo11.addPrgState(prg11);
            Controller ctr11 = new Controller(repo11);
            */


            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "exit"));
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
            menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
            menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
            menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
            menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
            menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
            menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
            menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
            menu.addCommand(new RunExample("9", ex9.toString(), ctr9));
            menu.addCommand(new RunExample("10", ex10.toString(), ctr10));
           // menu.addCommand(new RunExample("11", ex11.toString(), ctr11));
            menu.show();
        }
        catch (MyException e){
            System.out.println(e.getMessage());
        }
    }
}
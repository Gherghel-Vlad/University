package Models.States;

import Models.ADTs.*;
import Models.Exceptions.MyException;
import Models.Statements.IStmt;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.util.Arrays;
import java.util.Collections;

public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, IValue> symTable;
    MyIList<IValue> out;
    MyIDictionary<StringValue, BufferedReader> fileTable;
    MyIHeap heap;
    IStmt originalProgram;



    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, IValue> symtbl, MyIList<IValue> o, MyIDictionary<StringValue, BufferedReader> fileTbl, MyIHeap heap, IStmt prg) throws MyException{
        this.exeStack = stk;
        this.symTable = symtbl;
        this.out = o;
        this.fileTable = fileTbl;
        this.heap = heap;
        this.originalProgram = prg.deepCopy();
        this.exeStack.push(prg);
    }

    public String toString(){
        return this.exeStack.toString() + "\n " + this.symTable.toString() + "\n" + this.out.toString() + "\n";
    }

    public String toFileFormatString(){
        return "ExeStack:\n" + this.exeStackToFileFormatString() +
                "SymTable:\n" + this.symTableToFileFormatString() +
                "Out:\n" + this.outToFileFormatString() +
                "FileTable:\n" + this.fileTableToFileFormatString() +
                "Heap:\n" + this.heapToFileFormatString() +
                "\n\n----------------------------------------------------------------------\n\n";
    }

    public void setStk(MyIStack<IStmt> stk){
        this.exeStack = stk;
    }

    public void setOut(MyIList<IValue> o){
        this.out =o;
    }

    public void setSymTable(MyIDictionary<String, IValue> symTbl){
        this.symTable = symTbl;
    }

    public void setFileTable(MyIDictionary<StringValue, BufferedReader> newFileTable){
        this.fileTable = newFileTable;
    }

    public void setHeap(MyIHeap h) {
        this.heap = h;
    }

    public MyIStack<IStmt> getStk() {
        return this.exeStack;
    }

    public MyIList<IValue> getOut() {
        return this.out;
    }

    public MyIDictionary<String, IValue> getSymTable() {
        return this.symTable;
    }

    public MyIDictionary<StringValue, BufferedReader> getFileTable(){
        return this.fileTable;
    }

    public MyIHeap getHeap(){
        return this.heap;
    }

    public void resetPrgState(){

    }

    private String exeStackToFileFormatString(){
        StringBuilder exeStackStr = new StringBuilder();

        String stackStr = this.exeStack.toString();
        stackStr = stackStr.replace("[", "");
        stackStr = stackStr.replace("]", "");

        String[] listStr = stackStr.split(",");

        Collections.reverse(Arrays.asList(listStr));
        for(String s : listStr){
            exeStackStr.append(s).append("\n");
        }

        return exeStackStr.toString();
    }



    private String outToFileFormatString(){
        StringBuilder outStr = new StringBuilder();

        String str = this.out.toString();
        str = str.replace("[", "");
        str = str.replace("]", "");
        str = str.replace(" ", "");

        String[] listStr = str.split(",");

        for(String s : listStr){
            outStr.append(s).append("\n");
        }

        return outStr.toString();
    }

    private String symTableToFileFormatString(){
        StringBuilder symTableStr = new StringBuilder();

        String str = this.symTable.toString();
        str = str.replace("{", "");
        str = str.replace("}", "");
        str = str.replace(" ", "");
        str = str.replace("=", " --> ");

        String[] listStr = str.split(",");

        for(String s : listStr){
            symTableStr.append(s).append("\n");
        }

        return symTableStr.toString();
    }


    private String fileTableToFileFormatString(){
        StringBuilder symTableStr = new StringBuilder();

        String str = this.fileTable.toString();
        str = str.replace("{", "");
        str = str.replace("}", "");
        str = str.replace(" ", "");
        str = str.replace("=", " --> ");

        String[] listStr = str.split(",");

        for(String s : listStr){
            symTableStr.append(s).append("\n");
        }

        return symTableStr.toString();
    }


    private String heapToFileFormatString(){
        StringBuilder heapStr = new StringBuilder();

        String str = this.heap.toString();
        str = str.replace("{", "");
        str = str.replace("}", "");
        str = str.replace(" ", "");
        str = str.replace("=", " --> ");

        String[] listStr = str.split(",");

        for(String s : listStr){
            heapStr.append(s).append("\n");
        }

        return heapStr.toString();
    }



}


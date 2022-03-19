package Models.States;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIList;
import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Statements.IStmt;
import Models.Values.IValue;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, IValue> symTable;
    MyIList<IValue> out;
    IStmt originalProgram;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, IValue> symtbl, MyIList<IValue> o, IStmt prg) throws MyException{
        this.exeStack = stk;
        this.symTable = symtbl;
        this.out = o;
        this.originalProgram = prg.deepCopy();
        this.exeStack.push(prg);
    }

    public String toString(){
        return this.exeStack.toString() + "\n" + this.symTable.toString() + "\n" + this.out.toString() + "\n";
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

    public MyIStack<IStmt> getStk() {
        return this.exeStack;
    }

    public MyIList<IValue> getOut() {
        return this.out;
    }

    public MyIDictionary<String, IValue> getSymTable() {
        return this.symTable;
    }


    public static <T> T deepClone(T object) throws MyException{
        try {
            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(byteArrayOutputStream);
            objectOutputStream.writeObject(object);
            ByteArrayInputStream bais = new ByteArrayInputStream(byteArrayOutputStream.toByteArray());
            ObjectInputStream objectInputStream = new ObjectInputStream(bais);
            return (T) objectInputStream.readObject();
        }
        catch (Exception e) {
            throw new MyException(e.getStackTrace().toString());
        }
    }
}


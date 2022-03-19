package Models.Statements;

import Models.ADTs.*;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.BufferedReader;

public class forkStmt implements IStmt{
    private IStmt stmt;

    public forkStmt(IStmt s){
        this.stmt = s;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> exeStk = state.getStk();
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIHeap heap= state.getHeap();
        MyIDictionary<StringValue, BufferedReader> fileTbl = state.getFileTable();
        MyIList<IValue> out = state.getOut();
        MyISemaphore sem = state.getSemaphore();

        // creating the clone for the symtbl
        MyIDictionary<String, IValue> symTblDeepClone = new MyDictionary<String, IValue>();

        for(String k : symTbl.getContent().keySet()){
            symTblDeepClone.put(k, symTbl.get(k).deepCopy());
        }

        PrgState newPrgState = new PrgState(new MyStack<IStmt>(), symTblDeepClone, out, fileTbl,heap,this.stmt, sem);
        return newPrgState;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        this.stmt.typecheck(typeEnv.clone());
        return typeEnv;

    }

    @Override
    public IStmt deepCopy() {
        return new forkStmt(this.stmt.deepCopy());
    }

    public String toString(){
        return "fork( " + this.stmt.toString() + " )";
    }
}

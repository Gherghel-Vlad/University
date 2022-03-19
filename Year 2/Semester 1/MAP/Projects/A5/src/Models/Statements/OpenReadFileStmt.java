package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.StringType;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.*;

public class OpenReadFileStmt implements IStmt{

    IExp exp;

    public OpenReadFileStmt(IExp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIDictionary<StringValue, BufferedReader> fileTbl = state.getFileTable();

        IValue val = this.exp.eval(symTbl, state.getHeap());
        if(val.getType().equals(new StringType())){
            StringValue valStr = (StringValue)val;
            if(!fileTbl.isDefined(valStr)){
                try{
                    BufferedReader br = new BufferedReader(new FileReader(valStr.getVal()));
                    fileTbl.put(valStr, br);
                }
                catch (FileNotFoundException e){
                    throw new MyException("OpenReadFile: File not found. " + e);
                }
            }
            else{
                throw new MyException("OpenReadFile: File already opened.");
            }
        }
        else{
            throw new MyException("OpenReadFile: The filename isn't of type StringType.");
        }

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new OpenReadFileStmt(this.exp.deepCopy());
    }

    public String toString(){
        return "openRFile(" + this.exp.toString() + ")";
    }
}

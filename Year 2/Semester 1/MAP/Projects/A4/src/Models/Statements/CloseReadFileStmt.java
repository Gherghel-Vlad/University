package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.StringType;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFileStmt implements IStmt{

    private IExp exp;

    public CloseReadFileStmt(IExp e){
        this.exp = e;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIDictionary<StringValue, BufferedReader> fileTbl = state.getFileTable();
        MyIDictionary<String, IValue> symTable = state.getSymTable();

        IValue val = this.exp.eval(symTable, state.getHeap());

        if(val.getType().equals(new StringType())){
            StringValue valStr = (StringValue) val;

            if(fileTbl.isDefined(valStr)){
                BufferedReader br = fileTbl.lookup(valStr);
                try {
                    br.close();
                    fileTbl.remove(valStr);
                }
                catch (IOException e){
                    throw new MyException("CloseReadFile: Error at closing the file " + valStr.getVal() + ".");
                }
            }
            else{
                throw new MyException("CloseReadFile: No file with name " + valStr.getVal() + " is open.");
            }

        }
        else{
            throw new MyException("CloseReadFile: The value is not of StringType.");
        }


        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new CloseReadFileStmt(this.exp.deepCopy());
    }

    public String toString(){
        return "closeRFile(" + this.exp.toString() + ")";
    }
}

package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.IntType;
import Models.Types.StringType;
import Models.Values.IValue;
import Models.Values.IntValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStmt{

    private IExp exp;
    private String var_name;

    public ReadFileStmt(IExp e, String var_name){

        this.exp = e;
        this.var_name = var_name;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIDictionary<StringValue, BufferedReader> fileTbl = state.getFileTable();

        if(symTbl.isDefined(this.var_name)){
            IValue val = symTbl.lookup(this.var_name);
            if(val.getType().equals(new IntType())){
                IValue expVal = exp.eval(symTbl);
                if(expVal.getType().equals(new StringType())){
                    StringValue expValStr = (StringValue) expVal;

                    if(fileTbl.isDefined(expValStr)){
                        BufferedReader br = fileTbl.lookup(expValStr);
                        try {
                            IntValue value;
                            String line = br.readLine();
                            if (line == null){
                                value = new IntValue( 0);
                            }
                            else{
                                value = new IntValue(Integer.parseInt(line));
                            }

                            symTbl.update(this.var_name, value);
                        }
                        catch (IOException e){
                            throw new MyException("ReadFile: Error at reading " + e);
                        }
                    }
                    else{
                        throw new MyException("ReadFile: There is no file opened with the name " + expValStr.getVal() + ".");
                    }

                }
                else{
                    throw new MyException("ReadFile: The expression did not return a StringValue.");
                }
            }
            else{
                throw new MyException("ReadFile: Variable " + this.var_name + " is not an int type.");
            }

        }
        else{
            throw new MyException("ReadFile: Variable " + this.var_name + " has not been declared.");
        }


        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new ReadFileStmt(this.exp.deepCopy(), this.var_name);
    }

    public String toString(){
        return "readFile(" + this.exp.toString() + ". " + this.var_name + ")";
    }
}

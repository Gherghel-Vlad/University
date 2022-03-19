package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.RefType;
import Models.Values.IValue;
import Models.Values.RefValue;

public class NewStmt implements IStmt{

    private String var_name;
    private IExp exp;

    public NewStmt(String var_name, IExp e){
        this.var_name = var_name;
        this.exp = e;
    }




    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIHeap heap = state.getHeap();

        if(symTbl.isDefined(this.var_name)){
            IValue val = symTbl.lookup(this.var_name);
            if(val.getType() instanceof RefType){
                IValue expVal = this.exp.eval(symTbl, state.getHeap());
                RefValue valRef = (RefValue) val;
                if(expVal.getType().equals(valRef.getLocationType())){
                    int pos = heap.createEntry(expVal);
                    symTbl.update(this.var_name, new RefValue(pos, expVal.getType()));
                }
                else{
                    throw new MyException("NewStmt: The variable " + this.var_name + " is not the same type as the result of the expression.");
                }

            }
            else{
                throw new MyException("NewStmt: The variable " + this.var_name + " is not of RefType.");
            }
        }
        else{
            throw new MyException("NewStmt: Variable " + this.var_name + " does not exist.");
        }




        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new NewStmt(this.var_name, this.exp.deepCopy());
    }

    public String toString(){
        return "new(" + this.var_name + ". " + this.exp.toString() + ")";
    }
}

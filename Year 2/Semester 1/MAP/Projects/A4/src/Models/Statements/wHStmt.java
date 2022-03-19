package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.RefType;
import Models.Values.IValue;
import Models.Values.RefValue;

public class wHStmt implements IStmt{
    private String var_name;
    private IExp exp;

    public wHStmt(String var_name, IExp exp){
        this.var_name = var_name;
        this.exp = exp;
    }



    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIHeap heap = state.getHeap();

        if(symTbl.isDefined(this.var_name)){
            IValue val = symTbl.get(this.var_name);

            if(val.getType() instanceof RefType){
                RefValue valRef = (RefValue) val;

                if(heap.isDefined(valRef.getAddress())){
                    IValue expVal = this.exp.eval(symTbl, heap);

                    if(expVal.getType().equals(valRef.getLocationType())){
                        heap.update(valRef.getAddress(), expVal);
                    }
                    else{

                        throw new MyException("wHStmt: The expression didn't return the right variable type.");
                    }

                }
                else{
                    throw new MyException("wHStmt: There is no address " + valRef.getAddress() +".");
                }

            }
            else{
                throw new MyException("wHStmt: Variable " + this.var_name + " is not a RefType.");
            }

        }
        else{
            throw new MyException("wHStmt: Variable " + this.var_name + " is not defined.");
        }




        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new wHStmt(this.var_name, this.exp.deepCopy());
    }

    public String toString(){
        return "wHStmt(" + this.var_name + ". " + this.exp.toString() + ")";
    }
}

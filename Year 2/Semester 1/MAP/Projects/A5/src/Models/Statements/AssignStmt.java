package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Values.IValue;

public class AssignStmt implements IStmt{
    String id;
    IExp exp;

    public AssignStmt(String id, IExp e){
        this.id = id;
        this.exp = e;
    }

    public String toString(){
        return this.id+"="+this.exp.toString();
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        MyIDictionary<String, IValue>  symTbl = state.getSymTable();

        if(symTbl.isDefined(this.id)){
            IValue val = exp.eval(symTbl, state.getHeap());
            IType typeId = (symTbl.lookup(this.id)).getType();
            if(val.getType().equals(typeId)){
                symTbl.update(this.id, val);
            }
            else{
                throw new MyException("Declared type of variable " + id + " and type of the assigned expression do not match.");
            }
        }
        else{
            throw new MyException("The used variable " + id + " was not declared before.");
        }
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new AssignStmt(this.id, this.exp.deepCopy());
    }
}

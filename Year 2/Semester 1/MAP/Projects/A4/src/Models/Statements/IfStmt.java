package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.BoolType;
import Models.Values.BoolValue;
import Models.Values.IValue;

public class IfStmt implements IStmt{
    private IExp exp;
    private IStmt thenS;
    private IStmt elseS;

    public IfStmt(IExp e, IStmt t, IStmt el){
        this.exp = e;
        this.thenS = t;
        this.elseS = el;
    }

    public String toString(){
        return  "(IF("+ exp.toString()+") THEN(" +thenS.toString()  +")ELSE("+elseS.toString()+"))";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyIStack<IStmt> stk = state.getStk();

        IValue val = exp.eval(symTbl, state.getHeap());
        if((val.getType()).equals(new BoolType())){
            BoolValue b1 = (BoolValue)val;
            boolean n;
            n=b1.getVal();
            if(n){
                stk.push(this.thenS);
            }
            else{
                stk.push(this.elseS);
            }
        }
        else
            throw new MyException("The condition is not a boolean.");
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new IfStmt(this.exp.deepCopy(), this.thenS.deepCopy(), this.elseS.deepCopy());
    }
}

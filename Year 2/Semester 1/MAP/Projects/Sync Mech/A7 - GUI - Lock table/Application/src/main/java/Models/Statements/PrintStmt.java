package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIList;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Values.IValue;

public class PrintStmt implements IStmt{
    IExp exp;

    public PrintStmt(IExp exp){
        this.exp = exp;
    }

    public String toString(){
        return "print(" + exp.toString() +")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIList<IValue> out = state.getOut();
        out.add(this.exp.eval(state.getSymTable(), state.getHeap()));
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        exp.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(this.exp.deepCopy());
    }
}

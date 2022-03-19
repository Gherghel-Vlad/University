package Models.Statements;

import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.States.PrgState;

public class CompStmt implements IStmt{
    IStmt first;
    IStmt snd;

    public CompStmt(IStmt first, IStmt snd){
        this.first = first;
        this.snd = snd;
    }

    public String toString(){
        return "(" + first.toString() + ";" +snd.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getStk();
        stk.push(snd);
        stk.push(first);
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new CompStmt(this.first.deepCopy(), this.snd.deepCopy());
    }
}

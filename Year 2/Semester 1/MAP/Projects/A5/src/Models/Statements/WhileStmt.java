package Models.Statements;

import Models.ADTs.MyIStack;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.BoolType;
import Models.Values.BoolValue;
import Models.Values.IValue;

public class WhileStmt implements IStmt {

    private IExp exp;
    private IStmt stmt;

    public WhileStmt(IExp exp, IStmt stmt){
        this.exp = exp;
        this.stmt = stmt;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        IValue val = this.exp.eval(state.getSymTable(), state.getHeap());

        MyIStack<IStmt> exeStack = state.getStk();

        if(val.getType().equals(new BoolType())){
            BoolValue valBool  = (BoolValue) val;

            if(valBool.getVal()){
                exeStack.push(new WhileStmt(this.exp.deepCopy(), this.stmt.deepCopy()));
                exeStack.push(this.stmt);
                return null;
            }
            else{
                return null;
            }
        }
        else{
            throw new MyException("WhileStmt: The expression does not return a bool value.");
        }

    }

    @Override
    public IStmt deepCopy() {
        return new WhileStmt(this.exp.deepCopy(), this.stmt.deepCopy());
    }

    public String toString(){
        return "while("+ this.exp.toString() +") " + this.stmt.toString();
    }
}

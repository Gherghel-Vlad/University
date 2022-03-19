package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;

    MyIDictionary<String, IType> typecheck(MyIDictionary<String,IType> typeEnv) throws MyException;

    IStmt deepCopy();
}

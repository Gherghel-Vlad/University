package Models.Statements;

import Models.Exceptions.MyException;
import Models.States.PrgState;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException;

    IStmt deepCopy();
}

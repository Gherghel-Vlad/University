package Repository;

import Models.Exceptions.MyException;
import Models.States.PrgState;

public interface IRepo {
    public PrgState getCrtPrg();
    public void addPrgState(PrgState state);
    void logPrgStateExec() throws MyException;
    void clearLogFile() throws MyException;
}

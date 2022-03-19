package Repository;

import Models.Exceptions.MyException;
import Models.States.PrgState;

import java.util.ArrayList;
import java.util.List;

public interface IRepo {
    public void addPrgState(PrgState state);
    void logPrgStateExec(PrgState prgState) throws MyException;
    void clearLogFile() throws MyException;
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> newPrgList);

}

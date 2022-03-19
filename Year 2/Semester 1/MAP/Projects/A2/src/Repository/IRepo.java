package Repository;

import Models.States.PrgState;

public interface IRepo {
    public PrgState getCrtPrg();
    public void addPrgState(PrgState state);
}

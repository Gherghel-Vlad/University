package Repository;

import Models.States.PrgState;

import java.util.ArrayList;

public class Repo implements IRepo{
    private ArrayList<PrgState> prgStateList;

    public Repo(){
        this.prgStateList = new ArrayList<PrgState>();
    }

    public void addPrgState(PrgState state){
        this.prgStateList.add(state);
    }

    @Override
    public PrgState getCrtPrg() {
        return this.prgStateList.get(0);
    }



}

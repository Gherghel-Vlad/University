package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyISemaphore;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class ReleaseStmt implements IStmt{

    private String var;


    public ReleaseStmt(String var){
        this.var = var;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyISemaphore sem = state.getSemaphore();

        if(symTbl.isDefined(this.var) && symTbl.get(this.var).getType().equals(new IntType())) {
            IntValue foundIndex = (IntValue) symTbl.get(this.var);


            if(sem.isDefined(foundIndex.getVal())){
                Pair<Integer, List<Integer>> value = sem.lookup(foundIndex.getVal());

                if(value.getValue().contains(state.getIdPrgState())){
                    value.getValue().remove((Integer) state.getIdPrgState());
                }
                else{
                    return null;
                }
            }
            else{
                throw new MyException("Acquire: no index in the sempahore with that value");
            }

        }
        else{
            throw new MyException("Release: var doesnt exist in the symtable or is not of int type");

        }



        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        if(!(typeEnv.get(this.var).equals(new IntType()))){

            throw new MyException("ReleaseStmt: typecheck failed - variable given isnt of int type");
        }
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new ReleaseStmt(this.var);
    }

    public String toString(){
        return "release(" + this.var + ")";
    }
}

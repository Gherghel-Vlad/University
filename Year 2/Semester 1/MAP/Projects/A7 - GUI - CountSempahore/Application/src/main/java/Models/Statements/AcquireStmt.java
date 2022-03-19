package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyISemaphore;
import Models.ADTs.MySemaphore;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class AcquireStmt implements IStmt{

    String var;


    public AcquireStmt(String id){
        this.var = id;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTbl = state.getSymTable();
        MyISemaphore sem = state.getSemaphore();

        if(symTbl.isDefined(this.var) && symTbl.get(this.var).getType().equals(new IntType())){
            IntValue foundIndex = (IntValue) symTbl.lookup(this.var);

            if(sem.isDefined(foundIndex.getVal())){
                Pair<Integer, List<Integer>> value = sem.lookup(foundIndex.getVal());

                int NL = value.getValue().size();

                if(value.getKey() > NL){
                    if(value.getValue().contains(state.getIdPrgState())){
                        return null;
                    }
                    else{
                        value.getValue().add(state.getIdPrgState());
                    }
                }
                else{
                    state.getStk().push(new AcquireStmt(this.var));
                }
            }
            else{
                throw new MyException("Acquire: no index in the sempahore with that value");
            }
        }
        else{
            throw new MyException("Acquire: var doesnt exist in symtable or is not of int type");
        }

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        if(!(typeEnv.get(this.var).equals(new IntType()))){

            throw new MyException("AcquireStmt: typecheck failed - variable given isnt of int type.");
        }

        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new AcquireStmt(this.var);
    }

    public String toString(){
        return "acquire(" + this.var + ")";
    }
}

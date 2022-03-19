package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyILockTable;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;

public class NewLockStmt implements IStmt{

    private String var;

    public NewLockStmt(String var){
        this.var = var;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyILockTable lockTbl = state.getLockTable();
        MyIDictionary<String, IValue> symTbl = state.getSymTable();

        int freeLocation = lockTbl.allocate(-1);

        if(symTbl.isDefined(this.var) && symTbl.get(this.var).getType().equals(new IntType())){
            symTbl.update(this.var, new IntValue(freeLocation));
        }
        else{
            throw new MyException("NewLockStmt: variable doesnt exist or isnt of int type");
        }

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        if(!typeEnv.lookup(this.var).equals(new IntType())){
            throw new MyException("NewLockStmt: failed typecheck");

        }


        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new NewLockStmt(this.var);
    }

    public String toString(){
        return "newLock(" +this.var + ")";
    }
}

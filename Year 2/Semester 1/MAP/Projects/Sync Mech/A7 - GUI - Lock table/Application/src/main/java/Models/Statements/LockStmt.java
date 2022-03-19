package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyILockTable;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;

public class LockStmt implements IStmt{

    private String var;

    public LockStmt(String var){
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {


        MyILockTable lockTbl = state.getLockTable();
        MyIDictionary<String, IValue> symTbl = state.getSymTable();

        if(symTbl.isDefined(this.var) && symTbl.get(this.var).getType().equals(new IntType())){
            IValue foundIndex = symTbl.lookup(this.var);

            if(lockTbl.isDefined(((IntValue) foundIndex ).getVal())){
                if(lockTbl.getLockTable().get(((IntValue) foundIndex ).getVal()) == -1){
                    lockTbl.update(((IntValue) foundIndex ).getVal(), state.getIdPrgState());
                }
                else{
                    state.getStk().push(new LockStmt(this.var));
                }
            }
            else{
                throw new MyException("LockStmt: the integer doesnt show any valid lock table entry");

            }
        }
        else{
            throw new MyException("LockStmt: variable doesnt exist or isnt of int type");
        }


        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        if(!typeEnv.lookup(this.var).equals(new IntType())){
            throw new MyException("LockStmt: failed typecheck");

        }
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new LockStmt(this.var);
    }

    public String toString(){
        return "lock(" + this.var + ")";
    }
}

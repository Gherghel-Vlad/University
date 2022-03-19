package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyISemaphore;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;

public class CreateSemaphoreStmt implements IStmt{
    String id;
    IExp exp;


    public CreateSemaphoreStmt(String id, IExp exp){
        this.id = id;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyISemaphore sem = state.getSemaphore();
        MyIDictionary<String, IValue> symTbl =state.getSymTable();

        IValue number1 = this.exp.eval(state.getSymTable(), state.getHeap());
        Integer freeLocation;

        if(number1.getType().equals(new IntType())) {
            freeLocation = sem.allocate(new Pair<Integer, List<Integer>>(((IntValue)number1).getVal(), new ArrayList<>()));

            if(symTbl.isDefined(this.id) && symTbl.get(this.id).getType().equals(new IntType())){
                symTbl.update(this.id, new IntValue(freeLocation));
            }
            else{
                throw new MyException("CreateSemaphoreStmt: the var doesnt exist in symtable or si not of int type.");
            }
        }
        else{
            throw new MyException("CreateSemaphoreStmt: exp doesnt return an int.");
        }
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        if(!(typeEnv.get(this.id).equals(new IntType()) && this.exp.typecheck(typeEnv).equals(new IntType()))){

            throw new MyException("CreateSemaphoreStmt: typecheck failed - variable given isnt of int type or the expression doesnt return an int type.");
        }


        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new CreateSemaphoreStmt(this.id, this.exp.deepCopy());
    }

    public String toString(){
        return "createSemaphore(" + this.id + ", " +this.exp.toString()+ ")";
    }
}

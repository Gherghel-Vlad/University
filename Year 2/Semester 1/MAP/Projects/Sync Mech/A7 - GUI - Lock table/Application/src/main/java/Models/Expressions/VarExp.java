package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Values.IValue;

public class VarExp implements IExp{
    String id;

    public VarExp(String id){
        this.id = id;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl, MyIHeap heap) throws MyException {
        IValue v= tbl.lookup(this.id);
        if (v==null){
            throw new MyException("Variable " + this.id + " not defined.");
        }
        return v;
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        return typeEnv.lookup(id);
    }

    @Override
    public IExp deepCopy() {
        return new VarExp(this.id);
    }

    public String toString(){
        return this.id;
    }


}

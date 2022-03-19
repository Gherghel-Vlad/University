package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Values.IValue;

public class VarExp implements IExp{
    String id;

    public VarExp(String id){
        this.id = id;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl) throws MyException {
        IValue v= tbl.lookup(this.id);
        if (v==null){
            throw new MyException("Variable " + this.id + " not defined.");
        }
        return v;
    }

    @Override
    public IExp deepCopy() {
        return new VarExp(this.id);
    }

    public String toString(){
        return this.id;
    }


}

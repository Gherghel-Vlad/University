package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Values.IValue;

public class ValueExp implements IExp {
    private IValue e;

    public ValueExp(IValue val){
        this.e = val;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl, MyIHeap heap) throws MyException {
        return this.e;
    }

    @Override
    public IExp deepCopy() {
        return new ValueExp(this.e.deepCopy());
    }

    public String toString(){
        return this.e.toString();
    }

}

package Models.Values;


import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Types.IntType;

public class IntValue implements IValue {

    private int val;

    public IntValue(int v){
        this.val = v;
    }

    public int getVal(){
        return this.val;
    }

    public String toString() {
        return Integer.toString(this.val);
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public IValue deepCopy() {
        return new IntValue(this.val);
    }

    public boolean equals(Object another) {
        if(another instanceof IntValue){
            IntValue nr = (IntValue)another;
            return nr.getVal() == this.getVal();
        }
        else{
            return false;
        }

    }
}

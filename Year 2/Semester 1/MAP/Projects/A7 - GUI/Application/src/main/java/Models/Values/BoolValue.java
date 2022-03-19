package Models.Values;

import Models.Types.BoolType;
import Models.Types.IType;

public class BoolValue implements IValue{
    private boolean val;

    public BoolValue(boolean v) {
        this.val = v;
    }

    public boolean getVal(){
        return this.val;
    }

    public String toString(){
        return Boolean.toString(this.val);
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public IValue deepCopy() {
        return new BoolValue(this.val);
    }

    public boolean equals(Object another) {
        if(another instanceof BoolValue){
            BoolValue boolValue = (BoolValue)another;
            return boolValue.getVal() == this.getVal();
        }
        else{
            return false;
        }

    }
}

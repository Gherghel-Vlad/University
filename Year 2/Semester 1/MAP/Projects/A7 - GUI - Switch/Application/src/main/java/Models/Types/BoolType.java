package Models.Types;

import Models.Values.BoolValue;
import Models.Values.IValue;

public class BoolType implements IType{

    public boolean equals(Object another){
        if(another instanceof BoolType){
            return true;
        }
        else {
            return false;
        }
    }

    public String toString(){
        return "bool";
    }

    @Override
    public IValue defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public IType deepCopy() {
        return new BoolType();
    }
}

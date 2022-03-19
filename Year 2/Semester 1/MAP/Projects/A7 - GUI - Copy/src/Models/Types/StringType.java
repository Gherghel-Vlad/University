package Models.Types;

import Models.Values.IValue;
import Models.Values.StringValue;

public class StringType implements IType{


    public StringType(){}

    public boolean equals(Object another){
        if(another instanceof StringType){
            return true;
        }
        else{
            return false;
        }
    }

    @Override
    public IValue defaultValue() {
        return new StringValue("nullString");
    }

    @Override
    public IType deepCopy() {
        return new StringType();
    }

    public String toString(){
        return "string";
    }
}

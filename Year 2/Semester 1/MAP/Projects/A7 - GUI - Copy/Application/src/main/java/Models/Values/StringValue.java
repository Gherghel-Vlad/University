package Models.Values;

import Models.Types.IType;
import Models.Types.StringType;

public class StringValue implements IValue{
    private String stringValue;

    public StringValue(String value){
        this.stringValue = value;
    }

    public String getVal(){
        return this.stringValue;
    }

    public String toString(){
        return this.stringValue;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue deepCopy() {
        return new StringValue(this.stringValue);
    }

    public boolean equals(Object another) {
        if(another instanceof StringValue){
            StringValue stringValue = (StringValue)another;
            return stringValue.getVal().equals(this.getVal());
        }
        else{
            return false;
        }

    }
}

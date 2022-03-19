package Models.Values;

import Models.Types.IType;
import Models.Types.RefType;

public class RefValue implements IValue{
    private int address;
    private IType locationType;

    public RefValue(int adr, IType type){
        this.address = adr;
        this.locationType = type;
    }

    public int getAddress(){
        return address;
    }

    public IType getLocationType(){
        return this.locationType;
    }

    @Override
    public IType getType() {
        return new RefType(this.locationType);
    }

    @Override
    public IValue deepCopy() {
        return new RefValue(this.address, this.locationType.deepCopy());
    }

    public String toString(){
        return  this.address + ". " + this.locationType.toString();
    }
}

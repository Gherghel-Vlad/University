package Models.Types;

import Models.Values.IValue;

public interface IType {
    public IValue defaultValue();

    IType deepCopy();
}

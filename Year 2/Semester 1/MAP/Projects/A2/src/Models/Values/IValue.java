package Models.Values;

import Models.Types.IType;

public interface IValue {
    public IType getType();

    IValue deepCopy();
}

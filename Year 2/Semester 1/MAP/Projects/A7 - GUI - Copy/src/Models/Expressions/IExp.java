package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Values.IValue;


public interface IExp {
    IValue eval(MyIDictionary<String, IValue> tbl, MyIHeap hp) throws MyException;

    IType typecheck(MyIDictionary<String,IType> typeEnv) throws MyException;

    public IExp deepCopy();
}
